OBJS =  list.o main.o
solution: $(OBJS)
	g++ -o $@ $(OBJS)

%.o: %.c list.h
	g++ -c $*.c
clean:
	rm *.o solution
run:
	./solution
