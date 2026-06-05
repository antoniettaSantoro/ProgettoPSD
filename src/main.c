#include <stdio.h>
#include <stdlib.h>
#include "gestione.h"
#include "hashmap.h"
#include "item.h"
#include "utils.h"
#include "priorityQueue.h"
#include "data.h"

#define DIM 50

int main(){
	int scelta;
	int flag = 1;

	hashtable h = crea_Hashtable(DIM);
	PQueue q = crea_PQ(DIM);

	if(h == NULL){
		printf("Errore");
		return 1;
	}

	while(flag){
		system("clear");					//Pulisce lo schermo		
		stampa_menu();

		printf("> ");
		scanf("%d", &scelta);

		switch (scelta)
		{
		    case 0:
				libera_Hashtable(h);
				libera_PQ(q);
			    flag = 0;
			    break;
		    case 1:
			    registra_segnalazione_input(h, q);
				break;
			case 2:
				visualizza_segnalazioni(h);
				break;
			case 3:
				ricerca_segnalazione(h);
				break;
			case 4:
				aggiorna_stato_segnalazione(h);
				break;
			case 5:
				visualizza_segnalazioni_stato(h);
				break;
			case 6:
				visualizza_segnalazione_urgente(q);
				break;
			case 7:
				genera_report(h);
				break;
			case 8:
				salva_segnalazioni_file(h);
				break;
			case 9:
				leggi_segnalazioni_file(h, q);
				break;
			case 10:
				configura(&h, &q);
				break;
		    default:
				printf("Opzione insistente\n");				
			    break;
		}

	}

}