#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <assert.h>
#include <time.h>
#include <string.h>
//#include "ui.c"
/*
    Todo_cli.c is een programma dat bedoelt is om dagelijks een lijst bij te houden met taken.
    todo_cli genereert een score gebasseerd op het aantal geslaagde taken.
    Het maakt gebruik van invoer.
*/

int AANTAL_TAKEN = 4;

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
char **vraag_lijst(void) {
    int toets;
    size_t grootte = 300*sizeof(int);
    char **taken_str_lijst = malloc(AANTAL_TAKEN*sizeof(int)*300);

    for (int j = 0; j < AANTAL_TAKEN; j++) {      
       taken_str_lijst[j] = malloc(grootte);
        for (int i = 0; i < (int)grootte; i++) {
            taken_str_lijst[j][i] = 0;
        }

        int a = 0;
        while (toets != '\n') {
            printw("Noem een taak:\n");
            toets = getch();
            if ((int)toets == KEY_BACKSPACE) {
                if (taken_str_lijst[j][a] != 0) {
                    taken_str_lijst[j][a] = 0;
                    delch();
                    break;
                }
            }
            taken_str_lijst[j][a] = toets;
            printw("%c", toets);
            a++;
        }
    }
    return taken_str_lijst;
}

/*
Deze functie bevrijd het geheugen dat gebruikt wordt in de maak_lijst array.
Daarmee doel ik specifiek op de "taken_str_lijst" array.
*/
void free_lijst(char **taken) {
    for (int i = 0; i < AANTAL_TAKEN; i++) {
        free(taken[i]);
    }
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
        endwin();
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
taak_item *maak_taak(char *datum_str, char *taak_zin) {
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

taak_item *maak_item_array(void) {

    taak_item *taken_array = malloc(10*sizeof(taak_item));
    char **taken_str_lijst = vraag_lijst();

    for (int i = 0; i < AANTAL_TAKEN; i++) {
        taak_item *taak = maak_taak(malloc(sizeof(time_t)), taken_str_lijst[i]);
        taken_array[i] = *taak;
    }
    free(taken_str_lijst);
    return taken_array;
}

void free_item_array(taak_item* taken_array) {
    
    for(int i = 0; i < AANTAL_TAKEN; i++) {
        free(taken_array[i].taaknum.datum);
    }
    free(taken_array[AANTAL_TAKEN].taak_zin);
}

int main(void) {
    
    init_ncurses();
    taak_item *taken_item = maak_item_array();
    
    for(int i; i < AANTAL_TAKEN; i++) {
        free(taken_item[i].taak_zin);
        free(taken_item[i].taaknum.datum);
    }
    free(taken_item);

    endwin();
    return 0;
}