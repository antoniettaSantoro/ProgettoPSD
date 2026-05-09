//Stampa il menu principale del programma
void stampa_menu();

//Funzione che aggiunge una segnalazione alla hashmap.
//Durante la sua esecuzione chiede all'utente di inserire i parametri della segnalazione
void registra_segnalazione(hashtable h);

//Stampa a video tutte le segnalazioni presenti nella hashmap
void visualizza_segnalazioni(hashtable h);

//Stampa a video le segnalazioni che hanno un certo stato.
//Lo stato viene selezionato dall'utente durante l'esecuzione della funzione
void visualizza_segnalazioni_stato(hashtable h);

//Ricerca segnalazioni specifiche all'interno della hashmap
//È possibile effettuare una ricerca per id o per categoria
void ricerca_segnalazione(hashtable h);

//Funzione che aggiorna lo stato di una segnalazione
//Durante la sua esecuzione l'utente specifica l'id della segnalazione che vuole modificare
void aggiorna_stato_segnalazione(hashtable h);