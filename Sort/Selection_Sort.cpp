#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int a[1000];
	for (int i = 0;i < 1000;i++)
	{
		a[i] = rand() % 1000;
	}

	int x = clock();

	int i, temp;
	for (i = 0; i < 999; i++)
	{

		for (int j = i + 1;j < 1000;j++)
		{
			if (a[j] < a[i]) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}

	int y = clock();

	for (i = 0; i < 1000; i++)
	{
		printf("%d ", a[i]);
	}

	printf("시간차이=%d\n", y - x);
	return 0;

}