CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = LRanalyzer
TARGET2 = arbre_analyse.tex

all: $(TARGET) 

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c LRGrammar.c read_file.c pile.c aux.c arbre.c latex.c

clean:
	rm -f $(TARGET) $(TARGET2)
