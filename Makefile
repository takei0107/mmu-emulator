CC = gcc 
FLAGS = -Wall -I./include -lm

PROG = mmu.out

TEST = ./test/test.out
TESTSRC = ./test/main.c ./src/*.c ./src/emu/*.c

test: $(TEST)
	./$(TEST)

$(TEST): $(TESTSRC)
	$(CC) $(FLAGS) -o $(TEST) $(TESTSRC)
