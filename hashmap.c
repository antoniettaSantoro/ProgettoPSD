#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "item.h"

/***Definizioni Strutture****/

//Definizione della struttura nodo:
//Contiene un puntatore ad item e un puntatore al prossimo nodo
struct nodo{
    item segn;
    struct nodo *prossimo;
};

//Definizione della struttura della tabella hash
struct hash {
    int dimensione;              
    struct nodo **tabella;   //Puntatore ad un array di nodi
};

/****Funzioni Ausiliari****/

//Funzione di hash semplice
//Funzione hash che calcola l'indice basato sulla chiave e sulla dimensione della tabella
int hashFun(char *chiave, int dimensione) {
    int hash = 0;
    while (*chiave) {
        hash = (hash * 31 + *chiave) % dimensione;
        chiave++;
    }
    return hash;
}

//Funzione di supporto che rimuove una lista
static void libera_lista(struct nodo *p) {
    struct nodo *temp;
    while (p != NULL) {
        temp = p->prossimo;
        libera_segnalazione(p->segn);
        free(p);
        p = temp;
    }

}


/****Gestione della Memoria****/

hashtable crea_Hashtable(int dimensione) {
    int i;
    hashtable h = (struct hash *) malloc(sizeof(struct hash));
    if (h == NULL)
        return NULL;        //ritorna NULL se ci sono errori durante l'allocazione della memoria

    h->dimensione = dimensione;

    //Allocazione della memoria: inizializza tutti i puntatori a NULL tramite calloc
    h->tabella = (struct nodo **) calloc(dimensione, sizeof(struct nodo *));
    if (h->tabella == NULL) {
        free(h);            
        return NULL;        //ritorna NULL se ci sono errori durante l'allocazione della memoria
    }

    return h;
}

void libera_Hashtable(hashtable h) {

    //Elimina la lista collegata in ogni indice della tabella
    for(int i = 0; i < h->dimensione; i++) {
        libera_lista(h->tabella[i]);
    }
    
    free(h->tabella);
    free(h);
    return;
}

/****Gestione Hashmap****/

// Funzione per inserire un elemento in una tabella hash.
int inserisci_Hash(hashtable h, item elem) {

    if(h == NULL){
        return -1;                      //Hashmap inserita non è corretta, ritorna -1
    }

    int ind;
    struct nodo *attuale;

    ind = hashFun(get_id(elem), h->dimensione);
    attuale = h->tabella[ind];

    //Controlla se esiste già un elemento con la stessa chiave
    while(attuale){
        if (strcmp(get_id(attuale->segn), get_id(elem)) == 0) {
            return 0;                   //Elemento già presente, ritorna 0
        }
        attuale = attuale->prossimo;
    }

    //Crea un nuovo nodo e lo inserisce all'inizio della lista.
    struct nodo *nuovo = malloc(sizeof(struct nodo));
    nuovo->segn = elem;
    nuovo->prossimo = h->tabella[ind];
    h->tabella[ind] = nuovo;

    return 1;                           //Inserimento riuscito, ritorna 1
}

//Ricerca Item
item ricerca(hashtable h, char* chiave){

    if(h == NULL)
        return NULLITEM;                //Hashmap non è corretta, ritorna NULLITEM

    int ind = hashFun(chiave, h->dimensione);
    struct nodo *attuale = h->tabella[ind];

    while(attuale){
        if (strcmp(get_id(attuale->segn), chiave) == 0) {
            return attuale->segn;                
        }
        attuale = attuale->prossimo;
    }

    return NULLITEM;
}

/****Stampa****/

int stampa_Hashtable(hashtable h){

	if(h == NULL)
        return;                			//Hashmap non è corretta, ritorna 0

	//Cicla tutta la tabella hash e stampa le segnalazioni contenute in tutti i nodi delle liste
	for(int ind = 0; ind < h->dimensione; ind++){

		struct nodo *attuale = h->tabella[ind];

		while(attuale){
			stampa_segnalazione(attuale->segn);

			attuale = attuale->prossimo;
    	}
	}

	return 1;							//Stampa riuscita, ritorna 1
}

int stampa_Hashtable_file(hashtable h, FILE* f){

	if(h == NULL)
        return;                			//Hashmap non è corretta, ritorna 0
	
	//Cicla tutta la tabella hash e stampa le segnalazioni contenute in tutti i nodi delle liste
	for(int ind = 0; ind < h->dimensione; ind++){

		struct nodo *attuale = h->tabella[ind];

		while(attuale){
			stampa_segnalazione_file(attuale->segn, f);

			attuale = attuale->prossimo;
    	}
	}

	return 1;							//Stampa riuscita, ritorna 1
}
