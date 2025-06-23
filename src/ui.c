#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <termios.h>
#include <unistd.h>

#define CLEAR_SCREEN "clear"
#define ARROW_UP 65
#define ARROW_DOWN 66
#define ENTER 10
#define ESCAPE 27

#define SET_COLOR "\033[1;7m"
#define RESET_COLOR "\033[0m"

#define MAX_MENU_ITEM 6
#define MAX_STRING_LENGTH 1024

const char *menuItems[MAX_MENU_ITEM] = {"Menambah data", "Mengubah data", "Menampilkan semua data dengan index", "Menampilkan semua data tanpa index", "Hapus data", "Keluar"};

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
    enableRawMode();

    int selected = 0;
    int ch;
    while (1) {
        displayMenu(selected);
        ch = getch();

        switch (ch) {
        case ARROW_UP:
            selected = (selected - 1 + MAX_MENU_ITEM) % MAX_MENU_ITEM;
            break;
        case ARROW_DOWN:
            selected = (selected + 1) % MAX_MENU_ITEM;
            break;
        case ENTER:
            disableRawMode();
            return selected + 1;
        case ESCAPE:
            disableRawMode();
            return 6;
        case 'q':
        case 'Q':
            disableRawMode();
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

void addData() {
    clearScreen();
    printf("Ini addData\n");
    printf("Tekan Enter untuk kembali...");
    getchar();
}

void editData() {
    clearScreen();
    printf("Ini editData\n");
    printf("Tekan Enter untuk kembali...");
    getchar();
}

void displayData(int withIndex) {
    clearScreen();
    printf("Ini displayData dengan index: %d\n", withIndex);
    printf("Tekan Enter untuk kembali...");
    getchar();
}

void deleteData() {
    clearScreen();
    printf("Ini deleteData\n");
    printf("Tekan Enter untuk kembali...");
    getchar();
}

int main() {
    int choice;

    while (1) {
        choice = getMenuChoice();
        switch (choice) {
        case 1:
            addData();
            break;
        case 2:
            editData();
            break;
        case 3:
            displayData(1);
            break;
        case 4:
            displayData(1);
            break;
        case 5:
            deleteData();
            break;
        case 6:
            clearScreen();
            printf("Exiting\n");
            return 0;
        default:
            break;
        }
    }

    return 0;
}
