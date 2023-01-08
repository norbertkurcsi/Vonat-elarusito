#include "helykozi.h"
#include "memtrace.h"

Helykozi::Helykozi(const MyString &szam, const Datum &indulas, const Datum &erkezes, int elsoAr, int masodAr, int elso, int masodik)
    : Vonat(szam, indulas, erkezes, elsoAr, masodAr, elso, masodik) {}

void Helykozi::kiirVonat(std::ostream &os) const
{
    os << "Helykozi - ";
    Vonat::kiir(os);
    os << '\t';
    for (size_t i = 0; i < allomasok.size() - 1; ++i)
    {
        os << allomasok[i] << " -> ";
    }
    os << allomasok[allomasok.size() - 1] << '\n';
}

void Helykozi::pushAllomas(const MyString &all)
{
    allomasok.push_back(all);
}

Vonat *Helykozi::betoltVonat(std::ifstream &is)
{
    MyString szam;
    int elso, masod, megallokSzama, elsoAr, masodAr;
    Datum indulas, erkezes;
    is >> szam;
    is >> elso >> masod >> elsoAr >> masodAr;
    is >> indulas >> erkezes;
    is >> megallokSzama;
    Helykozi *vonat = new Helykozi(szam, indulas, erkezes, elsoAr, masodAr, elso, masod);
    for (int i = 0; i < megallokSzama; ++i)
    {
        MyString megallo;
        is >> megallo;
        vonat->pushAllomas(megallo);
    }
    return vonat;
}

Vonat *Helykozi::hozzaadVonat(std::istream &is)
{
    MyString szam;
    int elso, masod, elsoAr, masodAr, allomasokSzama;
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

    std::cout << "Adja meg az allomasok szamat(minimum 3): ";
    is >> allomasokSzama;
    if (allomasokSzama < 3)
    {
        throw std::runtime_error("A vonatnak min 3 megalloja kel legyen!");
    }

    Helykozi *vonat = new Helykozi(szam, indulas, erkezes, elsoAr, masodAr, elso, masod);

    for (int i = 0; i < allomasokSzama; ++i)
    {
        MyString megallo;
        is >> megallo;
        vonat->pushAllomas(megallo);
    }



    return vonat;
}

void Vonat::valtoztatElsoOsztAr(int ujAr)
{
    elsoOsztAr = ujAr;
}
void Vonat::valtoztatMasodOsztAr(int ujAr)
{
    masodOsztAr = ujAr;
}

bool Helykozi::megfelel(const MyString &kezdo, const MyString &veg) const
{
    Vector<MyString>::iterator iter = allomasok.begin();
    bool megfelel = false;
    while (iter != allomasok.end())
    {
        if (*iter == kezdo)
        {
            while (iter != allomasok.end())
            {
                if (*iter == veg)
                {
                    megfelel = true;
                }
                ++iter;
            }
        }
        ++iter;
    }
    return megfelel;
}

void Helykozi::mentAllomasok(std::ostream &os) const
{
    os << allomasok.size() << '\n';
    for (Vector<MyString>::iterator iter = allomasok.begin(); iter != allomasok.end(); ++iter)
    {
        os << *iter << '\n';
    }
}

void Helykozi::mentTipus(std::ostream &os) const
{
    os << "0 ";
}

bool Helykozi::athalad(const MyString &all) const
{
    bool athalad = false;
    for (Vector<MyString>::iterator iter = allomasok.begin(); iter != allomasok.end(); ++iter)
    {
        if (*iter == all)
        {
            athalad = true;
        }
    }
    return athalad;
}

MyString Helykozi::tipus() const
{
    return MyString("Helykozi");
}

void Helykozi::valtoztatAllomasok(std::istream &is)
{
    allomasok.erase();
    int db;
    std::cout << "Adja meg hany megalloja lesz a vonatnak: ";
    is >> db;
    if (db < 3)
    {
        throw std::runtime_error("Helykozi vonatnak minimum 3 megalloja kell legyen!");
    }
    std::cout << "Adja meg a " << db << " darab allomast: ";
    for (int i = 0; i < db; ++i)
    {
        MyString temp;
        is >> temp;
        allomasok.push_back(temp);
    }
    std::cout << "Az utvonal sikeresen meg lett valtoztatva!" << std::endl;
}