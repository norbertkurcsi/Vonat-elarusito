#ifndef _KOCSI_H
#define _KOCSI_H

/**
 * \file kocsi.h
 *
 * Kocsi osztály deklarációja és inline függvényei.
 */

#include <iostream>

/// Kocsi osztaly: egy vonatnak ilyen típusúak a kocsijai.
class Kocsi
{
private:
    bool hely[60]; ///< az adott kocsiban lévő helyek állapota
    int osztaly;   ///< a kocsi osztályának a típusa: első vagy második osztály

public:
    /// Konstruktor amelyben meg lehet adni a kocsi osztályát, de default konstruktor is egyben.
    explicit Kocsi(int tipus = 1);

    /// Getter függvény a kocsi típusának a lekérdezéséhez.
    int tipus() const;

    /// Kocsi kiírása
    void kiir(std::ostream &os) const;

    /// A függvény egy adatbázis betöltésénel használandó, segítségével le tudunk foglalni a kocsiban egy adott helyet.
    /// @param sorszam - a kocsin belüli hely sorszáma amit le akarunk foglalni
    void foglalBetoltesnel(size_t sorszam);
    
    /// A függvény megkeresi az első szabad helyet a kocsin belül és lefoglalja, majd visszaadja a hely sorszámát.
    /// Ha a kocsi már tele van, azaz nincs üres hely benne, akkor -1 értéket ad vissza
    /// @return a hely sorszáma vagy -1 ha nincs üres hely
    int foglal();

    /// Újból szabaddá tesz egy adott helyet a kocsin belül.
    /// @param sorszam - a felszbadítani kívánt hely sorszáma
    void felszabadit(size_t sorszam);
};

#endif // _KOCSI_H