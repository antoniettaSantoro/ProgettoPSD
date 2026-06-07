#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gestione.h"
#include "hashmap.h"
#include "priorityQueue.h"
#include "item.h"
#include "utils.h"
#include "data.h"

#define M 100		//max lunghezza nome dei file

void run_test_suite_REG(FILE* res, int num);
void run_test_suite_RID(FILE* res, int num);
void run_test_suite_RCT(FILE* res, int num);
void run_test_suite_AGG(FILE* res, int num);
void run_test_suite_PRT(FILE* res, int num);
void run_test_suite_VST(FILE* res, int num);
void run_test_suite_REP(FILE* res, int num);


//Funzione che confronta due file txt carattere per carattere
//Ritorna 0 se i file sono uguali
//Ritorna 1 se i file sono diversi
int confronto_output_oracolo(char* out_name, char* or_name){
	FILE *out, *or;
	char c1, c2;
	int flag = 0;

	out = fopen(out_name, "r");
	or = fopen(or_name, "r");

	if(out == NULL || or == NULL){
		printf("Errore in apertura dei file\n");
		exit(1);
	}

	//Confronta tutti i caratteri nei file di output e oracolo
	while ((c1 = fgetc(out)) != EOF && (c2 = fgetc(or)) != EOF) {
		if (c1 != c2) {     
			flag = 1;
			break;
		}
	}

	//Se uno dei due file non ha raggiunto EOF
	if(flag == 0 && (fgetc(out) != EOF || fgetc(or) != EOF))
		flag = 1;

	fclose(or);
	fclose(out);

	return flag;
}

int main(){
	FILE *result;

	result = fopen("txt_files/TEST_results.txt", "w");
	if(result == NULL ){
        printf("Errore in apertura del file TEST_results.txt\n");
        exit(1);
    }

	run_test_suite_REG(result, 3);		//3 casi di test per la registrazione
	run_test_suite_RID(result, 3);		//3 casi di test per la ricerca per id 
	run_test_suite_RCT(result, 2);		//2 casi di test per la ricerca per categoria
	run_test_suite_AGG(result, 4);		//4 casi di test per l'aggiornamento dello stato
	run_test_suite_PRT(result, 5);		//5 casi di test per la gestione della priorità
	run_test_suite_VST(result, 4);		//4 casi di test per la visualizzazione per stato
	run_test_suite_REP(result, 2);		//2 casi di test per la generazione del report

	printf("Test conclusi.\nI risultati sono memorizzati nel file 'TEST_results.txt\n");

	fclose(result);
	return 0;
}

//Test suite per la Registrazione
void run_test_suite_REG(FILE* res, int num){

	char nome[51], descrizione[101];
	int cat, g, m, a, urgenza;
	int dim;
	
	int n;
	int pass;

	FILE *in, *out;
	char input_fnome[M], output_fnome[M], oracolo_fnome[M];	
	char tc_id[] = "REG";
	
	for(int i = 1; i <= num; i++){
		//Costruisce i nomi dei file
		sprintf(input_fnome, "tests/test_cases/input/%s%d_input.txt", tc_id, i);
		sprintf(output_fnome, "tests/test_cases/output/%s%d_output.txt", tc_id, i);
		sprintf(oracolo_fnome, "tests/test_cases/oracolo/%s%d_oracolo.txt", tc_id, i);
	
		//Apre i file nelle modalità corrette
		in = fopen(input_fnome, "r");
		out = fopen(output_fnome, "w");

		if(in == NULL || out == NULL){
			printf("Errore in apertura file\n");
			exit(1);
		}

		fscanf(in, "%d", &n);

		fscanf(in, "%d", &dim);
		hashtable h = crea_Hashtable(dim);
		PQueue q = crea_PQ(dim);
		if(h == NULL || q == NULL){
			printf("Errore creazione hashmap e/o priority queue\n");
			exit(1);
		}

		//Legge dal file e registra n segnalazioni
		for(int j = 0; j < n; j++){
			fscanf(in, "%s\t%d\t%d/%d/%d\t%d\t%s", nome, &cat, &g, &m, &a, &urgenza, descrizione);
		
			data d = crea_data(g, m, a);
			if(d == NULL){
				printf("Errore creazione data\n");
				exit(1);
			}
		
			registra_segnalazione(h, q, nome, (categoria) cat, descrizione, d, urgenza, APERTO);
			//Lo stato delle segnalazioni viene sempre registrato come APERTO. La funzione registra_segnalazione_input,
			//che prende l'input dell'utente come segnalazione, chiama sempre questa funzione con stato APERTO.	
		}

		stampa_Hashtable_file(h, out);
	
		fclose(out);
		fclose(in);
		
		pass = confronto_output_oracolo(output_fnome, oracolo_fnome);
	
		//Stampa risultati
		fprintf(res, "%s%d\t", tc_id, i);
		if(pass == 0)	fprintf(res, "PASS\n");
		else			fprintf(res, "FAIL\n");

		libera_Hashtable(h);
		libera_PQ(q);
	}

	return;
}

//Test suite per la Ricerca per ID
void run_test_suite_RID(FILE* res, int num){

	item trovato;
	char id_da_trovare[9];
	
	int pass;

	FILE *in, *out;
	char input_fnome[M], output_fnome[M], oracolo_fnome[M];	
	char tc_id[] = "RID";

	for(int i = 1; i <= num; i++){
		//Costruisce i nomi dei file
		sprintf(input_fnome, "tests/test_cases/input/%s%d_input.txt", tc_id, i);
		sprintf(output_fnome, "tests/test_cases/output/%s%d_output.txt", tc_id, i);
		sprintf(oracolo_fnome, "tests/test_cases/oracolo/%s%d_oracolo.txt", tc_id, i);
	
		//Apre i file nelle modalità corrette
		in = fopen(input_fnome, "r");
		out = fopen(output_fnome, "w");

		if(in == NULL || out == NULL){
			printf("Errore in apertura file\n");
			exit(1);
		}

		fscanf(in, "%s", id_da_trovare);

		hashtable h;
		PQueue q;
		input_da_file(in, &h, &q);

		trovato = ricerca(h, id_da_trovare);

		if(trovato == NULLITEM){
			fprintf(out, "Segnalazione non trovata\n");
		}
		else{
			stampa_segnalazione_file(trovato, out);
		}

		fclose(out);
		fclose(in);
		
		pass = confronto_output_oracolo(output_fnome, oracolo_fnome);

		//Stampa risultati
		fprintf(res, "%s%d\t", tc_id, i);
		if(pass == 0)	fprintf(res, "PASS\n");
		else			fprintf(res, "FAIL\n");

		libera_Hashtable(h);
		libera_PQ(q);

		//fclose(in);
	}

	return;
}

//Test suite per la Ricerca per Categoria
void run_test_suite_RCT(FILE* res, int num){

	int categoria_da_trovare;
	
	int pass;

	FILE *in, *out;
	char input_fnome[M], output_fnome[M], oracolo_fnome[M];	
	char tc_id[] = "RCT";

	for(int i = 1; i <= num; i++){
		//Costruisce i nomi dei file
		sprintf(input_fnome, "tests/test_cases/input/%s%d_input.txt", tc_id, i);
		sprintf(output_fnome, "tests/test_cases/output/%s%d_output.txt", tc_id, i);
		sprintf(oracolo_fnome, "tests/test_cases/oracolo/%s%d_oracolo.txt", tc_id, i);
	
		//Apre i file nelle modalità corrette
		in = fopen(input_fnome, "r");
		out = fopen(output_fnome, "w");

		if(in == NULL || out == NULL){
			printf("Errore in apertura file\n");
			exit(1);
		}

		fscanf(in, "%d", &categoria_da_trovare);

		hashtable h;
		PQueue q;
		input_da_file(in, &h, &q);

		int n = get_numelem(h, categoria_da_trovare);
		stampa_categoria_file(h, categoria_da_trovare, n, out);

		fclose(out);
		fclose(in);
		
		pass = confronto_output_oracolo(output_fnome, oracolo_fnome);
	
		//Stampa risultati
		fprintf(res, "%s%d\t", tc_id, i);
		if(pass == 0)	fprintf(res, "PASS\n");
		else			fprintf(res, "FAIL\n");

		libera_Hashtable(h);
		libera_PQ(q);
	}

	return;
}

//Test suite per l'aggiornamento dello stato
void run_test_suite_AGG(FILE* res, int num){

	item trovato;
	char id_da_aggiornare[9];
	int stato_modificato;
	
	int ris;
	int pass;

	FILE *in, *out;
	char input_fnome[M], output_fnome[M], oracolo_fnome[M];	
	char tc_id[] = "AGG";

	for(int i = 1; i <= num; i++){
		//Costruisce i nomi dei file
		sprintf(input_fnome, "tests/test_cases/input/%s%d_input.txt", tc_id, i);
		sprintf(output_fnome, "tests/test_cases/output/%s%d_output.txt", tc_id, i);
		sprintf(oracolo_fnome, "tests/test_cases/oracolo/%s%d_oracolo.txt", tc_id, i);
	
		//Apre i file nelle modalità corrette
		in = fopen(input_fnome, "r");
		out = fopen(output_fnome, "w");

		if(in == NULL || out == NULL){
			printf("Errore in apertura file\n");
			exit(1);
		}

		fscanf(in, "%s", id_da_aggiornare);
		fscanf(in, "%d", &stato_modificato);

		hashtable h;
		PQueue q;
		input_da_file(in, &h, &q);

		ris = aggiorna_stato(h, id_da_aggiornare, (stato) stato_modificato);

		if(ris == 0){
			fprintf(out, "Nessun item trovato");
		}
		else{
			trovato = ricerca(h, id_da_aggiornare);
			stampa_segnalazione_file(trovato, out);
		}

		fclose(out);
		fclose(in);
		
		pass = confronto_output_oracolo(output_fnome, oracolo_fnome);

		//Stampa risultati
		fprintf(res, "%s%d\t", tc_id, i);
		if(pass == 0)	fprintf(res, "PASS\n");
		else			fprintf(res, "FAIL\n");

		libera_Hashtable(h);
		libera_PQ(q);
	}

	return;
}

//Test suite per la gestione della priorità
void run_test_suite_PRT(FILE* res, int num){

	item urgente;
	
	int pass;

	FILE *in, *out;
	char input_fnome[M], output_fnome[M], oracolo_fnome[M];	
	char tc_id[] = "PRT";

	for(int i = 1; i <= num; i++){
		//Costruisce i nomi dei file
		sprintf(input_fnome, "tests/test_cases/input/%s%d_input.txt", tc_id, i);
		sprintf(output_fnome, "tests/test_cases/output/%s%d_output.txt", tc_id, i);
		sprintf(oracolo_fnome, "tests/test_cases/oracolo/%s%d_oracolo.txt", tc_id, i);
	
		//Apre i file nelle modalità corrette
		in = fopen(input_fnome, "r");
		out = fopen(output_fnome, "w");
		
		if(in == NULL || out == NULL){
			printf("Errore in apertura file\n");
			exit(1);
		}
		
		hashtable h;
		PQueue q;
		input_da_file(in, &h, &q);
		
		urgente = get_max_urgente(q);
		
		if(urgente == NULLITEM){
			fprintf(out, "Coda a priorità vuota\n");
		
			//fclose(out);
			pass = confronto_output_oracolo(output_fnome, oracolo_fnome);
		}
		else{
			stampa_segnalazione_file(urgente, out);
		}

		fclose(out);
		fclose(in);
		
		pass = confronto_output_oracolo(output_fnome, oracolo_fnome);

		//Stampa risultati
		fprintf(res, "%s%d\t", tc_id, i);
		if(pass == 0)	fprintf(res, "PASS\n");
		else			fprintf(res, "FAIL\n");

		libera_Hashtable(h);
		libera_PQ(q);
	}

	return;
}

//Test suite per la visualizzazione per stato
void run_test_suite_VST(FILE* res, int num){

	int stato_da_filtrare;
	
	int pass;

	FILE *in, *out;
	char input_fnome[M], output_fnome[M], oracolo_fnome[M];	
	char tc_id[] = "VST";

	for(int i = 1; i <= num; i++){
		//Costruisce i nomi dei file
		sprintf(input_fnome, "tests/test_cases/input/%s%d_input.txt", tc_id, i);
		sprintf(output_fnome, "tests/test_cases/output/%s%d_output.txt", tc_id, i);
		sprintf(oracolo_fnome, "tests/test_cases/oracolo/%s%d_oracolo.txt", tc_id, i);
	
		//Apre i file nelle modalità corrette
		in = fopen(input_fnome, "r");
		out = fopen(output_fnome, "w");

		if(in == NULL || out == NULL){
			printf("Errore in apertura file\n");
			exit(1);
		}

		fscanf(in, "%d", &stato_da_filtrare);

		hashtable h;
		PQueue q;
		input_da_file(in, &h, &q);

		stampa_Hashtable_stato_file(h, stato_da_filtrare, out);

		fclose(out);
		fclose(in);
		
		pass = confronto_output_oracolo(output_fnome, oracolo_fnome);
	
		//Stampa risultati
		fprintf(res, "%s%d\t", tc_id, i);
		if(pass == 0)	fprintf(res, "PASS\n");
		else			fprintf(res, "FAIL\n");

		libera_Hashtable(h);
		libera_PQ(q);
	}

	return;
}

//Test suite per la generazione del report
void run_test_suite_REP(FILE* res, int num){

	int pass;

	FILE *in;
	char input_fnome[M], output_fnome[M], oracolo_fnome[M];	
	char tc_id[] = "REP";

	for(int i = 1; i <= num; i++){
		//Costruisce i nomi dei file
		sprintf(input_fnome, "tests/test_cases/input/%s%d_input.txt", tc_id, i);
		sprintf(output_fnome, "tests/test_cases/output/%s%d_output.txt", tc_id, i);
		sprintf(oracolo_fnome, "tests/test_cases/oracolo/%s%d_oracolo.txt", tc_id, i);
	
		//Apre i file nelle modalità corrette
		in = fopen(input_fnome, "r");

		if(in == NULL){
			printf("Errore in apertura file\n");
			exit(1);
		}

		hashtable h;
		PQueue q;
		input_da_file(in, &h, &q);

		stampa_report_su_file(h, output_fnome);

		fclose(in);
		
		pass = confronto_output_oracolo(output_fnome, oracolo_fnome);
	
		//Stampa risultati
		fprintf(res, "%s%d\t", tc_id, i);
		if(pass == 0)	fprintf(res, "PASS\n");
		else			fprintf(res, "FAIL\n");

		libera_Hashtable(h);
		libera_PQ(q);
	}

	return;
}