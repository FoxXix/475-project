# Compiler variable
CC = g++

O_FILES = wordCount.o Exceptions.o main.o Lexeme.o Stemmer.o TFIDF.o
# Compiler flags
LFLAGS = -o PA9
CFLAGS = -Wall -I. -c

PA9: $(O_FILES)
	$(CC) $(O_FILES) $(LFLAGS)

main.o: main.cpp
	$(CC) main.cpp $(CFLAGS)
	
Lexeme.o: Lexeme.cpp Lexeme.h
	$(CC) Lexeme.cpp $(CFLAGS)
	
Stemmer.o: Stemmer.cpp Stemmer.h
	$(CC) Stemmer.cpp $(CFLAGS)
	
wordCount.o: wordCount.cpp wordCount.h
	$(CC) wordCount.cpp $(CFLAGS)
	
Exceptions.o: Exceptions.cpp Exceptions.h
	$(CC) Exceptions.cpp $(CFLAGS)
	
TFIDF.o: TFIDF.cpp TFIDF.h
	$(CC) TFIDF.cpp $(CFLAGS)
	
test: tester.o Stemmer.o Lexeme.o Exceptions.o
	$(CC) $^ -o $@ -lpthread -lgtest
	
tester.o: tester.cpp
	$(CC) tester.cpp $(CFLAGS)

all: PA9
	
clean:
	rm *.o PA9 test
