#include <stdio.h> //Część deklaracyjna, deklaracja wymaganych bibliotek.
#include <stdlib.h>

struct Fraction {
	int num, den; //Definicja nowej struktury, odpowiedzialnej za przechowywanie licznika i mianownika danego ułamka
};

int gcd(int a, int b) { //Funkcja sprawdzająca czy dwie liczby podane jako argumenty mają wspólne dzielniki, jeśli tak zwraca największy, w przeciwnym wypadku funkcja zwraca 1
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}
struct Fraction printFraction(struct Fraction x) {
	if (x.den == 0) {//Próba wypisania ułamka o mianowniku równym zero, zakończy się wypisaniem NaN - Not A Number, dzielenie przez zero jest niewykonywalne
		printf("NaN");
		return;
	}
	if (x.num == 0) {//Ułamek który w którego liczniku występuje zero, ma wartośc zero
		printf("0");
		return;
	}
	if (x.num == x.den) { //Sprawdzenie czy ułamek nie jest równy 1
		printf("1");
		return;
	}
	//W dalszej części funkcji nie bierzemy już pod uwagę że licznik i mianownik są równe, lub jedno z nim jest zerem, ponieważ te przypadki zostały rozpatrzone wyżej
	if (abs(x.num) < abs(x.den)) { //Ta część funkcji wypisuje ułamki mniejsze od 1
		if (gcd(abs(x.num), abs(x.den)) != 1) { //Sprawdzenie czy licznik i mianownik występują w postaci skracalnej, funkcja gcd() zwraca wartość przez którą ułamke może zostać skrócony
			int gcd_temp = gcd(abs(x.num), abs(x.den));

			if (x.num < 0 || x.den < 0) { //Sprawdzenie czy mianownik lub licznik są liczbami ujemnymi
				if (x.num < 0 && x.den < 0) { //Licznik i mianownik są liczbami ujemnymi, gdy zachodzi taka zależność ułamek jest dodatni
					printf("%d/%d\n", abs(x.num) / gcd_temp, abs(x.den) / gcd_temp);
					return;
				}
				else { //Licznik lub mianownik jest liczbą ujemną, ułamek przyjmuje wartość ujemną
					printf("-%d/%d\n", abs(x.num) / gcd_temp, abs(x.den) / gcd_temp);
					return;
				}

			}
			else { //Licznik i mianownik są liczbami dodatnimi
				printf("%d/%d\n", x.num / gcd_temp, x.den / gcd_temp);
				return;
			}

		}
		else { //Mianownik i licznik występują w postaci nieskracalnej
			if (x.num < 0 || x.den < 0) { //Schemat działania jest taki sam jak wyżej
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
	if (abs(x.num) > abs(x.den)) { //Sprawdzenie czy ułamek jest większy od 1
		int gcd_temp = gcd(abs(x.num), abs(x.den));
		if (gcd_temp != 1) { //Sprawdzenie czy ułamek może zostać skrócony
			if (abs(x.num) % abs(x.den) == 0) { //Sprawdzenie czy licznik jest wielokrotnością mianownika, jeżeli tak wynikiem jest liczba całkowita dodatnia lub ujemna
				if (x.num < 0 | x.den < 0) { //Schemat działania jest taki sam jak wyżej
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
			} //Ułamek nie będzie liczbą całkowitą, musimy wypisać go w postaci mieszanej
			else {
				int reducedNominator = x.num / gcd(abs(x.num), abs(x.den));
				int reducedDenominator = x.den / gcd(abs(x.num), abs(x.den));
				if (x.num < 0 | x.den < 0) { //Schemat działania taki sam jak wyżej, rozpatrujemy przypadki gdy mianownik i licznik są liczbami ujemnymi, lub jeden z nich jest liczbą ujemną
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
		else { //Ułamek występuje w postaci nieskracalnej

			if (x.num < 0 | x.den < 0) { //Schemat działania taki jak wyżej
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

struct Fraction sum(struct Fraction x, struct Fraction y) { //Funkcja której zadaniem jest zsumowanie dwóch ułamków i wypisanie tej sumy w postaci właściwej
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

struct Fraction sub(struct Fraction x, struct Fraction y) { //Funkcja której zadaniem jest odjęcie ułamka y od ułamka x, i wypisanie wyniku w postaci właściwej
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

struct Fraction mul(struct Fraction x, struct Fraction y) { //Funkcja której zadaniem jest wykonanie mnożenia dwóch ułamków i wypisanie wyniku w postaci właściwej
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
struct Fraction quo(struct Fraction x, struct Fraction y) { //Funkcja której zadaniem jest wykonanie dzielenia dwóch ułamków i wypisanie wyniku w postaci właściwej
	int a = x.num; //licznik ulamka x
	int b = x.den;// mianownik ulamka x

	int c = y.num; //licznik ulamka y
	int d = y.den;// mianownik ulamka y
	if (c == 0) { //Dzielenie przez zero jest działaniem niewykonywalnym, program nie wykoan się i zwróci błąd
		printf("Błąd! Dzielenie przez zero jest niewykonywalne!");
		return;
	}

	struct Fraction z;
	z.num = a * d;
	z.den = b * c;
	printFraction(z);
	printf("\n");

}
struct Fraction fractionOperation(char operation, struct Fraction x, struct Fraction y) { //Funkcja wywołująca odpowiednie działanie na podstawie znaku który wprowadził użytkownik
	printFraction(x);
	printf("%c \n", operation);
	printFraction(y);
	printf("\n");
	printf("=\n");
	struct Fraction z;
	switch (operation) {
	case '+': //Wywołanie dodawania
		z = sum(x, y);
		break;
	case '-': //Wywołanie odejmnowania
		z = sub(x, y);
		break;
	case '/': //Wywołanie dzielenia
		z = quo(x, y);
		break;
	case '*': //Wywołanie mnożenia
		z = mul(x, y);
		break;
	default:
		printf("Niepoprawne działanie! Dostępne opcje: +, -, *, /");
		break;

		printFraction(z);
	}
}
void readFraction(struct Fraction* fraction) {
	char input[50];  // Zakładamy, że maksymalna długość wprowadzonego ciągu to 50 znaków

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
		}
	}
}
char readOperation() { //Sposób działania funkcji jest analogiczny do funkcji readFraction()
	char operation;
	do {
		printf("Wprowadz dzialanie (+, -, *, /): ");
		scanf_s(" %c", &operation, sizeof(operation));
	} while (operation != '+' && operation != '-' && operation != '*' && operation != '/');
	return operation;
}

int main() { //Funkcja main, wywoływanie funkcji
	struct Fraction z, q;
	readFraction(&z);
	readFraction(&q);
	char operation = readOperation();
	if (operation == '/' && q.num == 0) 
		printf("Błąd! Dzielenie przez zero jest niewykonywalne!");
	else
		fractionOperation(operation, z, q);
}
