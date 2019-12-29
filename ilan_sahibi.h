#ifndef ILAN_SAHIBI_H
#define ILAN_SAHIBI_H

#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include "dosya.h"
#include "defines.h"


using namespace std;

class ilan_sahibi
{
    public:
        ilan_sahibi();
        state ad_soyad(string adsoyad);
        string kayit_tarihi(void);
        state adres(string adres);
        state cep_tel(string cep);
        state email(string email);
        void dosyaya_yaz(dosya& dosya_obje);
        virtual ~ilan_sahibi();
    private:
        string _ad_soyad;
        string _kayit_tarihi;
        string _adres;
        string _cep_tel;
        string _email;
};

#endif // ILAN_SAHIBI_H
