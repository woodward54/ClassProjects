#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "bubble.h"


//Code by: David Woodward
//euid:		 dww0085

struct classStats {
	float mean;
	float min;
	float max;
	float median;
	char *name;
};

int main() {

	struct classStats *class1;
	class1 = (struct classStats *)malloc(sizeof(struct classStats));										//create classStats struct and malloc memory
	class1->name = (char*)malloc(sizeof(char) * 20);																		//malloc memory for char array
	class1->min = 100.00;
	class1->max = 0.00;

	int numOfStudents = 19;

	student *students[19];																															//malloc memory for each student struct

	scanf("%s", class1->name);

	//read grades file into struct array and find all stats
	for (int i=0; i < numOfStudents; i++) {
		//malloc memory for student struct and char pointer arrays
		students[i] = (student *)malloc(sizeof(student));
		students[i]->last = (char*)malloc(sizeof(char) * 20);
		students[i]->first = (char*)malloc(sizeof(char) * 20);
		scanf("%s %s %d %d %d", students[i]->first, students[i]->last, &(students[i]->exam1), &(students[i]->exam2), &(students[i]->exam3));

		students[i]->mean = (students[i]->exam1+students[i]->exam2+students[i]->exam3) / 3.00;	//get each students mean score

		//find min/max class scores and store them into classStats struct
		if (students[i]->mean > class1->max){
			class1->max = students[i]->mean;
		}
		if (students[i]->mean < class1->min){
			class1->min = students[i]->mean;
		}

		//calculate class mean
		class1->mean += students[i]->mean;
		if (i == numOfStudents-1){
			class1->mean /= numOfStudents;
		}
	}

	bubble(students, numOfStudents);				//bubble sort

	//find median value
	if (numOfStudents % 2 != 0){ 						//num of students is odd
		int temp = ((numOfStudents+1) / 2) - 1;
		class1->median = students[temp]->mean;
	} else { 																//num of students is even
		class1->median = students[(numOfStudents / 2) - 1]->mean;
	}
	//print results
	printf("\n\n%s\n\n", class1->name);
	printf("						Class Stats\n");
	printf("	Mean: %2.2f		 Min: %2.2f			Max: %2.2f 		Median: %2.2f\n\n", class1->mean, class1->min, class1->max, class1->median);
	printf("%-15s %-15s %4s\n", "First", "Last", "Mean");
	printf("\n");
	for (int i=0; i < 19; i++) {

		printf("%-15s %-15s %2.2f\n", students[i]->first, students[i]->last, students[i]->mean);
	}

	//free memory
	for (int i=0; i < numOfStudents; i++){
	  free(students[i]->first);
	  free(students[i]->last);
	}
  free(*students);
	free(class1);
	printf("\n");
  return 0;
}
