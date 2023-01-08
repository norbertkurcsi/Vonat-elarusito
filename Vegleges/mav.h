#ifndef MAV_H
#define MAV_H

/**
 * \file mav.h
 *
 * Mav osztály deklarációja és inline függvényei.
 */

#include "myvector.hpp"
#include "vonat.h"
#include "intercity.h"
#include "helykozi.h"
#include "jegy.h"

/// Mav osztály.
/// Ebben az osztályban vannak térolva a vonatok, illetve a jegyek.
/// Ez az osztály teremti meg a kapcsolatot a felhasználó és a módosításokat végző Vonat és Jegy osztályok között.
class Mav
{
private:
    Vector<Vonat *> vonatok;    ///< Vector típusú objektum, az adott adatbázishoz tartozó vonatok Vonat* mutatói
    Vector<Jegy> jegyek;    ///< Vector típusú objektum, amelyben a jegyek vann tárolva
    Vonat* keresVonat(const MyString &szam);

public:
    /// Visszaadja egy adott sorszámú vonat mutatóját.
    /// @param i - hányadik vonat mutatóját szeretnénk
    /// @return az adott sorszámú vonatra mutató pointer
    Vonat *getVonat(size_t i) const;

    /// Betölti egy adatbázis elemeit egy adott input file streamből.
    /// @param is  - input file stream amiből az adatokat kell betölteni
    void betoltAdatbazis(std::ifstream &is);

    /// Elmenti a vonatok illetve jegyek adatatit egy adott output streambe.
    /// @param os - output stream ahova az adatokat szretnénk menteni
    void mentes(std::ostream &os) const;

    /// Kiírja az összes vonat adatatit egy adott output streambe.
    /// @param os - ouput stream ahova a vonatokat szeretnénk kiírni 
    void kiirVonatok(std::ostream &os = std::cout) const;

    /// Kiírja az összes jegy adatatit egy adott output streambe.
    /// @param os - ouput stream ahova a jegyeket szeretnénk kiírni
    void kiirJegyek(std::ostream &os = std::cout) const;

    /// Rendezi a vonatokat a tárolójukban szám szerint növekvő sorrendben.
    void rendezSzam();

    /// Rendezi a vonatokat a tárolójukban dátum szerint növekvő sorrendben.
    void rendezDatum();

    /// Rendezi a jegyeket az áruk szerint növekvő sorrendben.
    void rendezJegyAr();

    /// Egy szűrést végez a vonatokra egy megadott állomás szerint, és kiírja a feltételnek megfelelő vonatokat.
    /// Ha nincs megfelelő bejegyzés, akkor kivételt dob.
    /// @param is - input stream ahonnan, a függvény az állomás nevét kapja, ami szerint a szűrést végzi
    /// @param os - output stream ahova, a függvény kiírja a feltételnek megfelelő bejegyzéseket
    int szurAllomas(std::istream &is, std::ostream &os = std::cout) const;

    /// Egy szűrést végez a vonatokra egy megadott típus szerint, és kiírja a feltételnek megfelelő vonatokat.
    /// Ha nincs megfelelő bejegyzés, akkor kivételt dob.
    /// @param is - input stream, ahonnan a függvény az típus nevét kapja, ami szerint a szűrést végzi.
    /// @param os - output stream, ahova a függvény kiírja a feltételnek megfelelő bejegyzéseket
    int szurTipus(std::istream &is, std::ostream &os = std::cout) const;

    /// Kitöröl egy felhaszáló által megadott vonatot és a vonatra tartozó jegyeket.
    /// Ha nincs olyan vonat az adatbázisban, mint amit a felhasználó megad, akkor kivételt dob.
    /// @param is - input stream, ahonnan megkapja, a törölni kívánt vonat azonosítószámát
    void torolVonat(std::istream &is);

    /// Egy új vonat hozzáadását bonyolítja le.
    /// Ha nem megfelelő adatokat adunk meg, akkor kivételt dob.
    /// @param is - input stream, ahonnan érkeznek az adatok
    void hozzaadVonat(std::istream &is);

    /// Egy adatbázisban lévő vonat indulási és érkezési időpontjainak megváltoztatását kezeli.
    /// Ha olyan azonosítószámot kap, ami nem létezik, akkor kivételt dob.
    /// @param is - input stream, ahonnan érkeznek az adatok
    void valtoztatMentrend(std::istream &is);

    /// Egy adatbázisban lévő vonat árainak megváltoztatását kezeli.
    /// Ha rossz azonosítószámot kap, vagy rossz osztály lesz kiválasztva, akkor kivételt dob.
    /// @param is - input stream ahonnan érkeznek az adatok
    void valtoztatArak(std::istream &is);

    /// Egy adatbázisban lévő vonat állimásainak módosítását bonyolítja le.
    /// Ha rossz azonosítószámot kap, akkor kivételt dob.
    /// @param is - input stream, ahonnan érkeznek az adatok
    void valtoztatAllomasok(std::istream &is);

    /// Egy új jegy hozzáadását bonyolítja le.
    /// Ha nincs az általunk megadott útvonalnak megfelelő vonat, vagy rossz vonat számot adunk meg kiválasztásnál, akkor kivételt dob.
    /// @param is - input stream, ahonnan az adatok érkeznek
    void vasarolJegy(std::istream &is);

    /// Jegy törlését végzi. Elsősorban kilistázza az adatbázisban szereplő jegyeket, majd egy sorszámot megadva törli az adott jegyet.
    /// Ha érvénytelen sorszámot kap, akkor kivételt dob.
    /// @param is - input stream, ahonnan az adatok érkeznek
    void torolJegy(std::istream &is);

    /// Törli a dinamikus foglalt vonatokat, felszabadítja a két vektorának lefoglalt helyet is.
    void torolAdatbazis();

    /// Getter függvény a jegyek számának lekérdezésére.
    /// @return az adatbázisban lévő jegyek száma
    size_t jegyekSzama() const;
    
    /// Destruktor
    ~Mav();
};

/// Predikátum a vonatok szám szerinti rendezéséhez.
/// @param a - első vonat
/// @param b - második vonat
/// @return igaz ha az elsőnek a száma előbbre van az ábc-ben
bool vonatSzam(const Vonat *a, const Vonat *b);

/// Predikátum a vonatok dátum szerinti rendezéséhez.
/// @param a - első vonat
/// @param b - második vonat
/// @return igaz ha az elsőnek kisebb a dátumja
bool vonatDatum(const Vonat *a, const Vonat *b);

/// Predikátum a jegyek ár szerinti rendezéséhez.
/// @param a - első vonat
/// @param b - második vonat
/// @return igaz ha az elsőnek kisebb a dátumja
bool jegyAr(const Jegy &a, const Jegy &b);

#endif