#include <stdio.h>
#include <string.h>
#include "komponen.h"

void simpan_komponen(Komponen);
void tampil_semua(int);
int ubah_komponen(const char*, Komponen);
int hapus_komponen(const char*);

void input_komponen(Komponen *k) {
    printf("Masukkan Kode (6 digit): ");
    scanf("%6s", k->kode); getchar();
    printf("Masukkan Nama Komponen: ");
    fgets(k->nama, 26, stdin);
    k->nama[strcspn(k->nama, "\n")] = 0;
    printf("Masukkan Stok: ");
    scanf("%d", &k->stok);
    printf("Masukkan Harga: ");
    scanf("%f", &k->harga);
}

int main(){
    while (1) {
        printf("\n=== Menu Komponen Kendaraan ===\n");
        printf("1. Tambah Data\n");
        printf("2. Ubah Data\n");
        printf("3. Tampil Data (dengan Index)\n");
        printf("4. Tampil Data (tanpa Index)\n");
        printf("5. Hapus Data\n");
        printf("6. Keluar\n");
        printf("Pilih: ");

        int pil;
        scanf("%d", &pil); getchar();
        if (pil == 1) {
            Komponen k;
            input_komponen(&k);
            simpan_komponen(k);
        } else if (pil == 2) {
            Komponen k;
            char kode[7];
            printf("Masukkan kode komponen yang ingin diubah: ");
            scanf("%6s", kode); 
                getchar();
            printf("Masukkan data baru:\n");
            input_komponen(&k);
            if (!ubah_komponen(kode, k))
                printf("Data tidak ditemukan.\n");
        } else if (pil == 3) {
            tampil_semua(1);
        } else if (pil == 4) {
            tampil_semua(0);
        } else if (pil == 5) {
            char kode[7];
            printf("Masukkan kode yang akan dihapus: ");
            scanf("%6s", kode); 
                getchar();
            if (!hapus_komponen(kode))
                printf("Data tidak ditemukan.\n");
        } else if (pil == 6) break;
        else printf("Pilihan tidak valid.\n");
    }

    return 0;
}