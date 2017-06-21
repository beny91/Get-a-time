#include <stdio.h>
#define PI 3.14
#define numType int

int main(void)
{
	// #11 복합대입 연산자 , 조건 연산자(삼항 연산자)
	int a = 10, b = 20;
	int res = 2;

	a += 20;
	res *= b + 10; // res = res *(b + 10)

	printf("a = %d, b = %d\n", a, b);
	printf("res = %d\n", res);

	// 삼항 연산자
	a = 10, b = 20;

	res = (a > b) ? a : b;
	// 조건이 참이면 a , 거짓이면 b 
	printf("큰값 : %d\n", res);

	// #10 sizeof()
	// 자료형의 크기를 반환한다.
	/*int a = 10;
	double b = 3.4;

	printf("int형 변수의 크기 : %d\n", sizeof(a));
	printf("double형 변수의 크기 : %d\n", sizeof(b));
	printf("정수형 상수의 크기 : %d\n", sizeof(10));
	printf("수식의 결과값을 크기 : %d\n", sizeof(1.5 + 3.4));
	printf("char 자료형의 크기 : %d\n", sizeof(char));*/
	//// #9 형변환 연산자
	//int a = 20, b = 3;
	//double res;

	////res = ((double)a) / ((double)b); //강제형변환
	////res = ((double)a) / b; // 피연산자만 형변환
	//res = a / b; // a/b의 결과를 double 인 res의 형변환이 일어나 6.0 이 된다.
	//printf("a = %d, b = %d\n", a, b);
	//printf("a / b의 결과 %.1lf\n", res);

	//a = (int)res;
	//printf("(int) %.1lf의 결과 %d\n", res, a);

	//// #8 관계연산자 와 논리연산자
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

	// #6 증감 연산자

	//int a = 10, b = 10;
	//
	//++a; // a = a + 1
	//--b; // b = b - 1

	//printf("a : %d\n", a);
	//printf("b : %d\n", b);

	// 증감 연산의 전위와 후위
	//int a = 5, b = 5;
	//int pre, post;

	//pre = (++a) * 3;
	//post = (b++) * 3;

	//printf("초기값 a = %d, b = %d\n", a, b);
	//printf("전위형 (++a) * 3 = %d\n", pre);
	//printf("후위형 (b++) * 3 = %d\n", post);

	// #5 산술 연산자
	//int a, b;
	//int sum, sub, mul, inv;

	//a = 10;
	//b = 20;
	//sum = a + b;
	//sub = a - b;
	//mul = a * b;
	//inv = -a;

	//printf("a의 값 : %d, b의 값 : %d \n", a, b);
	//printf("덧셈 : %d\n", sum);
	//printf("뺄셈 : %d\n", sub);
	//printf("곱셈 : %d\n", mul);
	//printf("a의 음수연산 : %d\n", inv);

	/*double apple;
	int banana;
	int orange;

	apple = 5.0 / 2.0;
	banana = 5 / 2;
	orange = 5 % 2;

	printf("apple : %.1lf\n", apple);
	printf("banana : %d\n", banana);
	printf("orange : %d\n", orange);*/

	//// #4 상수
	//// 1. 리터럴 상수
	//// 숫자상수, 문자 상수

	//// 2. 심볼릭 상수 (const)
	//// 변수를 상수화 
	//// -> 심볼릭 상수는 선언과 함께 초기화 해야한다.

	//const int Num = 100; // const 상수화
	////Num = 100; // 상수에 대입 하는 것과 같은 것 - error
	////printf("num : %d\n", Num);

	////#define(치환) -> 전처리기에 해당

	//numType a = 10;
	//printf("a : %d\n", a);
	//printf("PI : %lf\n", PI );
	//printf("PI : %lf\n", 3.14);

	//// #3 문자열 입력
	//char grade;
	//char name[20];

	//printf("학점 입력 : ");
	//scanf("%c", &grade);
	//printf("이름 입력 : ");
	//scanf("%s", name); //배열의 이름은 배열의 주소 
	//printf("%s의 학점은 %c 입니다.\n", name, grade);

	//// 0번째 주소의 값을 가져온다.
	//printf("%c\n", name[0]);

	//// #2 복수 변수 입력
	//int age;
	//double height;
	//char ch;

	//printf("나이와 키를 입력하세여 : ");
	//scanf("%d %lf", &age, &height);
	//printf("나이는 %d살, 키는 %.1lfcm입니다.\n", age, height);

	//
	//scanf("%c", &ch); //위에 개행 문자 \n 때문에 버퍼에서 \n 가져와버린다.
	//printf("입력받은값은 : %c", ch);

	//// #1 Scanf
	//
	//int a;

	//scanf("%d", &a);
	//// &a -> &(앤퍼샌트) 는 변수의 주소
	//printf("입력된 값 %d", a);

	return 0;

}