#ifndef GESTIONE
#define GESTIONE

#include "hashmap.h"
#include "priorityQueue.h"

//Stampa il menu principale del programma
void stampa_menu();

//Funzione che aggiunge una segnalazione alla hashmap.
//Durante la sua esecuzione chiede all'utente di inserire i parametri della segnalazione
void registra_segnalazione_input(hashtable h, PQueue q);

//Stampa a video tutte le segnalazioni presenti nella hashmap
void visualizza_segnalazioni(hashtable h);

//Stampa a video le segnalazioni che hanno un certo stato.
//Lo stato viene selezionato dall'utente durante l'esecuzione della funzione
void visualizza_segnalazioni_stato(hashtable h);

//Ricerca segnalazioni specifiche all'interno della hashmap
//È possibile effettuare una ricerca per id o per categoria
void ricerca_segnalazione(hashtable h);

//Funzione che aggiorna lo stato di una segnalazione
//Durante la sua esecuzione l'utente specifica l'id della segnalazione che vuole modificare
//Non è possibile modificare lo stato da CHIUSO
void aggiorna_stato_segnalazione(hashtable h);

void visualizza_segnalazione_urgente(PQueue q);

//Funzione che genera e stampa su file un report con:
//numero totale di segnalazioni,
//segnalazioni per categoria,
//segnalazioni aperte e chiuse,
//categoria con più segnalazioni.
//Il file generato è 'report.txt'
void genera_report(hashtable h);

//Funzione che legge da un file txt delle segnalazioni
//Le segnalazioni già presenti nel programma vengono sovrascritte
void leggi_segnalazioni_file(hashtable h, PQueue q);

//Funzione che salva le segnalazioni correnti in un file txt
void salva_segnalazioni_file(hashtable h);

/****TEST****/
/*
	Le seguenti funzioni sono funzioni ausiliari e in quanto tali non dovrebbero essere utilizzate al di fuori del file
	gestione.c
	Sono presenti nel file gestione.h perché utilizzate nel testing
*/

int registra_segnalazione(hashtable h, PQueue q, char* nome, categoria cat, char* descrizione, data d, int urgenza, stato st);

void input_da_file(FILE* input, hashtable* h, PQueue* q);

void stampa_categoria_file(hashtable h, categoria cat, int n, FILE* f);

int aggiorna_stato(hashtable h, char* id, stato n_st);

void stampa_report_su_file(hashtable h, char* fnome);

#endif