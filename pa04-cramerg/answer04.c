#include <stdio.h>
#include <stdbool.h>
#include "pa04.h"

// must enclose the function by #ifdef TEST_INTEGRATE 
// and #endif to enable partial credits
#ifdef TEST_INTEGRATE
void integrate(Integration * intrg)
{
  // integrate the function stored in intrg's func
  // store the result in intrg's answer
	double result = 0; //final answer
	double area = 0; //area of current interval
	double width = ((intrg -> upperlimit) - (intrg -> lowerlimit))/(intrg -> intervals); //width of each interval
	double x1 = 0; //smaller x-coordinate of current interval being summed
	double x2 = 0; //larger x-coordinate of current interval being summed
	for(int i = 0; i <= (intrg -> intervals) - 1; i++) //iterates through all intervals necessary
	{
		x1 = (intrg -> lowerlimit) + width*i; //current lower limit
		x2 = x1 + width; //current upper limit
		area = width*(intrg -> func(x1));
		result += area;
	}
	intrg -> answer = result;
}
#endif // TEST_INTEGRATE

// must enclose the function by #ifdef RUN_INTEGRATE
// and #endif to enable partial credits

#ifdef RUN_INTEGRATE
bool  runIntegrate(char * infilename, char * outfilename)
// return true if it can successfully open and read the input 
// and open and write the output
// return false when encountering any problem
{
  // open the input file name for reading
 	Integration intrg;
	FILE * ifptr = fopen(infilename, "r");
 // if fopen fails, return false
	if (ifptr == NULL)
    	{
		return false;
    	}
  // read one double from the input file and store it in 
  // intrg's lowerlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
  	int check = fscanf(ifptr, "%lf\n", &intrg.lowerlimit);
	if (check != 1)
    	{
      		fclose(ifptr);
		return false;
    	}
  // read one double from the input file and store it in 
  // intrg's upperlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
	check = fscanf(ifptr, "%lf\n", &intrg.upperlimit);
	if (check != 1)
    	{
      		fclose(ifptr);
		return false;
    	}
  // read one int from the input file and store it in 
  // intrg's intervals
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
	check = fscanf(ifptr, "%d\n", &intrg.intervals);
	if (check != 1)
    	{
      		fclose(ifptr);
		return false;
    	}
  // close the input file
	fclose(ifptr);
  // open the output file for writing
  // if fopen fails, return false
	FILE * ofptr = fopen(outfilename, "w");
	if (ofptr == NULL)
	{
		return false;
	}
  // create an array of funcptr called funcs with five elements:
  // func1, func2, ..., func5
	funcptr funcs[5] = {&func1, &func2, &func3, &func4, &func5};
  // go through the elements in funcs 
  // for each element, call integrate for that function
  // write the result (stored in intrg's answer to 
  // the output file. each answer occupies one line (add "\n")
  // use fprintf
	for (int i = 0; i < 5; i++)
	{
		intrg.func = funcs[i];
		integrate(&intrg);
  // check the return value of fprintf. 
  // If it is less one one, close the output
  // file and return false
		check = fprintf(ofptr, "%lf\n", intrg.answer);
		if (check < 1)
		{
			fclose(ofptr);
			return false;
		}
	}
  // after going through all functions in funcs
  // close the output file
	fclose(ofptr);
  // if the function reaches here, return true
	return true;
}
#endif // RUN_INTEGRATE
