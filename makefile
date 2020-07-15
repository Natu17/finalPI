COMPILER=gcc
OUTPUT_FILE_BUE=arbolesADTBUE
OUTPUT_FILE_VAN=arbolesADTVAN
FILES=main.c queries.c treeADT.o neighbourhood.o
BACK =treeADT.c neighbourhood.c
FLAGS=-lm -pedantic -std=c99 -Wall -fsanitize=address

all: back.o
	$(COMPILER) -o $(OUTPUT_FILE_VAN) $(FILES) $(FLAGS)
	$(COMPILER) -o $(OUTPUT_FILE_BUE) $(FILES) $(FLAGS)

back.o:
	$(COMPILER) -c $(BACK)

clean:
	rm -r $(OUTPUT_FILE) *.o