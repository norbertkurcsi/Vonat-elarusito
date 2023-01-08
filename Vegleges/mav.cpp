#include "mav.h"
#include "memtrace.h"

Vonat* Mav::keresVonat(const MyString &szam){
    Vonat *keresett = nullptr;
    for(Vector<Vonat*>::iterator iter = vonatok.begin();iter != vonatok.end();++iter){
        if((*iter)->getSzam() == szam){
            keresett = *iter;
        }
    }
    return keresett;
}

Vonat *Mav::getVonat(size_t i) const
{
    return vonatok[i];
}

void Mav::betoltAdatbazis(std::ifstream &is)
{
    int vonatokSzama, jegyekSzama;
    is >> vonatokSzama >> jegyekSzama;
    for (int i = 0; i < vonatokSzama; ++i)
    {
        bool tipus;
        is >> tipus;
        if (tipus)
        {
            vonatok.push_back(Intercity::betoltVonat(is));
        }
        else
        {
            vonatok.push_back(Helykozi::betoltVonat(is));
        }
    }

    for (int i = 0; i < jegyekSzama; ++i)
    {
        jegyek.push_back(Jegy::betoltes(is, vonatok));
    }
}

void Mav::mentes(std::ostream &os) const
{
    os << vonatok.size() << ' ' << jegyek.size() << std::endl;
    for (Vector<Vonat *>::iterator eleje = vonatok.begin(); eleje != vonatok.end(); ++eleje)
    {
        (*eleje)->mentTipus(os);
        os << (*eleje)->getSzam() << '\n';
        os << (*eleje)->getElsoOsztKocsik().size() << ' ';
        os << (*eleje)->getMasodOsztKocsik().size() << ' ';
        os << (*eleje)->getElsoOsztAr() << ' ';
        os << (*eleje)->getMasodOsztAr() << '\n';
        (*eleje)->mentDatumok(os);
        (*eleje)->mentAllomasok(os);
        os << '\n';
    }

    for (Vector<Jegy>::iterator eleje = jegyek.begin(); eleje != jegyek.end(); ++eleje)
    {
        eleje->mentes(os);
        os << std::endl;
    }
}

void Mav::kiirVonatok(std::ostream &os) const
{
    for (Vector<Vonat *>::iterator eleje = vonatok.begin(); eleje != vonatok.end(); ++eleje)
    {
        (*eleje)->kiirVonat(os);
        os << std::endl;
    }
}

void Mav::kiirJegyek(std::ostream &os) const
{
    for (Vector<Jegy>::iterator eleje = jegyek.begin(); eleje != jegyek.end(); ++eleje)
    {
        eleje->kiir(os);
        os << std::endl;
    }
}

void Mav::rendezSzam()
{
    // rendez(vonatok, vonatSzam);
    vonatok.rendez(vonatSzam);
    std::cout << "Sikeres rendezes!" << std::endl;
}

void Mav::rendezDatum()
{
    // rendez(vonatok, vonatDatum);
    vonatok.rendez(vonatDatum);
    std::cout << "Sikeres rendezes!" << std::endl;
}

void Mav::rendezJegyAr()
{
    // rendez(jegyek, jegyAr);
    jegyek.rendez(jegyAr);
    std::cout << "Sikeres rendezes!" << std::endl;
}

int Mav::szurAllomas(std::istream &is, std::ostream &os) const
{
    int talalat = 0;
    std::cout << "Adja meg milyen allomasra szeretne szurni: ";
    MyString allomas;
    is >> allomas;
    for (Vector<Vonat *>::iterator eleje = vonatok.begin(); eleje != vonatok.end(); ++eleje)
    {
        if ((*eleje)->athalad(allomas))
        {
            (*eleje)->kiirVonat(os);
            talalat++;
        }
    }
    if (talalat == 0)
    {
        throw std::runtime_error("Nincs a megadott feltetelnek megfelelo vonat az adatbazisban!");
    }
    return talalat;
}

int Mav::szurTipus(std::istream &is, std::ostream &os) const
{
    int talalat = 0;
    std::cout << "Adja meg milyen vonat tipusra szeretne szurni: ";
    MyString tipus;
    is >> tipus;
    for (Vector<Vonat *>::iterator eleje = vonatok.begin(); eleje != vonatok.end(); ++eleje)
    {
        if ((*eleje)->tipus() == tipus)
        {
            (*eleje)->kiirVonat(os);
            talalat++;
        }
    }
    if (talalat == 0)
    {
        throw std::runtime_error("Nincs a megadott feltetelnek megfelelo vonat az adatbazisban!");
    }
    return talalat;
}

void Mav::hozzaadVonat(std::istream &is)
{
    std::cout << "Adja meg a vonat tipusat (Intercity - 1, Helykozi - 2): ";
    size_t tipus;
    is >> tipus;
    Vonat *vonat;
    if (tipus == 1)
    {
        vonat = Intercity::hozzaadVonat(is);
    }
    else if (tipus == 2)
    {
        vonat = Helykozi::hozzaadVonat(is);
    }
    else
    {
        throw std::runtime_error("A megadott tipus ervenytelen!");
    }

    bool szerepel = false;
    for (size_t i = 0; i < vonatok.size(); ++i)
    {
        if (vonatok[i]->getSzam() == vonat->getSzam())
        {
            szerepel = true;
        }
    }
    if (szerepel)
    {
        delete vonat;
        throw std::runtime_error("A megadott vonat neve mar szerepel! Nem lehet hozzaadni!");
    }
    else
    {
        vonatok.push_back(vonat);
    }
}

void Mav::valtoztatMentrend(std::istream &is)
{
    MyString szam;
    std::cout << "Adja meg a valtoztatni kivant vonatnak a szamat: ";
    is >> szam;
    Vonat *keresett = keresVonat(szam);
    if(keresett == nullptr){
        throw std::runtime_error("Nem szerepel a megadott vonat az adatbazisban!");
    }
    Datum d;
    std::cout << "Adja meg az uj indulas datumat: ";
    is >> d;
    keresett->valtoztatIndulas(d);

    std::cout << "Adja meg az uj erkezes datumat: ";
    is >> d;
    keresett->valtoztatErkezes(d);
    std::cout << "A menetrend sikeresen meglett valzotatva!" << std::endl;
}

void Mav::valtoztatArak(std::istream &is)
{
    MyString szam;
    std::cout << "Adja meg, hogy melyik vonat arat szeretne megvaltoztatni: ";
    is >> szam;
    Vonat *keresett = keresVonat(szam);
    if(keresett == nullptr){
        throw std::runtime_error("A megadott vonat nem talalhato az adatbazisban!");
    }

    std::cout << "Adja meg, hogy melyik osztaly arat szeretne megvaltoztatni (Elso osztaly - 1, Masod osztaly - 2): ";
    size_t tipus;
    is >> tipus;
    int ujAr;
    std::cout << "Adja meg az adott osztaly uj arat: ";
    is >> ujAr;
    if (tipus == 1)
    {
        keresett->valtoztatElsoOsztAr(ujAr);
        std::cout << "Az elso osztaly ara sikeresen meg lett valtoztatva!" << std::endl;
    }
    else if (tipus == 2)
    {
        keresett->valtoztatMasodOsztAr(ujAr);
        std::cout << "Az masod osztaly ara sikeresen meg lett valtoztatva!" << std::endl;
    }
    else
    {
        throw std::runtime_error("A megadott tipus ervenytelen!");
    }
}

void Mav::torolVonat(std::istream &is)
{
    MyString szam;
    std::cout << "Adja meg, hogy melyik vonatot szeretne torolni: ";
    is >> szam;
    std::cout << "Bemegy" << szam;

    bool talalat = true;
    Vector<Vonat *>::iterator keresett;
    for (Vector<Vonat *>::iterator eleje = vonatok.begin(); eleje != vonatok.end() && talalat; ++eleje)
    {
        if ((*eleje)->getSzam() == szam)
        {
            talalat = false;
            keresett = eleje;
        }
    }

    if (!talalat)
    {
        size_t i = 0;
        while (i < jegyek.size())
        {
            if (szam == jegyek[i].getVonat()->getSzam())
            {
                jegyek.erase(Vector<Jegy>::iterator(jegyek, i));
            }
            else
            {
                ++i;
            }
        }
        delete (*keresett);
        vonatok.erase(keresett);

        std::cout << "A vonat es a hozzatartozo jegyek sikeresen torolve!";
    }

    if (talalat)
    {
        throw std::runtime_error("Nem talalhato a torolni kivant vonat az adatbazisban!");
    }
}

void Mav::valtoztatAllomasok(std::istream &is)
{
    MyString szam;
    std::cout << "Adja meg, hogy melyik vonat utvonalat szeretne megvaltoztatni: ";
    is >> szam;
    Vonat *keresett = keresVonat(szam);
    if(keresett == nullptr){
        throw std::runtime_error("Nincs ilyen vonat az adatbazisban!");
    }

    keresett->valtoztatAllomasok(is);

    size_t i = 0;
    while (i < jegyek.size())
    {
        if (szam == jegyek[i].getVonat()->getSzam())
        {
            jegyek.erase(Vector<Jegy>::iterator(jegyek, i));
        }
        else
        {
            ++i;
        }
    }
}

void Mav::vasarolJegy(std::istream &is)
{
    MyString kezdo, veg;
    std::cout << "Adja meg honnan szeretne indulni: ";
    is >> kezdo;
    std::cout << "Adja meg hova szeretne erkezni: ";
    is >> veg;
    bool talalat = false;
    for (Vector<Vonat *>::iterator eleje = vonatok.begin(); eleje != vonatok.end(); ++eleje)
    {
        if ((*eleje)->megfelel(kezdo, veg))
        {
            talalat = true;
            (*eleje)->kiirVonat(std::cout);
        }
    }

    if (talalat)
    {
        MyString szam;
        int osztaly;
        std::cout << "Adja meg a lefoglalni kivant vonat szamat: ";
        is >> szam;
        std::cout << "Adja meg hogy milyen osztalyon szeretne a jegyet(elso osztaly - 1, masod osztaly - 2): ";
        is >> osztaly;
        bool ok = true;
        for (Vector<Vonat *>::iterator eleje = vonatok.begin(); eleje != vonatok.end() && ok; ++eleje)
        {
            if (szam == (*eleje)->getSzam())
            {
                ok = false;
                size_t kocsi = 0, hely = 0;
                if (osztaly == 1)
                {
                    (*eleje)->vasarolElsoOszt(kocsi, hely);
                    if (kocsi != 0)
                    {
                        jegyek.push_back(Jegy((*eleje), kocsi, hely, kezdo, veg, (*eleje)->getElsoOsztAr()));
                    }
                }
                else if (osztaly == 2)
                {
                    (*eleje)->vasarolMasodOszt(kocsi, hely);
                    if (kocsi != 0)
                    {
                        jegyek.push_back(Jegy((*eleje), kocsi, hely, kezdo, veg, (*eleje)->getMasodOsztAr()));
                    }
                }
                else
                {
                    throw std::runtime_error("Rossz osztalyt adott meg");
                }

                if (kocsi != 0)
                {
                    std::cout << "Sikeres vasarlas! A jegye adatai a kovetkezok:" << std::endl;
                    jegyek[jegyek.size() - 1].kiir(std::cout);
                }
                else
                {
                    throw std::runtime_error("Sajnos a megadott vonaton elgyotak a helyek!");
                }
            }
        }
        if (ok)
        {
            throw std::runtime_error("Rossz vonat szamot adott meg!");
        }
    }
    else
    {
        throw std::runtime_error("Sajnos nincs megfelelo vonat az on szamara!");
    }
}

size_t Mav::jegyekSzama() const
{
    return jegyek.size();
}

void Mav::torolJegy(std::istream &is)
{
    for (Vector<Jegy>::iterator eleje = jegyek.begin(); eleje != jegyek.end(); ++eleje)
    {
        std::cout << "Sorszam: " << eleje.index() + 1 << std::endl;
        eleje->kiir(std::cout);
        std::cout << std::endl;
    }

    size_t sorszam;
    std::cout << "Adja meg a torolni kivant jegy sorszamat: ";
    is >> sorszam;
    if (sorszam > jegyek.size() || sorszam < 1)
    {
        throw std::runtime_error("Helytelen sorszamot adott meg!");
    }

    jegyek[sorszam - 1].torolFoglalas();
    jegyek.erase(Vector<Jegy>::iterator(jegyek, sorszam - 1));
}

void Mav::torolAdatbazis()
{
    for (Vector<Vonat *>::iterator eleje = vonatok.begin(); eleje != vonatok.end(); ++eleje)
    {
        delete *eleje;
    }
    vonatok.erase();
    jegyek.erase();
}

Mav::~Mav()
{
    torolAdatbazis();
}

///////////////////////////////////////////////////////////

bool vonatSzam(const Vonat *a, const Vonat *b)
{
    return a->getSzam() < b->getSzam();
}

bool vonatDatum(const Vonat *a, const Vonat *b)
{
    return a->getIndulas() < b->getIndulas();
}

bool jegyAr(const Jegy &a, const Jegy &b)
{
    return a.getAr() < b.getAr();
}