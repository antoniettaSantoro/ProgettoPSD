#include <stdio.h>
#include <stdlib.h>
#include "data.h"

/****Definizioni Strutture****/

//Definizione della struttura data
struct dt{
	int giorno;
	int mese;
	int anno;
};

/****Gestione della Memoria****/

data crea_data(int g, int m, int a){

	int val = valida_data(g, m, a);
	if(val == 0)	return NULLDATA;			//Ritorna NULLITEM se la data inserita non è valida

	data d = (data) malloc(sizeof(struct dt));
	if(d == NULL)	return NULL;				//Ritorna NULL se ci sono errori durante l'allocazione della memoria

	d->anno = a;
	d->mese = m;
	d->giorno = g;

	return d;
}

void libera_data(data d){
	free(d);
}

/****Gestione Date****/

//Restituisce 1 se d1 è più grande di d2, 0 se uguali
//-1 se s2 più grande di s1
int confronta_date(data d1, data d2){

	long dt1, dt2;

	dt1 = (d1->anno)*10000 + (d1->mese)*100 + (d1->giorno);
	dt2 = (d2->anno)*10000 + (d2->mese)*100 + (d2->giorno);

	if(dt1 > dt2)			return 1;
	else if(dt1 == dt2)		return 0;
	else					return -1;
}

int valida_data(int g, int m, int a){
	if(a < 2000 || m < 1 || m > 12 || g < 1)	return 0;

    int giorni[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};		//Giorni in ogni mese
	
	if(a%4 == 0)	giorni[2] = 29;			//Controllo anno bisestile

	if(g > giorni[m])	return 0;

	return 1;
}

/****Stampa****/

//Stampa la data in formato gg/mm/aaaa
void stampa_data(data d){
	printf("%02d/%02d/%04d", d->giorno, d->mese, d->anno);
}


//Stampa la data in formato gg/mm/aaaa su file
void stampa_data_file(data d, FILE* f){
	fprintf(f, "%02d/%02d/%04d", d->giorno, d->mese, d->anno);
}