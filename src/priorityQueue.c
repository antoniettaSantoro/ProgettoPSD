#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"
#include "item.h"
#include "data.h"

/***Definizioni Strutture****/

//Definizione della struttura per la coda di priorità.
struct PQ{
	item *vet;			//Array di item
    int numelem;		//Numero elementi nella coda a priorità
	int dimensione;		//Dimensione della coda a priorità
};

/****Funzioni Ausiliari****/

//Funzioni statiche per la manipolazione della coda

//Funzione per riaggiustare la coda verso il basso
static void scendi(PQueue q)
{
	int n = q->numelem, i = 1, pos;
	item temp;
	
	while (1)
	{
		// Determina la posizione del figlio con il valore più grande
		if(2*i + 1 <= n){		//Ha due figli

			//Controlla il primo criterio di priorità: urgenza
			if(get_urgenza(q->vet[2*i]) > get_urgenza(q->vet[2*i + 1])){
				pos = 2*i;
			}
			//Se le urgenze sono uguali, controlla il secondo criterio di priorità: data
			//Vengono considerate più urgenti le richieste più vecchie
			else if(get_urgenza(q->vet[2*i]) == get_urgenza(q->vet[2*i + 1]) && confronta_date(get_data(q->vet[2*1]), get_data(q->vet[2*i + 1])) == -1){
				pos = 2*1;
			}
			else{
				pos = 2*i + 1;
			}
		}
		else if (2*i <= n)		//Ha un solo figlio
			pos = 2*i;
		else 
			break; 				//Interrompe il ciclo se non ha figli
			
		//Scambia i valori se il figlio ha un valore più grande del nodo
		//Primo criterio: urgenza
		if(get_urgenza(q->vet[pos]) > get_urgenza(q->vet[i]))												
		{
				temp = q->vet[i];
				q->vet[i] = q->vet[pos];
				q->vet[pos] = temp;
				i = pos;			//Continua a scendere nella coda
		}
		//Secondo criterio: data
		else if(get_urgenza(q->vet[pos]) == get_urgenza(q->vet[i]) && confronta_date(get_data(q->vet[pos]), get_data(q->vet[i])) == -1){
			temp = q->vet[i];
			q->vet[i] = q->vet[pos];
			q->vet[pos] = temp;
			i = pos;			//Continua a scendere nella coda
		}
		else
			break;				//Termina se non sono necessari altri scambi.
	}
}

// Funzione per riaggiustare la coda verso l'alto
static void sali(PQueue q)
{
	int pos = q->numelem, i = pos / 2;
	item temp;

	while (pos > 1)
	{
		//Scambia i valori se l'elemento inserito è maggiore del suo genitore
		//Controlla il primo criterio di priorità: urgenza
		if (get_urgenza(q->vet[pos]) > get_urgenza(q->vet[i]))
		{
			temp = q->vet[i];
			q->vet[i] = q->vet[pos];
			q->vet[pos] = temp;
			pos = i;
			i = pos / 2;		//Continua a salire nella coda
		}
		//Se le urgenze sono uguali, controlla il secondo criterio di priorità: data
		//Vengono considerate più urgenti le richieste più vecchie
		else if(get_urgenza(q->vet[pos]) == get_urgenza(q->vet[i]) && confronta_date(get_data(q->vet[pos]), get_data(q->vet[i])) == -1){
			temp = q->vet[i];
			q->vet[i] = q->vet[pos];
			q->vet[pos] = temp;
			pos = i;
			i = pos / 2; 		//Continua a salire nella coda
		}
		else
			break;				//Termina se non sono necessari altri scambi
	}
}

//Funzione per controllare se la coda è vuota
int vuota_PQ(PQueue q)
{
	if (!q)		return 1;          	//Controlla se il puntatore è NULL
	return q->numelem == 0;    		//Ritorna 1 se la coda è vuota
}

//Funzione per eliminare l'elemento massimo dalla coda di priorità
int deleteMax(PQueue q)
{
	if (!q || q->numelem == 0)	return 0;	//Ritorna 0 se la coda è vuota o NULL

	q->vet[1] = q->vet[q->numelem];  		//Sostituisce la radice con l'ultimo elemento
	q->numelem--;                    		//Decrementa il numero di elementi

	scendi(q);  	//Riaggiusta la coda facendo scendere l'elemento sostituito
	return 1;
}


/****Gestione della Memoria****/

PQueue crea_PQ(int dim)
{
	PQueue q = (PQueue) malloc(sizeof(struct PQ));
    if(q == NULL)		return NULL;	//Ritorna NULL se ci sono errori durante l'allocazione della memoria
	q->numelem = 0;
	q->dimensione = dim;
	q->vet = (item*) malloc(dim*sizeof(item));
	if(q->vet == NULL)	return NULL;	//Ritorna NULL se ci sono errori durante l'allocazione della memoria

    return q;
}

//La funzione non libera gli item perché questi vengono già liberati da altre funzioni precedentemente al suo richiamo
//Liberare due volte la stessa area di memoria porta ad un comportamento indefinito
void libera_PQ(PQueue q){
	free(q->vet);
	free(q);
	return;
}

//Funzione che ingrandisce l'array della coda a priorità
int ingrandisci_PQ(PQueue q){

	int dim = (q->dimensione * 2);

	q->vet = (item*) realloc(q->vet, dim * sizeof(item));
	if(q->vet == NULL)		return 0;

	q->dimensione = q->dimensione * 2;
	return 1;
}

/****Gestione coda a priorità****/

//Funzione per ottenere l'elemento a maggiore priorità
item get_max_urgente(PQueue q)
{
	if(vuota_PQ(q) == 1)	return NULLITEM;

	//Se lo stato dell'item è CHIUSO, questo viene eliminato dalla coda a priorità.
	//Continua a farlo fino a quando lo stato dell'elemento in cima non è CHIUSO
	while(get_stato(q->vet[1]) == CHIUSO){
		if(vuota_PQ(q) == 1)	return NULLITEM;	//Ritorna NULLITEM se la coda è vuota
		deleteMax(q);
	}

	return q->vet[1];		//Ritorna l'elemento al primo indice
}

// Funzione per inserire un nuovo elemento nella coda
int inserisci_PQ(PQueue q, item segn)
{
	if (!q || q->numelem == q->dimensione){
		int val = ingrandisci_PQ(q);
		if(val == 0){
			printf("Errore realloc memoria\n");
			printf("Fine programma\n");
			exit(1);
		}
	}	//Se la coda è piena o NULL la ingrandisce

    q->numelem++;
    q->vet[q->numelem] = segn;					//Inserisce il nuovo elemento all'ultima posizione

    sali(q);  									//Riaggiusta la coda facendo risalire l'elemento inserito
    return 1;
}
