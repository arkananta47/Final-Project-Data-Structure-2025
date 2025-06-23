#ifndef KOMPONEN_H
#define KOMPONEN_H

#define FILE_NAME "data_komponen.bin"

typedef struct {
    char kode[7];
    char nama[26];
    int stok;
    float harga;
} Komponen;

void simpan_komponen(Komponen *);
void tampil_semua(int);
int ubah_komponen(const char*, Komponen *);
int hapus_komponen(const char*);
void input_komponen(Komponen *);

#endif
