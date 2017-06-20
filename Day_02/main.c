#include <stdio.h>
#include <string.h>

int main(void)
{
	// #7 
	char fruit[20] = "strawberry";
	//배열-> 같은 자료형의 집합 
	//배열명은 배열의 주소(첫번째주소)

	// #include<string.h> -> 문자열 처리 함수 집합
	printf("딸기 : %s\n", fruit);
	printf("딸기쨈 : %s %s\n", fruit, "jam");
	
	strcpy(fruit,"Banana");
	printf("바나나 : %s\n", fruit);

	//// #6
	//char ch1 = 'A';
	//char ch2 = 65;

	//printf("문자 %c의 아스키 코드값 : %d\n", ch1, ch1);
	//printf("아스키 코드값이 %d인 문자 ; %c\n", ch2, ch2);


	////	#5 변수의 초기화와 쓰레기값
	//int a;
	//int b = 20;
	//int c;

	//a = 10;
	//printf("a : %d\n", a);
	//printf("b : %d\n", b);
	//printf("c : %d\n", c);
	
	////	#4
	////	변수 선언 규칙(C언어)
	////	- 변수 선언은 최상단
	////	- 변수의 이름은 예약어 키워드 사용불가(자료형,컨테이너 이름 등등)
	////	- 이름에 공백 불가, 첫글자 숫자 불가, 특수문자 불가
	////	* 변수 이름에는 의미가 있어야 한다. 이름만 보아도 사용 용도를 알 수 있어야 한다.

	////	변수 : 자료형 변수명;
	//int a;
	//int b, c;
	//double da;
	//char ch;

	//a = 10;			// = 대입 기호 (같다 X)
	//b = a;			// L_Value(변수) <- R_Value(변수, 상수)
	//// 10 = a;  -> L_value가 변수여야 합니다 라는 오류를 호출함
	//c = a + 20;
	//da = 3.5;
	//ch = 'A';

	//printf("변수 a의 값 : %d\n", a);
	//printf("변수 b의 값 : %d\n", b);
	//printf("변수 c의 값 : %d\n", c);
	//printf("변수 da의 값 : %.1lf\n", da);
	//printf("변수 ch의 값 : %c\n", ch);


	// #3
	// %d 정수
	//printf("%d\n", 12);		//10진수
	//printf("%d\n", 014);	// 8진수
	//printf("%d\n", 0xc);	// 16진수

	//printf("%d (10) , %x (16), %o (8)\n ", 50, 50, 50);
	////		(1)			(2)			(3)		(1)(2)(3)  인수를 맞춰야 한다. 3=3, 2=2 


	//// 문자 와 문자열
	//// 문자		|	문자열
	//// 'A'		|	"ABCD...."
	////			|	\0 null (문자열의 끝) 문장의 끝을 알려주는 기호
	//// ' '		|   "" -> ("\0") 
	//// %c (char)| %s (string)
	//// 1개의 문자| 문자열의 끝까지 출력
	////				-> NULL을 만날때 까지 출력
	//printf("%c\n", 'A');
	//printf("%s\n", "A");
	//printf("%c은 %s입니다.\n", '1', "first");

	////ASCII CODE
	//printf("A -> %d\n", 'A');
	//printf("a -> %d\n", 'a');

	// #2
	//printf("1234567890\n");		//화면 칸 번호
	//printf("Be Happy\n");		// "be happy" 출력
	//printf("My\tfriend\n");		// "My" 출력 후 tab 출력
	//printf("goot\bd\tchance\n");// "t"를 "d"로 바꾸고 tab 출력
	//printf("Cow\rw\a\n");		// C를 W로 바꾸고 벨소리 출력

	//printf("%d\n", 10);			// %d 위치에 10출력
	//printf("%lf\n", 3.4);		// %lf 위치에 3.4 소수점 6자리 출력
	//printf("%.1lf\n", 3.45);	// 소수점 이하 첫째 까지 출력
	//printf("%.10lf\n", 3.4);	// 소수점 이하 10자리 까지 출력

	//printf("%d과 %d의 합은 %d 입니다. \n", 10, 20, 10 + 20);
	//printf("%.1lf - %.1lf = %.1lf\n", 3.4, 1.2, 3.4 - 1.2);


	 //#1 주석
	 //1. // 한줄주석
	 //2. /* */  여러줄 주석
	/* 문장주석 ( 블럭 설정 ) 
		주석 걸기 ctrl + K + C
		주석 풀기 ctrl + K + U
	*/
	/*printf("be happy");
	printf("my friend");

	return 0;*/

}