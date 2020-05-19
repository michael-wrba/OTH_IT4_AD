#include "tester.h"

int tester::SysTimeToMS(SYSTEMTIME time)	//Gibt Sytem(-tages-)zeit in Millisekunden aus
{
	int timeMS = 0;

	timeMS = time.wHour * 3600 * 1000 +
		time.wMinute * 60 * 1000 +
		time.wSecond * 1000 +
		time.wMilliseconds;

	return timeMS;
}

int tester::ranValue()
{
	int ranVal = 0;
	srand(time(NULL));

	/* generate secret number between 1 and 10: */
	ranVal = rand();// % 10 + 1;
	return ranVal;
}



void tester::beginTest()
{
	GetSystemTime(&ts1);
	counter = 0;
}

void tester::endTest()
{
	int dT = 0; //elapsed Time in MS
	int t1 = 0, t2 = 0;	//sys time in MS
	
	GetSystemTime(&ts2);
	t1 = SysTimeToMS(ts1);
	t2 = SysTimeToMS(ts2);
	dT = t2 - t1;

	std::cout << "Vergangene Zeit: " << dT << " ms " << std::endl;
	std::cout << "Anzahl Schritte: " << counter << std::endl;
}

tester tester::operator++(int)
{
	counter++;
	return *this;
}


