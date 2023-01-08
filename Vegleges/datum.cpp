#include <iomanip>
#include "datum.h"
#include "memtrace.h"

Datum::Datum(int honap, int nap, int ora, int perc)
    : honap(honap), nap(nap), ora(ora), perc(perc)
{
    if (!valid(honap, nap, ora, perc))
    {
        throw std::runtime_error("Rossz datummal akar inicializalni!");
    }
}

bool Datum::valid(int honap, int nap, int ora, int perc)
{
    return honap >= 1 && honap <= 12 && nap >= 1 && nap <= 30 && ora >= 0 && ora <= 23 && perc >= 0 && perc <= 59;
}

void Datum::set(int honap, int nap, int ora, int perc)
{
    if (!valid(honap, nap, ora, perc))
    {
        throw std::runtime_error("Rossz datumot adott meg");
    }
    this->honap = honap;
    this->nap = nap;
    this->ora = ora;
    this->perc = perc;
}

int Datum::osszehasonlit(const Datum &b) const
{
    unsigned int tempA = this->convertToMin();
    unsigned int tempB = b.convertToMin();
    int val = 0;
    if (tempA < tempB)
    {
        val = -1;
    }
    else if (tempA > tempB)
    {
        val = 1;
    }
    else
    {
        val = 0;
    }
    return val;
}

bool Datum::operator<(const Datum &b) const
{
    return this->osszehasonlit(b) == -1;
}

bool Datum::operator>(const Datum &b) const
{
    return this->osszehasonlit(b) == 1;
}

bool Datum::operator==(const Datum &b) const
{
    return this->osszehasonlit(b) == 0;
}

void Datum::beolvas(std::istream &is)
{
    int honap, nap, ora, perc;
    is >> honap;
    is >> nap;
    is >> ora;
    is >> perc;
    this->set(honap, nap, ora, perc);
}

void Datum::kiir(std::ostream &os) const
{
    os << std::setfill('0') << std::setw(2) << honap << '.';
    os << std::setw(2) << nap << ", ";
    os << std::setw(2) << ora << ':';
    os << std::setw(2) << perc;
}

void Datum::mentes(std::ostream &os) const
{
    os << honap << ' ';
    os << nap << ' ';
    os << ora << ' ';
    os << perc << ' ';
}

unsigned int Datum::convertToMin() const
{
    unsigned int min = perc;
    min += ora * 60;
    min += nap * 24 * 60;
    min += honap * 30 * 24 * 60;
    return min;
}

std::ostream &operator<<(std::ostream &os, const Datum &d)
{
    d.kiir(os);
    return os;
}

std::istream &operator>>(std::istream &is, Datum &d)
{
    d.beolvas(is);
    return is;
}