#pragma once
#include <Windows.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class tester
{
public: 
	int SysTimeToMS(SYSTEMTIME time);
	int ranValue();
	void beginTest();
	void endTest();


	tester operator ++(int);	//postfix, zum hochzaehlen von Rechenschritten


private:
	SYSTEMTIME ts1, ts2; //Timestamps, 1 vor, 2 nach Test
	int dT; //vergangene Zeit in Millisek
	int counter; //
};

