#ifndef MYVECTOR_H
#define MYVECTOR_H

/**
 * \file myvector.hpp
 *
 * Vector osztály deklarációja és függvényeinek definíciójai .
 */

#include <exception>
#include "memtrace.h"

/// Változtatható méretű generikus tömb.
/// @param T - tárolt adattípus
template <class T>
class Vector
{
private:
    T *pData;   ///< tárolt adatok tömbjének első elemére mutató pointer
    size_t len; ///< tárolt adatok száma
    Vector(const Vector &t);
    Vector &operator=(const Vector &t);

public:
    class iterator;
    class const_iterator;

    /// Default és olyan konstruktor egyben, amelyben meg lehet adni, hogy mekkorára inicializája a vektort.
    /// @param n - méret
    explicit Vector(size_t n = 0);

    /// Getter függvény a vektor méretére.
    /// @return méret
    size_t size() const { return len; }

    /// Egy új elem hozzáfűzése a vektor végéhez.
    /// @param data - az adat amit hozzá kell fűzni
    void push_back(const T &data);

    /// Felszbadítja a vektor összes elemét.
    void erase();

    /// Kitöröl egy adott elemet a tömbből.
    /// @param elem - iterátorral megadott elem, amit törölni szeretnénk
    void erase(iterator elem);

    /// Indexelő operátor.
    /// @param index - index
    /// @return index. elem vagy std::out_of_range hiba
    T &operator[](size_t index);

    /// Indexelő operátor konstans objektumra.
    /// @param index - index
    /// @return index. elem vagy std::out_of_range hiba
    const T &operator[](size_t index) const;

    /// Létrehoz egy iterátort és az elejére állítja.
	/// @return - iterátor az adatsorozat elejére
    iterator begin() { return iterator(*this); }

    /// Létrehoz egy iterátort és az utolsó elem után állítja.
	/// @return - iterátor az adatsorozat végére
    iterator end() { return iterator(*this, len); }

    /// Létrehoz egy konstans objektumra alkalmazható iterátort és az elejére állítja.
	/// @return - iterátor az adatsorozat elejére
    const_iterator begin() const { return const_iterator(*this); }

    /// Létrehoz egy iterátort és az utolsó elem után állítja.
	/// @return - iterátor az adatsorozat végére
    const_iterator end() const { return const_iterator(*this, len); }

    /// Egy Vector típusú tároló rendezése egy adott predikátum szerint.
    /// @param vec - rendezni kívánt vektor referenciája
    /// @param pred - predikátum amelyet az összehasonlításnál használ az algoritmus
    template <typename P>
    void rendez( P pred){
        for (size_t i = 0; i < len - 1; ++i)
        {
            size_t minindex = i;
            for (size_t j = i + 1; j < len; ++j)
            {
                if (pred(pData[j], pData[minindex]))
                {
                    minindex = j;
                }
            }

            if (minindex != i)
            {
                T temp = pData[minindex];
                pData[minindex] = pData[i];
                pData[i] = temp;
            }
        }
    }

    /// Iterator osztály
    class iterator
    {
        Vector *p;  ///< tároljuk, hogy melyik az objektumhoz tartozik az iterátor
        size_t idx; ///< tároljuk az aktuális index értéket

    public:
        /// Default konstruktor.
        iterator() : p(0), idx(0) {}

        /// Konstruktor, egy konkrét objektum ix-edik elemére mutat.
        /// @param a - a konkrét objektum
        /// @param ix - ide állítja az indexet
        iterator(Vector &a, size_t ix = 0) : p(&a), idx(ix) {}

        /// Tagfüggvény mely visszadja, hogy az itarátor, hányadik elemre mutat.
        /// @return index
        size_t index() const
        {
            return idx;
        }

        /// Pre-inkremens operátor.
        /// Csak hatékonyság miatt ref. visszatérésű,
        /// értelmetlen lenne balértékként használni.
        /// @return léptett iterator
        iterator &operator++()
        {
            if (idx != p->len)
            {
                ++idx;
            }
            return *this;
        }

        /// Pre-dekremens.
        /// Csak hatékonyság miatt ref. visszatérésű,
        /// értelmetlen lenne balértékként használni
        /// @return léptett iterator
        iterator &operator--()
        {
            if (idx != 0)
            {
                --idx;
            }
            return *this;
        }

        /// Post-inkremens operátor.
        /// @return léptett iterator
        iterator operator++(int)
        {
            iterator tmp = *this; // növelés előtti értékkel kell visszatérni
            if (idx != p->len)
            {
                ++idx;
            }
            return tmp;
        }

        /// Egyenlőtlenség vizsgálat.
        /// @param i - jobboldali operandus
        /// @return igaz ha nem egyenlőek az iterátorok által mutatott adatok
        bool operator!=(const iterator &i) const
        {
            return (idx != i.idx);
        }

        /// Egyenlőség vizsgálat.
        /// @param i - jobboldali operandus
        /// @return igaz ha egyenlőek az iterátorok által mutatott adatok
        bool operator==(const iterator &i) const
        {
            return !operator!=(i);
        }

        /// indirekció
        T &operator*() const
        {
            if (idx != p->len)
            {
                return p->pData[idx];
            }
            else
            {
                throw std::runtime_error("Hibas indirekcio");
            }
        }

        /// Szelekció pointerrel (nyíl). Címet kell, hogy adjon.
        T *operator->() const
        {
            return &operator*();
        }
    };


    /// const_iterator osztály.
    /// Visszavezetjük az iterator osztályra.
    class const_iterator : public iterator
    {
    public:
        /// default konstruktor
        const_iterator() : iterator() {}

        /// konstruktor, egy konkrét objektum ix-edik elemére mutat
        /// @param a - a konkrét objektum
        /// @param ix - ide állítja az indexet
        const_iterator(const Vector &a, size_t ix = 0)
            : iterator(const_cast<Vector &>(a), ix) {} /// Kis trükközés a kasztolással: Levesszük a
                                                       /// konstans attribútumot, de nem fogjuk írni.

        /// indirekció
        const T &operator*() const
        {                                 /// Ezen keresztül biztosan nem fogjuk írni, de sajnos kompatibilitás
            return iterator::operator*(); /// miatt egy const_iterator -> iterator konverzió nem kerül semmibe...
        }

        /// Szelekció pointerrel (nyil). Címet kell, hogy adjon.
        const T *operator->() const
        {
            return &operator*();
        }
    };

    /// Destruktor
    ~Vector();
};


//----------------------------------------------------------------------------------------------------------------------------------


template <class T>
Vector<T>::Vector(size_t n) : len(n)
{
    pData = new T[n];
}

template <class T>
void Vector<T>::push_back(const T &data)
{
    T *temp = new T[len + 1];
    for (size_t i = 0; i < len; ++i)
    {
        temp[i] = pData[i];
    }
    temp[len++] = data;
    delete[] pData;
    pData = temp;
}

template <class T>
void Vector<T>::erase()
{
    delete[] pData;
    len = 0;
    pData = new T[len];
}

template <class T>
void Vector<T>::erase(iterator elem)
{
    T *temp = new T[len - 1];
    size_t j = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (i != elem.index())
        {
            temp[j++] = pData[i];
        }
    }
    len -= 1;
    delete[] pData;
    pData = temp;
}

template <class T>
T &Vector<T>::operator[](size_t index)
{
    if (index >= len)
    {
        throw std::out_of_range("Tul nagy index!");
    }
    return pData[index];
}

template <class T>
const T &Vector<T>::operator[](size_t index) const
{
    if (index >= len)
    {
        throw std::out_of_range("Tul nagy index!");
    }
    return pData[index];
}

template <class T>
Vector<T>::~Vector()
{
    delete[] pData;
}

#endif
