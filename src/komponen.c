#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "komponen.h"

void simpan_komponen(Komponen *k) {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        fprintf(stderr, "ERROR: failed to open file %s: %s\n", FILE_NAME, strerror(errno));
        return;
    }
    fwrite(k, sizeof(Komponen), 1, fp);
    fclose(fp);
}

void tampil_semua(int dengan_index) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("Data belum tersedia.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    int jumlah = size / sizeof(Komponen);

    Komponen *list = malloc(sizeof(Komponen) * jumlah);
    if (!list) {
        printf("Gagal alokasi memori.\n");
        fclose(fp);
        return;
    }

    fread(list, sizeof(Komponen), jumlah, fp);
    fclose(fp);

    if (dengan_index) {
        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = i + 1; j < jumlah; j++) {
                if (strcmp(list[i].kode, list[j].kode) > 0) {
                    Komponen temp = list[i];
                    list[i] = list[j];
                    list[j] = temp;
                }
            }
        }
    }

    float total = 0;
    for (int i = 0; i < jumlah; i++) {
        if (dengan_index)
            printf("[%s] ", list[i].kode);
        printf("Kode: %s | Nama: %s | Stok: %d | Harga: %.2f\n",
               list[i].kode, list[i].nama, list[i].stok, list[i].harga);
        total += list[i].stok * list[i].harga;

        if ((i + 1) % 10 == 0) {
            printf("Tekan enter untuk lanjut...\n");
            getchar();
        }
    }

    printf("Total nilai aset: %.2f\n", total);
    free(list);
}

int ubah_komponen(const char *kode_target, Komponen *k_baru) {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) return 0;

    Komponen k;
    while (fread(&k, sizeof(Komponen), 1, fp)) {
        if (strcmp(k.kode, kode_target) == 0) {
            fseek(fp, -sizeof(Komponen), SEEK_CUR);
            fwrite(k_baru, sizeof(Komponen), 1, fp);
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
    if (!fp || !temp) {
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return 0;
    }

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
