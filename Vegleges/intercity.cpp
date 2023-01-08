#include "intercity.h"
#include "memtrace.h"

Intercity::Intercity(const MyString &szam, const Datum &indulas, const Datum &erkezes, const MyString &kezdo, const MyString &veg, int elsoAr, int masodAr, int elso, int masodik)
    : Vonat(szam, indulas, erkezes, elsoAr, masodAr, elso, masodik), kezdoAllomas(kezdo), vegallomas(veg) {}

Vonat *Intercity::betoltVonat(std::ifstream &is)
{
    MyString szam, kezdo, veg;
    Datum indulas, erkezes;
    int elso, masod, elsoAr, masodAr;
    is >> szam;
    is >> elso >> masod >> elsoAr >> masodAr;
    is >> indulas >> erkezes;
    is >> kezdo >> veg;
    Vonat *vonat = new Intercity(szam, indulas, erkezes, kezdo, veg, elsoAr, masodAr, elso, masod);
    return vonat;
}

Vonat *Intercity::hozzaadVonat(std::istream &is)
{
    MyString szam, kezdo, veg;
    int elso, masod, elsoAr, masodAr;
    Datum indulas, erkezes;

    std::cout << "Adja meg a vonat azonosito szamat: ";
    is >> szam;
    std::cout << "Elso osztalyu kocsik szama: ";
    is >> elso;

    std::cout << "Masod osztalyu kocsik szama: ";
    is >> masod;

    std::cout << "Elso osztalyu jegy ara: ";
    is >> elsoAr;

    std::cout << "Masod osztalyu jegy ara: ";
    is >> masodAr;

    std::cout << "Indulas idopontja (honap, nap, ora, perc): ";
    is >> indulas;

    std::cout << "Erkezes idopontja (honap, nap, ora, perc): ";
    is >> erkezes;

    std::cout << "A vonat indulasi allomasa: ";
    is >> kezdo;

    std::cout << "A vonat erkezesi allomasa: ";
    is >> veg;


    Vonat *vonat = new Intercity(szam, indulas, erkezes, kezdo, veg, elsoAr, masodAr, elso, masod);
    return vonat;
}

void Intercity::kiirVonat(std::ostream &os) const
{
    os << "Intercity - ";
    Vonat::kiir(os);
    os << '\t' << kezdoAllomas << " -> " << vegallomas << "\n";
}

bool Intercity::megfelel(const MyString &kezdo, const MyString &veg) const
{
    return kezdo == kezdoAllomas && veg == vegallomas;
}

void Intercity::mentAllomasok(std::ostream &os) const
{
    os << kezdoAllomas << '\n';
    os << vegallomas << '\n';
}

void Intercity::mentTipus(std::ostream &os) const
{
    os << "1 ";
}

bool Intercity::athalad(const MyString &allomas) const
{
    return allomas == kezdoAllomas || allomas == vegallomas;
}

MyString Intercity::tipus() const
{
    return MyString("Intercity");
}

void Intercity::valtoztatAllomasok(std::istream &is)
{
    std::cout << "Adja meg a kezdo allomast: ";
    is >> kezdoAllomas;

    std::cout << "Adja meg a veg allomast: ";
    is >> vegallomas;

    std::cout << "Az utvonal sikeresen meg lett valtoztatva!" << std::endl;
}