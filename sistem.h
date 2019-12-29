#ifndef SISTEM_H
#define SISTEM_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "dosya.h"
#include "ilan_sahibi.h"
#include "defines.h"

using namespace std;

class sistem
{
    public:
        sistem();
        void calistir(void);
        void temizle(void);
        void menu(void);
        void yeni_kayit(void);
        void arama(void);
        void cikis(void);
    private:

        void emlak_turu(void);
        void konut(void);
        void isyeri(void);
        void arsa(void);
        stringstream arama_ilan_nolari;
        int arama_nolari_sayac;

        void dosyalarda_arama(string aranacak_bilgi, string aranan);

        int kayit_sayisi;
        ilan_sahibi _ilan_sahibi;
};

#endif // EKRAN_H
