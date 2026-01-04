#include <stdio.h>

#define MAX 100

// Diziyi ekrana yazdýran fonksiyon
void yazdir(int dizi[], int n) {
    int i;
    printf("Dizi: ");
    for (i = 0; i < n; i++) {
        printf("%d ", dizi[i]);
    }
    printf("\n");
}

// Diziyi tersine çeviren fonksiyon
void tersCevir(int dizi[], int n) {
    int i, temp;
    for (i = 0; i < n / 2; i++) {
        temp = dizi[i];
        dizi[i] = dizi[n - 1 - i];
        dizi[n - 1 - i] = temp;
    }
}

// Diziye eleman ekleme (sona ekler)
void elemanEkle(int dizi[], int *n, int eleman) {
    if (*n >= MAX) {
        printf("Dizi dolu! Eleman eklenemez.\n");
        return;
    }
    dizi[*n] = eleman;
    (*n)++;
}

// Diziden eleman silme (indise göre)
void elemanSil(int dizi[], int *n, int indeks) {
    int i;
    if (indeks < 0 || indeks >= *n) {
        printf("Gecersiz indeks!\n");
        return;
    }
    for (i = indeks; i < *n - 1; i++) {
        dizi[i] = dizi[i + 1];
    }
    (*n)--;
}

int main() {
    int dizi[MAX];
    int n, i;
    int secim, eleman, indeks;

    printf("Dizi eleman sayisini girin: ");
    scanf("%d", &n);

    // Güvenlik: n MAX'i aþmasýn
    if (n < 0 || n > MAX) {
        printf("Gecersiz eleman sayisi! (0-%d arasi olmali)\n", MAX);
        return 0;
    }

    printf("Dizi elemanlarini girin:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &dizi[i]);
    }

    do {
        printf("\n--- MENU ---\n");
        printf("1 - Diziyi Yazdir\n");
        printf("2 - Diziye Eleman Ekle\n");
        printf("3 - Diziden Eleman Sil\n");
        printf("4 - Diziyi Tersine Cevir\n");
        printf("0 - Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                yazdir(dizi, n);
                break;

            case 2:
                printf("Eklenecek elemani girin: ");
                scanf("%d", &eleman);
                elemanEkle(dizi, &n, eleman);
                break;

            case 3:
                printf("Silinecek elemanin indeksini girin (0-%d): ", n - 1);
                scanf("%d", &indeks);
                elemanSil(dizi, &n, indeks);
                break;

            case 4:
                tersCevir(dizi, n);
                printf("Dizi tersine cevrildi.\n");
                break;

            case 0:
                printf("Programdan cikiliyor...\n");
                break;

            default:
                printf("Gecersiz secim!\n");
        }

    } while (secim != 0);

    return 0;
}

