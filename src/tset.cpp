// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : bitField(mp)
{
	maxPower = mp;
}
// ---------------------------------------------------------------------------
TSet::TSet(const TSet &s) : bitField(s.bitField)
{
	maxPower = s.maxPower;
}
// ---------------------------------------------------------------------------
TSet::TSet(const TBitField &bf) : bitField(bf)
{
	maxPower = bitField.GetLength();
}
// ---------------------------------------------------------------------------
TSet::operator TBitField()
{
	return bitField;
}
// ---------------------------------------------------------------------------
int TSet::GetMaxPower(void) const
{
	return maxPower;
}
// ---------------------------------------------------------------------------
int TSet::IsMember(const int Elem) const
{
	if (Elem < 0 || Elem >= maxPower)
		throw "Incorrect element";
	return bitField.GetBit(Elem);
}
// ---------------------------------------------------------------------------
void TSet::InsElem(const int Elem)
{
	if (Elem < 0 || Elem >= maxPower)
		throw "Incorrect element";
	bitField.SetBit(Elem);
}
// ---------------------------------------------------------------------------
void TSet::DelElem(const int Elem)
{
	if (Elem < 0 || Elem >= maxPower)
		throw "Incorrect element";
	bitField.ClrBit(Elem);
}
// ---------------------------------------------------------------------------
TSet& TSet::operator=(const TSet &s)
{
	maxPower = s.maxPower;
	bitField = s.bitField;
	return *this;
}
// ---------------------------------------------------------------------------
int TSet::operator==(const TSet &s) const
{
	if (maxPower != s.maxPower)
		return 0;
	else
		if (bitField != s.bitField)
			return 0;
	return 1;
}
// ---------------------------------------------------------------------------
int TSet::operator!=(const TSet &s) const
{
	if (maxPower != s.maxPower)
		return 1;
	else
		if (bitField != s.bitField)
			return 1;
	return 0;
}
// ---------------------------------------------------------------------------
TSet TSet::operator+(const TSet &s)
{
	int len = maxPower;
	if (s.maxPower > maxPower)
		len = s.maxPower;
	TSet temp(len);
	temp.bitField = bitField | s.bitField;
	return temp;
}
// ---------------------------------------------------------------------------
TSet TSet::operator+(const int Elem)
{
	if (Elem < 0 || Elem >= maxPower)
		throw "Incorrect element";
	bitField.SetBit(Elem);
	return *this;
}
// ---------------------------------------------------------------------------
TSet TSet::operator-(const int Elem)
{
	if (Elem < 0 || Elem >= maxPower)
		throw "Incorrect element";
	bitField.ClrBit(Elem);
	return *this;
}
// ---------------------------------------------------------------------------
TSet TSet::operator*(const TSet &s)
{
	int len = maxPower;
	if (s.maxPower > maxPower)
		len = s.maxPower;
	TSet temp(len);
	temp.bitField = bitField & s.bitField;
	return temp;
}
// ---------------------------------------------------------------------------
TSet TSet::operator~(void)
{
	TSet temp = *this;
	temp.bitField = ~temp.bitField;
	return temp;
}
// ---------------------------------------------------------------------------
istream &operator>>(istream &istr, TSet &s)
{
	int i;
	cin >> i;
	for (; ((i > -1) && (i < s.maxPower)); cin >> i)
		s.bitField.SetBit(i);
	return istr;
}
// ---------------------------------------------------------------------------
ostream& operator<<(ostream &ostr, const TSet &s)
{
	ostr << s.bitField << ' ';
	return ostr;
}


