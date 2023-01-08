#include "vonat.h"
#include "memtrace.h"

Vonat::Vonat(const MyString &szam, const Datum &indulas, const Datum &erkezes, int elsoAr, int masodAr, int elso, int masodik)
    : szam(szam), indulas(indulas), erkezes(erkezes), elsoOsztAr(elsoAr), masodOsztAr(masodAr)
{
    for (int i = 0; i < elso; ++i)
    {
        elsoOsztKocsik.push_back(new Kocsi(1));
    }
    for (int i = 0; i < masodik; ++i)
    {
        masodOsztKsocsik.push_back(new Kocsi(2));
    }
}

MyString Vonat::getSzam() const
{
    return szam;
}

Vector<Kocsi *> &Vonat::getElsoOsztKocsik()
{
    return elsoOsztKocsik;
}

Vector<Kocsi *> &Vonat::getMasodOsztKocsik()
{
    return masodOsztKsocsik;
}

Datum Vonat::getIndulas() const
{
    return indulas;
}

int Vonat::getElsoOsztAr() const
{
    return elsoOsztAr;
}
int Vonat::getMasodOsztAr() const
{
    return masodOsztAr;
}

void Vonat::mentDatumok(std::ostream &os) const
{
    indulas.mentes(os);
    erkezes.mentes(os);
    os << '\n';
}

void Vonat::valtoztatIndulas(const Datum &ind)
{
    indulas = ind;
}

void Vonat::valtoztatErkezes(const Datum &erk)
{
    erkezes = erk;
}

// void Vonat::kocsiHozzaad(Kocsi *kocsi)
// {
//     if (kocsi->tipus() == 1)
//     {
//         elsoOsztKocsik.push_back(kocsi);
//     }
//     else
//     {
//         masodOsztKsocsik.push_back(kocsi);
//     }
// }

void Vonat::kiir(std::ostream &os) const
{
    os << szam << "\n\t"
       << "Indulas: " << indulas << "\n\t"
       << "Ekrezes: " << erkezes << "\n\t";
    os << elsoOsztKocsik.size() + masodOsztKsocsik.size() << " db kocsi"
       << "\n\t";
    os << "Elso osztaly: " << elsoOsztAr << "Ft\n\t";
    os << "Masod osztaly: " << masodOsztAr << "Ft\n";
}

Vonat::~Vonat()
{
    for (Vector<Kocsi *>::iterator eleje = elsoOsztKocsik.begin(); eleje != elsoOsztKocsik.end(); ++eleje)
    {
        delete *eleje;
    }
    for (Vector<Kocsi *>::iterator eleje = masodOsztKsocsik.begin(); eleje != masodOsztKsocsik.end(); ++eleje)
    {
        delete *eleje;
    }
}

void Vonat::vasarolElsoOszt(size_t &kocsi, size_t &hely)
{
    bool talalat = true;
    for (Vector<Kocsi *>::iterator eleje = elsoOsztKocsik.begin(); eleje != elsoOsztKocsik.end() && talalat; ++eleje)
    {
        int temp = (*eleje)->foglal();
        if (temp != -1)
        {
            kocsi = eleje.index() + 1;
            hely = temp + 1;
            talalat = false;
        }
    }
}

void Vonat::vasarolMasodOszt(size_t &kocsi, size_t &hely)
{
    bool talalat = true;
    for (Vector<Kocsi *>::iterator eleje = masodOsztKsocsik.begin(); eleje != masodOsztKsocsik.end() && talalat; ++eleje)
    {
        int temp = (*eleje)->foglal();
        if (temp != -1)
        {
            kocsi = eleje.index() + 1 + elsoOsztKocsik.size();
            hely = temp + 1;
            talalat = false;
        }
    }
}