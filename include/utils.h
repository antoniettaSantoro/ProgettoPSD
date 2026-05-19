#include "item.h"


/****Input****/

//Svuota il buffer dell'input
void svuota_input_buffer();


/****Gestione Id****/

//Genera id validi, dati una categoria e un numero
//ES: 	cat = 0, num = 35
//		id = "ILL00035"
char* genera_id(categoria cat, int num);

//Valida gli id dati in input
//Restituisce 1 se l'id è valido, 0 se non lo è
int valida_id(char* id);
