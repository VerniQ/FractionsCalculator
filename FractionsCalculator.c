#include <stdio.h>
#include <stdlib.h>

struct Fraction {
	int num, den; //numerator, denomiator
};


int smaller(int a, int b) {
	if (a < b) return a;
	return b;
}
int gcd(int a, int b) { //Greatest common divisor
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}
struct Fraction printFraction(struct Fraction x) {
	int a = x.num;
	int b = x.den;
	if (b == 0) {
		printf("NaN");
		return;
	}
	if (a == 0) {
		printf("0");
		return;
	}
	if (abs(a) < abs(b)) { //fraction lower than 1
		if (gcd(abs(a), abs(b)) != 1) { //Check if numbers have common divisor
			int gcd_temp = gcd(abs(a), abs(b));

			if (a < 0 || b < 0) {
				if (a < 0 && b < 0) {
					printf("%d/%d", a / gcd_temp, b / gcd_temp);
					return ;
				}
				else {
					printf("-%d/%d", abs(a) / gcd_temp, abs(b) / gcd_temp);
					return ;
				}

			}
			else {
				printf("%d/%d", a / gcd_temp, b / gcd_temp);
				return ;
			}

		}
		else {
			if (a < 0 || b < 0) {
				if (a < 0 && b < 0) {
					printf("%d/%d", a, b);
					return ;
				}
				else {
					printf("-%d/%d", abs(a), abs(b));
					return ;
				}

			}
			else {
				printf("%d/%d", a, b);
				return ;
			}
		}
	}
	if (abs(x.num) > abs(x.den)) { //fraction greater than 1
		int gcd_temp = gcd(abs(a), abs(b));
		if (gcd_temp != 1) { //jest najwiekszy wspolny dzielnik
			if (abs(x.num) % abs(x.den) == 0) { //wypisywanie u³amków w postaci liczby ca³kowitej
				if (x.num < 0 | x.den < 0) {
					printf("-%d", abs(x.num) / abs(x.den));
					return;
				}
				else {
					printf("%d", abs(x.num) / abs(x.den));
					return;
				}
			}
			else {
				int reducedNominator = x.num / gcd(abs(x.num), abs(x.den));
				int reducedDenominator = x.den / gcd(abs(x.num), abs(x.den));
				if (x.num < 0 | x.den < 0) {
					printf("-%d %d/%d\n", abs(reducedNominator) / abs(reducedDenominator), abs(reducedNominator) % abs(reducedDenominator), abs(reducedDenominator));
					return;
				}
				else {
					printf("%d %d/%d\n", reducedNominator / reducedDenominator, reducedNominator % reducedDenominator, reducedDenominator);
					return;

				}
				
			}
		}
		else { //nie ma najwiekszego wspolnego dzielnika

			if (x.num < 0 | x.den < 0) {
				printf("-%d %d/%d\n", abs(x.num) / abs(x.den), abs(x.num) % abs(x.den), abs(x.den));
				return;
			}
			else {
				printf("%d %d/%d\n", x.num / x.den, x.num % x.den, x.den);
				return;
			}
		}
	}
}
struct Fraction sum(struct Fraction x, struct Fraction y) {
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y

	struct Fraction z;
	z.num = a * d + c * b;
	z.den = b * d;

	printFraction(z);
	printf("\n");
}
struct Fraction sub(struct Fraction x, struct Fraction y) {
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y

	struct Fraction z;
	z.num = a * d - c * b;
	z.den = b * d;
	printFraction(z);
	printf("\n");

}
struct Fraction mul(struct Fraction x, struct Fraction y) {
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y

	struct Fraction z;
	z.num = a * c;
	z.den = b * d;
	printFraction(z);
	printf("\n");

}
struct Fraction quo(struct Fraction x, struct Fraction y) {
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y

	struct Fraction z;
	z.num = a * d;
	z.den = b * c;
	printFraction(z);
	printf("\n");

}
struct Fraction fractionOperation(char operation, struct Fraction x, struct Fraction y) {
	printFraction(x);
	printf("\n");
	printf("%c \n", operation);
	printFraction(y);
	printf("\n");
	printf("=");
	printf("\n");
	struct Fraction z;
	switch (operation) {
	case '+':
		z = sum(x, y);
		break;
	case '-':
		z = sub(x, y);
		break;
	case '%':
		z = quo(x, y);
		break;
	case '*':
		z = mul(x, y);
		break;
	default:
		printf("Unexpected operation. Please try again");
		break;

		printFraction(z);
	}
}
void readFraction(struct Fraction* fraction) {
	printf("Podaj ulamek w formacie a/b: ");
	scanf_s("%d/%d", &(fraction->num), &(fraction->den));
}
char readOperation() {
	char operation;
	do {
		printf("Wprowadz dzialanie (+, -, *, /): ");
		scanf_s(" %c", &operation, sizeof(operation));
	} while (operation != '+' && operation != '-' && operation != '*' && operation != '/');
	return operation;
}

int main() {
	struct Fraction x = {2, 5};
	struct Fraction y = { 1, 2};
	//printFraction(x);
	struct Fraction z, q;
	readFraction(&z);
	readFraction(&q);
	char operation = readOperation();
	fractionOperation(operation, z, q);
}