#ifndef _VONAT_H
#define _VONAT_H

/**
 * \file vonat.h
 *
 * Vonat absztarkt osztály deklarációja és inline függvényei.
 */

#include <iostream>
#include <fstream>
#include <vector>

#include "kocsi.h"
#include "myvector.hpp"
#include "mystring.h"
#include "datum.h"

/// Vonat osztály.
/// Absztarkt osztály, az Intercity és Helyközi osztályok őse.
/// Egy vonattal kapcsolatos műveleteket képes elvégezni.
class Vonat
{
private:
    MyString szam;  ///< vonat azonosító száma
    Vector<Kocsi *> elsoOsztKocsik; ///< Vector típus, amelyben dinamikusan foglalt elsőosztályú Kocsi objektumok vannak
    Vector<Kocsi *> masodOsztKsocsik;   ///< Vector típus, amelyben dinamikusan foglalt másodosztályú Kocsi objektumok vannak
    Datum indulas;  ///< a vonat indulásának időpontja
    Datum erkezes;  ///< a vonat érkezésének időpontja
    int elsoOsztAr; ///< egy elsőosztáyú jegy ára a vonaton
    int masodOsztAr;    ///< egy másodosztályú jegy ára a vonaton

public:
    /// Konstruktor,amelyben meg kell adni minden adatot a vonattal kapcsolatban.
    /// @param szam - vonat azonosító száma
    /// @param indulas - vonat indulásának időpontja
    /// @param erkezes - vonat érkezésének időpontja
    /// @param elsoAr - első osztályon egy jegy ára
    /// @param masodAr - másod osztályon egy jegy ára
    /// @param elso - első osztályú kocsik száma
    /// @param masodik - másod oszályú kocsik ára
    Vonat(const MyString &szam, const Datum &indulas, const Datum &erkezes, int elsoAr, int masodAr, int elso = 1, int masodik = 0);

    /// Getter függvény, amely visszaadja az adott vonat azonosítószámát.
    /// @return a vonat azonosítószáma
    MyString getSzam() const;

    /// A függvény egy referenciát ad vissza arra a Vector objektumra, amelyben az elsőosztályú kocsik vannak tárolva.
    /// @return referencia az elsőosztályú kocsikra
    Vector<Kocsi *> &getElsoOsztKocsik();

    /// A függvény egy referenciát ad vissza arra a Vector objektumra, amelyben az másodosztályú kocsik vannak tárolva.
    /// @return referencia az másodosztályú kocsikra
    Vector<Kocsi *> &getMasodOsztKocsik();

    /// Getter függvény, amely visszadja a vonat indulási időpontját.
    /// @return a vonat indulásának időpontja
    Datum getIndulas() const;

    /// Getter függvény, amely megadja, hogy az elsőosztályon mennyibe kerül egy jegy.
    /// @return elsőosztályú jegy ára
    int getElsoOsztAr() const;

    /// Getter függvény, amely megadja, hogy az másodosztályon mennyibe kerül egy jegy.
    /// @return másodosztályú jegy ára
    int getMasodOsztAr() const;

    /// A függvény elmenti a vonat indulási, illetve érkezési időpontjait.
    /// @param os - output stream arra a fájlra, amibe el akarjuk menteni a dátumokat
    void mentDatumok(std::ostream &os) const;

    /// Egy vonat kiírására szolgáló függvény.
    /// @param os - output stream, ahova ki szeretnénk írni az adatokat
    virtual void kiirVonat(std::ostream &os) const = 0;

    /// Eldönti, egy adott kezdő- és végállomásról, hogy benne van-e a vonat útvonalában.
    /// @param kezdo - kezdőállomás
    /// @param veg - végállomás
    /// @return igaz ha a vonat megfelel az útvonalnak
    virtual bool megfelel(const MyString &kezdo, const MyString &veg) const = 0;

    /// Eldönti, hogy a vonat áthalad-e vagy sem egy adott megállón.
    /// @param allomas - megálló amiről el kell dönteni, hogy az útvonal része-e
    /// @return igaz ha a vonat áthalad a megadott megállón
    virtual bool athalad(const MyString &allomas) const = 0;

    /// Elementi a vonat típusát.
    /// @param os - output stream ahova a típust szeretnénk menteni
    virtual void mentTipus(std::ostream &os) const = 0;

    /// Elmenti az állomásait egy adott output streambe.
    /// @param os - output stream ahova szereténk menteni az állomásokat
    virtual void mentAllomasok(std::ostream &os) const = 0;

    /// A vonat állomásainak a megváltoztatására szólgáló függvény.
    /// @param is - input stream, ahonnan jönnek az szükséges adatok
    virtual void valtoztatAllomasok(std::istream &is) = 0;

    /// Egy MyStringet ad vissza, amiben a vonat típusa van.
    /// @return MyString típus, a vonat típusával
    virtual MyString tipus() const = 0;

    /// A függvény megváltoztatja a vonat indulási időpontját.
    /// @param ind - az új indulás időpontja
    void valtoztatIndulas(const Datum &ind);

    /// A függvény megváltoztatja a vonat érkezési időpontját.
    /// @param erk - az új érkezés időpontja
    void valtoztatErkezes(const Datum &erk);

    /// A függvény megváltoztatja a vonat elsőoszályú jegyének árát.
    /// @param ujAr -  új elsőosztályú jegy ára
    void valtoztatElsoOsztAr(int ujAr);

    /// A függvény megváltoztatja a vonat másodoszályú jegyének árát.
    /// @param ujAr -  új másodosztályú jegy ára
    void valtoztatMasodOsztAr(int ujAr);

    /// A vonattal kapcsolatos általános adatok kiírása.
    /// @param os - output stream ahova az adatokat ki szeretnénk írni
    void kiir(std::ostream &os) const;

    /// A függvény lefoglal egy elsőosztályú jegyet a vonaton, és a paramétereiben visszaadja a kocsi számát, illetve a hely sorszámát.
    /// @param kocsi - referencia a lefoglalt kocsi sorszámára
    /// @param hely - referencia a lefoglalt hely sorszámára
    void vasarolElsoOszt(size_t &kocsi, size_t &hely);

    /// A függvény lefoglal egy másodosztályú jegyet a vonaton, és a paramétereiben visszaadja a kocsi számát, illetve a hely sorszámát.
    /// @param kocsi - referencia a lefoglalt kocsi sorszámára
    /// @param hely - referencia a lefoglalt hely sorszámára
    void vasarolMasodOszt(size_t &kocsi, size_t &hely);

    /// Virtuális destruktor
    virtual ~Vonat();
};
#endif // _VONAT_H