#include <stdio.h>
#define PI 3.14
#define numType int

int main(void)
{
	// #11 ���մ��� ������ , ���� ������(���� ������)
	int a = 10, b = 20;
	int res = 2;

	a += 20;
	res *= b + 10; // res = res *(b + 10)

	printf("a = %d, b = %d\n", a, b);
	printf("res = %d\n", res);

	// ���� ������
	a = 10, b = 20;

	res = (a > b) ? a : b;
	// ������ ���̸� a , �����̸� b 
	printf("ū�� : %d\n", res);

	// #10 sizeof()
	// �ڷ����� ũ�⸦ ��ȯ�Ѵ�.
	/*int a = 10;
	double b = 3.4;

	printf("int�� ������ ũ�� : %d\n", sizeof(a));
	printf("double�� ������ ũ�� : %d\n", sizeof(b));
	printf("������ ����� ũ�� : %d\n", sizeof(10));
	printf("������ ������� ũ�� : %d\n", sizeof(1.5 + 3.4));
	printf("char �ڷ����� ũ�� : %d\n", sizeof(char));*/
	//// #9 ����ȯ ������
	//int a = 20, b = 3;
	//double res;

	////res = ((double)a) / ((double)b); //��������ȯ
	////res = ((double)a) / b; // �ǿ����ڸ� ����ȯ
	//res = a / b; // a/b�� ����� double �� res�� ����ȯ�� �Ͼ 6.0 �� �ȴ�.
	//printf("a = %d, b = %d\n", a, b);
	//printf("a / b�� ��� %.1lf\n", res);

	//a = (int)res;
	//printf("(int) %.1lf�� ��� %d\n", res, a);

	//// #8 ���迬���� �� ��������
	//int a = 10, b = 20, c = 10; 
	//int res;

	//res = (a > b);
	//printf("a > b : %d\n", res);
	//res = (a >= b);
	//printf("a >= b : %d\n", res);
	//res = (a < b);
	//printf("a < b : %d\n", res);
	//res = (a <= b);
	//printf("a <= b : %d\n", res);
	//res = (a == b);
	//printf("a == b : %d\n", res);
	//res = (a != c);
	//printf("a != c : %d\n", res);

	//a = 30;
	//res = (a > 10) && (a < 20);
	//printf("(a > 10) && (a < 20) : %d\n", res);
	//res = (a < 10) || (a > 20);
	//printf("(a < 10) || (a > 20) : %d\n", res);
	//res = !(a >= 30);
	//printf("!(a >= 30 : %d\n", res);

	// #6 ���� ������

	//int a = 10, b = 10;
	//
	//++a; // a = a + 1
	//--b; // b = b - 1

	//printf("a : %d\n", a);
	//printf("b : %d\n", b);

	// ���� ������ ������ ����
	//int a = 5, b = 5;
	//int pre, post;

	//pre = (++a) * 3;
	//post = (b++) * 3;

	//printf("�ʱⰪ a = %d, b = %d\n", a, b);
	//printf("������ (++a) * 3 = %d\n", pre);
	//printf("������ (b++) * 3 = %d\n", post);

	// #5 ��� ������
	//int a, b;
	//int sum, sub, mul, inv;

	//a = 10;
	//b = 20;
	//sum = a + b;
	//sub = a - b;
	//mul = a * b;
	//inv = -a;

	//printf("a�� �� : %d, b�� �� : %d \n", a, b);
	//printf("���� : %d\n", sum);
	//printf("���� : %d\n", sub);
	//printf("���� : %d\n", mul);
	//printf("a�� �������� : %d\n", inv);

	/*double apple;
	int banana;
	int orange;

	apple = 5.0 / 2.0;
	banana = 5 / 2;
	orange = 5 % 2;

	printf("apple : %.1lf\n", apple);
	printf("banana : %d\n", banana);
	printf("orange : %d\n", orange);*/

	//// #4 ���
	//// 1. ���ͷ� ���
	//// ���ڻ��, ���� ���

	//// 2. �ɺ��� ��� (const)
	//// ������ ���ȭ 
	//// -> �ɺ��� ����� ����� �Բ� �ʱ�ȭ �ؾ��Ѵ�.

	//const int Num = 100; // const ���ȭ
	////Num = 100; // ����� ���� �ϴ� �Ͱ� ���� �� - error
	////printf("num : %d\n", Num);

	////#define(ġȯ) -> ��ó���⿡ �ش�

	//numType a = 10;
	//printf("a : %d\n", a);
	//printf("PI : %lf\n", PI );
	//printf("PI : %lf\n", 3.14);

	//// #3 ���ڿ� �Է�
	//char grade;
	//char name[20];

	//printf("���� �Է� : ");
	//scanf("%c", &grade);
	//printf("�̸� �Է� : ");
	//scanf("%s", name); //�迭�� �̸��� �迭�� �ּ� 
	//printf("%s�� ������ %c �Դϴ�.\n", name, grade);

	//// 0��° �ּ��� ���� �����´�.
	//printf("%c\n", name[0]);

	//// #2 ���� ���� �Է�
	//int age;
	//double height;
	//char ch;

	//printf("���̿� Ű�� �Է��ϼ��� : ");
	//scanf("%d %lf", &age, &height);
	//printf("���̴� %d��, Ű�� %.1lfcm�Դϴ�.\n", age, height);

	//
	//scanf("%c", &ch); //���� ���� ���� \n ������ ���ۿ��� \n �����͹�����.
	//printf("�Է¹������� : %c", ch);

	//// #1 Scanf
	//
	//int a;

	//scanf("%d", &a);
	//// &a -> &(���ۻ�Ʈ) �� ������ �ּ�
	//printf("�Էµ� �� %d", a);

	return 0;

}