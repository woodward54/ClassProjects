OBJS = main.o student.o students.o course.o courses.o enrollment.o enrollments.o

master: $(OBJS)
	g++ -o $@ $(OBJS)

%.o: %.c student.h students.h course.h courses.h enrollment.h enrollments.h
	g++ -c $*.c

clean:
	rm *.o master

run:
	./master
