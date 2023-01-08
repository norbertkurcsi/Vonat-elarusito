#include "jegy.h"

Jegy::Jegy(Vonat *vonatszam, size_t kocsiSzam, size_t hely, const MyString &honnan, const MyString &hova, int ar)
    : vonatSzam(vonatszam), kocsiSzam(kocsiSzam), hely(hely), honnan(honnan), hova(hova), ar(ar) {}

int Jegy::getAr() const
{
    return ar;
}

Vonat *Jegy::getVonat() const
{
    return vonatSzam;
}

void Jegy::kiir(std::ostream &os) const
{
    os << "Vonatszam: " << vonatSzam->getSzam() << std::endl;
    os << "Kocsi: " << kocsiSzam << std::endl;
    os << "Hely: " << hely << std::endl;
    os << honnan << " -> " << hova << std::endl;
    os << "Jegy ara: " << ar << "Ft" << std::endl;
}

void Jegy::mentes(std::ostream &os) const
{
    os << vonatSzam->getSzam() << '\n';
    os << kocsiSzam << '\n';
    os << hely << '\n';
    os << honnan << '\n';
    os << hova << '\n';
    os << ar << '\n';
}

Jegy Jegy::betoltes(std::ifstream &is, Vector<Vonat *> &vonatok)
{
    Jegy temp;
    MyString vonatszam;
    is >> vonatszam;
    bool talalat = true;
    for (Vector<Vonat *>::iterator kezdo = vonatok.begin(); kezdo != vonatok.end() && talalat; ++kezdo)
    {
        if ((*kezdo)->getSzam() == vonatszam)
        {
            temp.vonatSzam = *kezdo;
            talalat = false;
        }
    }
    is >> temp.kocsiSzam >> temp.hely >> temp.honnan >> temp.hova;
    is >> temp.ar;

    size_t elsoOsztKocsikSzama = temp.vonatSzam->getElsoOsztKocsik().size();
    if (temp.kocsiSzam <= elsoOsztKocsikSzama)
    {
        temp.vonatSzam->getElsoOsztKocsik()[temp.kocsiSzam - 1]->foglalBetoltesnel(temp.hely - 1);
    }
    else
    {
        temp.vonatSzam->getMasodOsztKocsik()[temp.kocsiSzam - elsoOsztKocsikSzama]->foglalBetoltesnel(temp.hely - 1);
    }

    return temp;
}

void Jegy::torolFoglalas() const
{
    size_t elsoOsztKocsikSzama = vonatSzam->getElsoOsztKocsik().size();
    if (kocsiSzam <= elsoOsztKocsikSzama)
    {
        vonatSzam->getElsoOsztKocsik()[kocsiSzam - 1]->felszabadit(hely - 1);
    }
    else
    {
        vonatSzam->getMasodOsztKocsik()[kocsiSzam - elsoOsztKocsikSzama]->felszabadit(hely - 1);
    }
}
