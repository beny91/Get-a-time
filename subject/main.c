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
//	printf("국어, 영어, 수학 3과목의 점수를 입력해 주세요. : ");
//	scanf("%d", &kor);
//	scanf("%d", &eng);
//	scanf("%d", &mat);
//
//	tot = total(kor, eng, mat);
//	avg = average(tot);
//
//	printf("--------------------------\n");
//	printf(" 국어 \t 영어 \t 수학 \t\t\t 총점\t 평균\n");
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
//	printf(" 1~ n 까지 더해질 숫자 n 입력 : ");
//	scanf("%d", &input);
//
//	tot = rec_func(input);
//
//	printf("결과 : %d", tot);
//	return 0;
//}
//
//int rec_func(int n)
//{
//	int value = 0;
//
//	if (n < 1) return 0; // 재귀함수의 반복을 끊어줄  조건식
//
//	value = rec_func(n - 1); //반환 받은 값을 입력해준다.	
//	
//	return value+n; // 반환받은 값과 매개변수를 더해서 넘겨줌.
//}

void PrimeNumCalculater(int n);

int main(void)
{
	int inputNum = 0;
	
	printf(" 2부터 입력받은 n 값까지의 소수 출력 입력 : ");
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

