#include <stdio.h>
#include <stdlib.h>

struct Fraction {
	int num, den; //numerator, denomiator
};

struct Fraction sum(struct Fraction x, struct Fraction y) {
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y

	struct Fraction z;
	z.num = a * d + c * b;
	z.den = b * d;
	return z;
}
struct Fraction sub(struct Fraction x, struct Fraction y) {
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y

	struct Fraction z;
	z.num = a * d - c * b;
	z.den = b * d;
	return z;

}
struct Fraction mul(struct Fraction x, struct Fraction y) {
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y

	struct Fraction z;
	z.num = a * c;
	z.den = b * d;
	return z;

}
struct Fraction quo(struct Fraction x, struct Fraction y) {
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y

	struct Fraction z;
	z.num = a * d;
	z.den = b * c;
	return z;

}
int smaller(int a, int b) {
	if (a < b) return a;
	return b;
}
/*struct Fraction printFraction(struct Fraction x) {
	int a = x.num;
	int b = x.den;
	int temp1;
	int temp2;

	if (b == 0) {
		printf("NaN");
	}
	else if (a == 0) {
		printf("0");
	}
	//else if (a > 0 && b > 0) {
		if (abs(a) > abs(b)) {
			int complete = a / b;
			int rest = a % b;
			int min = b;

			if (rest != 0) {
				printf(" %d %d/%d", complete, rest, b);
			}
			else {
				printf("%d", complete);

			}

		}
		else {
			for (int i = smaller(abs(a), abs(b)); i > 0; i--) {
				if (abs(a) % i == 0 && abs(b) % i == 0) {
					temp1 = abs(a);
					temp2 = abs(b);

					temp1 = temp1 / i;
					temp2 = temp2 / i;

				}
			}
			printf("%d/%d", a, temp2);
		}

	return x;
}*/
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
	if (b == 0) printf("NaN");
	if (a == 0) printf("0");
	if (abs(a) < abs(b)) { //fraction lower than 1
		if (gcd(abs(a), abs(b)) != 1) { //Check if numbers have common divisor
			int gcd_temp = gcd(abs(a), abs(b));

			if (a < 0 || b < 0) {
				if (a < 0 && b < 0) {
					printf("%d/%d", a / gcd_temp, b / gcd_temp);
				}
				else {
					printf("-%d/%d", abs(a) / gcd_temp, abs(b) / gcd_temp);
				}

			}
			else {
				printf("%d/%d", a / gcd_temp, b / gcd_temp);
			}

		}
		else {
			if (a < 0 || b < 0) {
				if (a < 0 && b < 0) {
					printf("%d/%d", a, b);
				}
				else {
					printf("-%d/%d", abs(a), abs(b));
				}

			}
			else {
				printf("%d/%d", a, b);
			}
		}
	}
	if (a > b) { //fraction greater than 1
		int gcd_temp = gcd(abs(a), abs(b));
		if (gcd_temp != 1) {
			if (abs(a) % b == 0) {
				if (a < 0 || b < 0) {
					printf("-%d", a / b);
				}
				else {
					printf("%d", a / b);
				}
			}
		}
		else {
			int complete = a / b;
			int rest = a % b;
			if (a < 0 || b < 0) {
				if (a < 0 && b < 0) {
					printf("%d %d/%d", abs(complete), abs(rest), abs(b));
				}
				else {
					printf("-%d %d/%d", abs(complete), abs(rest), abs(b));
				}

			}
			else {
				printf("%d %d/%d", abs(complete), abs(rest), abs(b));
			}





		}
	}
}
int main() {
	struct Fraction x = { 38, 6 };
	printFraction(x);
}