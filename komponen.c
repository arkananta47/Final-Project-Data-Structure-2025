#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "komponen.h"

#define FILE_NAME "data_komponen.bin"

void simpan_komponen(Komponen k) {
    FILE *fp = fopen(FILE_NAME, "ab");
    fwrite(&k, sizeof(Komponen), 1, fp);
    fclose(fp);
}

void tampil_semua(int dengan_index) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("Data belum tersedia.\n");
        return;
    }

    Komponen k;
    int i = 0;
    float total = 0;
    while (fread(&k, sizeof(Komponen), 1, fp)) {
        if (dengan_index) printf("[%02d] ", i);
        printf("Kode: %s | Nama: %s | Stok: %d | Harga: %.2f\n", k.kode, k.nama, k.stok, k.harga);
        total += k.stok * k.harga;
        i++;
        if (i % 10 == 0) {
            printf("Tekan enter untuk lanjut...\n");
            getchar();
        }
    }
    printf("Total nilai aset: %.2f\n", total);
    fclose(fp);
}

int ubah_komponen(const char *kode_target, Komponen k_baru) {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) return 0;

    Komponen k;
    while (fread(&k, sizeof(Komponen), 1, fp)) {
        if (strcmp(k.kode, kode_target) == 0) {
            fseek(fp, -sizeof(Komponen), SEEK_CUR);
            fwrite(&k_baru, sizeof(Komponen), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int hapus_komponen(const char *kode_target) {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.bin", "wb");
    int found = 0;
    Komponen k;

    while (fread(&k, sizeof(Komponen), 1, fp)) {
        if (strcmp(k.kode, kode_target) == 0) {
            found = 1;
            continue;
        }
        fwrite(&k, sizeof(Komponen), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.bin", FILE_NAME);
    return found;
}