#ifndef PriorityQ
#define PriorityQ

#include "item.h"

typedef struct PQ *PQueue;

/****Gestione della Memoria****/

//Crea una nuova coda a priorità e restituisce un puntatore ad essa
PQueue crea_PQ(int dim);

//Elimina e libera la memoria della coda a priorità data in input
void libera_PQ(PQueue q);

/****Gestione coda a priorità****/

//Funzione per ottenere l'elemento a maggiore priorità
//Restituisce NULLITEM se la coda è vuota
item get_max_urgente(PQueue q);

//Inserisce l'item dato in input nell coda data in input
//Restituisce 0 se la coda è piena o il puntatore ad essa è NULL
//Restituisce 1 se l'operazione va a buon fine
int inserisci_PQ(PQueue q, item segn);

#endif