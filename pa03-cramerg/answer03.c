#include "pa03.h"
double integrate1(Range rng)
{
	//Perform numerical integration of the function func(x)
	//INPUT: Range rng -- the lower and upper limits of the integration
	//                    and the number of intervals to integrate over
	//OUTPUT: Return the result of the integration

	//will perform a trapezoidal sum approximation (as stated in README)
	double result = 0; //final answer to be returned
	double area = 0; //area of current interval
	double width = (rng.upperlimit - rng.lowerlimit)/rng.intervals; //width of each interval
	double x1 = 0; //smaller x-coordinate of current interval being summed
	double x2 = 0; //larger x-coordinate of current interval being summed
	for(int i = 0; i <= rng.intervals - 1; i++) //iterates through all intervals necessary
	{
		x1 = rng.lowerlimit + width*i; //current lower limit
		x2 = x1 + width; //current upper limit
		area = width*func(x1);
		result += area;
	}
	return result;
}

void integrate2(RangeAnswer * rngans)
{
	//Perform numerical integration of the function func(x)
	//INPUT: RangeAnswer * rngans 
	//              -- the lower and upper limits of the integration
	//                 and the number of intervals to integrate over
	//OUTPUT: The result of the integration should be placed in rngans->answer

	//You should try to call integrate1 when implementing integrate2
	rngans -> answer = integrate1(rngans -> rng);
}
