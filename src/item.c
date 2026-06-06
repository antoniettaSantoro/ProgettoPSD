#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "data.h"
#include "utils.h"

/****Definizioni Strutture****/

//Definizione della struttura segnalazione
struct segnalazione {
    char id[9];                     //chiave
    char nome[51];
    categoria cat;
    char descrizione[101];
    data dt;
    int urgenza;
    stato st;
};

/****Gestione della Memoria****/

item crea_segnalazione(char* id, char* nome, categoria cat, char* descrizione, data data, int urgenza, stato st){
    item s = (item) malloc(sizeof(struct segnalazione));
    if(s == NULL)
        return NULL;    //ritorna NULL se ci sono errori durante l'allocazione della memoria

    s->cat = cat;
    s->urgenza = urgenza;
    s->st = st;
    s->dt = data;

    strncpy(s->id, id, sizeof(s->id) - 1);
    s->nome[sizeof(s->id) - 1] = '\0';

    strncpy(s->nome, nome, sizeof(s->nome) - 1);
    s->nome[sizeof(s->nome) - 1] = '\0';

    strncpy(s->descrizione, descrizione, sizeof(s->descrizione) - 1);
    s->descrizione[sizeof(s->descrizione) - 1] = '\0';
    
    return s;
}

void libera_segnalazione(item s){
    libera_data(s->dt);
    free(s);
}

/****Get****/
//Queste funzioni restituiscono i parametri di una segnalazione data in input

char* get_id(item s){
    return s->id;
}

char* get_nome(item s){
    return s->nome;
}

categoria get_cat(item s){
    return s->cat;
}

char* get_descrizione(item s){
    return s->descrizione;
}

data get_data(item s){
    return s->dt;
}

int get_urgenza(item s){
    return s->urgenza;
}

stato get_stato(item s){
    return s->st;
}

/****Stato****/

void modifica_stato(item s, stato st){
    s->st = st;
}

/****Stampa****/

void stampa_segnalazione(item s){
    printf("%s\t%s\t%d\t", s->id, s->nome, s->cat);
    stampa_data(s->dt);
    printf("\t%d\t%d\t%s\n",s->urgenza, s->st, s->descrizione);
}

//Nella stampa su file le stringhe vengono modificate in modo da non contenere il carattere ' '
void stampa_segnalazione_file(item s, FILE* f){

    char *nome_trattino, *descrizione_trattino;
    nome_trattino = (char*) malloc(51 * sizeof(char));
    descrizione_trattino = (char*) malloc(101 * sizeof(char));
    if(nome_trattino == NULL || descrizione_trattino == NULL){
        return;   
    }

    nome_trattino = scambio_spazio_trattino(s->nome, nome_trattino);
    descrizione_trattino = scambio_spazio_trattino(s->descrizione, descrizione_trattino);

    fprintf(f, "%s\t%s\t%d\t", s->id, nome_trattino, s->cat);
    stampa_data_file(s->dt, f);
    fprintf(f, "\t%d\t%d\t%s\n",s->urgenza, s->st, descrizione_trattino);

    free(nome_trattino);
    free(descrizione_trattino);
}

/****Altro****/

int confronta_segnalazioni(item s1, item s2){
    if(strcmp(s1->id, s2->id) == 0 && s1->cat == s2->cat && s1->st == s2->st && s1->urgenza == s2->urgenza &&
        confronta_date(s1->dt, s2->dt) == 0 && strcmp(s1->nome, s2->nome) == 0 && strcmp(s1->descrizione, s2->descrizione) == 0){
            return 0;
    }
    else    return 1;
}