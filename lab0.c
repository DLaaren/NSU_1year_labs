#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int bad_input() {
	printf("bad input\n");
	exit(0);
    return 0;    
}

unsigned int c_to_int(char n) {
	unsigned int t = n - '0';
	if(t > 9) { 
		t = tolower(n) - 'a' + 10; 
	}
	return t;
}

char int_to_c(int n) {
	if(n < 10) {
		return n + '0'; 
	}
	if(n < 16) {
		return n + 'A' - 10;
	}
	bad_input();
	return 0;
}

int check(char *s1, unsigned int b1) {
	int len = strlen(s1);
	if(s1[0] == '.' || s1[len - 1] == '.') {
		bad_input();
	}
	for(int i = 0; i < len; i++){
		if(c_to_int(s1[i]) >= b1 && s1[i] != '.') {
			bad_input();
		}
	}
	return 1;
}

int check_point(char *s1) {
	unsigned int k = 0;
	int len = strlen(s1);
	for(int i = 0; i < len; i++) {
		if(s1[i] == '.') {
			k++;
			if(k > 1) {
				bad_input();
			}
		}
	}
	return 1;
}

void point_location(char *s1, unsigned int *point) {
	int len = strlen(s1);
	for(int i = 0; i < len; i++) {
		if (s1[i] == '.') {  
			*point = i; 
		}
	}
}

void reverse(char *s) {
	int len = strlen(s);
	for(int i = 0, j = len - 1; i < j; i++, j--){
		int t = s[i];
		s[i] = s[j];
		s[j] = t;
	}
}

void add(char *s, char c) {
	char t[2] = {c, 0};
	strcat(s,t); 
}

void b1_to_decimal(unsigned int b1, unsigned long long int *num1, unsigned long long int *num2, unsigned long long int *d, char *s1, unsigned int *point) {
	for (unsigned int i = 0; i < *point; i++) {//целая
		*num1 = c_to_int(s1[i]) + *num1 * b1;
	}
	for (unsigned int i = *point + 1; i < strlen(s1); i++) {//дробная
		*num2 = c_to_int(s1[i]) + *num2 * b1;
		*d *= b1;
	}
}

void decimal_to_b2(unsigned b2, unsigned long long *num1, unsigned long long *num2, unsigned long long *d, char *s2) {
	while(*num1 >= b2) {
		char number = int_to_c(*num1 % b2);
		*num1 /= b2;
		add(s2, number);
	}

	add(s2, int_to_c(*num1));
	reverse(s2);
	
	if(*num2 != 0) {
		char comma = '.';
		add(s2, comma);
	}
	
	unsigned k = 0;
	while(*num2 != 0) {
		*num2 *= b2;
		char number2 = int_to_c(*num2 / *d);
		add(s2, number2);
		*num2 -= *d * (*num2 / *d);
		k++;
		if(k == 12) {
			break;
		}
	}
}

int main() {

	unsigned int b1, b2;
	char s1[1000] = "", s2[1000] = "";

	if(scanf("%u %u %999s", &b1, &b2, s1) != 3){
		bad_input();
	}

	if((b1 < 2 || b1 > 16) || (b2 < 2 || b2 > 16)){
		bad_input();
	}

	if (!check(s1, b1) || !check_point(s1)){
		bad_input();
	}

	unsigned int point = strlen(s1); 
	point_location(s1, &point);

	unsigned long long num1 = 0/*целая*/, num2 = 0/*дробная*/; 
	unsigned long long d = 1;
	b1_to_decimal(b1, &num1, &num2, &d, s1, &point);
	decimal_to_b2(b2, &num1, &num2, &d, s2);

	printf("%s\n", s2);
	return 0;
}
	
