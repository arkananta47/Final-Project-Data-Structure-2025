#ifndef _UI_H
#define _UI_H

#ifdef __WIN32
#include <conio.h>
#include <windows.h>

#define CLEAR_SCREEN "cls"
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ENTER 13
#define ESC 27

#else

#include <termios.h>
#include <unistd.h>

#define CLEAR_SCREEN "clear"
#define ARROW_UP 65
#define ARROW_DOWN 66
#define ENTER 10
#define ESCAPE 27

#define SET_COLOR "\033[1;7m"
#define RESET_COLOR "\033[0m"

#endif

#define MAX_MENU_ITEM 6

#ifndef __WIN32
void disableRawMode();
void enableRawMode();
int getch();
#endif
void clearScreen();
void displayMenu(int selected);
int getMenuChoice();

extern const char *menuItems[MAX_MENU_ITEM];

#endif
