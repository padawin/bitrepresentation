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
	for(i=(sizeof(int)*8)-1; i>=0; i--) {
		(x&(1u<<i))?putchar('1'):putchar('0');
	}
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
		printf("Operation (|, &, ^, <<, >>, ~): ");
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
				printf("Number b: ");
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
	}

	printf("\n################################\n");
	printf("Bit Representation\n");
	printf("################################\n\n");
	printf("a:\t");
	showbits(a);
	if (operator[0] != '~') {
		printf("\nb:\t");
		showbits(b);
	}
	printf("\nres:\t");
	showbits(res);
	printf("\n");

	return 0;
}
