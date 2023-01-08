#include "kocsi.h"
#include "memtrace.h"

Kocsi::Kocsi(int tipus) : osztaly(tipus)
{
    for (int i = 0; i < 60; ++i)
    {
        hely[i] = false;
    }
}

int Kocsi::tipus() const
{
    return osztaly;
}

void Kocsi::kiir(std::ostream &os) const
{
    switch (osztaly)
    {
    case 1:
        os << "Elso osztaly";
        break;

    case 2:
        os << "Masod osztaly";
    }
}

void Kocsi::foglalBetoltesnel(size_t sorszam)
{
    hely[sorszam] = true;
}

int Kocsi::foglal()
{
    int ures = -1;
    for (int i = 0; i < 60 && ures == -1; ++i)
    {
        if (hely[i] == false)
        {
            hely[i] = true;
            ures = i;
        }
    }

    return ures;
}

void Kocsi::felszabadit(size_t sorszam)
{
    hely[sorszam] = false;
}
