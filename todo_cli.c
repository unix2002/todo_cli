#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <assert.h>
#include <time.h>
#include <string.h>
/*
    Todo_cli.c is een programma dat bedoelt is om dagelijks een lijst bij te houden met taken.
    todo_cli genereert een score gebasseerd op het aantal geslaagde taken.
    Het maakt gebruik van invoer.
*/

// Union zorgt dat de twee variabelen hetzelfde geheugenadress delen.
struct taak_num {
    char *datum;
    int score;
};

struct taak_item {
    char *taak_zin;
    struct taak_num taaknum;
};

typedef struct taak_item taak_item;

/*
Deze functie vraagt de gebruiker om invoer.
*/
char *vraag_lijst(void) {
    int toets;
    size_t grootte = 300*sizeof(int);    
    char *taak = malloc(grootte);

    for (int i = 0; i < (int)grootte; i++) {
        taak[i] = 0;
    }
        
    int i = 0;
    printw("Noem een taak:\n");
    while (toets != '\n') {
        toets = getch();
        if ((int)toets == 263) {
            if (taak[i] != 0) {
                taak[i] = 0;
                break;
            }
        }

        taak[i] = toets;
        printw("%c", toets);
        i++;
    }
    return taak;
}

/*
Deze functie print de inhoud van een array
*/
void print_array(char ar[]) {
    int i = 0;
    while (ar[i] != '\n') {
        printw("%c", ar[i]);
        i++;
    }
    printw("\n");
}

/*Deze functie vraagt de prioriteitsscore aan de gebruiker.
Invoer: void.
Uitvoer: de score.
*/
int score_vraag(void) {
    int toets;
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

/*Deze functie initialiseert ncurses.*/
void init_ncurses(void) {
    initscr();
    noecho();
    clear();
    keypad(stdscr, true);
}

/*
Deze functie organiseert de taken als enkele speciale variabele,
*/
taak_item *maak_taak(char *datum_str, char *taak_zin){
    static taak_item task;
    time_t d;
    time(&d);
    task.taak_zin = taak_zin;
    task.taaknum.datum = ctime(&d);
    task.taaknum.score = score_vraag()-48;
    return &task; 
}

/*Print alle info in de taak op een overzichtelijke manier.*/
void print_taak(taak_item *taak) {    
    clear();
    printw("Score: %d\n", taak->taaknum.score);
    printw("De taak is: ");
    print_array(taak->taak_zin);
    printw("Datum: %s", taak->taaknum.datum);
    getch();
}

int main(void) {
    init_ncurses();
    char *datum_str = malloc(sizeof(time_t));
    char *taak_zin = vraag_lijst();
 
    taak_item *taak_een = maak_taak(datum_str, taak_zin);

    print_taak(taak_een);

    endwin();
    free(datum_str);
    free(taak_zin);
    return 0;
}
