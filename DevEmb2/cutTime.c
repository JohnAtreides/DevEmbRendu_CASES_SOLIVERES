#include <stdio.h>

void cutTime(int sec, int *pSec, int *pMinu, int *pHour)
{	
	*pHour = *pMinu / 60;
	*pMinu = *pMinu % 60;
}

int main()
{
	void cutTime(int secTotal, int *sec, int *minu, int *hour);

	
	int sec=0, minu=0, hour=0;
	int secTotal = 3783;
	cutTime(secTotal, &sec, &minu, &hour);
	printf("on since %d hour, %d minutes and %d seconds.\n", hour, minu, sec);
	
}
