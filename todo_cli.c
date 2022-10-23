#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
/*
    Todo_cli.c is een programma dat bedoelt is om dagelijks een lijst bij te houden met taken.
    todo_cli genereert een score gebasseerd op het aantal geslaagde taken.
    Het maakt gebruik van invoer.
*/

/*Deze functie vraagt de gebruiker om invoer.
 * */
void vraag_lijst(void) {
    char toets;
    char taak[300];
    for (int i = 0; i < (int)sizeof(taak); i++) {
        taak[i] = 0;
    }
    int i = 0;

    printw("Noem een taak:\n");
    while (toets != '\n') {
        toets = getch();
        if (toets != (char)KEY_BACKSPACE || toets != '\n') {
            taak[i] = toets;
            printw("%c", toets);
        }
        else if (toets == (char)KEY_BACKSPACE && i != 0) {
            i--;
            printw("jajas");
            taak[i] = '0';
            clear();
            for (int j = 0; j < (int)sizeof(taak); j++) {
                printw("%c", taak[j]);
                if (taak[j] == '0'){
                    break;
                }
            }
        }
        
        i++;
    }
    clear();
    printw("klaar");
    getch();
}

int main(void) {
    initscr();
    noecho();
    clear();
    keypad(stdscr, true);
    vraag_lijst(); 
    endwin();
    return 0;
}
