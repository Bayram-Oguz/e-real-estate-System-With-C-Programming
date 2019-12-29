#include "dosya.h"

dosya::dosya(string dosya_adi)
{
    // Dosya adinin sonun .txt eklenmesi.
    _dosya_adi = dosya_adi;

    // Daha once boyle bir dosya olusturuldu mu
    _idosya.open(_dosya_adi.c_str(), ios::in);

    string kontrol;
    getline(_idosya, kontrol);
    _idosya.close();

    // Olusturulmadı ise olustur.
    if(kontrol == "")
    {
        // Dosyanin acilmasi.
        _odosya.open(_dosya_adi.c_str());
        _odosya.close();
    }
}

state dosya::yaz(string metin)
{
    // Dosyanin append modunda acilmasi
    _odosya.open(_dosya_adi.c_str(), ios::app);
    if(_odosya.is_open() == false)
    {
        return hata;
    }
    // Dosyaya metinin yazilmasi.
    _odosya << metin << endl;
    // Dosyai kapat.
    _odosya.close();
    return ok;
}

void dosya::bilgi_degistir(string degistirilecek_bilgi, string yeni_bilgi)
{
    string metin;
    ofstream gecici;

    string satir = degistirilecek_bilgi + ':' + bilgi_oku(degistirilecek_bilgi);

    _idosya.open(_dosya_adi.c_str(), ios::in);
    gecici.open("gecici.txt");

    while(getline(_idosya, metin))
    {
        if(metin == satir)
        {
            gecici << degistirilecek_bilgi + ':' + yeni_bilgi << endl;
        }
        else
        {
            gecici << metin << endl;
        }
    }
    gecici.close();
    _idosya.close();
    remove(_dosya_adi.c_str());
    rename("gecici.txt", _dosya_adi.c_str());
}

bool dosya::bos_mu(void)
{
    string satir;
    _idosya.open(_dosya_adi.c_str(), ios::in);
    while(getline(_idosya, satir))
    {
        if(satir != "")
        {
            _idosya.close();
            return false;
        }
    }
    _idosya.close();
    return true;
}

string dosya::bilgi_oku(string okunacak_bilgi)
{
    string metin, bilgi, onemsiz;
    // Dosyanin in modunda acilmasi
    _idosya.open(_dosya_adi.c_str(), ios::in);
    // Satır satır okuma
    while(getline(_idosya, metin))
    {
        stringstream m(metin);
        getline(m, onemsiz, ':');
        if(onemsiz == okunacak_bilgi)
        {
            getline(m, bilgi);
        }
    }
    _idosya.close();

    return bilgi;
}

void dosya::tumunu_yazdir(void)
{
    string satir;
    // Dosyanin in modunda acilmasi
    _idosya.open(_dosya_adi.c_str(), ios::in);

    while(getline(_idosya, satir))
    {
        cout<<satir<<endl;
    }
}

dosya::~dosya()
{
    //dtor
}
