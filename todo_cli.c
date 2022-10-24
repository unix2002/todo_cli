#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
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
        if (toets != 'k' || toets != '\n') {
            taak[i] = toets;
            printw("%c", toets);
        }
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
    //for (int i = 0; i < (int)(TAAK_GROOTTE*sizeof(int)); i++) {
    //printw("%c%c%c", ar[0], ar[1], ar[2]);
    for (int i = 0; i < (int)(300*sizeof(int)); i++) {
        printw("%c", ar[i]);
    }
            
}

int main(void) {
    initscr();
    noecho();
    clear();
    keypad(stdscr, true);

    char *taak = vraag_lijst(); 
    print_array(taak);
    
    int datum = 20;
    //int datum = datum_vraag();
    int score = 30;
    //int score = score_vraag();
    maak_taak_struct(taak, datum, score);

    getch();
    endwin();
    free(taak);
    return 0;
}