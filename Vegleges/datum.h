#ifndef DATUM_H
#define DATUM_H

/**
 * \file datum.h
 *
 * Dátum osztály deklarációja és inline függvényei.
 */

#include <iostream>

/// Datum osztály.
/// Egy dátum (hónap,nap) és idő (perc,másodperc) tárolására képes.
/// Ha rossz dátumot adunk meg const char* kivételt dob.
class Datum
{
    int honap, nap, ora, perc; ///< egész típusú változók a dátum adatainak tárolásához

    /// Dátum helyesség ellenőrzése
    /// @param honap - dátum hónapja
    /// @param nap - dátum napja
    /// @param ora - időpont órája
    /// @param perc - időpont perce
    static bool valid(int honap, int nap, int ora, int perc);

    /// Dátumot összehasonlító függvény.
    /// @param b - összehasonlítani kívánt dátum referenciája
    /// @return - 0 ha egyenlőek, -1 ha sorrendben vannak, 1 ha az első nagyobb
    int osszehasonlit(const Datum &b) const;

    /// Átváltás percre.
    /// @return - adott dátum percben számított értéke
    unsigned int convertToMin() const;

public:
    /// Konstruktor, amely egyben default konstruktor is amely első hónap, első nap, dél 12 órát állít be.
    Datum(int honap = 1, int nap = 1, int ora = 12, int perc = 0);

    /// Setter függvény, amely ellenőrzi az adatok helyességét is.
    /// @param honap - új hónap értéke
    /// @param nap - új nap értéke
    /// @param ora - új óra értéke
    /// @param perc - új perc értéke
    void set(int honap, int nap, int ora, int perc);

    /// Dátum beolvasása.
    /// @param is - input stream ahonnan olvas
    void beolvas(std::istream &is);

    /// Dátum kiirása.
    /// @param os - output stream ahova írunk
    void kiir(std::ostream &os) const;

    /// Dátum mentése.
    /// @param os - output file stream ahova mentünk
    void mentes(std::ostream &os) const;

    /// Összehasonító operátor.
    /// @param b - jobb oldali operandus
    /// @return - igaz ha a bal oldali dátum hamarabb van
    bool operator<(const Datum &b) const;

    /// Összehasonító operátor.
    /// @param b - jobb oldali operandus
    /// @return - igaz ha a jobb oldali dátum hamarabb van
    bool operator>(const Datum &b) const;

    /// Egyenlőség ellenőrzés operátor.
    /// @param b - jobb oldali operandus
    /// @return - igaz ha a két dátum egyenlő
    bool operator==(const Datum &b) const;
};

/// Globális inserter.
/// @param os - output stream referencia
/// @param s - Datum referencia
/// @return output stream referencia
std::ostream &operator<<(std::ostream &os, const Datum &d);

/// Globális extractor.
/// @param os - input stream referencia
/// @param s - Datum referencia
/// @return input stream referencia
std::istream &operator>>(std::istream &is, Datum &d);

#endif // DATUM_H