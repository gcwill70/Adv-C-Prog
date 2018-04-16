// Do not remove #ifdef ... #endif before and after each function.
// 
// They are used to test different functions in your program and give
// partial credits, in case your program does not work completely.

#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StudentPrint(Student * stu, int num)
{
  printf("There are %d students\n", num);
  for (int ind = 0; ind < num; ind ++)
    {
      printf("ID = %d, First Name = %s, Last Name = %s\n",
	     stu[ind].ID,  stu[ind].firstname, stu[ind].lastname);
    }
}

#ifdef TEST_READ
// return false if anything is wrong 
// return true if reading the file successfully and the data is save in
// the allocated memory
// input: filename, the name of the input file
// output: address of the allocated memory
// output: number of students
bool StudentRead(char * filename, Student * * stu, int * numelem)
{
  // open the file to read
	FILE * fptr = fopen(filename, "r");
  // if fopen fails, return false
  // do not use fclose since fopen already fails
	if (fptr == NULL)
	{
		return false;
	}
  // count the number of lines to determine the number of students
	while (!feof(fptr))
	{
		if (fgetc(fptr) == '\n')
		{
			(*numelem)++;
		}
	}
  // return to the beginning of the file
  // you can use fseek or
  // fclose followed by fopen
  // You need to check whether fseek or fopen fails
  // Do not use rewind because it does not report whether it fails
	fclose(fptr);
	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		return false;
	}
  // allocate memory for the data
	Student* temp = malloc(sizeof(Student)*(*numelem));
  // check whether memory allocation fails
	if (temp == NULL)
	{
		return false;
	}
  // read the data from the file and store the data in the allocated memory
	for (int i = 0; i < *numelem; i++)
	{
		if(fscanf(fptr, "%d %s %s\n", &temp[i].ID, temp[i].firstname, temp[i].lastname) != 3)
		{
			free(temp);
			fclose(fptr);//?
			return false;
		}
	}
	*stu = temp;
  // close the file
	fclose(fptr);
  	return true;
}
#endif

#ifdef TEST_WRITE
// return false if anything is wrong 
// return true if writing the file successfully
// input: filename, the name of the output file
// input: address of the student array
// input: number of students

bool StudentWrite(char * filename, Student * stu, int numelem)
{
  // open the file to write 
	FILE * fptr = fopen(filename, "w");
  // if fopen fails, return false
  // do not use fclose since fopen already fails
	if (fptr == NULL)
	{
		return false;
	}
  // write the students to the output file
	for (int i = 0; i < numelem; i++)
	{
		fprintf(fptr, "%d %s %s\n", stu[i].ID, stu[i].firstname, stu[i].lastname);
	};

  //close file
	fclose(fptr);
	return true;
}
#endif 

#ifdef TEST_SORTID
void StudentSortbyID(Student * stu, int numelem)
{	
	qsort(stu, numelem, sizeof(*stu), compareID);

}

int compareID(const void * arg1, const void * arg2)
{
	const Student * ptr1 = (const Student *) arg1; 
	const Student * ptr2 = (const Student *) arg2;  
	// get the value from the address
	// compare the value
	if (ptr1->ID < ptr2->ID) { return -1; }
	if (ptr1->ID == ptr2->ID) { return 0; }
	return 1;
}
#endif

#ifdef TEST_SORTFIRSTNAME
void StudentSortbyFirstName(Student * stu, int numelem)
{
	qsort(stu, numelem, sizeof(*stu), compareFN);
}

int compareFN(const void * arg1, const void * arg2)
{
	const Student * ptr1 = (const Student *) arg1;
	const Student * ptr2 = (const Student *) arg2;  
	// get the value from the address
	// compare the value
	return strcmp(ptr1 -> firstname, ptr2 -> firstname);
}
#endif

#ifdef TEST_SORTLASTNAME
void StudentSortbyLastName(Student * stu, int numelem)
{
	qsort(stu, numelem, sizeof(*stu), compareLN);
}

int compareLN(const void * arg1, const void * arg2)
{
	const Student * ptr1 = (const Student *) arg1;
	const Student * ptr2 = (const Student *) arg2;  
	// get the value from the address
	// compare the value
	return strcmp(ptr1 -> lastname, ptr2 -> lastname);
}
#endif
