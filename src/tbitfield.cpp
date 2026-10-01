// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cstring>


// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static size_t SIZE = sizeof(TELEM) * 8;

TBitField::TBitField(int len) {
    BitLen = len;
    MemLen = (len - 1) / SIZE + 1;
    pMem = new TELEM[MemLen];
    std::memset(pMem, 0, sizeof(TELEM) * MemLen);
}
// конструктор копирования
TBitField::TBitField(const TBitField &bf) {
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    std::memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
}

TBitField::~TBitField() {
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n > BitLen)
        return FAKE_INT;
    return n / SIZE;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n > BitLen)
        return FAKE_INT;
    return bool(pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции
// присваивание 
TBitField& TBitField::operator=(const TBitField &bf) {
    if (this == &bf)
        return *this;

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    delete[] pMem;
    
    pMem = new TELEM[MemLen];
    std::memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
    
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (bf.BitLen != BitLen)
        return 0;
    
    return memcmp(pMem, bf.pMem, MemLen * sizeof(TELEM)) != 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (bf.MemLen != MemLen)
        return 1;

    return memcmp(pMem, bf.pMem, MemLen * sizeof(TELEM)) == 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    size_t len = BitLen;
    if (bf.BitLen > BitLen)
        len = bf.BitLen;
    
    TBitField tmp(len);

    for (int i = 0; i < MemLen; ++i)
        tmp.pMem[i] = pMem[i];

    for (int i = 0; i < bf.MemLen; ++i) {
        tmp.pMem[i] |= bf.pMem[i];
    }

    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    size_t len = BitLen;
    if (bf.BitLen > BitLen)
        len = bf.BitLen;
    
    TBitField tmp(len);

    for (int i = 0; i < MemLen; ++i)
        tmp.pMem[i] = pMem[i];

    for (int i = 0; i < bf.MemLen; ++i) {
        tmp.pMem[i] &= bf.pMem[i];
    }

    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);

    for (int i = 0; i < MemLen; ++i) {
        tmp.pMem[i] = ~pMem[i];
    }
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.MemLen; ++i) {
        istr >> bf.pMem[i];
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; ++i)
        ostr << bf.GetBit(i);
    return ostr;
}
