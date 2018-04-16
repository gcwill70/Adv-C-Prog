// You must modify this file
#ifndef PA05_H
#define PA05_H
#include "constant.h"
#include <stdbool.h>
#define NAME_LENGTH 80
// create a structure type that has the following attributes
// please make sure the names are exactly the same
//  int- ID
//  char- firstname[NAME_LENGTH]
//  char- lastname[NAME_LENGTH]
typedef struct
{
	int ID;
	char firstname[NAME_LENGTH];
	char lastname[NAME_LENGTH];

} Student;

// functions to be implemented
bool StudentRead(char * filename, Student * * stu, int * numelem);
bool StudentWrite(char * filename, Student * stu, int numelem);
void StudentSortbyID(Student * stu, int numelem);
void StudentSortbyFirstName(Student * stu, int numelem);
void StudentSortbyLastName(Student * stu, int numelem);

//self-made functions
int compareID(const void * arg1, const void * arg2);
int compareFN(const void * arg1, const void * arg2);
int compareLN(const void * arg1, const void * arg2);

// function already impelemented for you
void StudentPrint(Student * stu, int num);
#endif
