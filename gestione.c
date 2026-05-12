#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "hashmap.h"
#include "gestione.h"

/**************************/
/****FUNZIONI AUSILIARI****/
/**************************/

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
	else if(cat == STRADE);		id_cat = "STR";

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

	if(strcmp(cat, "ILL") != 0)			return 0;
	else if(strcmp(cat, "GUA") != 0)	return 0;
	else if(strcmp(cat, "RIF") != 0)	return 0;
	else if(strcmp(cat, "STR") != 0)	return 0;

	char n[6];

	strcpy(cat, id+3);
	n[5] = '\0';
	int num = atoi(n);				//Restituisce 0 se il valore non è un numero 

	if (num = 0)	return 0;		//Gli id validi iniziano dal numero 1

	return 1;
}

/****Stampa****/

void stampa_menu(){
	printf("\n");
    printf("=====================================\n");
    printf("\t\t\tMENU\n");
    printf("=====================================\n");
    printf("0 - Esci\n");
    printf("1 - Registra Segnalazione\n");
    printf("2 - Visualizza Tutte le Segnalazioni\n");
    printf("3 - Ricerca Segnalazione\n");
    printf("4 - Aggiorna Stato Segnalazione\n");
    printf("5 - Visualizza Segnalazioni per Stato\n");
    printf("6 - Visualizza Segnalazioni più Urgenti\n");
    printf("7 - Genera Report\n");
    printf("=====================================\n");
    printf("\n\n");
}

void stampa_menu_ricerca(){
	printf("\n");
    printf("=====================================\n");
    printf("\t\t\tRICERCA\n");
    printf("=====================================\n");
    printf("0 - Indietro\n");
    printf("1 - Ricerca per ID\n");
    printf("2 - Ricerca per Categoria\n");
    printf("=====================================\n");
    printf("\n\n");
}

void stampa_menu_visualizza_stato(){
	printf("\n");
    printf("=====================================\n");
    printf("\t\t\t VISUALIZZAZIONE\n");
    printf("=====================================\n");
    printf("0 - Indietro\n");
    printf("1 - Segnalazioni Aperte\n");
    printf("2 - Segnalazioni Chiuse\n");
    printf("3 - Segnalazioni In Lavorazione\n");
    printf("=====================================\n");
    printf("\n\n");

}

void stampa_intestazione_tabella(){
	printf("\n");
	printf("Indici di Categoria:ILLUMINAZIONE = 0, GUASTI = 1, RIFIUTI = 2, STRADE = 3\n");
	printf("Indici di Stato: APERTO = 0, CHIUSO = 1, INLAVORAZIONE = 2\n");
	printf("Indici di urgenza: Numero da 1 a 10. 1 indica 'poco urgente', 10 indica 'molto urgente'\n");
	printf("\n");
	printf("ID\tNOME\tCATEGORIA\tDATA\tURGENZA\tSTATO\tDESCRIZIONE\n");
	printf("\n");
}

/****Ricerca****/

//Ricerca una segnalazione tramite id dato in input
//Restituisce 0 se non è stato trovata la segnalazione e 1 se è stata trovata
//Stampa la segnalazione se è stata trovata
int ricerca_id(hashtable h, char* id){

	item trovato = ricerca(h, id);

	if(trovato == NULLITEM){
		return 0;
	}

	stampa_intestazione_tabella();
	stampa_segnalazione(trovato);
	printf("\n");

	return 1;
}

//Ricerca per categoia e stampa tutti i risultati corrispondenti
int ricerca_categoria(hashtable h, categoria cat){

	char* id;
	int num = get_numelem(h, cat);

	if(num == 0){
		return 0;
	}

	stampa_intestazione_tabella();

	for(int i = 1; i <= num; i++){
		id = genera_id(cat, i);
		item trovato = ricerca(h, id);

		stampa_segnalazione(trovato);
	}

	printf("\n");
	return 1;
}

/****Stato****/

//Stampa tutte le segnalazioni che hanno come stato lo stato dato in input
//Restituisce 0 se l'operazione fallisce, 1 se l'operazione va a buon fine
int visualizza_stato(hashtable h, stato st){

	stampa_intestazione_tabella();
	int val = stampa_Hashtable_stato(h, st);

	if (val == 0){
		printf("Errore. Stampa Fallita\n");
		return 0;
	}

	return 1;
}

//Aggiorna lo stato della segnalazione con id dato in input
//Restituisce 0 se la segnalazione non è stata trovata e 1 se l'operazione va a buon fine
int aggiorna_stato(hashtable h, char* id){

	item trovato = ricerca(h, id);

	if(trovato == NULLITEM){
		return 0;
	}

	stato st = get_stato(trovato);
	printf("\n");
	printf("Stato attuale: ");

	if(st == APERTO)				printf("APERTO\n");
	else if(st == INLAVORAZIONE)	printf("IN LAVORAZIONE\n");
	else if(st == CHIUSO)			printf("CHIUSO\n");

	printf("\n");
	printf("Indici di Stato: APERTO = 0, CHIUSO = 1, INLAVORAZIONE = 2\n");

	while(1){
		printf("Inserisci il nuovo stato: ");	
	
		scanf("%d", &st);
		if(st < 0 || st > 2){
			printf("Valore inserito non valido\n");
		}
		else	break;			
	}

	modifica_stato(trovato, st);

	printf("Stato aggiornato\n");

	return 1;
}

/*******************************/
/****FINE FUNZIONI AUSILIARI****/
/*******************************/


void registra_segnalazione(hashtable h){
	
	char nome[51];
	char descrizione[101];
	char data[11];
	categoria cat;
	int urgenza;
	stato st = APERTO;					//Alla creazione ogni segnalazione è automaticamente aperta

	getchar();							//Svuoto il buffer

	printf("\n");
	printf("Nome: ");
	scanf("%50[^\n]", nome);

	getchar();							//Svuoto il buffer

	printf("Data [Formato 'gg/mm/aaaa']: ");
	scanf("%10[^\n]", data);

	while(1){
		printf("Categoria [0 = ILLUMINAZIONE, 1 = GUASTI, 2 = RIFIUTI, 3 = STRADE]: ");
		scanf("%d", &cat);
		if(cat < 0 || cat > 3){
			printf("Valore inserito non valido\n");
		}
		else	break;			
	}
	
	while(1){	
		printf("Urgenza [Usare un numero da 1 a 10. 1 indica 'poco urgente', 10 indica 'molto urgente']: ");
		scanf("%d", &urgenza);
			if(urgenza < 1 || urgenza > 10){
				printf("Valore inserito non valido\n");
			}
			else	break;
	}

	getchar();							//Svuoto il buffer

	printf("Descrizione: ");
	scanf("%100[^\n]", descrizione);

	int num = get_numelem(h, cat) + 1;
	char* id = genera_id(cat, num);

	item s = crea_segnalazione(id, nome, cat, descrizione, data, urgenza, st);
	int val = inserisci_Hash(h, s);

	if(val == 0){
		printf("La segnalazione inserita è già presente\n");
	}

	return;
}

void visualizza_segnalazioni(hashtable h){

	stampa_intestazione_tabella();

	int val = stampa_Hashtable(h);

	if (val == 0)	printf("Errore. Stampa Fallita\n");

	return;
}

void ricerca_segnalazione(hashtable h){

	int val;
	int scelta;
	int flag = 1;	

	while(flag){
		stampa_menu_ricerca();

		printf("> ");

		getchar();
		scanf("%d", &scelta);

		switch (scelta)
		{
			case 0:
				flag = 0;
				break;
			case 1:
				char id[9];
				
				printf("\n");
				printf("Id: ");
				scanf("%8[^\n]", id);

				val = valida_id(id);
				if(val == 0){
					printf("Id non valido\n");
					break;
				}

				val = ricerca_id(h, id);
				if(val == 0){
					printf("Segnalazione non trovata\n");
					flag = 0;
				}
				break;
			case 2:
				categoria cat;

				printf("\n");
				printf("Categoria [0 = ILLUMINAZIONE, 1 = GUASTI, 2 = RIFIUTI, 3 = STRADE]: ");
				scanf("%d", &cat);
				if(cat < 0 || cat > 3){
					printf("Valore inserito non valido\n");
					break;
				}

				val = ricerca_categoria(h, cat);
				if(val == 0){
					printf("Nessuna segnalazione trovata\n");
					flag = 0;
				}
				break;
			default:
				printf("Opzione insistente\n");			
				break;
		}
		break;
	}

	return;
}

void visualizza_segnalazioni_stato(hashtable h){

	int val;
	int scelta;
	int flag = 1;	

	while(flag){
		stampa_menu_visualizza_stato;

		printf("> ");
		scanf("%d", &scelta);

		switch (scelta)
		{
			case 0:
				flag = 0;
				break;
			case 1:
				val = visualizza_stato(h, 0);
				if(val == 0)		flag = 0;
				break;
			case 2:
				val = visualizza_stato(h, 1);
				if(val == 0)		flag = 0;
				break;
			case 3:
				val = visualizza_stato(h, 2);
				if(val == 0)		flag = 0;
				break;
			default:
				printf("Opzione insistente\n");
				break;
		}
	}

	return;
}

void aggiorna_stato_segnalazione(hashtable h){

	char id[9];
	
	printf("\n");
	printf("Id: ");
	scanf("%8[^\n]", id);

	int val = valida_id(id);
	if(val == 0){
		printf("Id non valido\n");
		return;
	}

	val = aggiorna_stato(h, id);
	if(val == 0){
		printf("Segnalazione non trovata\n");
		return;
	}

	return;
}