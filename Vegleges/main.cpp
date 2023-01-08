#include "teszteles.h"
#include "menu.h"

#include "memtrace.h"

//#define TESZTELES

int main()
{
#ifndef TESZTELES
    Menu menu;
    menu.fociklus();
#endif

#ifdef CPORTA
    tesztekFuttatasa();
#endif
}