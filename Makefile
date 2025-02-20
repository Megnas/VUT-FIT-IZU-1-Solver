CC=gcc
PROG=prog
MODULES=2dField nodeSet
OBJS=$(addsuffix .o, $(MODULES))
TABLE_PTH=data/TABLE

.PHONY: all run clean vlg

all: $(PROG)

vlg: $(PROG)
	valgrind ./$(PROG) < $(TABLE_PTH)

deb: $(PROG)
	./$(PROG) < $(TABLE_PTH) -d

run: $(PROG)
	./$(PROG) < $(TABLE_PTH)

$(PROG): main.c $(OBJS)
	$(CC) $^ -o $(PROG)

%.o: %.c %.h
	$(CC) -c $< -o $@

clean:
	rm *.o $(PROG)
