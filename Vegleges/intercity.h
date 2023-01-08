#ifndef INTERCITY_H
#define INTERCITY_H

/**
 * \file intercity.h
 *
 * Intercity származtatott osztály deklarációja és inline függvényei.
 */

#include "vonat.h"

/// Intercity osztály.
/// Vonat oszályból van származtatva.
/// Intercity vonatokkal kapcsolatos műveleteket képes elvégezni.
class Intercity : public Vonat
{
private:
    MyString kezdoAllomas;  ///< MyString típus amelyben az kezdőállomás van tarolva
    MyString vegallomas;    ///< MyString típus amelyben az végállomás van tarolva

public:
    /// Konstruktor,amelyben meg kell adni minden adatot a intercity vonattal kapcsolatban.
    /// @param szam - vonat azonosító száma
    /// @param indulas - vonat indulásának időpontja
    /// @param erkezes - vonat érkezésének időpontja
    /// @param kezdo - a vonat kezdőállomása
    /// @param veg - a vonat végállomása
    /// @param elsoAr - első osztályon egy jegy ára
    /// @param masodAr - másod osztályon egy jegy ára
    /// @param elso - első osztályú kocsik száma
    /// @param masodik - másod oszályú kocsik ára
    Intercity(const MyString &szam, const Datum &indulas, const Datum &erkezes, const MyString &kezdo, const MyString &veg, int elsoAr, int masodAr, int elso = 1, int masodik = 0);
    
    /// Statikus függvény egy intercity vonat betöltéséhez.
    /// @param is - input filestream, ahonnan be szertnénk tölteni az adatotkat
    /// @return dinamikusan foglalt vonat mutató
    /// \warning - a függvény dinamikusan foglal le egy intercity vonatot, a hívó felelőssége ezt felszabadítani
    static Vonat *betoltVonat(std::ifstream &is);

    /// Statikus függvény egy intercity vonat hozzáasásához az adatbázishoz.
    /// @param is - input stream, ahonnan be szertnénk vinni a vonat adatait
    /// @return dinamikusan foglalt vonat mutató
    /// \warning - a függvény dinamikusan foglal le egy intercity vonatot, a hívó felelőssége ezt felszabadítani
    static Vonat *hozzaadVonat(std::istream &is);

    /// Egy intercity vonat kiírására szolgáló függvény.
    /// @param os - output stream, ahova ki szeretnénk írni az adatokat
    void kiirVonat(std::ostream &os) const override;

    /// Eldönti, egy adott kezdő- és végállomásról, hogy ugyanazok-e mint a vonat állomásai.
    /// @param kezdo - kezdőállomás
    /// @param veg - végállomás
    /// @return igaz ha a vonat megfelel az útvonalnak
    bool megfelel(const MyString &kezdo, const MyString &veg) const override;

    /// Elmenti az állomásait egy adott output streambe.
    /// @param os - output stream ahova szereténk menteni az állomásokat
    void mentAllomasok(std::ostream &os) const override;

    /// Elementi az intercity vonat típusát.
    /// @param os - output stream ahova a típust szeretnénk menteni
    void mentTipus(std::ostream &os) const override;

    /// Eldönti, hogy a vonat áthalad-e vagy sem egy adott megállón.
    /// @param allomas - megálló amiről el kell dönteni, hogy az útvonal része-e
    /// @return igaz ha a vonat áthalad a megadott megállón
    bool athalad(const MyString &allomas) const override;

    /// Egy MyStringet ad vissza, amiben a vonat típusa van, azaz Intercity.
    /// @return MyString típus, amiben "Intercity" van
    MyString tipus() const override;

    /// A vonat állomásainak a megváltoztatására szólgáló függvény.
    /// @param is - input stream, ahonnan jönnek az szükséges adatok
    void valtoztatAllomasok(std::istream &is) override;
};

#endif