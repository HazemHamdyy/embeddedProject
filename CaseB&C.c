#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


int CookingTimeBeef(int weight)
	{ double timeps;
    timeps=	0.5*weight*60;
		return timeps;
	}
	int CookingTimeChicken(int weight)
	{ double timeps;
    timeps=	0.2*weight*60;
		return timeps;
	}
	
		bool CheckInValidNum(char weight) //string
{
    bool isNotDigit= false;
        isNotDigit = isalpha(weight);
    int we ;
		we = weight-'0';// string to integer zay -'0'
    bool invalidRange = (we < 1) || (we > 9);
    return (invalidRange || isNotDigit);
}
