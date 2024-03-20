CC=gcc
PROG=prog
MODULES=2dField nodeSet
OBJS=$(addsuffix .o, $(MODULES))

.PHONY: all run clean vlg

all: run

vlg: $(PROG)
	valgrind ./$(PROG) < TABLE

deb: $(PROG)
	./$(PROG) < TABLE -d

run: $(PROG)
	./$(PROG) < TABLE

$(PROG): main.c $(OBJS)
	$(CC) $^ -o $(PROG)

%.o: %.c %.h
	$(CC) -c $< -o $@

clean:
	rm *.o $(PROG)
