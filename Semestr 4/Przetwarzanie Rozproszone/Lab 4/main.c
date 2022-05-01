#include <windows.h>
#include <stdio.h>
#include <conio.h>
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma argsused
struct dane_dla_watku // tablica zawiera dane , ktore otrzymaja watki
{
	char nazwa[50];
	int parametr;
} dane[5] = { { "[1]" , 5 } , { "[2]" , 8 } , { "[3]" , 12 }, { "[4]" , 16 }, { "[5]" , 20 } };

// priorytety watkow
int priorytety[5] = {
	//THREAD_PRIORITY_BELOW_NORMAL,
	THREAD_PRIORITY_NORMAL ,
	THREAD_PRIORITY_NORMAL ,
	THREAD_PRIORITY_NORMAL ,
	THREAD_PRIORITY_NORMAL ,
	THREAD_PRIORITY_ABOVE_NORMAL
};

HANDLE watki[5]; // dojscia ( uchwyty ) watkow
// deklaracja funkcji watku
DWORD WINAPI funkcja_watku(void * argumenty);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int main(int argc, char ** argv)
{
	int i;
	DWORD id; // identyfikator watku
	system("cls");
	printf(" Uruchomienie programu \n");
	// tworzenie watkow
	for (i = 0; i < 5; i++)
	{
		watki[i] = CreateThread(
			NULL, // atrybuty bezpieczenstwa
			0, // inicjalna wielkosc stosu
			funkcja_watku, // funkcja watku
			(void *)& dane[i],// dane dla funkcji watku
			0, // flagi utworzenia
			&id);
		if (watki[i] != INVALID_HANDLE_VALUE)
		{
			printf(" Utworzylem watek %s o id %x \n", dane[i].nazwa, id);
			// ustawienie priorytetu
			SetThreadPriority(watki[i], priorytety[i]);
		}
	}
	Sleep(4000);
	TerminateThread(watki[4], 1);
	printf("killed %s \n", dane[4].nazwa);
	Sleep(15000); // uspienie watku glownego na 20 s
	return 0;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// trzy takie funkcje pracuja wspolbieznie w programie
DWORD WINAPI funkcja_watku(void * argumenty)
{
	Sleep(100);
	struct dane_dla_watku * moje_dane = (struct dane_dla_watku *) argumenty;
	printf("%s - wiadomosc nr 1\n", moje_dane->nazwa);
	Sleep(10000);
	printf("%s - wiadomosc nr 2\n", moje_dane->nazwa);
	Sleep(2000);
	printf("koniec watku: %s\n", moje_dane->nazwa);
	return 0;
}