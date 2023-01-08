#include <cstring>
#include <stdlib.h>

#include "menu.h"
#include "memtrace.h"

bool Menu::megfelelNev(const MyString &nev) const
{
    bool megfelel = true;
    for (size_t i = 0; i < adatbazisok.size(); ++i)
    {
        if (nev == adatbazisok[i])
        {
            megfelel = false;
        }
    }
    return megfelel;
}

void Menu::mentesKezeles()
{
    if (adatbazisAllapot.uj)
    {
        std::cout << "Adja meg az uj adatbazis nevet: ";
        MyString nev;
        is >> nev;
        nev+= MyString(".txt");
        if (!megfelelNev(nev))
        {
            throw std::runtime_error("Ilyen nevu adatbazis mar letezik!");
        }
        std::ofstream fout(nev.c_str());
        m.mentes(fout);
        fout.close();
        m.torolAdatbazis();
        programAllapot = adatbazis;
    }
    else
    {
        std::ofstream fout(adatbazisAllapot.nev.c_str());
        m.mentes(fout);
        fout.close();
        m.torolAdatbazis();
        programAllapot = adatbazis;
    }
}

void Menu::adatbazisListazas()
{
    txtMentes();
    std::cout << "Letezo adatbazisok: ";
    kiirAdatbazisok();
    std::cout << "Adja meg, hogy melyik adatbazis szeretne betolteni: ";
    size_t szam;
    is >> szam;
    betoltAdatbazis(szam);
}

void Menu::txtMentes()
{
    adatbazisok.erase();
    DIR *dir;
    if ((dir = opendir(".")) != nullptr)
    {
        struct dirent *diread;
        while ((diread = readdir(dir)) != nullptr)
        {
            if (strstr(diread->d_name, ".txt") != nullptr)
            {
                MyString fajlnev(diread->d_name);
                if(teszteles && (fajlnev == MyString("be.txt") || fajlnev == MyString("be2.txt"))){
                    adatbazisok.push_back(fajlnev);
                }
                if(!teszteles && fajlnev != MyString("be.txt") && fajlnev != MyString("be2.txt")){
                    adatbazisok.push_back(fajlnev);
                }
            }
        }
        closedir(dir);
    }
    else
    {
        throw std::runtime_error("Nem sikerult megnyitni a mappat ahol az adatbazisok vannak!");
    }
}

Menu::Menu(std::istream &is,bool teszteles) : programAllapot(adatbazis), is(is),teszteles(teszteles) {}

void Menu::kiirAdatbazisok() const
{
    std::cout << std::endl;
    for (Vector<MyString>::iterator eleje = adatbazisok.begin(); eleje != adatbazisok.end(); ++eleje)
    {
        std::cout  << '['<< eleje.index()+1 << "]: ";
        std::cout << *eleje << std::endl;
    }
}

void Menu::betoltAdatbazis(size_t szam)
{
    if (szam > adatbazisok.size())
    {
        throw std::runtime_error("Rossz sorszamot adtott meg");
    }
    adatbazisAllapot.uj = false;
    adatbazisAllapot.nev = adatbazisok[szam - 1];
    std::ifstream fin(adatbazisok[szam - 1].c_str());
    m.betoltAdatbazis(fin);
    fin.close();
}

void Menu::fociklus()
{
    bool futas = true;
    while (futas)
    {
        try{
            switch (programAllapot)
            {
            case adatbazis:
                adatbazisAblak();
                break;

            case fomenu:
                fomenuAblak();
                break;

            case kilep:
                futas = false;
                std::cout << "A program leallt!" << std::endl;
                break;
            }
        }
        catch (std::runtime_error &uzenet)
        {
            std::cout << uzenet.what() << std::endl;
        }
        catch (std::out_of_range &hiba)
        {
            std::cout << hiba.what();
            programAllapot = kilep;
        }
        catch (std::bad_alloc &hiba)
        {
            std::cout << "Hiba a memoriafoglalasnal: " << hiba.what();
            programAllapot = kilep;
        }
    }
}

void Menu::fomenuAblak()
{
    for(int i=0;i<100;++i){
        std::cout << '*';
    }
    std::cout << "\n\n";
    std::cout << "[1] - Vonat hozzaadasa" << std::endl;
    std::cout << "[2] - Jegyvasarlas" << std::endl;
    std::cout << "[3] - Vonat torlese" << std::endl;
    std::cout << "[4] - Jegy torlese" << std::endl;
    std::cout << "[5] - Utvonal megvaltoztatasa" << std::endl;
    std::cout << "[6] - Menetrend megvaltoztatasa" << std::endl;
    std::cout << "[7] - Arak megvaltoztatasa" << std::endl;
    std::cout << "[8] - Vonatok rendezese szam szerint" << std::endl;
    std::cout << "[9] - Vonatok rendezese datum szerint" << std::endl;
    std::cout << "[10] - Vonatok szurese tipus szerint" << std::endl;
    std::cout << "[11] - Vonatok szurese allomas szerint" << std::endl;
    std::cout << "[12] - Osszes vonat listazasa" << std::endl;
    std::cout << "[13] - Jegyek rendezese aruk szerint" << std::endl;
    std::cout << "[14] - Osszes jegy listazasa" << std::endl;
    std::cout << "[15] - Mentes" << std::endl;

    std::cout << "Adja melyik utasitast szeretne valasztani: ";
    size_t utasitas;
    is >> utasitas;
    switch (utasitas)
    {
    case 1:
        m.hozzaadVonat(is);
        break;

    case 2:
        m.vasarolJegy(is);
        break;

    case 3:
        m.torolVonat(is);
        break;

    case 4:
        m.torolJegy(is);
        break;

    case 5:
        m.valtoztatAllomasok(is);
        break;

    case 6:
        m.valtoztatMentrend(is);
        break;

    case 7:
        m.valtoztatArak(is);
        break;

    case 8:
        m.rendezSzam();
        break;

    case 9:
        m.rendezDatum();
        break;

    case 10:
        m.szurTipus(is);
        break;

    case 11:
        m.szurAllomas(is);
        break;

    case 12:
        m.kiirVonatok();
        break;

    case 13:
        m.rendezJegyAr();
        break;

    case 14:
        m.kiirJegyek();
        break;

    case 15:
        mentesKezeles();
        break;

    default:
        throw std::runtime_error("Rossz utasitas sorszamot adott meg!");
        break;
    }
}

void Menu::adatbazisAblak()
{
    for(int i=0;i<100;++i){
        std::cout << '*';
    }
    std::cout << "\n\n";
    std::cout << "[1] - Meglevo adatbazis betoltese" << std::endl;
    std::cout << "[2] - Uj adatbazis letrehozasa" << std::endl;
    std::cout << "[3] - Kilepes" << std::endl;

    std::cout << "Adja melyik utasitast szeretne valasztani: ";
    size_t utasitas;

    is >> utasitas;

    switch (utasitas)
    {
    case 1:
        adatbazisListazas();
        programAllapot = fomenu;
        break;

    case 2:
        adatbazisAllapot.uj = true;
        programAllapot = fomenu;
        break;

    case 3:
        programAllapot = kilep;
        break;

    default:
        throw std::runtime_error("Rossz sorszamot adott meg!");
        break;
    }
}

Allapotok Menu::getAllapot()const {
    return programAllapot;
}