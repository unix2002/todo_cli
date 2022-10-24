#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <assert.h>
#include <time.h>
/*
    Todo_cli.c is een programma dat bedoelt is om dagelijks een lijst bij te houden met taken.
    todo_cli genereert een score gebasseerd op het aantal geslaagde taken.
    Het maakt gebruik van invoer.
*/

union taak_num {
    int datum;
    int score;
};

struct taak_item {
    char *taak_zin;
    union taak_num taaknum;
};

typedef struct taak_item taak_item;

/*Deze functie vraagt de gebruiker om invoer.
 * */
char *vraag_lijst(void) {
    char toets;
    char *taak = malloc(300*sizeof(int));
    
    for (int i = 0; i < (int)(300*sizeof(int)); i++) {
        taak[i] = 0;
    }

    int i = 0;
    printw("Noem een taak:\n");
    while (toets != '\n') {
        toets = getch();
        taak[i] = toets;
        printw("%c", toets);
        i++;
    }
    return taak;
}

taak_item *maak_taak_struct(char *taak, int datum, int score) {
    static taak_item task;
    task.taaknum.datum = datum;
    task.taaknum.score = score;
    task.taak_zin = taak;
    return &task;
}

/*Deze functie print de inhoud van een array
*/
void print_array(char ar[]) {
    for (int i = 0; i < (int)(300*sizeof(int)); i++) {
        printw("%c", ar[i]);
    }
}

int score_vraag(void) {
    char toets;
    int score;    
    int valide_invoer = 0;
    toets = 0;

    while (toets != '\n') {
        printw("Wat is de prioriteit van 1 tot 10?\n");
        toets = getch();
        if (48 < toets && toets < 58) {
            score = toets;
            valide_invoer = 1;
            break;
        }
    }
    if (valide_invoer == 0) {
        printw("error, invalide invoer");
        getch();
        exit(1);
    }
    return score;
}

int main(void) {
    initscr();
    noecho();
    clear();
    keypad(stdscr, true);

    char *taak = vraag_lijst(); 
    //print_array(taak);
    
    int datum = 20;
    //int datum = datum_vraag();

    int score = score_vraag();
    taak_item *taakje = maak_taak_struct(taak, datum, score);
    clear(); 
    printw("%d", taakje->taaknum.score-48);
    getch();

    endwin();
    free(taak);
    return 0;
}