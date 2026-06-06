#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "hashmap.h"
#include "gestione.h"
#include "utils.h"
#include "priorityQueue.h"
#include "data.h"

/**************************/
/****FUNZIONI AUSILIARI****/
/**************************/

/****Stampa****/

void stampa_menu(){
	printf("\n");
    printf("=====================================\n");
    printf("\t\tMENU\n");
    printf("=====================================\n");
    printf("0  - Esci\n");
    printf("1  - Registra Segnalazione\n");
    printf("2  - Visualizza Tutte le Segnalazioni\n");
    printf("3  - Ricerca Segnalazione\n");
    printf("4  - Aggiorna Stato Segnalazione\n");
    printf("5  - Visualizza Segnalazioni per Stato\n");
    printf("6  - Visualizza Segnalazione più Urgente\n");
    printf("7  - Genera Report\n");
	printf("8  - Salva su File\n");
	printf("9  - Carica da File\n");
	printf("10 - Configura\n");
    printf("=====================================\n");
    printf("\n\n");
}

void stampa_menu_ricerca(){
	printf("\n");
    printf("=====================================\n");
    printf("\t\tRICERCA\n");
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
    printf("\t\tVISUALIZZAZIONE\n");
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
	printf("Indici di Categoria: ILLUMINAZIONE = 0, GUASTI = 1, RIFIUTI = 2, STRADE = 3\n");
	printf("Indici di Stato: APERTO = 0, CHIUSO = 1, INLAVORAZIONE = 2\n");
	printf("Indici di urgenza: Numero da 1 a 10. 1 indica 'poco urgente', 10 indica 'molto urgente'\n");
	printf("\n");
	printf("ID\t\tNOME\t\tCAT\tDATA\t\tURGENZA\tSTATO\tDESCRIZIONE\n");
	printf("\n");
}

void stampa_intestazione_tabella_file(FILE* f){
	fprintf(f, "\n");
	fprintf(f, "Indici di Categoria: ILLUMINAZIONE = 0, GUASTI = 1, RIFIUTI = 2, STRADE = 3\n");
	fprintf(f, "Indici di Stato: APERTO = 0, CHIUSO = 1, INLAVORAZIONE = 2\n");
	fprintf(f, "Indici di urgenza: Numero da 1 a 10. 1 indica 'poco urgente', 10 indica 'molto urgente'\n");
	fprintf(f, "\n");
	fprintf(f, "ID\t\t\tNOME\t\t\tCAT\tDATA\tURGENZA\tSTATO\tDESCRIZIONE\n");
	fprintf(f, "\n");
}


/****Registra****/

//Registra un segnalazione su hashmap e coda a priorità
int registra_segnalazione(hashtable h, PQueue q, char* nome, categoria cat, char* descrizione, data d, int urgenza, stato st){

	int num = get_numelem(h, cat) + 1;
	char* id = genera_id((categoria) cat, num);

	item s = crea_segnalazione(id, nome, cat, descrizione, d, urgenza, st);
	int val = inserisci_Hash(h, s);
	inserisci_PQ(q, s);

	return val;
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

//Ricerca per categoria e stampa tutti i risultati corrispondenti
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
//Non è possibile modificare lo stato da CHIUSO
//Restituisce 0 se la segnalazione non è stata trovata,
//-1 se lo stato attuale della segnalazione è CHIUSO,
//1 se l'operazione va a buon fine
int aggiorna_stato(hashtable h, char* id, stato n_st){

	item trovato = ricerca(h, id);

	if(trovato == NULLITEM){
		return 0;
	}

	stato st = get_stato(trovato);

	if(st == CHIUSO){
		return -1;
	}

	modifica_stato(trovato, n_st);

	return 1;
}

/****Generazione Report****/

//Stampa su file tutte le segnalazioni della categoria data in input
void stampa_categoria_file(hashtable h, categoria cat, int n, FILE* f){
	
	fprintf(f, "CATEGORIA %d: ", cat);
	if(cat == ILLUMINAZIONE)	fprintf(f, "ILLUMINAZIONE\n");
	else if(cat == GUASTI)		fprintf(f, "GUASTI\n");
	else if(cat == RIFIUTI)		fprintf(f, "RIFIUTI\n");
	else if(cat == STRADE)		fprintf(f, "STRADE\n");
	fprintf(f, "Numero segnalazioni: %d\n", n);
	fprintf(f, "================================================================================\n");
	
	if(n != 0){
		char* id;
	
		stampa_intestazione_tabella_file(f);
	
		for(int i = 1; i <= n; i++){
			id = genera_id(cat, i);
			item trovato = ricerca(h, id);
	
			stampa_segnalazione_file(trovato, f);
		}
	
		fprintf(f, "\n");
	}	
	
	fprintf(f, "================================================================================\n");
}

//Stampa sul file il cui nome è dato in input un report contenente:
//numero totale di segnalazioni,
//segnalazioni per categoria,
//segnalazioni aperte e chiuse,
//categoria con più segnalazioni.
void stampa_report_su_file(hashtable h, char* fnome){

	FILE* f = fopen(fnome, "w");
	if(f == NULL){
		printf("Errore. Impossibile aprire il file\n");
		return;
	}

	int num[5];
	for(int i = 0; i < 5; i++){
		num[i] = get_numelem(h, i);
	}

	fprintf(f, "================================================================================\n");
	fprintf(f, "Numero totale segnalazioni: %d\n", num[4]);
	fprintf(f, "================================================================================\n\n");
	fprintf(f, "Segnalazioni per Categoria\n");
	fprintf(f, "================================================================================\n");

	for(int i = 0; i < 4; i++){
		stampa_categoria_file(h, i, num[i], f);
	}


	fprintf(f, "Segnalazioni per Stato\n");
	fprintf(f, "================================================================================\n\n");

	for(int i = 0; i < 3; i++){
		fprintf(f, "Segnalazioni ");

		if(i == 0)				fprintf(f, "APERTO\n");
		else if(i == 1)			fprintf(f, "IN LAVORAZIONE\n");
		else if(i == 2)			fprintf(f, "CHIUSO\n");

		stampa_intestazione_tabella_file(f);
		stampa_Hashtable_stato_file(h, i, f);
		fprintf(f, "================================================================================\n");
	}

	int max = 0;
	for(int i = 1; i < 4; i++){
		if(num[i] > num[max]){
			max = i;
		}
	}
	
	fprintf(f, "\nLa categoria con più segnalazioni è: ");

	if(max == 0)	fprintf(f, "ILLUMINAZIONE");
	else if(max == 1)		fprintf(f, "GUASTI");
	else if(max == 2)		fprintf(f, "RIFIUTI");
	else if(max == 3)		fprintf(f, "STRADE");

	fprintf(f, " con %d segnalazioni\n", num[max]);
	fprintf(f, "================================================================================\n");

	fclose(f);

	return;
}


/****File****/

//Input segnalazioni da file
void input_da_file(FILE* input, hashtable* h, PQueue* q){
	char nome[51], descrizione[101], id[9];
	int cat, g, m, a, urgenza, st;
	int dim;

	fscanf(input, "%d", &dim);

	*h = crea_Hashtable(dim);
	*q = crea_PQ(dim);
	if(*h == NULL || *q == NULL){
		printf("Errore\n");
		exit(1);
	}

	while(fscanf(input,"%s%s%d%d/%d/%d%d%d%s", id, nome, &cat, &g, &m, &a, &urgenza, &st, descrizione) == 9){

		data d = crea_data(g, m, a);
		if(d == NULL){
			printf("Errore data input\n");
			exit(1);
		}

		scambio_trattino_spazio(nome);
		scambio_trattino_spazio(descrizione);

		item s = crea_segnalazione(id, nome, cat, descrizione, d, urgenza, st);
		inserisci_Hash(*h, s);
		inserisci_PQ(*q, s);
	}

	return;
}

//Output su file delle segnalazioni
void output_file(FILE* out, hashtable h){

	int dim = get_dimensione(h);

	fprintf(out, "%d\n", dim);
	stampa_Hashtable_file(h, out);

	return;
}


/*******************************/
/****FINE FUNZIONI AUSILIARI****/
/*******************************/


void registra_segnalazione_input(hashtable h, PQueue q){

	system("clear");					//Pulisce lo schermo

	printf("\n");
    printf("=====================================\n");
    printf("\tREGISTRA SEGNALAZIONE\n");
    printf("=====================================\n");

	char nome[51];
	char descrizione[101];
	data d;
	int g, m, a;
	int cat;
	int urgenza;

	svuota_input_buffer();

	printf("\n");
	printf("Nome: ");
	scanf("%50[^\n]", nome);

	while(1){
		svuota_input_buffer();
		printf("Data [Formato 'gg mm aaaa']: ");
		if(scanf("%d %d %d", &g, &m, &a) != 3) {
			printf("Formato data non valido.\n");
		}
		else{
			d = crea_data(g, m, a);

			if(d == NULLDATA){
				printf("Data non valida.\n");
			}
			else if(d == NULL){
				printf("Errore durante allocazione memoria.\n");
			}
			else break;
		}
	}

	while(1){
		svuota_input_buffer();
		printf("Categoria [0 = ILLUMINAZIONE, 1 = GUASTI, 2 = RIFIUTI, 3 = STRADE]: ");
		scanf("%d", &cat);
		if(cat < 0 || cat > 3){
			printf("Valore inserito non valido\n");
		}
		else	break;			
	}
	
	while(1){
		svuota_input_buffer();
		printf("Urgenza [Usare un numero da 1 a 10. 1 indica 'poco urgente', 10 indica 'molto urgente']: ");
		scanf("%d", &urgenza);
		if(urgenza < 1 || urgenza > 10){
			printf("Valore inserito non valido\n");
		}
		else	break;
	}

	svuota_input_buffer();

	printf("Descrizione: ");
	scanf("%100[^\n]", descrizione);

	stato st = APERTO;		//Alla creazione ogni segnalazione è automaticamente aperta

	int val = registra_segnalazione(h, q, nome, (categoria) cat, descrizione, d, urgenza, st);
	
	if(val == 0){
		printf("La segnalazione inserita è già presente\n");
	}

	printf("\nRegistrazione avvenuta correttamente\n");

	svuota_input_buffer();
	printf("\nPremere INVIO per continuare...");
	getchar();

	return;
}

void visualizza_segnalazioni(hashtable h){

	system("clear");					//Pulisce lo schermo

	printf("\n");
    printf("=====================================\n");
    printf("\tVISUALIZZA SEGNALAZIONI\n");
    printf("=====================================\n");

	stampa_intestazione_tabella();

	int val = stampa_Hashtable(h);

	if (val == 0)	printf("Errore. Stampa Fallita\n");

	svuota_input_buffer();
	printf("\nPremere INVIO per continuare...");
	getchar();

	return;
}

void ricerca_segnalazione(hashtable h){

	int val;
	int scelta;
	int flag = 1;	

	svuota_input_buffer();

	while(flag){
		system("clear");					//Pulisce lo schermo
		stampa_menu_ricerca();				// 0 = indietro, 1 = id, 2 = categoria
		
		printf("> ");
		scanf("%d", &scelta);

		switch (scelta)
		{
			case 0:
				flag = 0;
				break;
			case 1:
				char id[9];
				
				svuota_input_buffer();
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
				}
				break;
			case 2:
				int cat;

				//svuota_input_buffer();
				printf("\n");
				printf("Categoria [0 = ILLUMINAZIONE, 1 = GUASTI, 2 = RIFIUTI, 3 = STRADE]: ");
				scanf("%d", &cat);
				if(cat < 0 || cat > 3){
					printf("Valore inserito non valido\n");
					break;
				}

				val = ricerca_categoria(h, (categoria) cat);
				if(val == 0){
					printf("Nessuna segnalazione trovata\n");
				}
				break;
			default:
				printf("Opzione insistente\n");			
				break;
		}

		svuota_input_buffer();
		printf("\nPremere INVIO per continuare...");
		getchar();
	}

	return;
}

void visualizza_segnalazioni_stato(hashtable h){

	int val;
	int scelta;
	int flag = 1;	

	svuota_input_buffer();

	while(flag){
		system("clear");					//Pulisce lo schermo
		stampa_menu_visualizza_stato();

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

		svuota_input_buffer();
		printf("\nPremere INVIO per continuare...");
		getchar();
	}

	return;
}

void aggiorna_stato_segnalazione(hashtable h){

	system("clear");					//Pulisce lo schermo

	printf("\n");
    printf("=====================================\n");
    printf("\tAGGIORNA STATO\n");
    printf("=====================================\n");

	char id[9];

	svuota_input_buffer();
	printf("\n");
	printf("Id: ");
	scanf("%8[^\n]", id);

	int val = valida_id(id);
	if(val == 0){
		printf("Id non valido\n");
	}
	else{
		int st;

		printf("\n");
		printf("Indici di Stato: APERTO = 0, CHIUSO = 1, INLAVORAZIONE = 2\n");

		while(1){
			printf("Inserisci il nuovo stato: ");

			svuota_input_buffer();
			scanf("%d", &st);
			if(st < 0 || st > 2){
				printf("Valore inserito non valido\n");
			}
			else	break;
		}

		val = aggiorna_stato(h, id, (stato) st);
		if(val == 0){
			printf("Segnalazione non trovata\n");
		}
		else if(val == -1){
			printf("Non è possibile modificare lo stato da CHIUSO\n");
		}
		else{
			printf("Stato aggiornato\n");
		}
	}

	svuota_input_buffer();
	printf("\nPremere INVIO per continuare...");
	getchar();

	return;
}

void visualizza_segnalazione_urgente(PQueue q){
	
	system("clear");					//Pulisce lo schermo

	printf("\n");
    printf("=====================================\n");
    printf("\tVISUALIZZA URGENTE\n");
    printf("=====================================\n");

	item segn = get_max_urgente(q);

	if(segn == NULLITEM){
		printf("Nessuna segnalazione urgente\n");
	}
	else{
		printf("La segnalazione più urgente è:\n");

		stampa_intestazione_tabella();
		stampa_segnalazione(segn);
	}
	
	svuota_input_buffer();
	printf("\nPremere INVIO per continuare...");
	getchar();

	return;
}

void genera_report(hashtable h){

	system("clear");					//Pulisce lo schermo

	printf("==========================\n");
	printf("\tREPORT\n");
	printf("==========================\n");
	printf("Il report viene creato nel file \"report.txt\"\n\n");
	
	char fnome[] = "txt_files/report.txt";
	
	stampa_report_su_file(h, fnome);

	printf("Report generato\n");
	svuota_input_buffer();
	printf("\nPremere INVIO per continuare...");
	getchar();

	return;
}

void leggi_segnalazioni_file(hashtable h, PQueue q){

	char nomefile[45];
	char nome[31];
	char scelta;

	system("clear");					//Pulisce lo schermo

	printf("==========================\n");
	printf("\tLEGGI DA FILE\n");
	printf("==========================\n");

	printf("Attenzione\n");
	printf("Se viene eseguita questa operazione tutti i dati correnti verrano sovrascritti.\n");
	printf("Procedere? [y/n]");
	
	svuota_input_buffer();
	scanf("%c", &scelta);
	if(scelta == 'n'){
		svuota_input_buffer();
		printf("\nPremere INVIO per continuare...");
		getchar();
		return;
	}
	else if(scelta != 'y'){
		printf("Scelta non valida\n");
		svuota_input_buffer();
		printf("\nPremere INVIO per continuare...");
		getchar();
		return;
	}

	printf("Il file deve trovarsi nella cartella: 'txt_files'\n");
	printf("Il file deve essere stato generato dal programma o avere formato compatibile\n");
	printf("In caso contrario non si assicura la corretta interpretazione dei dati\n");
	printf("Inserisci il nome del file [Lunghezza massima 30 caratteri. Non includere '.txt']: ");

	svuota_input_buffer();
	scanf("%30s", nome);
	sprintf(nomefile, "txt_files/%s.txt", nome);

	FILE* input;
	input = fopen(nomefile, "r");
	if(input == NULL){
		printf("Errore nell'apertura file\n");
		return;
	}

	libera_Hashtable(h);
	libera_PQ(q);

	input_da_file(input, &h, &q);

	printf("Operazione completata\n");
	svuota_input_buffer();
	printf("\nPremere INVIO per continuare...");
	getchar();

	return;
}

void salva_segnalazioni_file(hashtable h){

	char nome[31];
	char nomefile[45];

	system("clear");					//Pulisce lo schermo

	printf("==========================\n");
	printf("\tSALVA SU FILE\n");
	printf("==========================\n");

	printf("Se il file inserito già esiste, questo verrà sovrascritto.\n");
	printf("Inserisci il nome del file [Lunghezza massima 30 caratteri. Non includere '.txt']: ");

	svuota_input_buffer();
	scanf("%30s", nome);
	sprintf(nomefile, "txt_files/%s.txt", nome);

	FILE* output;
	output = fopen(nomefile, "w");
	if(output == NULL){
		printf("Errore nell'apertura file\n");
		return;
	}

	output_file(output, h);

	printf("Operazione completata\n");
	svuota_input_buffer();
	printf("\nPremere INVIO per continuare...");
	getchar();

	fclose(output);

	return;
}

void configura(hashtable* h, PQueue* q){

	int dim;
	char scelta;
	
	system("clear");					//Pulisce lo schermo

	printf("==========================\n");
	printf("\tCONFIGURAZIONE\n");
	printf("==========================\n");

	printf("Attenzione\n");
	printf("Se viene eseguita questa operazione tutti i dati correnti verrano eliminati.\n");
	printf("Procedere? [y/n]");
	
	svuota_input_buffer();
	scanf("%c", &scelta);
	if(scelta == 'n'){
		svuota_input_buffer();
		printf("\nPremere INVIO per continuare...");
		getchar();
		return;
	}
	else if(scelta != 'y'){
		printf("Scelta non valida\n");
		svuota_input_buffer();
		printf("\nPremere INVIO per continuare...");
		getchar();
		return;
	}

	printf("\nScegliere la dimensione in base alla popolazione del comune e al numero di segnalazioni previste.\n");
	printf("ES: popolazione: 5000 abitanti; segnalazioni previste: 1500; dimensione appropriata: 3000\n\n");
	printf("Inserisci dimensione: ");
	svuota_input_buffer();
	scanf("%d", &dim);

	if(dim < 1){
		printf("Errore. Dimensione non consentita.\n");
			
		svuota_input_buffer();
		printf("\nPremere INVIO per continuare...");
		getchar();

		return;					//ritorna se la dimensione non è valida
	}

	libera_Hashtable(*h);
	libera_PQ(*q);

	*h = crea_Hashtable(dim);
	*q = crea_PQ(dim);

	printf("Operazione completata\n");
	svuota_input_buffer();
	printf("\nPremere INVIO per continuare...");
	getchar();

	return;
}