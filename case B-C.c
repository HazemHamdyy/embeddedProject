#include <stdint.h>
#include <stdio.h>
#include <string.h>

int CookingTime_case_B( int w)
	{ 
		int timeps;
    timeps=	0.1*w*60; //time in second
		return timeps;
	}
	
int CookingTime_case_C(int w)
	{ 
		int timeps;
    timeps=	0.5*w*60;
		return timeps;
	}
	