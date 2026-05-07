typedef struct hash *hashtable;

/****Gestione della Memoria****/

//Crea una nuova hashmap della dimensione data in input e restituisce un puntatore ad essa
hashtable crea_Hashtable(int dimensione);

//Elimina e libera la memoria dato un puntatore a hashmap in input
void libera_Hashtable(hashtable h);

/****Gestione Hashmap****/

//Inserisce l'item dato in input nella hashmap data in input e restituisce un intero che indica il risultato dell'operazione:
//-1 = Hashmap inserita non è corretta
//0 = Elemento già presente
//1 = Inserimento riuscito
int inserisci_Hash(hashtable h, item elem);

//Ricerca e restituisce nella hashmap data in input un item corrispondente alla chiave data in input 
//Se la chiave non è presente nella hashmap restituisce NULLITEM
//Se la hashmap non è corretta restituisce NULLITEM
item ricerca(hashtable h, char* chiave);

/****Stampa****/

//Stampa a video l'intera hashmap
//Se la hashmap in input non è corretta restituisce 0
//Se la stampa va a buon fine restituisce 1
int stampa_Hashtable(hashtable h);

//Stampa su file l'intera hashmap
//Se la hashmap in input non è corretta restituisce 0
//Se la stampa va a buon fine restituisce 1
int stampa_Hashtable_file(hashtable h, FILE* f);