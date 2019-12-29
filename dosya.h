#ifndef DOSYA_H
#define DOSYA_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "defines.h"

using namespace std;

class dosya
{
    public:
        dosya(string dosya_adi);
        state yaz(string metin);
        string bilgi_oku(string okunacak_bilgi);
        void bilgi_degistir(string degistirilecek_bilgi, string yeni_bilgi);
        void tumunu_yazdir(void);
        bool bos_mu(void);
        virtual ~dosya();
    private:
        ofstream _odosya;
        ifstream _idosya;
        string _dosya_adi;
};

#endif // DOSYA_H
