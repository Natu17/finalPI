COMPILER=gcc
OUTPUT_FILE=output
FILES=main.c queries.c treeADT.o neighbourhood.o
BACK =treeADT.c neighbourhood.c
FLAGS=-lm -pedantic -std=c99 -Wall -fsanitize=address

all: back.o
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) $(FLAGS)


back.o:
	$(COMPILER) -c $(BACK)

clean:
	rm -r $(OUTPUT_FILE) *.o