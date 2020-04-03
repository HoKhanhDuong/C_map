all: chay

chay: main.o fields.o jrb.o jval.o dllist.o qs3w.o
	gcc main.o fields.o jrb.o jval.o dllist.o qs3w.o -o chay

main.o: main.c
	gcc -c -Wall main.c

graph.o: graph.c
	gcc -c -Wall graph.c

dllist.o: dllist.c
	gcc -c -Wall dllist.c

fields.o: fields.c
	gcc -c -Wall fields.c

jrb.o: jrb.c
	gcc -c -Wall jrb.c

jval.o: jval.c
	gcc -c -Wall jval.c

qs3w.o: qs3w.c
	gcc -c -Wall qs3w.c

clean:
	rm -f *.o *~
