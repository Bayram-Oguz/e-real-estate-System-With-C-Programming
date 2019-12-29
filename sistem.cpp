/**
    @Tarih : 25.12.2016
*/

#include "sistem.h"

dosya emlak("emlak.txt");

sistem::sistem()
{
    arama_nolari_sayac = 0;
    string ks;

    //system("mode con cols=51");

    // Beyaz arka plana siyah font.
    system("COLOR F0");
    // emlak.txt bos olması yani emlak.txt ilk kez
    // olusturuluyor. Bu yuzden henuz hiz kayıt yok.
    if(emlak.bos_mu())
    {
        emlak.yaz("Kayit Sayisi:0");
    }
    ks = emlak.bilgi_oku("Kayit Sayisi");

    kayit_sayisi = atoi(ks.c_str());
    cout<<"Kayit sayiiiii: "<<kayit_sayisi<<endl;
}

void sistem::calistir(void)
{
    menu();
}

void sistem::menu(void)
{
    char secim;
    temizle();
    // Menuyu olustur.
    cout<<"--------------------------------------------------"<<endl;
    cout<<"                  EMLAK SYSTEM                    "<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"                    ANA MENU                      "<<endl;
    cout<<"             ----------------------               "<<endl;
    cout<<"                 A  Yeni Kayit                    "<<endl;
    cout<<"                 B  Arama                         "<<endl;
    cout<<"                 C  Cikis                         "<<endl;
    islem_sece_git:
    cout<<"--------------------------------------------------"<<endl;
    cout<<" Islemi secin: ";
    cin >> secim;
    cout<<"--------------------------------------------------"<<endl;
    switch(secim)
    {
        case 'a':
        case 'A':
            yeni_kayit();
            break;
        case 'b':
        case 'B':
            arama();
            break;
        case 'c':
        case 'C':
            cikis();
            break;
        default:
            cout<<" Hatali Giris!"<<endl;
            goto islem_sece_git;
            break;
    }
}

void sistem::yeni_kayit(void)
{
    stringstream ks;
    ++kayit_sayisi;
    ks << kayit_sayisi;

    string ilan_no = ks.str();

    emlak.bilgi_degistir("Kayit Sayisi", ilan_no);
    dosya yeni_kayit_dosya("ilan_no_" + ilan_no + ".txt");

    yeni_kayit_dosya.yaz("--------------------------------------------------");
    yeni_kayit_dosya.yaz("                  ILAN NO " + ilan_no + "         ");

    temizle();
    string adsoyad, cep_tel, email, adres;
    cout<<"             ----------------------               "<<endl;
    cout<<"                   YENI KAYIT                     "<<endl;
    cout<<"             ----------------------               "<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"                  Ilan Sahibi                     "<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"Kayit Tarihi: "<<_ilan_sahibi.kayit_tarihi()<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"Ad Soyad: "; cin.ignore(); getline(cin, adsoyad, '\n');
    while(_ilan_sahibi.ad_soyad(adsoyad) == hata)
    {
        cout<<"--------------------------------------------------"<<endl;
        cout << "Hata: Bu bolumu bos gecemezsiniz!"<<endl;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"Ad Soyad: "; cin.ignore(); getline(cin, adsoyad, '\n');
    }
    cout<<"--------------------------------------------------"<<endl;
    cout<<"Cep Telefonu: "; cin>>cep_tel;
    while(_ilan_sahibi.cep_tel(cep_tel) == hata)
    {
        cout<<"--------------------------------------------------"<<endl;
        cout << "Hata: Cep telefonunu hatali veya eksik girildi!"<<endl;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"Cep Telefonu: "; cin>>cep_tel;
    }
    cout<<"--------------------------------------------------"<<endl;
    cout<<"Email: "; cin>>email;
    _ilan_sahibi.email(email);
    cout<<"--------------------------------------------------"<<endl;
    cout<<"Adres: "; cin.ignore(); getline(cin, adres, '\n');
    _ilan_sahibi.adres(adres);
    cout<<"--------------------------------------------------"<<endl;
    _ilan_sahibi.dosyaya_yaz(yeni_kayit_dosya);

    // Bir sonraki asamada artık emlak bilgileri girilmeye baslanıcak.
    emlak_turu();
}

void sistem::dosyalarda_arama(string aranacak_bilgi, string aranan)
{
     bool aramada_sonuc_var = false;
    // Filitelemeye il defa baslanmıssa.
    if(arama_nolari_sayac == 0)
    {
        for(int i = 1; i < kayit_sayisi + 1; ++i)
        {
            stringstream ks;
            ks << i;

            dosya arama("ilan_no_" + ks.str() + ".txt");
            if(arama.bilgi_oku(aranacak_bilgi) == aranan)
            {
                aramada_sonuc_var = true;
                cout<<"--------------------------------------------------"<<endl;
                cout<<" Bulundu: Ilan No "<< i <<endl;
                arama_ilan_nolari<<i<<' ';
                ++arama_nolari_sayac;
            }
        }
    }
    // Filitrelenmis doyaların icinden ara.
    else
    {
        string ilan_no;
        int onemsiz = arama_nolari_sayac;
        arama_nolari_sayac = 0;
        for(int i = 0; i < onemsiz; ++i)
        {
            arama_ilan_nolari >> ilan_no;

            dosya arama(" Bulundu: ilan_no_" + ilan_no + ".txt");
            if(arama.bilgi_oku(aranacak_bilgi) == aranan)
            {
                cout<<"--------------------------------------------------"<<endl;
                cout << " Ilan No " << ilan_no << endl;
                arama_ilan_nolari<<ilan_no<<' ';
                ++arama_nolari_sayac;
            }
        }
    }
    if(aramada_sonuc_var == true)
    {
        cout<<"--------------------------------------------------"<<endl;
        cout<< " " <<arama_nolari_sayac<< " tane ilan bulundu."<<endl;
    }
    else if(aramada_sonuc_var == false)
    {
        cout<<"--------------------------------------------------"<<endl;
        cout<<" Sonuc YOK!"<<endl;
    }
}

void sistem::arama(void)
{
    char secici;
    temizle();
    cout<<"             ----------------------               "<<endl;
    cout<<"                     ARAMA                        "<<endl;
    cout<<"             ----------------------               "<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"                 A Ilan Sahibi                    "<<endl;
    cout<<"                 B Emlak Turu                     "<<endl;
    cout<<"                 C Fiyat Araligi                  "<<endl;
    cout<<"                 D Konum (Il - Ilce)              "<<endl;
    cout<<"                 E Isitma Durumu                  "<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"                 T Sonuclari Yazdir               "<<endl;
    cout<<"                 Q Ana Menu                       "<<endl;
    islemi_sece_git:
    cout<<"--------------------------------------------------"<<endl;
    cout<<" Islemi Sec: "; cin>>secici;
    cout<<"--------------------------------------------------"<<endl;

    string adsoyad;
    string emlak_turu;
    string il, ilce;
    string isitma;

    string ilan_no;
    int onemsiz;
    switch(secici)
    {
        case 'a':
        case 'A':
            cout<<" Ilan Sahibinin Adi: "; cin.ignore(); getline(cin, adsoyad, '\n');
            dosyalarda_arama("Ad Soyad" , adsoyad);
            goto islemi_sece_git;
            break;

        case 'b':
        case 'B':
            cout<<" Emlak Turunu Girin: "; cin >> emlak_turu;
            dosyalarda_arama("Emlak Turu", emlak_turu);
            goto islemi_sece_git;
            break;

        case 'd':
        case 'D':
            cout<<" Konumu Girin: "; cin >> il >> ilce;
            dosyalarda_arama("Konum", il + ' ' + ilce);
            goto islemi_sece_git;
            break;

        case 'e':
        case 'E':
            cout<<" Isıtma Tipi: "; cin >> isitma;
            dosyalarda_arama("Isıtma Tipi", isitma);
            goto islemi_sece_git;
            break;

        case 't':
        case 'T':
            onemsiz = arama_nolari_sayac;
            arama_nolari_sayac = 0;
            for(int i = 0; i < onemsiz; ++i)
            {
                arama_ilan_nolari >> ilan_no;

                dosya arama_sonuc("ilan_no_" + ilan_no + ".txt");

                cout<<endl<<endl;
                arama_sonuc.tumunu_yazdir();
            }
            goto islemi_sece_git;
            break;

        case 'q':
        case 'Q':
            arama_ilan_nolari.clear();
            arama_nolari_sayac = 0;
            menu();
            break;
        default:
            cout<<" Hatali Giris!"<<endl;
            goto islemi_sece_git;
            break;
    }
}

void sistem::cikis(void)
{
    exit(0);
}

void sistem::emlak_turu(void)
{
    char secim;
    temizle();
    cout<<"--------------------------------------------------"<<endl;
    cout<<"                    Emlak Turu                    "<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"                     A Konut                      "<<endl;
    cout<<"                     B Isyeri                     "<<endl;
    cout<<"                     C Arsa                       "<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout << " Emlak turunu secin: ";
    cin >> secim;
    switch(secim)
    {
        case 'a':
        case 'A':
            konut(); break;
        case 'b':
        case 'B':
            isyeri(); break;
        case 'c':
        case 'C':
            arsa(); break;
    }
}



void sistem::konut(void)
{
    temizle();
    cout<<"konut secildi";
}

void sistem::isyeri(void)
{

}

void sistem::arsa(void)
{

}



void sistem::temizle(void)
{
    // Ekrani temizle.
    //system("CLS");
}


