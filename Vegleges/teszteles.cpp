#include "teszteles.h"

#include <iostream>
#include <fstream>

#include "vonat.h"
#include "datum.h"
#include "mystring.h"
#include "mav.h"
#include "menu.h"

#include "gtest_lite.h"
#include "memtrace.h"

void tesztekFuttatasa()
{
    TEST(Datum, Datum osztaly)
    {
        // konstruktor
        EXPECT_NO_THROW(Datum d);
        EXPECT_NO_THROW(Datum d(3,4,5,6));
        EXPECT_THROW(Datum d(-1, 12, 12, 12), std::runtime_error&);

        // setter
        Datum d;
        EXPECT_THROW(d.set(-1, 12, 12, 12), std::runtime_error&);
        EXPECT_NO_THROW(d.set(1, 1, 1, 1));

        // osszehasonlitas
        Datum d1(5, 4, 10, 10);
        Datum d2(6, 10, 10, 10);
        EXPECT_EQ(d1 < d2, true);
        EXPECT_EQ(d2 < d1, false);
        EXPECT_EQ(d1 > d2, false);
        d1 = d2;
        EXPECT_EQ(d1 == d2, true);
        
        // kiiras
        std::stringstream ss;
        ss << d1;
        EXPECT_STREQ("06.10, 10:10", ss.str().c_str());
        
        //beolvasas
        ss.str("2 3 13 20");
        ss >> d1;
        std::stringstream s2;
        s2 << d1;
        EXPECT_STREQ("02.03, 13:20", s2.str().c_str());

        //mentes
        std::stringstream s3;
        d1.mentes(s3);
        EXPECT_STREQ("2 3 13 20 ",s3.str().c_str());
    }
    END

    TEST(Vector, index)
    {
      Vector<int> vec;
      EXPECT_THROW(vec[1],std::out_of_range&);
    }
    END

    TEST(MyString, emptyStr) {
      MyString ures;
      EXPECT_EQ((size_t)0, ures.size());
      EXPECT_STREQ("", ures.c_str());
    }
    END

    TEST(MyString, fromChr) {
      char ch = 'a';
      MyString a(ch);
      EXPECT_EQ((size_t)1, a.size());
      EXPECT_STREQ("a", a.c_str());

      MyString b('a');    // konstansból is megy?
      EXPECT_STREQ("a", b.c_str());
    }
    END

    TEST(MyString, FromCstr) {
      const char *hello = "Hello sztring";
      MyString a(hello);
      EXPECT_EQ(strlen(hello), a.size()) << "Baj van a MyString hosszaval" << std::endl;
      EXPECT_STREQ(hello, a.c_str()) << "C-sztringbol MyString letrehozasa nem sikerult!" << std::endl;

      /// Ellenőrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
      char cpp[] = { 'C', '+', '+', '\0' };
      MyString b(cpp);
      cpp[0] = 'X';
      EXPECT_STRNE(cpp, b.c_str()) << "FromCstr: le kellett volna masolni a karaktertombot!" << std::endl;
    }
    END

    TEST(MyString, ctor) {
      const char *hello = "Hello sztring";
      MyString a(hello);
      MyString b = a;
      EXPECT_EQ(strlen(hello), b.size()) << "Baj van a MyString hosszaval!" << std::endl;
      EXPECT_STREQ(hello, b.c_str()) << "Baj van a masolo konstruktorral!" << std::endl;

      EXPECT_STREQ(hello, a.c_str()) << "Masolo kontsr. elromlott a forras!" << std::endl;
      EXPECT_EQ(strlen(hello), a.size()) << "Masolo konstr. alatt elromlott a forras hossza!" << std::endl;

      const MyString c = a;
      MyString d = c;     // konstansból is megy?
      EXPECT_STREQ(hello, d.c_str()) << "Baj van a masolo konstruktorral" << std::endl;
    }
    END

    TEST(MyString, ctor_nullptr) {
      MyString d0;
      MyString ures = d0;     // üres sztringet is le tudja másolni?
      EXPECT_EQ((size_t)0, ures.size()) << "Baj van a MyString hosszaval" << std::endl;
      /// Ellenőrizzük, hogy üres sztringet ("") kaptunk-e vissza?
      EXPECT_STREQ("", ures.c_str()) << "Nem ures sztring jott letre" << std::endl;
    }
    END

    TEST(MyString, opAssign) {
      const char *hello = "Hello sztring";
      MyString a(hello);
      MyString b("Duma1"), c("Duma2");
      EXPECT_STRNE(a.c_str(), b.c_str());
      a = a;
      EXPECT_EQ(strlen(hello), a.size()) << "Baj van az ertekadassal: a = a hossz" << std::endl;
      EXPECT_STREQ(hello, a.c_str()) << "Baj van az ertekadassal: a = a" << std::endl;
      c = b = a;

      EXPECT_EQ(strlen(hello), a.size()) << "Ertekedasnal elromlott a forras hossza!" << std::endl;
      EXPECT_STREQ(hello, a.c_str()) << "Ertekadasnal elromlott a forras!" << std::endl;
      EXPECT_EQ(strlen(hello), b.size()) << "Ertekedas: nem jo a hossz!" << std::endl;
      EXPECT_STREQ(hello, b.c_str()) << "Ertekadas nem sikerult!" << std::endl;
      EXPECT_EQ(strlen(hello), c.size()) << "Ertekedas: nem jo a hossz!" << std::endl;
      EXPECT_STREQ(hello, c.c_str()) << "Ertekadas nem sikerult!" << std::endl;

      const MyString d("Konst.");
      c = d;        // konstansból is megy?
      EXPECT_EQ(c.size(), c.size()) << "Ertekedas konstansbol: nem jo a hossz!" << std::endl;
      EXPECT_STREQ(d.c_str(), c.c_str()) << "Ertekadas konstansbol nem sikerult!" << std::endl;
    }
    END

    TEST(MyString, opAssign_nullptr) {
      MyString d0;
      MyString c = d0;     // üres sztringet is le tudja másolni?
      EXPECT_EQ((size_t)0, c.size()) << "Baj van a MyString hosszaval" << std::endl;
      /// Ellenőrizzük, hogy üres sztringet ("") kaptunk-e vissza?
      EXPECT_STREQ("", c.c_str()) << "Nem ures sztring jott letre" << std::endl;

    }
    END

    TEST(MyString, strPlusStr) {
        MyString a("Hello ");
        MyString b("sztring");
        MyString c;
        c = a + b;
        EXPECT_STREQ("Hello sztring", c.c_str()) << "Nem sikerult a + MyString muvelet!" << std::endl;
        EXPECT_STREQ("Hello ", a.c_str()) << "A + muvelet elrontja a bal oldalt?" << std::endl;
        EXPECT_STREQ("sztring", b.c_str()) << "A + muvelet elrontja a jobb oldalt?" << std::endl;

        c+=a;
        EXPECT_STREQ("Hello sztringHello ", c.c_str());
        c+='!';
        EXPECT_STREQ("Hello sztringHello !", c.c_str());

        const MyString a1 = a, b1 = b;

        MyString c1;
        c1 = a1 + b1;          // konstansból is megy?
        EXPECT_STREQ("Hello sztring", c1.c_str()) << "Nem sikerult a + MyString muvelet!" << std::endl;
    }
    END

    TEST(MyString, strPlusChr) {
      MyString a("Hello ");
      MyString b;
      b = a + 'B';
      EXPECT_STREQ("Hello B", b.c_str()) << "Nem sikerult a + char muvelet!" << std::endl;
      EXPECT_STREQ("Hello ", a.c_str()) << "A + muvelet elrontja a bal oldalt?" << std::endl;

      const MyString a1 = a;
      MyString b1;
      b1 = a1 + 'B';          // konstansból is megy?
      EXPECT_STREQ("Hello B", b1.c_str()) << "Nem sikerult a + char muvelet!" << std::endl;
      EXPECT_STREQ("Hello ", a1.c_str()) << "A + muvelet elrontja a bal oldalt?" << std::endl;

    }
    END

    TEST(MyString, index) {
      MyString a("Hello 678");
      EXPECT_NO_THROW(a[0]);
      EXPECT_NO_THROW(a[7]);
      EXPECT_NO_THROW(a[8]);
      EXPECT_THROW(a[9], std::out_of_range&);
      EXPECT_THROW(a[-1], std::out_of_range&);
      EXPECT_EQ('7', a[7]);
      a[7] = '.';
      EXPECT_EQ('.', a[7]);
    }
    END

    TEST(MyString, const_index) {
      const MyString a("Hello 678");
      EXPECT_NO_THROW(a[0]);
      EXPECT_NO_THROW(a[7]);
      EXPECT_NO_THROW(a[8]);
      EXPECT_THROW(a[9], std::out_of_range&);
      EXPECT_THROW(a[-1], std::out_of_range&);
      EXPECT_EQ('7', a[7]);
    }
    END

    TEST(MyString, osszehasonlit)
    {
        MyString a("abc"),b("def");
        EXPECT_EQ(true, a < b);
        EXPECT_EQ(false, a > b);
        a=b;
        EXPECT_EQ(true,a==b);
    }
    END

    TEST(MyString, insert) {
      MyString a("Hello sztring");
      std::stringstream ss;
      ss << a;
      EXPECT_STREQ("Hello sztring", ss.str().c_str());
    }
    END

    TEST(MyString, extract)
    {
      MyString a("Hello   sztring \n Lajos12");
      std::stringstream ss;
      ss << a;
      MyString in1, in2, in3;
      ss >> in1 >> in2;         // fűzhetőnek kell lenni
      while (ss >> in3);        // csak kicsit gonosz a teszt !
      EXPECT_STREQ("Hello   sztring ", in1.c_str());
      EXPECT_STREQ("Lajos12", in2.c_str());
    }
    END

    TEST(Kocsi, Kocsi osztaly)
    {
        Kocsi kocsi;
        EXPECT_EQ(1,kocsi.tipus());
        Kocsi kocsi2(2);
        EXPECT_EQ(2,kocsi2.tipus());

        std::stringstream ss;
        kocsi.kiir(ss);
        EXPECT_STREQ("Elso osztaly",ss.str().c_str());

        std::stringstream ss2;
        kocsi2.kiir(ss2);
        EXPECT_STREQ("Masod osztaly",ss2.str().c_str());

        for(int i=0;i<10;++i){
          kocsi.foglalBetoltesnel(i);
        }
        int hely=kocsi.foglal();
        EXPECT_EQ(10,hely);

        for(int i=0;i<60;++i){
          kocsi.foglalBetoltesnel(i);
        }
        hely=kocsi.foglal();
        EXPECT_EQ(-1,hely);

        kocsi.felszabadit(30);
        hely=kocsi.foglal();
        EXPECT_EQ(30,hely);
    }
    END

    TEST(Mav,betoltAdatbazis)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream ss;
      Vonat * vonat = m.getVonat(2);
      ss << vonat->getSzam();
      EXPECT_STREQ("C0HGI",ss.str().c_str());
      EXPECT_EQ(2,vonat->getElsoOsztKocsik().size());
      EXPECT_EQ(8,vonat->getMasodOsztKocsik().size());
      EXPECT_EQ(2000,vonat->getElsoOsztAr());
      EXPECT_EQ(3000,vonat->getMasodOsztAr());
    }
    END

    TEST(Vonat, dynamicCast)
    {
      Datum a;
      Vonat *vonat1 = new Intercity(MyString("ABC"),a,a,MyString("Budapest"),MyString("Nagyvarad"),2,2,2000,1000);
      Vonat *vonat2 = new Helykozi(MyString("ABC"),a,a,2,2,2000,1000);
      EXPECT_TRUE(dynamic_cast<Intercity*>(vonat1) != NULL);
      EXPECT_TRUE(dynamic_cast<Helykozi*>(vonat1) == NULL);
      EXPECT_TRUE(dynamic_cast<Intercity*>(vonat2) == NULL);
      EXPECT_TRUE(dynamic_cast<Helykozi*>(vonat2) != NULL);
      delete vonat1;
      delete vonat2;
    }
    END

    TEST(Mav,kiirVonatok)
    {
      Mav m;
      std::ifstream fin("be2.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream ss;
      m.kiirVonatok(ss);
      EXPECT_STREQ("Helykozi - Tu8O\n\tIndulas: 01.01, 01:01\n\tEkrezes: 02.02, 02:02\n\t10 db kocsi\n\tElso osztaly: 3000Ft\n\tMasod osztaly: 1500Ft\n\tBudapest -> Jeszberny -> Balaton -> Nagyvarad -> Marosvasarhely\n\nIntercity - T7J9O\n\tIndulas: 02.10, 23:10\n\tEkrezes: 02.11, 01:20\n\t10 db kocsi\n\tElso osztaly: 4000Ft\n\tMasod osztaly: 1500Ft\n\tBudapest -> Nagyvarad\n\n"
        ,ss.str().c_str());
    }
    END

    TEST(Mav,kiirJegyek)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream bemenet;
      bemenet << "2\n";
      m.torolJegy(bemenet);

      std::stringstream ss;
      m.kiirJegyek(ss);
      EXPECT_STREQ("Vonatszam: C0HGI\nKocsi: 1\nHely: 1\nJaszbereny -> Budapest\nJegy ara: 30Ft\n\n",ss.str().c_str());

    }
    END

    TEST(Mav,rendezesek)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      m.rendezDatum();
      Vonat *vonat=m.getVonat(0);
      EXPECT_STREQ("Tu8O",vonat->getSzam().c_str());
      m.rendezSzam();
      vonat = m.getVonat(0);
      EXPECT_STREQ("C0HGI",vonat->getSzam().c_str());
    }
    END

    TEST(Mav,szurAllomas)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream bemenet,kimenet;
      bemenet << "Marosvasarhely\n";
      int talalatok =  m.szurAllomas(bemenet,kimenet);
      EXPECT_EQ(1,talalatok);
      bemenet << "abcd";
      EXPECT_THROW(m.szurAllomas(bemenet,kimenet),std::runtime_error&);
    }
    END

    TEST(Mav,szurTipus)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream bemenet,kimenet;
      bemenet << "Helykozi\n";
      int talalatok =  m.szurTipus(bemenet,kimenet);
      EXPECT_EQ(2,talalatok);
      bemenet << "abcd";
      EXPECT_THROW(m.szurTipus(bemenet,kimenet),std::runtime_error&);
    }
    END

    TEST(Mav,hozzaadVonat)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream bemenet;
      bemenet << "1\nabc\n3\n4\n1000\n2000\n1\n1\n1\n1\n2\n2\n2\n2\nBudapest\nSiofok";
      m.hozzaadVonat(bemenet);
      Vonat *vonat = m.getVonat(3);
      EXPECT_STREQ("abc",vonat->getSzam().c_str());

      std::stringstream bemenet2;
      bemenet2 << "2\ndef\n3\n4\n1000\n2000\n1\n1\n1\n1\n2\n2\n2\n2\n3\nBudapest\nSiofok\nSzeged";
      m.hozzaadVonat(bemenet2);
      vonat = m.getVonat(4);
      EXPECT_STREQ("def",vonat->getSzam().c_str());

      bemenet2 << "3";
      EXPECT_THROW(m.hozzaadVonat(bemenet2),std::runtime_error&);

      std::stringstream bemenet3;
      bemenet3 << "1\nabc\n3\n4\n1000\n2000\n1\n1\n1\n1\n2\n2\n2\n2\nBudapest\nSiofok";
      EXPECT_THROW(m.hozzaadVonat(bemenet3),std::runtime_error&);

      std::stringstream bemenet4;
      bemenet4 << "2\ndef\n3\n4\n1000\n2000\n1\n1\n1\n1\n2\n2\n2\n2\n2\nBudapest\nSiofok\nSzeged";
      EXPECT_THROW(m.hozzaadVonat(bemenet4),std::runtime_error&);
    }
    END

    TEST(Mav,valtoztatMenetrend)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream bemenet,kimenet;
      bemenet << "Tu8O\n3\n3\n3\n3\n4\n4\n4\n4\n";
      m.valtoztatMentrend(bemenet);
      Vonat *vonat = m.getVonat(0);
      kimenet << vonat->getIndulas();
      EXPECT_STREQ("03.03, 03:03",kimenet.str().c_str());

      bemenet << "adasd";
      EXPECT_THROW(m.valtoztatMentrend(bemenet),std::runtime_error&);
    }
    END

    TEST(Mav,valtoztatArak)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream bemenet,bemenet2,bemenet3,bemenet4;
      bemenet << "C0HGI\n1\n20000";
      m.valtoztatArak(bemenet);
      Vonat *vonat = m.getVonat(2);
      EXPECT_EQ(20000,vonat->getElsoOsztAr());
      bemenet2 << "C0HGI\n2\n100";
      m.valtoztatArak(bemenet2);
      EXPECT_EQ(100,vonat->getMasodOsztAr());
      bemenet3 << "C0HGI\n4";
      EXPECT_THROW(m.valtoztatArak(bemenet3),std::runtime_error&);
      bemenet4 << "C0HH";
      EXPECT_THROW(m.valtoztatArak(bemenet4),std::runtime_error&);
    }
    END

    TEST(Mav,torolJegy)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream bemenet;
      bemenet << "1\n";
      m.torolJegy(bemenet);
      Vonat *vonat = m.getVonat(2);
      Kocsi *kocsi = vonat->getMasodOsztKocsik()[0];
      EXPECT_EQ(0,kocsi->foglal());

      bemenet << "1\n";
      m.torolJegy(bemenet);
      vonat = m.getVonat(2);
      kocsi = vonat->getElsoOsztKocsik()[0];
      EXPECT_EQ(0,kocsi->foglal());

      bemenet << "2\n";
      EXPECT_THROW(m.torolJegy(bemenet),std::runtime_error&);
    }
    END

    TEST(Mav,vasarolJegy)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream bemenet,bemenet2,bemenet3,bemenet4,bemenet5;
      bemenet << "Jaszbereny\nBudapest\nC0HGI\n1\n";
      m.vasarolJegy(bemenet);
      EXPECT_EQ(3,m.jegyekSzama());

      bemenet << "Jaszbereny\nBudapest\nC0HGI\n2\n";
      m.vasarolJegy(bemenet);
      EXPECT_EQ(4,m.jegyekSzama());

      bemenet2 << "Jaszbereny\nBudapest\nafdf\n1\n";
      EXPECT_THROW(m.vasarolJegy(bemenet2),std::runtime_error&);

      bemenet3 << "Jaszbereny\nBudapest\nC0HGI\n3\n";
      EXPECT_THROW(m.vasarolJegy(bemenet3),std::runtime_error&);

      bemenet4 << "Jaszbereny\nAprajafalva\n";
      EXPECT_THROW(m.vasarolJegy(bemenet4),std::runtime_error&);

      bemenet5 << "Budapest\nNagyvarad\nT7J9O\n1\n";
      EXPECT_THROW(m.vasarolJegy(bemenet5),std::runtime_error&);
    }
    END

    TEST(Mav,rendezjegyAr)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      m.rendezJegyAr();
      std::stringstream kimenet,bemenet;
      bemenet << "1\n";
      m.torolJegy(bemenet);
      m.kiirJegyek(kimenet);
      EXPECT_STREQ("Vonatszam: C0HGI\nKocsi: 3\nHely: 1\nJaszbereny -> Budapest\nJegy ara: 3000Ft\n\n",kimenet.str().c_str());
    }
    END

    TEST(Mav,torolVonat)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream bemenet;
      bemenet << "Budapest\nNagyvarad\nT7J9O\n2\n";
      m.vasarolJegy(bemenet);

      
      bemenet << "C0HGI\n";
      m.torolVonat(bemenet);
      EXPECT_EQ(1,m.jegyekSzama());
      EXPECT_THROW(m.getVonat(3),std::out_of_range&);
      bemenet << "asd\n";
      EXPECT_THROW(m.torolVonat(bemenet),std::runtime_error&);
    }
    END

    TEST(Mav,valtoztatAllomasok)
    {
      Mav m;
      std::ifstream fin("be.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream bemenet;
      bemenet << "Budapest\nNagyvarad\nT7J9O\n2\n";
      m.vasarolJegy(bemenet);

      
      bemenet << "asd\n";
      EXPECT_THROW(m.valtoztatAllomasok(bemenet),std::runtime_error&);

      bemenet << "C0HGI\n4\na\nb\nc\nd\n";
      m.valtoztatAllomasok(bemenet);

      bemenet << "T7J9O\na\nb\n";
      m.valtoztatAllomasok(bemenet);
      EXPECT_EQ(0,m.jegyekSzama());

      bemenet << "C0HGI\n2\n";
      EXPECT_THROW(m.valtoztatAllomasok(bemenet),std::runtime_error&);

    }
    END

    TEST(Mav,mentes)
    {
      Mav m;
      std::ifstream fin("be2.txt");
      m.betoltAdatbazis(fin);
      fin.close();

      std::stringstream kimenet;
      m.mentes(kimenet);
      EXPECT_STREQ("2 1\n0 Tu8O\n0 10 3000 1500\n1 1 1 1 2 2 2 2 \n5\nBudapest\nJeszberny\nBalaton\nNagyvarad\nMarosvasarhely\n\n1 T7J9O\n3 7 4000 1500\n2 10 23 10 2 11 1 20 \nBudapest\nNagyvarad\n\nT7J9O\n1\n1\nBudapest\nNagyvarad\n4000\n\n"
        ,kimenet.str().c_str());
    }
    END

    TEST(Menu,Menu osztaly)
    {
      std::stringstream bemenet;
      bemenet << "1\n1\n1\n3\n2\ndsad\ndfsdf\n3\nhfgh\n4\n0\n5\ndgdg\n6\ngfh\n7\nhgf\n8\n9\n10\nfgh\n";
      bemenet << "11\nfghf\n12\n13\n14\n19\n15\n";
      bemenet << "1\n3\n2\n15\nbe\n15\nujadatbazis\n4\n3\n";
      Menu menu(bemenet,true);
      menu.fociklus();
      EXPECT_EQ(kilep,menu.getAllapot());
      remove("ujadatbazis.txt");

      bemenet << "1\n1\n15\n3\n";
      Menu menu2(bemenet);
      menu2.fociklus();
      EXPECT_EQ(kilep,menu2.getAllapot());

      bemenet << "";
    }
    END
}