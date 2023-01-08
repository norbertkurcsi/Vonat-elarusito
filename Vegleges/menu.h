#ifndef MENU_H
#define MENU_H

/**
 * \file menu.h
 *
 * A program Menu osztályának deklarációja és inline függvényei.
 */

#include <iostream>
#include <dirent.h>
#include "myvector.hpp"
#include "mav.h"
#include "mystring.h"

/// A program nézeteinek állapotai.
enum Allapotok
{
    adatbazis,
    fomenu,
    kilep
};

/// AZ éppen betöltött adatbázis állapota.
/// Ha az adatbázis nem új, akkor a MyString típusban az van tárolva, hogy mentéskor milyen nevű fájlba kell visszamenteni.
/// Ha az adatbázis új, akkor a MyStringben tárolt adat érvénytelen, mert mentésnél a felhasználó adja megy , hogy mi legyen az adatbázis neve.
struct AdatbazisAllapot
{
    bool uj;
    MyString nev;
    AdatbazisAllapot():uj(false),nev(""){}
};

/// Menu osztály.
/// Ez az osztály felelős a program nézeteinek a kezeléséért,az adatbázisok kezeléséért, illetve a Mav osztály különböző osztályainak meghívásáért.
class Menu
{
    Mav m;  ///< Mav típusú objektum, amelyben tárolva vannak az adatbázis vonatai és jegyei
    Vector<MyString> adatbazisok;   ///< Vector típusú objektum, melyben az adatbázisok fájlnevei vannak tárolva
    Allapotok programAllapot;   ///< program nézete
    AdatbazisAllapot adatbazisAllapot;  ///< az éppen betöltve lévő adatbázisnak a típusa
    std::istream &is;   ///< input file stream ahonnan a programba bemenő adatok érkeznek
    bool teszteles; ///< milyen célból futtatjuk a programot: tesztelés vagy nem

    /// Abban az esetben, ha el akarunk menteni egy adatbázist ez a függvény hívódik meg.
    /// Ha az elmenteni kívánt adatbázis új, akkor meg kell adni az új adatbázis nevét. Ha a megadott név alatt már szerepel adatbázis akkor kivételt dob a főggvény.
    /// Ellenkező esetben ugyan abba a fájlba mentődik az adatbázis, ahonnan betőltőttük.
    void mentesKezeles();

    /// Kilistázza a meglévő adatbázisokat, majd kéri hogy válasszuk ki, hogy melyiket szeretnénk betölteni és betölti azt az adatbázist.
    void adatbazisListazas();

    /// A program folderében lévő .txt fájlokat menti el egy Vector típusú objektumba.
    /// Ha tesztelés céljából futtatunk, akkor a teszt állományait tölti be.
    void txtMentes();

    /// Kiírja a létező adatbázisok nevét.
    void kiirAdatbazisok() const;

    /// Betölti a megadott sorszámú adatbázist.
    /// Ha rossz sorszámot adunk meg a kiválasztásnál akkor egy kivételt dob.
    /// @param szam - a betölteni kívánt adatbázis sorszáma.
    void betoltAdatbazis(size_t szam);

    /// Az adatbazis ablakot kezeli.
    /// Kiírja a menü alpontjait, illetve egy adott utasítás sorszám esetén meghívja az ahoz tartozó függvényt.
    /// Ha rossz utasítás kódja, akkor kivételt dob.
    void adatbazisAblak();

    /// Az fomenu ablakot kezeli.
    /// Kiírja a menü alpontjait, illetve egy adott utasítás sorszám esetén meghívja az ahoz tartozó függvényt.
    /// Ha rossz utasítás kódja, akkor kivételt dob.
    void fomenuAblak();

    /// Azt ellenőrzi, hogy a paraméterben megadott nev szerepel-e a már meglévő adatbázisok nevei között.
    /// @param nev - a keresett adatbazis nev
    /// @return igaz ha nem szerepel olyan név, amit megadtunk paraméterben
    bool megfelelNev(const MyString &nev) const;

public:
    /// Menu osztály konstruktora.
    /// @param is - input stream ahonnan érkeznek az utasítások és az adatok
    /// @param teszteles - milyen célból futtatjuk a programot: tesztelés vagy nem
    Menu(std::istream &is = std::cin, bool teszteles = false);

    /// Getter függvény, amely visszadja a menü állapotát.
    /// @return menü állapota
    Allapotok getAllapot()const;

    /// Kezeli, hogy éppen melyik ablakot kell megjeleníteni, a programAllapot vátozótól függően, leállítja a programot szükség esetén, illetve kezeli a dobott kivételeket.
    void fociklus();
};

#endif