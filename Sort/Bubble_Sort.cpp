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
	for (i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 999; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}

		}
	}

	int y = clock();

	for (i = 0; i < 1000; i++)
		printf("%d ", a[i]);

	printf("시간차이=%d", y - x);
	return 0;
}
