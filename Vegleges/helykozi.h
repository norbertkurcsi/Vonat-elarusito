#ifndef HELYKOZI_H
#define HELYKOZI_H

/**
 * \file helykozi.h
 *
 * Helykozi származtatott osztály deklarációja és inline függvényei.
 */

#include "vonat.h"

/// Helykozi osztály.
/// Vonat oszályból van származtatva.
/// Helyközi vonatokkal kapcsolatos műveleteket képes elvégezni.
class Helykozi : public Vonat
{
private:
    Vector<MyString> allomasok; ///< Vector típus amelyben MyString-ként tároljuk a vonat megállóit (min 3 kell legyen)

public:
    /// Konstruktor,amelyben meg kell adni minden adatot a helyközi vonattal kapcsolatban.
    /// @param szam - vonat azonosító száma
    /// @param indulas - vonat indulásának időpontja
    /// @param erkezes - vonat érkezésének időpontja
    /// @param elsoAr - első osztályon egy jegy ára
    /// @param masodAr - másod osztályon egy jegy ára
    /// @param elso - első osztályú kocsik száma
    /// @param masodik - másod oszályú kocsik ára
    Helykozi(const MyString &szam, const Datum &indulas, const Datum &erkezes, int elsoAr, int masodAr, int elso = 0, int masodik = 0);

    /// Egy helyközi vonat kiírására szolgáló függvény.
    /// @param os - output stream, ahova ki szeretnénk írni az adatokat
    void kiirVonat(std::ostream &os) const override;

    /// Egy újabb állomást ad hozzá az eddigi útvonalhoz.
    /// @param all - az új állomás neve
    void pushAllomas(const MyString &all);

    /// Statikus függvény egy helyközi vonat betöltéséhez.
    /// @param is - input filestream, ahonnan be szertnénk tölteni az adatotkat
    /// @return dinamikusan foglalt vonat mutató
    /// \warning - a függvény dinamikusan foglal le egy helyközi vonatot, a hívó felelőssége ezt felszabadítani
    static Vonat *betoltVonat(std::ifstream &is);

    /// Statikus függvény egy helyközi vonat hozzáasásához az adatbázishoz.
    /// @param is - input stream, ahonnan be szertnénk vinni a vonat adatait
    /// @return dinamikusan foglalt vonat mutató
    /// \warning - a függvény dinamikusan foglal le egy helyközi vonatot, a hívó felelőssége ezt felszabadítani
    static Vonat *hozzaadVonat(std::istream &is);

    /// Eldönti, egy adott kezdő- és végállomásról, hogy a vonat útvonalának része-e vagy nem.
    /// @param kezdo - kezdőállomás
    /// @param veg - végállomás
    /// @return igaz ha a vonat megfelel az útvonalnak
    bool megfelel(const MyString &kezdo, const MyString &veg) const override;

    /// Elmenti az állomásait egy adott output streambe.
    /// @param os - output stream ahova szereténk menteni az állomásokat
    void mentAllomasok(std::ostream &os) const override;

    /// Elementi a helyközi vonat típusát.
    /// @param os - output stream ahova a típust szeretnénk menteni
    void mentTipus(std::ostream &os) const override;

    /// Eldönti, hogy a vonat áthalad-e vagy sem egy adott megállón.
    /// @param allomas - megálló amiről el kell dönteni, hogy az útvonal része-e
    /// @return igaz ha a vonat áthalad a megadott megállón
    bool athalad(const MyString &allomas) const override;

    /// Egy MyStringet ad vissza, amiben a vonat típusa van, azaz Helyközi.
    /// @return MyString típus, amiben "Helykozi" van
    MyString tipus() const override;

    /// A vonat állomásainak a megváltoztatására szólgáló függvény.
    /// @param is - input stream, ahonnan jönnek az szükséges adatok
    /// @return kivételt dob, ha kevesebb mint 3 megállót akarunk megadni
    void valtoztatAllomasok(std::istream &is) override;
};

#endif