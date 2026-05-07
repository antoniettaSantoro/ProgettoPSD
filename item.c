#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

/****Definizioni Strutture****/

//Definizione della struttura segnalazione
struct segnalazione {
    char id[10];                     //chiave
    char nome[51];
    categoria cat;
    char descrizione[101];
    char data[10];
    int urgenza;
    stato st;
};

/****Gestione della Memoria****/

item crea_segnalazione(char* id, char* nome, categoria cat, char* descrizione, char* data, int urgenza, stato st){
    item s = (item) malloc(sizeof(struct segnalazione));
    if(s == NULL)
        return NULL;    //ritorna NULL se ci sono errori durante l'allocazione della memoria

    s->cat = cat;
    s->urgenza = urgenza;
    s->st = st;

    //TO DO: GENERAZIONE ID
    strncopy(s->id, id, sizeof(s->id) - 1);
    s->nome[sizeof(s->id) - 1] = '\0';

    strncopy(s->nome, nome, sizeof(s->nome) - 1);
    s->nome[sizeof(s->nome) - 1] = '\0';

    strncopy(s->descrizione, descrizione, sizeof(s->descrizione) - 1);
    s->descrizione[sizeof(s->descrizione) - 1] = '\0';

    strncopy(s->data, data, sizeof(s->data) - 1);
    s->data[sizeof(s->data) - 1] = '\0';
    
    return s;
}

void libera_segnalazione(item s){
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

char* get_data(item s){
    return s->data;
}

int get_urgenza(item s){
    return s->urgenza;
}

stato get_stato(item s){
    return s->st;
}

/*Stato*/

void aggiorna_stato(item s, stato st){
    s->st = st;
}
