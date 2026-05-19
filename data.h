#ifndef DATA
#define DATA

#define NULLDATA 0

typedef struct dt *data;


/****Gestione della Memoria****/


//Crea una nuova data e restituisce un puntatore ad essa.
//Prende in input: giorno, mese, anno
//Restituisce NULLDATA se l'input inserito non corrisponde ad una data valida
//Restituisce NULL se ci sono errori di allocazione della memoria
data crea_data(int g, int m, int a);

//Elimina e libera la memoria di una data in input
void libera_data(data d);


/****Gestione Date****/

//Confronta due date in input.
//Restituisce 1 se d1 è più grande di d2
//Restituisce 0 se d1 e d2 sono uguali
//Restituisce -1 se d2 più grande di d1
int confronta_date(data d1, data d2);

//Valida una data
//Prende in input: giorno, mese, anno.
//Restituisce 1 se la data è valida, 0 se non lo è
int valida_data(int g, int m, int a);


/****Stampa****/

//Stampa la data in formato gg/mm/aaaa
void stampa_data(data d);

//Stampa la data in formato gg/mm/aaaa su file
void stampa_data_file(data d, FILE* f);

#endif