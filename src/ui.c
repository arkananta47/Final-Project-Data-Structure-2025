#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

const char *menuItems[MAX_MENU_ITEM] = {
    "Menambah data",
    "Mengubah data",
    "Menampilkan semua data dengan index",
    "Menampilkan semua data tanpa index",
    "Hapus data",
    "Keluar"
};

#ifdef __WIN32
#define SET_COLOR ""
#define RESET_COLOR ""
#define ESCAPE 27
#endif

#ifndef __WIN32
struct termios sterm;
void disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &sterm); }

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &sterm);
    atexit(disableRawMode);

    struct termios raw = sterm;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int getch() {
    int ch = getchar();
    // ESC seq
    if (ch == 27) {
        ch = getchar();
        // [
        if (ch == 91) {
            ch = getchar();
            return ch;
        }
    }
    return ch;
}
#endif

void clearScreen() { system(CLEAR_SCREEN); }

void displayMenu(int selected) {
    clearScreen();
    printf("╔══════════════════════════════════╗\n");
    printf("║           MENU UTAMA             ║\n");
    printf("╚══════════════════════════════════╝\n\n");

    for (int i = 0; i < MAX_MENU_ITEM; i++) {
        if (i == selected) {
            printf(" %s%d. %s%s\n", SET_COLOR, i + 1, menuItems[i], RESET_COLOR);
        } else {
            printf("   %d. %s\n", i + 1, menuItems[i]);
        }
    }
}

int getMenuChoice() {
#ifndef __WIN32
    enableRawMode();
#endif

    int selected = 0;
    int ch;

    while (1) {
        displayMenu(selected);
#ifdef __WIN32
        ch = _getch();
        if (ch == 224) {
            ch = _getch();
        }
#else
        ch = getch();
#endif

        switch (ch) {
        case ARROW_UP:
            selected = (selected - 1 + MAX_MENU_ITEM) % MAX_MENU_ITEM;
            break;
        case ARROW_DOWN:
            selected = (selected + 1) % MAX_MENU_ITEM;
            break;
        case ENTER:
#ifndef __WIN32
            disableRawMode();
#endif
            return selected + 1;
        case ESCAPE:
#ifndef __WIN32
            disableRawMode();
#endif
            return 6;
        case 'q':
        case 'Q':
#ifndef __WIN32
            disableRawMode();
#endif
            return 6;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
            selected = ch - '0' - 1;
            break;
        default:
            break;
        }
    }
}
