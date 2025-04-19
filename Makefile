# sone0149@gmail.com

CC = g++
CFLAGS = -Wall -g
SOURCES = graph.cpp queue.cpp priority_queue.cpp union_find.cpp algorithms.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TEST_SOURCES = tests.cpp $(SOURCES)
MAIN_SOURCES = main.cpp $(SOURCES)
EXEC = main
TEST_EXEC = test

all: Main

Main: $(MAIN_SOURCES)
	$(CC) $(CFLAGS) -o $(EXEC) $(MAIN_SOURCES)

test: $(TEST_SOURCES)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_SOURCES)
	./$(TEST_EXEC)

valgrind: Main
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

clean:
	rm -f $(EXEC) $(TEST_EXEC) *.o