#ifndef ITEM
#define ITEM

#define NULLITEM 0

#include <stdio.h>
#include "data.h"

/*ILLUMINAZIONE = 0, GUASTI = 1, RIFIUTI = 2, STRADE = 3*/
typedef enum{
    ILLUMINAZIONE,
    GUASTI,
    RIFIUTI,
    STRADE
} categoria;

/*APERTO = 0, CHIUSO = 1, INLAVORAZIONE = 2*/
typedef enum{
    APERTO,
    CHIUSO,
    INLAVORAZIONE
} stato;

typedef struct segnalazione *item;

/****Gestione della Memoria****/

//Crea una nuova segnalazione e restituisce un puntatore ad essa.
//Prende in input: id, nome del cittadino, categoria del problema, descrizione, data di inserimento,
//livello di urgenza, stato della segnalazione
//Nome max 50 caratteri, Descrizione max 100 caratteri
item crea_segnalazione(char* id, char* nome, categoria cat, char* descrizione, data data, int urgenza, stato st);

//Elimina e libera la memoria dato un puntatore a segnalazione in input
void libera_segnalazione(item s);

/****Get****/
//Queste funzioni restituiscono i parametri di una segnalazione data in input

char* get_id(item s);
char* get_nome(item s);
categoria get_cat(item s);
char* get_descrizione(item s);
data get_data(item s);
int get_urgenza(item s);
stato get_stato(item s);

/****Stato****/

//Modifica il valore dello stato nella segnalazione data in input
void modifica_stato(item s, stato st);

/****Stampa****/

//Stampa a video una segnalazione
void stampa_segnalazione(item s);

//Stampa su file una segnalazione
void stampa_segnalazione_file(item s, FILE* f);

#endif