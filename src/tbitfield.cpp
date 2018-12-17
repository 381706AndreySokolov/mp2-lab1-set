// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>

TBitField::TBitField(int len)
{
	if (len <= 0)
		throw "Incorrect length";
	bitLen = len;

	memLen = (bitLen / (8 * sizeof(TELEM))) + 1;
	pMem = new TELEM[memLen];
	int n = bitLen / (sizeof(TELEM) * 8);
	for (int i = 0; i < memLen; i++)
		pMem[i] = 0;
}
// ---------------------------------------------------------------------------
TBitField::TBitField(const TBitField &bf)
{
	bitLen = bf.bitLen;
	memLen = bf.memLen;
	pMem = new TELEM[memLen];
	for (int i = 0; i < memLen; i++)
		pMem[i] = bf.pMem[i];
}
// ---------------------------------------------------------------------------
TBitField::~TBitField()
{
	delete[]pMem;
	pMem = NULL;
}
// ---------------------------------------------------------------------------
int TBitField::GetMemIndex(const int n) const
{
	if (n < 0 || n >= bitLen)
		throw "Incorrect bit";
	return (n / (sizeof(TELEM) * 8));
}
// ---------------------------------------------------------------------------
TELEM TBitField::GetMemMask(const int n) const
{
	if ((n < 0) || (n >= bitLen))
		throw "Incorrect bit";
	return 1 << ((n - 1) % (8 * sizeof(TELEM)));
}
// ---------------------------------------------------------------------------
int TBitField::GetLength(void) const
{
	return bitLen;
}
// ---------------------------------------------------------------------------
void TBitField::SetBit(const int n)
{
	if ((n < 0) || (n >= bitLen))
		throw "Incorrect bit";
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}
// ---------------------------------------------------------------------------
void TBitField::ClrBit(const int n)
{
	if ((n < 0) || (n >= bitLen))
		throw "Incorrect bit";
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}
// ---------------------------------------------------------------------------
int TBitField::GetBit(const int n) const
{
	if ((n < 0) || (n >= bitLen))
		throw "Incorrect bit";
	return (pMem[GetMemIndex(n)] & GetMemMask(n));
}
// ---------------------------------------------------------------------------
TBitField& TBitField::operator=(const TBitField &bf)
{
	if (this != &bf)
	{
		delete[]pMem;
		bitLen = bf.bitLen;
		memLen = bf.memLen;
		pMem = new TELEM[memLen];
		for (int i = 0; i < memLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}
// ---------------------------------------------------------------------------
int TBitField::operator==(const TBitField &bf) const
{
	int res = 1;
	if (bitLen != bf.bitLen)
		res = 0;
	else
		for (int i = 0; i < memLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				res = 0;
				break;
			}
	return res;
}
// ---------------------------------------------------------------------------
int TBitField::operator!=(const TBitField &bf) const
{
	int res = 0;
	if (bitLen != bf.bitLen)
		res = 1;
	else
		for (int i = 0; i < memLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				res = 1;
				break;
			}
	return res;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator|(const TBitField &bf)
{
	int i, len = bitLen;
	if (bf.bitLen > len)
		len = bf.bitLen;
	TBitField temp(len);
	for (i = 0; i < memLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.memLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator&(const TBitField &bf)
{
	int i, len = bitLen;
	if (bf.bitLen > len)
		len = bf.bitLen;
	TBitField temp(len);
	for (i = 0; i < memLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.memLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator~(void)
{
	TBitField temp = *this;
	for (int i = 0; i < temp.bitLen; i++)
	{
		if (temp.GetBit(i))
			temp.ClrBit(i);
		else
			temp.SetBit(i);
	}
	return temp;
}
// ---------------------------------------------------------------------------
istream &operator>>(istream &istr, TBitField &bf)
{
	string temp;
	istr >> temp;
	if (temp.size() != bf.GetLength())
		throw "Incorrect length";
	for (int i = 0; i < bf.bitLen; i++)
	{
		if (temp[i] == '0')
			bf.ClrBit(i);
		else if (temp[i] == '1')
			bf.SetBit(i);
		else
			throw "Incorrect input";
	}
	return istr;
}
// ---------------------------------------------------------------------------
ostream &operator<<(ostream &ostr, const TBitField &bf)
{
	for (int i = 0; i < bf.bitLen; i++)
	{
		if (bf.GetBit(i))
			ostr << 1;
		else
			ostr << 0;
	}
	return ostr;
}