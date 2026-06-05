#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

/****Input****/

//Svuota il buffer dell'input
void svuota_input_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/****Gestione Id****/

//Genera id validi, dati una categoria e un numero
//ES: 	cat = 0, num = 35
//		id = "ILL00035"
char* genera_id(categoria cat, int num){

	char* id = (char*) malloc(9*sizeof(char));
	if(id == NULL)	return NULL;

	char* id_cat;

	if(cat == ILLUMINAZIONE)	id_cat = "ILL";
	else if(cat == GUASTI)		id_cat = "GUA";
	else if(cat == RIFIUTI)		id_cat = "RIF";
	else if(cat == STRADE)		id_cat = "STR";

	snprintf(id, 9, "%s%05d", id_cat, num);			//Crea una stringa dal format "CAT00000" nella variabile id

	return id;
}

//Valida gli id dati in input
//Restituisce 1 se l'id è valido, 0 se non lo è
int valida_id(char* id){

	if(strlen(id) < 8)		return 0;

	char cat[4];
	strncpy(cat, id, 3);
	cat[3] = '\0';

	if(strcmp(cat, "ILL") != 0 && strcmp(cat, "GUA") != 0 && strcmp(cat, "RIF") != 0 && strcmp(cat, "STR") != 0)
		return 0;

	char n[6];

	strcpy(n, id+3);
	n[5] = '\0';
	int num = atoi(n);				//Restituisce 0 se il valore non è un numero 

	if (num == 0)	return 0;		//Gli id validi iniziano dal numero 1

	return 1;
}


/****Stringhe****/

//Scambia il carattere ' ' con '_' in una stringa
char* scambio_spazio_trattino(char* stringa, char* nuova_stringa){	
	int len = strlen(stringa);

	int i;

	for(i = 0; i < len; i++) {
		if(stringa[i] == ' ')
			nuova_stringa[i] = '_';
		else
			nuova_stringa[i] = stringa[i];
	}

	nuova_stringa[i + 1] = '\0';

	return nuova_stringa;
}

//Scambia il carattere '_' con ' ' in una stringa
void scambio_trattino_spazio(char* stringa){

	int len = strlen(stringa);

	for(int i = 0; i < len; i++) {
		if(stringa[i] == '_')
			stringa[i] = ' ';
	}

	return;
}