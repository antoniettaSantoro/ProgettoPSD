CFLAGS = -Wall -std=c99 -Iinclude
#Attiva i warning, usa C99 e cerca gli header in include/

TARGET = segnalazioni
TEST_TARGET = run_tests
#Nome degli eseguibili finali

OBJ = obj/gestione.o obj/hashmap.o obj/item.o obj/priorityQueue.o obj/utils.o obj/data.o
#File oggetto necessari per costruire il programma

all: $(TARGET) $(TEST_TARGET)
#Target predefinito: costruisce gli eseguibili

#Compila segnalazioni
$(TARGET): obj/main.o $(OBJ)
	$(CC) obj/main.o $(OBJ) -o $(TARGET)

obj/main.o: src/main.c include/item.h include/gestione.h include/hashmap.h include/utils.h include/data.h include/priorityQueue.h
#main.o dipende da main.c e dagli header
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o
# Compila main.c e genera obj/main.o

obj/gestione.o: src/gestione.c include/hashmap.h include/priorityQueue.h include/utils.h include/data.h include/item.h
	$(CC) $(CFLAGS) -c src/gestione.c -o obj/gestione.o

obj/hashmap.o: src/hashmap.c include/item.h
	$(CC) $(CFLAGS) -c src/hashmap.c -o obj/hashmap.o

obj/priorityQueue.o: src/priorityQueue.c include/item.h include/data.h
	$(CC) $(CFLAGS) -c src/priorityQueue.c -o obj/priorityQueue.o

obj/data.o: src/data.c
	$(CC) $(CFLAGS) -c src/data.c -o obj/data.o

obj/item.o: src/item.c include/data.h include/utils.h
	$(CC) $(CFLAGS) -c src/item.c -o obj/item.o

obj/utils.o: src/utils.c include/item.h
	$(CC) $(CFLAGS) -c src/utils.c -o obj/utils.o

#Compila run_tests
$(TEST_TARGET): obj/main_test.o $(OBJ)
	$(CC) obj/main_test.o $(OBJ) -o $(TEST_TARGET)

obj/main_test.o:	tests/main_test.c include/item.h include/gestione.h include/hashmap.h include/utils.h include/data.h include/priorityQueue.h
	$(CC) $(CFLAGS) -c tests/main_test.c -o obj/main_test.o

clean:
#Target per eliminare i file generati
	rm -f obj/*.o $(TARGET) $(TEST_TARGET)