// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cmath>

TBitField::TBitField(int len)
{
	if (len < 0)
		throw "Negative_length";

	BitLen = len;
	if (BitLen % (sizeof(TELEM) * 8) == 0)
	{
		MemLen = BitLen / (sizeof(TELEM) * 8);
		pMem = new TELEM[MemLen];
	}
	else
	{
		MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
	/*BitLen = len;
	MemLen = (len + 31) >> 5; 
	TELEM* pMem = new TELEM [MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}*/
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	pMem = NULL;
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw "Wrong_index";
	int temp = GetMemIndex(n); 
	pMem[temp] = pMem[temp] | GetMemMask(n); 
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
		throw "Wrong_index";
	int temp = GetMemIndex(n); 
	pMem[temp] = pMem[temp] & ~GetMemMask(n); 
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if((n < 0) || (n > BitLen))
		throw "Wrong_index";
	int temp = GetMemIndex(n);
	TELEM value = pMem[temp] & GetMemMask(n);
	if (value == 0) 
		return 0;
	else 
		return 1;
	/*int temp = GetMemIndex(n);
	return (pMem[temp] & GetMemMask(n)) >> (n % 32);*/
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (*this == bf)
		return *this;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	TELEM MemMask = 0xffffffff;
	if (BitLen != bf.BitLen)
		return 0;
	else
		for (int i = 0; i < MemLen - 1; i++)
			if ((pMem[i] & MemMask) != (bf.pMem[i] & MemMask))
			{
				return 0;
			}
	for (int i = MemLen - 1; i < MemLen; i++)
		if (GetBit(i) != bf.GetBit(i))
		{
			return 0;
		}
	return 1;
	/*for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return 0;
		return 1;
	}*/
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	for (int i = 0; i < MemLen; i++)
	{
		int res = 0;
		if (BitLen != bf.BitLen)
			res = 1;
		else
			for (int i = 0; i < MemLen; i++)
				if (pMem[i] != bf.pMem[i])
				{
					res = 1; break;
				}
		return res;
		/*if (pMem[i] != bf.pMem[i])
		{
			return 1;
		}
		return 0;*/
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len;
	if (BitLen < bf.BitLen)
		len = bf.BitLen;
	else 
		len = BitLen;

	TBitField temp(len);

	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] = temp.pMem[i] | bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len;
	if (BitLen < bf.BitLen)
		len = bf.BitLen;
	else 
		len = BitLen;

	TBitField temp(len);

	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] = temp.pMem[i] & bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (int i = 0; i < MemLen; i++) 
		temp.pMem[i] = ~pMem[i];
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0; char ch;
	do
	{
		istr >> ch;
	} while (ch != ' ');
	while (1) 
	{
		istr >> ch;
		if (ch == '0') 
			bf.ClrBit(i++);
		else
			if (ch == '1') 
				bf.SetBit(i++);
		else 
			break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{

	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i)) 
			ostr << '1';
		else 
			ostr << '0';
	return ostr;
}
