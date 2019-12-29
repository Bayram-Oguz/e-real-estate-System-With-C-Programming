#include "ilan_sahibi.h"

ilan_sahibi::ilan_sahibi()
{
    _ad_soyad = "Henuz girilmemis.";
    _kayit_tarihi = "Henuz girilmemis.";
    _adres = "Henuz girilmemis.";
    _cep_tel = "Henuz girilmemis.";
    _email = "Henuz girilmemis.";
}

state ilan_sahibi::ad_soyad(string adsoyad)
{
    // Ad ya da soyad girilmediyse.
    if(adsoyad == "")
    {
        return hata;
    }

    _ad_soyad = adsoyad;
    return ok;
}

string ilan_sahibi::kayit_tarihi(void)
{
    time_t     suan = time(0);
    struct tm  t;
    char       hafiza[20];
    t = *localtime(&suan);

    strftime(hafiza, 20, "%d-%m-%Y %X", &t);

    _kayit_tarihi = string(hafiza);

    return _kayit_tarihi;
}


state ilan_sahibi::adres(string adres)
{
    // Adres girilmediyse.
    if(adres == "")
    {
        return hata;
    }
    _adres = adres;
    return ok;
}

state ilan_sahibi::cep_tel(string cep)
{
    int tel_hane_sayisi;
    // Ilk hane sifir olarak girildiginde.
    if(cep[0] == '0')
    {
        tel_hane_sayisi = cep.size();
    }
    else
    {
        tel_hane_sayisi = cep.size();
        ++tel_hane_sayisi;
    }
    // Cep telefonu numarasi 11 haneli olmali.
    if(tel_hane_sayisi != 11)
    {
        return hata;
    }
    _cep_tel = cep;
    return ok;
}

state ilan_sahibi::email(string email)
{
    _email = email;
    return ok;
}

void ilan_sahibi::dosyaya_yaz(dosya& dosya_obje)
{

    dosya_obje.yaz("--------------------------------------------------");
    dosya_obje.yaz("                  Ilan Sahibi                     ");
    dosya_obje.yaz("--------------------------------------------------");
    dosya_obje.yaz("Kayit Tarihi:" + _kayit_tarihi);
    dosya_obje.yaz("--------------------------------------------------");
    dosya_obje.yaz("Ad Soyad:" + _ad_soyad);
    dosya_obje.yaz("--------------------------------------------------");
    dosya_obje.yaz("Adres:" + _adres);
    dosya_obje.yaz("--------------------------------------------------");
    dosya_obje.yaz("Email:" + _email);
    dosya_obje.yaz("--------------------------------------------------");
    dosya_obje.yaz("Cep Telefonu:" + _cep_tel);

}

ilan_sahibi::~ilan_sahibi()
{
    //dtor
}
