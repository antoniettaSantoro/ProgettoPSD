#include <stdio.h>
#include <stdlib.h>
#include "gestione.h"
#include "hashmap.h"
#include "item.h"
#include "utils.h"

#define DIM 50

int main(){
	int scelta;
	int flag = 1;

	hashtable h = crea_Hashtable(DIM);
	if(h == NULL){
		printf("Errore");
		return 1;
	}

	while(flag){
		system("cls || clear");					//Pulisce lo schermo		
		stampa_menu();

		printf("> ");
		scanf("%d", &scelta);

		switch (scelta)
		{
		    case 0:
				libera_Hashtable(h);
			    flag = 0;
			    break;
		    case 1:
			    registra_segnalazione(h);
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
				break;
			case 7:
				genera_report(h);
				break;
		    default:
				printf("Opzione insistente\n");				
			    break;
		}

	}

}