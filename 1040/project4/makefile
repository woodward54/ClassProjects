OBJS = main.o plane.o planes.o pilot.o crew_member.o crew.o flight.o flights.o

master: $(OBJS)
	g++ -o $@ $(OBJS)

%.o: %.c plane.h planes.h pilot.h crew_member.h crew.h flight.h flights.h
	g++ -c $*.c

clean:
	rm *.o master

run:
	./master
