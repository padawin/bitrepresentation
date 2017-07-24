#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void showbits(unsigned int x);
char readDigit();
char readLetter(const char *prompt);
char readChar();
void readString(char* str);

void showbits(unsigned int x) {
	int i;
	for(i=(sizeof(int)*8)-1; i>=0; i--)
		(x&(1u<<i))?putchar('1'):putchar('0');

	printf("\n");
}

void readString(char str[3]) {
	size_t sizeChoice = 3;
	char* in = malloc(sizeof(char) * sizeChoice);
	getline(&in, &sizeChoice, stdin);
	strncpy(str, in, 3);
	free(in);
}

int main() {
	int a, b, res = 0;
	char operator[3];
	char buf[3];
	char valid = 0;
	printf("\nNumber a: ");
	readString(buf);
	a = atoi(buf);
	while (!valid) {
		printf("\nOperation (|, &, ^, <<, >> ~): ");
		readString(buf);
		operator[0] = buf[0];
		switch (operator[0]) {
			case '<':
			case '>':
				if (buf[1] != buf[0]) {
					break;
				}
				operator[1] = operator[0];
				valid = 1;
				operator[2] = '\0';
			case '|':
			case '&':
			case '^':
				printf("\nNumber b: ");
				readString(buf);
				b = atoi(buf);
				if (!valid) {
					valid = 1;
					operator[1] = '\0';
				}
				break;
			case '~':
				valid = 1;
				break;
			default:
				break;
		}
	}

	if (operator[0] == '~') {
		res = ~a;
		printf("%s%d = %d\n", operator, a, res);

		printf("a:\t");
		showbits(a);
		printf("\nres:\t");
		showbits(res);
	}
	else {
		switch (operator[0]) {
			case '<':
				res = a << b;
				break;
			case '>':
				res = a >> b;
				break;
			case '|':
				res = a | b;
				break;
			case '&':
				res = a & b;
				break;
			case '^':
				res = a ^ b;
				break;
		}
		printf("%d %s %d = %d\n", a, operator, b, res);

		printf("a:\t");
		showbits(a);
		printf("\nb:\t");
		showbits(b);
		printf("\nres:\t");
		showbits(res);
	}

	///* assume we have a function that prints a binary string when given
	//   a decimal integer
	//   */
	//showbits(j);

	///* the loop for right shift operation */
	//for ( m = 0; m <= 5; m++ ) {
	//	n = j >> m;
	//	printf("%d right shift %d gives ", j, m);
	//	showbits(n);
	//}
	return 0;
}
