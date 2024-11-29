#include <stdio.h>

// Öğrenci bilgilerini tutacak yapı tanımı
typedef struct {        //struct fonksiyonun başında "typdef" kullanmamızın sebebi struct fonksiyonumuza "Ogrenci" takma adını tanımlamak ve her çağırışımızda tekrar struct yazmamaktır aynı zamanda kodun okunabilirliği ve yazım kolaylığını bize sağlamış olur
    int vize;           // Vize notunu tutar
    int final;          // Final notunu tutar
    float toplam;       // Vize ve finalden hesaplanan toplam not
    char harf_notu[3];  // Öğrencinin aldığı harf notunu tutar (örneğin: "AA", "BA")
    char durum[20];     // Geçme durumu: "Gecti", "Kaldi" veya "Sartli Gecti"
} Ogrenci;              //tüm öğrenci verilerini bir arada tutabilmek amacıyla struct fonksiyonumuza verdiğimiz bu takma ad ile hem bize yazım kolaylığı sağlar hem de diğer fonksiyonlarda çağırma kolaylığı sağlar

// Fonksiyonların prototipleri  ty                 //bu değişkenlerle işlem yapılacağı için void fonksiyonuyla dışarda atama işlemi yaptık
void ogrenciSayisiAl(int *ogrenci_sayisi);        // Kullanıcıdan geçerli öğrenci sayısını almak için
void notlariAl(Ogrenci *ogrenci);                // Bir öğrencinin vize ve final notlarını almak için
void hesaplaDurumVeHarfNotu(Ogrenci *ogrenci);   // Bir öğrencinin toplam notunu hesaplamak ve durumunu belirlemek için
void sonucYazdir(Ogrenci ogrenciler[], int ogrenci_sayisi); // Tüm öğrencilerin sonuçlarını topluca yazdırmak için

// Ana program
int main()
{
    int ogrenci_sayisi; // Kullanıcıdan alınacak toplam öğrenci sayısı

    // Kullanıcıdan öğrenci sayısını al
    ogrenciSayisiAl(&ogrenci_sayisi);

    // Öğrencilerin bilgilerini tutacak dizi
    Ogrenci ogrenciler[ogrenci_sayisi];

    // Her öğrenci için notları al ve durumu hesapla
    for (int i = 0; i < ogrenci_sayisi; i++) {
        printf("\n%d. Ogrencinin bilgilerini giriniz:\n", i + 1);
        notlariAl(&ogrenciler[i]);              // Öğrencinin notlarını al
        hesaplaDurumVeHarfNotu(&ogrenciler[i]); // Harf notunu ve geçme durumunu hesapla
    }

    // Tüm öğrencilerin sonuçlarını yazdır
    sonucYazdir(ogrenciler, ogrenci_sayisi);

    return 0; // Program başarıyla tamamlandı
}

// Kullanıcıdan geçerli öğrenci sayısını alma fonksiyonu
void ogrenciSayisiAl(int *ogrenci_sayisi)
{
    int kontrol; // Kullanıcının girdiğinin sayısal olup olmadığını kontrol etmek için
    printf("\nOgrenci sayisini giriniz: ");
    while (1)
    {
        kontrol = scanf("%d", ogrenci_sayisi); // Kullanıcı girişi alınıyor

        // Eğer sayı girilmediyse veya sayı sıfırdan küçükse
        if (kontrol != 1 || *ogrenci_sayisi <= 0) {
            printf("Lutfen gecerli bir ogrenci sayisi giriniz.\n");
            while (getchar() != '\n'); // Hatalı giriş varsa tamponu temizle
        } else {
            break; // Geçerli bir sayı girildiyse döngüden çık
        }
    }
}

// Bir öğrencinin vize ve final notlarını alma fonksiyonu
void notlariAl(Ogrenci *ogrenci)
{
    int kontrol; // Kullanıcının geçerli bir sayı girip girmediğini kontrol etmek için

    // Vize notu alma
    printf("Vize notunu giriniz: ");
    while (1)
    {
        kontrol = scanf("%d", &ogrenci->vize); // Vize notunu kullanıcıdan al
        if (kontrol != 1 || ogrenci->vize < 0 || ogrenci->vize > 100) {
            printf("Lutfen 0 ile 100 arasinda gecerli bir not giriniz.\n");
            while (getchar() != '\n'); // Hatalı giriş varsa tamponu temizle
        } else {
            break; // Geçerli bir not girildiyse döngüden çık
        }
    }

    // Final notu alma
    printf("Final notunu giriniz: ");
    while (1)
    {
        kontrol = scanf("%d", &ogrenci->final); // Final notunu kullanıcıdan al
        if (kontrol != 1 || ogrenci->final < 0 || ogrenci->final > 100) {
            printf("Lutfen 0 ile 100 arasinda gecerli bir not giriniz.\n");
            while (getchar() != '\n'); // Hatalı giriş varsa tamponu temizle
        } else {
            break; // Geçerli bir not girildiyse döngüden çık
        }
    }
}

// Öğrencinin toplam notunu hesaplayan ve durumunu belirleyen fonksiyon
void hesaplaDurumVeHarfNotu(Ogrenci *ogrenci)
{
    // Toplam notu hesapla (Vize %40, Final %60)
    ogrenci->toplam = (ogrenci->vize * 0.4) + (ogrenci->final * 0.6);

    // Toplam nota göre harf notunu ve durumunu belirle
    if (ogrenci->toplam >= 90) {                        //sprintf amacı "ogrenci" adındaki bir "struct" yapısının "harf_notu" alanına "AA" stringini kaydetmektir.
        sprintf(ogrenci->harf_notu, "AA");           //"sprintf" komudu bir string oluştururken bu stiringi doğrudan bir değişkene 
        sprintf(ogrenci->durum, "Gecti");           //yazmak için kullanılır 
    } else if (ogrenci->toplam >= 80) {           
        sprintf(ogrenci->harf_notu, "BA");       //birden falza değişkeni bir string de birleştirmek ya da belirli bir biçimde
        sprintf(ogrenci->durum, "Gecti");       //string oluşturmak gerektiğinde kullanılır. Örneğin;
    } else if (ogrenci->toplam >= 70) {        //snprintf(harf_notu, sizeof(harf_notu), "%s", "AA"); komuduyla harf_notu değişkenine "AA" stringi atanabilir
        sprintf(ogrenci->harf_notu, "BB");      
        sprintf(ogrenci->durum, "Gecti");
    } else if (ogrenci->toplam >= 60) {
        sprintf(ogrenci->harf_notu, "CB");
        sprintf(ogrenci->durum, "Gecti");
    } else if (ogrenci->toplam >= 50) {
        sprintf(ogrenci->harf_notu, "CC");
        sprintf(ogrenci->durum, "Gecti");
    } else if (ogrenci->toplam >= 40) {
        sprintf(ogrenci->harf_notu, "DC");
        sprintf(ogrenci->durum, "Sartli Gecti");
    } else if (ogrenci->toplam >= 30) {
        sprintf(ogrenci->harf_notu, "DD");
        sprintf(ogrenci->durum, "Kaldi");
    } else if (ogrenci->toplam >= 20)
    {
        sprintf(ogrenci->harf_notu, "FD");
        sprintf(ogrenci->durum, "Kaldi");
    }
    else
    {
        sprintf(ogrenci->harf_notu, "FF");
        sprintf(ogrenci->durum, "Kaldi");
    }
}

// Tüm öğrencilerin sonuçlarını topluca yazdırma fonksiyonu
void sonucYazdir(Ogrenci ogrenciler[], int ogrenci_sayisi)
{
    printf("\n---------- Ogrencilerin Gecme Durumlari ve Harf Notlari ----------\n");
    // Her bir öğrencinin bilgilerini yazdır
    for (int i = 0; i < ogrenci_sayisi; i++) {
        printf("%d. Ogrencinin toplam notu: %.2f, Harf Notu: %s, Durum: %s\n",
               i + 1, ogrenciler[i].toplam, ogrenciler[i].harf_notu, ogrenciler[i].durum);
    }
}
