#include<stdio.h>

int main(void)
{

	// #9 break, continue
	for (int i = 0; i < 10; i++)
	{
		if (i > 8)
			break; // 8���� ũ�� �ݺ��� ������

		if (i == 2)
			continue; // ������ ���� ��Ű�� ���ǹ����� �̵�

		printf("%d\n", i);
	}

	//// # ��ø for
	//int i, j;
	//for (i = 0; i < 3; i++)
	//{
	//	for (j = 0; j < 5; j++)
	//	{
	//		printf("*");
	//	}
	//	printf("\n");
	//}

	////������
	//int dan = 2;
	//for (int i = 1; i < 10; i++)
	//{
	//	//printf("%d X %d = %d\n", dan, i, dan*i);
	//	//printf("%03d X %03d = %03d\n", dan, i, dan*i); �� �ڸ� Ȯ�� ������ĭ 0 ���� ä���
	//	//printf("%-3d X %-3d = %-3d\n", dan, i, dan*i); ���� ���� �� �ڸ� Ȯ��
	//	//printf("%+3d X %+3d = %+3d\n", dan, i, dan*i); ������ ���� ���ڸ� Ȯ�� ��ȣǥ��.
	//}


	// #7 do while
	// ���� �ѹ��� ������ ����
	/*int a = 1;
	do
	{
		a = a * 2;
	} while (a < 2);
	printf("a : %d\n", a);*/

	// #6 for
	
	/*
	for ( �ʱⰪ ; ���ǰ� ; ������ ) // ������ ���� ( ; ; ) �̷�������
	{
		���๮;
	}
	*/

	/*int a = 1;
	int i;

	for (i = 0; i < 3; i++)
	{
		a = a * 2;
	}
	printf("a : %d\n", a);*/

	//int i = 0, sum = 0;
	//for (i = 0; i <= 10; i++)
	//{
	//	sum += i;
	//	printf("i = %d, sum = %d\n", i, sum);
	//}

	/*int j = 0, sum = 0;
	for (;;)
	{
		if (j > 10)
			break;

		sum += j;
		printf("j = %d, sum = %d\n", j, sum);
		j++;
	}
	printf("Exit! \n");*/

	// #5 while

	/*
	 while( ���ǽ� ) 
	 {
		������ ( ���ǽ��� �� ����)
		���๮

		����б���( ����ó��)
	 }
	*/

	//int a = 1;
	////while (a < 10)
	////{
	////	a *= 2;  // a = a * 2;
	////	printf("a : %d\n", a);
	////}

	//while (1)
	//{
	//	a *= 2;
	//	printf("a : %d\n", a);

	//	//���ǽ�
	//	if (a > 10)
	//		break;
	//}

	//printf("out a : %d\n", a);

	//��ø while

	/*int  i = 0, j = 0;

	while (i < 2)
	{
		printf("i �ݺ�\n");
		while (j < 2)
		{
			printf("	j �ݺ� \n");
			j++;
		}
		i++;
		j = 0;
	}*/


	//double height = 1.70, weight = 75, BMI;
	//BMI = weight / (height * height);

	////(BMI > 18.50) && (BMI < 25.90)

	//if ((BMI > 18.50) && (BMI < 25.90))
	//{
	//	printf(" ǥ���Դϴ�.\n");
	//}
	//else
	//{
	//	//
	//	if (BMI <= 18.50)
	//	{
	//		printf(" ���� ü���� ����!\n");
	//	}
	//	else
	//	{
	//		printf(" ���� ü���� ����!\n");
	//	}
	//}

	//if switch EX
	//---------------------------------------------//
	/*int score = 0;
	char grade;
	printf("���� �Է� [0 ~ 100] : ");
	scanf("%d", &score);*/

	//if (score > 90)
	//{
	//	grade = 'A';
	//}
	//else if (score > 80)
	//{
	//	grade = 'B';
	//}
	//else if (score > 70)
	//{
	//	grade = 'C';
	//}
	//else if (score > 60)
	//{
	//	grade = 'D';
	//}
	//else
	//{
	//	grade = 'F';
	//}
	/*score /= 10;
	score -= 1;
	switch (score)
	{
		case  9:
			grade = 'A';
			break;

		case 8:
			grade = 'B';
			break;

		case 7:
			grade = 'C';
			break;
		case 6:
			grade = 'D';
			break;
		default :
			grade = 'F';
			break;
	}

	printf("���� : %d ���� : %c", score, grade);*/
	//---------------------------------------------//

	//---------------------------------------------//
	/*int rank, m = 0;
	printf("���� : ");
	scanf("%d", &rank);

	switch (rank)
	{
	case 3:
	case 4:
		m = 200;
		break;

	case 1:
	case 2:
		m = 300;
		break;
	
	case 5:
	case 6:
		m = 100;
		break;

	default:
		m = 10;
		break;
	}

	if (rank < 7)
	{
		if (rank >= 5)
		{
			m = 100;
		}
		else if (rank >= 3)
		{
			m = 200;
		}
		else if (rank >= 1)
		{
			m = 300;
		}
	}
	else
	{
		m = 10;
	}

	printf(" ���� : %d ��� : %d\n", rank, m);
*/
	//---------------------------------------------//
	


	////#3 Switch case
	//int Rank = 2, m = 0;
	//// ���ǽ� - ������ ����� ����
	//// �Ǽ�(�Ҽ���), ���迬�� ���� �� �� ����.
	//switch (Rank) //������ �Ǵ� ���ǽ� �Ǵ� ���� 
	//{
	//case 1:
	//	m = 300;
	//	break;
	//case 2:
	//	m = 200;
	//	break;
	//case 3:
	//	m = 100;
	//	break;
	//default : 
	//	m = 10;
	//	break;
	//}

	//printf(" m : %d\n", m);


	//// #2 if~ else if ~ else
	//int a = 0, b = 0;

	//if (a > 0)
	//{
	//	printf("(a > 0) True\n");
	//	b = 1;
	//}
	//else if (a == 0)		//if( (a <= 0) && (a == 0) )  
	//{
	//	printf("(a > 0) False (a == 0) True\n");
	//	b = 2;
	//}
	//else
	//{
	//	printf("(a > 0) False (a == 0) False\n");
	//	b = 3;
	//}

	//printf("b : %d\n", b);

	//// #1 ���ǹ�

	//int a = 20, b = 0;

	//if (a > b)
	//{
	//	b = a;
	//}

	//
	//printf("a : %d, b : %d\n", a, b);

	//if (a >= 0)
	//{
	//	a = 1;
	//}
	//else
	//{
	//	if (a < -10)
	//	{
	//		a = -10;
	//	}
	//	else
	//	{
	//		a = -1;
	//	}

	//	a = -1;
	//}

	//printf("a : %d \n", a);

	return 0;
}