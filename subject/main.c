#include <stdio.h>

//int total(int kor, int eng, int mat);
//double average(int tot);
//
//
//int main()
//{
//	int kor, eng, mat;
//	int tot;
//	double avg;
//
//	printf("����, ����, ���� 3������ ������ �Է��� �ּ���. : ");
//	scanf("%d", &kor);
//	scanf("%d", &eng);
//	scanf("%d", &mat);
//
//	tot = total(kor, eng, mat);
//	avg = average(tot);
//
//	printf("--------------------------\n");
//	printf(" ���� \t ���� \t ���� \t\t\t ����\t ���\n");
//	printf("--------------------------\n");
//	printf(" %d  \t %d  \t %d \t\t\t %d \t %.1lf ", kor, eng, mat, tot, avg);
//	return 0;
//}
//
//int total(int kor, int eng, int mat)
//{
//	int sum;
//	sum = kor + eng + mat;
//	return sum;
//}
//double average(int tot)
//{
//	double avg;
//	avg = tot / 3.0;
//	return avg;
//}

//int rec_func(int n);
//
//int main()
//{
//	int tot , input;
//
//	printf(" 1~ n ���� ������ ���� n �Է� : ");
//	scanf("%d", &input);
//
//	tot = rec_func(input);
//
//	printf("��� : %d", tot);
//	return 0;
//}
//
//int rec_func(int n)
//{
//	int value = 0;
//
//	if (n < 1) return 0; // ����Լ��� �ݺ��� ������  ���ǽ�
//
//	value = rec_func(n - 1); //��ȯ ���� ���� �Է����ش�.	
//	
//	return value+n; // ��ȯ���� ���� �Ű������� ���ؼ� �Ѱ���.
//}

void PrimeNumCalculater(int n);

int main(void)
{
	int inputNum = 0;
	
	printf(" 2���� �Է¹��� n �������� �Ҽ� ��� �Է� : ");
	scanf("%d", &inputNum);

	PrimeNumCalculater(inputNum);

	
	return 0;
}

void PrimeNumCalculater(int n)
{
	int i, j, count = 0;

	for (i = 2; i <= n; i++)
	{
		for (j = 2; j <= i - 1; j++)
		{
			if ( i == 2 || i == 3)
			{
				printf("%d , ", i);
			}
			else if (  i % j == 0)
			{
				break;
			}
			else
			{
				printf("%d , ", i);
			}

			count++;
			if (count % 5 == 0)
				printf("\n");
		}
		
			
		
	}
}

//int rec_func(int n)
//{
//	int sum = n;
//	
//	if (n < 1) return;
//
//	printf("%d +", n);
//	sum = sum + rec_func(n - 1);
//
//	return sum;
//
//}

