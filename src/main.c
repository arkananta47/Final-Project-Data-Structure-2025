#include "komponen.h"
#include "ui.h"
#include <stdio.h>

int main() {
    int choice;

    while (1) {
        choice = getMenuChoice();

        if (choice == 1) {
            clearScreen();
            Komponen k;
            input_komponen(&k);
            simpan_komponen(&k);

        } else if (choice == 2) {
            clearScreen();
            Komponen k;
            char kode[7];
            printf("Masukkan kode komponen yang ingin diubah: ");
            scanf("%6s", kode);
            printf("Masukkan data baru:\n");
            input_komponen(&k);
            if (!ubah_komponen(kode, &k))
                printf("Data tidak ditemukan.\n");

        } else if (choice == 3) {
            clearScreen();
            tampil_semua(1);

        } else if (choice == 4) {
            clearScreen();
            tampil_semua(0);

        } else if (choice == 5) {
            clearScreen();
            char kode[7];
            printf("Masukkan kode komponen yang ingin dihapus: ");
            scanf("%6s", kode);
            if (!hapus_komponen(kode))
                printf("Data tidak ditemukan.\n");
        } else if (choice == 6) {
            clearScreen();
            printf("Exiting\n");
            return 0;
        } else {
            fprintf(stderr, "Pilihan tidak valid\n");
        }
    }
    return 0;
}
