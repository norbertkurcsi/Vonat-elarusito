#ifndef JEGY_H
#define JEGY_H

/**
 * \file jegy.h
 *
 * Jegy osztály deklarációja és inline függvényei.
 */

#include "mystring.h"
#include "myvector.hpp"
#include "vonat.h"
#include "kocsi.h"
#include <iostream>
#include <fstream>

class Jegy
{
private:
    Vonat *vonatSzam; ///< vonatnak a száma amire szól a jegy
    size_t kocsiSzam; ///< vonaton belüli kocsi száma
    size_t hely;      ///< a kocsin belül a hely száma
    MyString honnan;  ///< honnan indul a vonat
    MyString hova;    ///< hova érkezik
    int ar;           ///< jegy ára
public:
    /// Default konstruktor.
    Jegy() {}

    /// Konstrukor amelyben meg kell adni az összes jeggyel kapcsolatos adatot.
    Jegy(Vonat *vonatszam, size_t kocsiSzam, size_t hely, const MyString &honnan, const MyString &hova, int ar);

    /// Jegy árának lekérdezése.
    /// @return - az adott jegynek az ára
    int getAr() const;

    /// Megadja hogy melyik vonatra van a jegy.
    /// @return - adott jegyhez tartozó vonat
    Vonat *getVonat() const;

    /// Kiírja a jegy adatait.
    /// @param os - output stream ahova kiírja a jegy adatait
    void kiir(std::ostream &os) const;

    /// Elmenti a jegy adatait.
    /// @param os - output file stream ahova elmenti a jegy adatait
    void mentes(std::ostream &os) const;

    /// Létrehoz egy Jegy típusú objektumot és feltölti adatokkal.
    /// @param is - input file stream ahonnan olvassa az adatokat a jegybe
    /// @return - a létrehozott Jegy típusú objektum
    static Jegy betoltes(std::ifstream &is, Vector<Vonat *> &vonatok);

    /// A függvény az adott jegy adattagjaiban megadott információk szerint törli a foglalást, azaz újra szabad lesz a vonaton ez a hely.
    void torolFoglalas() const;
};

#endif