#include <stdio.h>

void main()
{
	int i, j, sum;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j <= i; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	printf("\n");

	i = 0, j = 0;

	for (i = 5; i >= 1; i--)
	{
		for (j = 0; j < i; j++)
		{
			printf("*");
		}
		printf("\n");
	}

	printf("\n");

	i = 0, j = 0;

	for (i = 2; i <= 9; i++)
	{
		for (j = 1; j <= 9; j++)
		{
			printf("%d X %d = %d\n", i, j, i*j);
		}
		printf("\n");
	}

	printf("\n");

	i = 0, j = 0;
	int count = 1;

	for (i = 1; i <= 9; i++)
	{
		for (j = 2; j <= 9; j++)
		{
			printf("%d X %d = %d \t", j, i, i*j);
		}
		
		printf("\n");
	}

	printf("\n");

	i = 0, j = 0, sum= 0;
	
	for (i = 1; i <= 100; i++)
	{
		if (i % 2 == 0)
		{
			printf("Â¦¼ö : %d\n",i);
			sum += i;
		}	
	}
	printf("Â¦¼öÇÕ : %d\n", sum);

	printf("\n");

	i = 0, j = 0, sum = 0;
	int a = 0;

	for (i = 1; i <= 5; i++)
	{
		for (j = i+2 ; j < 5 ; j++)
		{
		

		}
		
		
		printf("\n");
	}
}
