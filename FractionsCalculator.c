#include <stdio.h>
#include <stdlib.h>

struct Fraction {
	int num, den; //numerator, denomiator czyli licznik i mianownik
};

int gcd(int a, int b) { //Najwiekszy wspolny dzielnik
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}
struct Fraction printFraction(struct Fraction x) {
	if (x.den == 0) {//czy da sie wykonac dzielenie przez zero?
		printf("NaN");
		return;
	}
	if (x.num == 0) {//co w przypadku gdy licznik jest rowny zero?
		printf("0");
		return;
	}
	if (x.num == x.den) { //
		printf("1");
		return;
	}
	if (abs(x.num) < abs(x.den)) { //ulamki mniejsze od 1
		if (gcd(abs(x.num), abs(x.den)) != 1) { //sprawdzenie czy mianownik i licznik maja najwiekszy wspolny dzielnik
			int gcd_temp = gcd(abs(x.num), abs(x.den));

			if (x.num < 0 || x.den < 0) {
				if (x.num < 0 && x.den < 0) {
					printf("%d/%d\n", abs(x.num) / gcd_temp, abs(x.den) / gcd_temp);
					return;
				}
				else {
					printf("-%d/%d\n", abs(x.num) / gcd_temp, abs(x.den) / gcd_temp);
					return;
				}

			}
			else {
				printf("%d/%d\n", x.num / gcd_temp, x.den / gcd_temp);
				return;
			}

		}
		else {
			if (x.num < 0 || x.den < 0) {
				if (x.num < 0 && x.den < 0) {
					printf("%d/%d\n", x.num, x.den);
					return;
				}
				else {
					printf("-%d/%d\n", abs(x.num), abs(x.den));
					return;
				}

			}
			else {
				printf("%d/%d\n", x.num, x.den);
				return;
			}
		}
	}
	if (abs(x.num) > abs(x.den)) { //ulamki wieksze od 1
		int gcd_temp = gcd(abs(x.num), abs(x.den));
		if (gcd_temp != 1) { //jest najwiekszy wspolny dzielnik
			if (abs(x.num) % abs(x.den) == 0) { //wypisywanie ulamków w postaci liczby calkowitej
				if (x.num < 0 | x.den < 0) {
					if (x.num < 0 && x.den < 0) {
						printf("%d\n", abs(x.num) / abs(x.den));
						return;
					}
					else {
						printf("-%d\n", abs(x.num) / abs(x.den));
						return;
					}

				}
				else {
					printf("%d\n", abs(x.num) / abs(x.den));
					return;
				}
			}
			else {
				int reducedNominator = x.num / gcd(abs(x.num), abs(x.den));
				int reducedDenominator = x.den / gcd(abs(x.num), abs(x.den));
				if (x.num < 0 | x.den < 0) {
					if (x.num < 0 && x.den < 0) {
						printf("%d %d/%d\n", abs(reducedNominator) / abs(reducedDenominator), abs(reducedNominator) % abs(reducedDenominator), abs(reducedDenominator));
						return;
					}
					else {
						printf("-%d %d/%d\n", abs(reducedNominator) / abs(reducedDenominator), abs(reducedNominator) % abs(reducedDenominator), abs(reducedDenominator));
						return;
					}

				}
				else {
					printf("%d %d/%d\n", reducedNominator / reducedDenominator, reducedNominator % reducedDenominator, reducedDenominator);
					return;

				}

			}
		}
		else { //nie ma najwiekszego wspolnego dzielnika

			if (x.num < 0 | x.den < 0) {
				if (x.num < 0 && x.den < 0) {
					printf("%d %d/%d\n", abs(x.num) / abs(x.den), abs(x.num) % abs(x.den), abs(x.den));
					return;
				}
				else {
					printf("-%d %d/%d\n", abs(x.num) / abs(x.den), abs(x.num) % abs(x.den), abs(x.den));
					return;
				}

			}
			else {
				printf("%d %d/%d\n", x.num / x.den, x.num % x.den, x.den);
				return;
			}
		}
	}
	return;
}
/*
a/b + c/d = (a*d)/(b*d) + (c*b)/(d*b) = (a*d + c*b) / (b*d)
*/

struct Fraction sum(struct Fraction x, struct Fraction y) { //suma dwoch ulamkow
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y

	struct Fraction z;
	z.num = (a * d) + (c * b);
	z.den = b * d;

	printFraction(z);
	printf("\n");
}
/*
a/b - c/d = (a*d)/(b*d) - (c*b)/(d*b) = (a*d - c*b) / (b*d)
*/

struct Fraction sub(struct Fraction x, struct Fraction y) { //roznica dwoch ulamkow
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y

	struct Fraction z;
	z.num = (a * d) - (c * b);
	z.den = b * d;
	printFraction(z);
	printf("\n");

}
/*
a/b * c/d = a*c/b*d
*/

struct Fraction mul(struct Fraction x, struct Fraction y) { //iloczyn dwoch ulamkow
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
/*
a/b % c/d = a*d/b*c
*/
struct Fraction quo(struct Fraction x, struct Fraction y) { //iloraz dwoch ulamkow
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
struct Fraction fractionOperation(char operation, struct Fraction x, struct Fraction y) { //funckja wywolujaca dzialania, na podstawie danych przekazanych przez uzytkownika
	printFraction(x);
	printf("%c \n", operation);
	printFraction(y);
	printf("\n");
	printf("=\n");
	struct Fraction z;
	switch (operation) {
	case '+':
		z = sum(x, y);
		break;
	case '-':
		z = sub(x, y);
		break;
	case '/':
		z = quo(x, y);
		break;
	case '*':
		z = mul(x, y);
		break;
	default:
		printf("Niepoprawne działanie! Dostępne opcje: +, -, *, /");
		break;

		printFraction(z);
	}
}
void readFractions(struct Fraction* fraction) {
	printf("Podaj ulamek w formacie a/b: ");
	scanf_s("%d/%d", &(fraction->num), &(fraction->den));
}
void readFraction(struct Fraction* fraction) {
	char input[50];  // Zakładam, że maksymalna długość wprowadzonego ciągu to 50 znaków

	// Używamy pętli while, aby kontynuować próby wczytywania, dopóki nie zostanie wprowadzony poprawny format
	while (1) {
		printf("Podaj ulamek w formacie a/b: ");
		scanf_s("%s", input, sizeof(input));

		// Używamy sscanf do analizy wprowadzonego ciągu w formacie a/b
		int result = sscanf_s(input, "%d/%d", &(fraction->num), &(fraction->den));

		// Sprawdzamy, czy udało się poprawnie wczytać wartości
		if (result == 2) {
			break;  // Wychodzimy z pętli, gdy dane zostały poprawnie wczytane
		}
		else {
			printf("Bledny format. Podaj ulamek w formacie a/b.\n");
			// Opcjonalnie, można dodać kod obsługujący ten błąd, np. poprzez ponowne wywołanie funkcji lub zakończenie programu
		}
	}
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
	struct Fraction z, q;
	readFraction(&z);
	readFraction(&q);
	char operation = readOperation();
	fractionOperation(operation, z, q);
}
