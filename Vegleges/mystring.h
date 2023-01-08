#ifndef STRING_H
#define STRING_H

/**
 * \file mystring.h
 *
 * MyString osztály deklarációja és inline függvényei.
 */

#include <iostream>
#include <cstring>

/**
 * MyString osztály.
 * A pData-ban vannak a karakterek (a lezáró nullával együtt).
 * len a hossz.A hosszba nem számít bele a lezáró nulla.
 */
class MyString
{
private:
    char *pData; ///< pointer az adatra
    size_t len;  ///< hossz lezáró nulla nélkül

public:
    /// Konstruktor egy nullával lezárt char sorozatból.
    /// Ez a deafault is!
    /// @param str - pointer egy C sztringre
    explicit MyString(const char *str = "");

    /// Konstruktor egy char karakterből.
    /// @param c - karakter
    explicit MyString(const char c);

    /// Másoló konstruktor.
    /// @param s - MyString, amiből létrehozzuk az új String-et
    MyString(const MyString &s);

    /// Értékadó operátor.
    /// @param s - jobboldali String
    /// @return baoldali (módosított) string (referenciája)
    MyString &operator=(const MyString &s);

    /// Milyen hosszú az adott MyString '\0' nélkül.
    /// @return MyString hossza
    size_t size()const;

    /// Két Stringet összefűz.
    /// @param s - jobboldali String
    /// @return új MyString, ami tartalmazza a két stringet egmás után
    MyString operator+(const MyString &s) const;

    /// Sztrinhez karaktert összefűz.
    /// @param c - jobboldali karakter
    /// @return új MyString, ami tartalmazza a sztringet és a karaktert egymás után
    MyString operator+(const char c) const;

    /// Hozzáfűz egy MyStringet az adott objektum végéhez.
    /// @param s - MyString amit hozzá szeretnénk fűzni
    /// @return - MYString referencia az összfűzött sztringekre
    MyString &operator+=(const MyString &s);

    /// Hozzáfűz egy karaktert az adott objektum végéhez.
    /// @param c - karakter amit hozzá szeretnénk fűzni
    /// @return - MYString referencia az összfűzött sztringekre
    MyString &operator+=(const char c);

    /// A string egy megadott indexű elemének REFERENCIÁJÁVAL tér vissza.
    /// @param index - charakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob.
    char &operator[](size_t index);

    /// A string egy megadott indexű elemének REFERENCIÁJÁVAL tér vissza.
    /// @param index - karakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob (assert helyett).
    const char &operator[](size_t index) const;

    /// Összehasonlító operátor.
    /// @param s- jobb oldali MyString
    /// @return -igaz ha a két sztring egyenlő
    bool operator==(const MyString &s) const;

    /// Összehasonlító operátor.
    /// @param s- jobb oldali MyString
    /// @return -igaz ha a két sztring különbözik
    bool operator!=(const MyString &s) const;

    /// Összehasonlító operátor.
    /// @param s- jobb oldali MyString
    /// @return -igaz ha a bal oldal előbre van az ábc sorrendben
    bool operator<(const MyString &s) const;

    /// Összehasonlító operátor.
    /// @param s- jobb oldali MyString
    /// @return -igaz ha a bal oldal hátrébb van az ábc sorrendben
    bool operator>(const MyString &s) const;

    /// C-sztringet ad vissza.
    /// @return pinter egy '\0'-val lezárt (C) sztringre
    const char *c_str() const;

    /// Destruktor
    ~MyString();
};

/// Kiír az ostream-re.
/// @param os - ostream típusú objektum
/// @param s0 - String, amit kiírunk
/// @return os
std::ostream &operator<<(std::ostream &os, const MyString &s);

/// Beolvas az istream-ről egy szót egy string-be.
/// @param is - istream típusú objektum
/// @param s0 - String, amibe beolvas
/// @return is
std::istream &operator>>(std::istream &is, MyString &s);

#endif