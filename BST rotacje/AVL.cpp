#include <iostream>
#include <time.h>
using namespace std;

struct wezel
{
	int klucz;
	struct wezel *lewy;
	struct wezel *prawy;
	int wspolczynnik_wywazenia;
};

int dodaj(struct wezel *&korzen, int klucz);
void losuj(struct wezel *&korzen, int x);
void wyswietl(struct wezel *korzen);
int znajdz(struct wezel *korzen, int x);
int usun(struct wezel *&korzen, int klucz);
int rotacja_prawa(struct wezel *&korzen, int klucz);
int rotacja_lewa(struct wezel *&korzen, int klucz);
void lista_liniowa( struct wezel *&korzen);
void wywazanie(long int ilosc_elementow, struct wezel *&korzen);
wezel *&ojciec(struct wezel *&korzen, int klucz);
int AVL(struct wezel *&korzen, int klucz);
void rekonstrukcja(struct wezel *&korzen, int klucz);


int ilosc_elementow = 0;


void main ()
{
	wezel *drzewko;
	drzewko = NULL;

	int a;
	do
	{
		cout << endl << "Wybierz opcje" << endl
			 << "1. Wstawianie X losowych elementow" << endl
			 << "2. Wstawianie elementu" << endl
			 << "3. Szukanie, czy zadany element znajduje sie w drzewku" << endl
			 << "4. Usuwanie wartosci z drzewa" << endl
			 << "5. Wyswietlanie" << endl
			 << "6. Rotacja w prawo" << endl
			 << "7. Rotacja w lewo" << endl
			 << "8. Zamien w liste liniowa" << endl
			 << "9. Wywazanie" << endl
			 << "0. Wyjscie" << endl;

		cout << endl;
		cin >> a;

		cout << endl;

		switch (a)
		{
		case 1: 
			{
				int x;
				cout << "Podaj ilosc elementow, ktore chcesz wstawic" << endl << endl;
				cin >> x;

				losuj(drzewko,x);
				break;
			}
		case 2:
			{
				int x;
				cout << "Podaj wartosc, jaka chcesz wstawic" << endl << endl;
				cin >> x;

				if(dodaj(drzewko,x))
					cout << endl << "Taka wartosc juz istnieje w drzewku" << endl;
				break;
			}
		case 3:
			{
				int x;
				cout << "Podaj wartosc, jakiej chcesz szukac" << endl << endl;
				cin >> x;
				cout << endl;

				if(znajdz(drzewko,x))
				
				{
					cout << "Zadana wartosc znajduje sie w drzewku"<< endl << endl;

				}
				else {
					cout << "Zadanej wartosci nie ma w drzewku"<< endl << endl;
				};

				break;
			}
		case 4:
			{
				int x;
				cout << "Podaj, ktory klucz chcesz usunac z drzewka" << endl << endl;
				cin >> x;
				cout << endl;

				if(usun(drzewko,x))
					cout<< "Hola, hola Szeryfie! Nie mozna usunac elementu, ktorego nie ma!" << endl;
				else
					cout << "Usunieto klucz: " << x << endl;
				break;
			}
		case 5:
			{
				if (!drzewko)
					cout << "Drzewko jest puste" << endl;
				else
				{
					cout << "Oto drzewko" << endl << endl;
					wyswietl(drzewko);

					cout << endl << "Korzeniem jest: " << drzewko->klucz << endl;
				}
				break;
			}
		case 6:
			{
				int x;
				cout << "Podaj klucz, wzgledem ktorego chcesz rotowac" << endl << endl;
				cin >> x;
				cout << endl;
				if(rotacja_prawa(drzewko, x))
					cout << "Nie mozna rotowac tego elementu w prawo" << endl << endl;
				else 
					cout << "Dokonano rotacji elementu " << x << " w prawo" << endl << endl;

				break;
			}
		case 7:
			{
				int x;
				cout << "Podaj klucz, wzgledem ktorego chcesz rotowac" << endl << endl;
				cin >> x;
				cout << endl;
				if(rotacja_lewa(drzewko, x))
					cout << "Nie mozna rotowac tego elementu w lewo" << endl << endl;
				else
					cout << "Dokonano rotacji elementu " << x << " w lewo" << endl << endl;

				break;
			}
		case 8:
			{
				lista_liniowa ( drzewko );
				break;
			}
		case 9:
			{
				cout << ilosc_elementow << endl;
				lista_liniowa ( drzewko );
				wywazanie ( ilosc_elementow, drzewko );
				break;
			}
		case 0:
			{
				break;
			}
			break;
		}
	}
	while(a!=0);

	system("pause");

}


int dodaj(struct wezel *&korzen, int klucz)
{
	struct wezel *biezacy, *poprzedni, *nowy_wezel, *przodek, * bufor;
	int bufor_klucza;
	nowy_wezel = new wezel;
	nowy_wezel->lewy = NULL;
	nowy_wezel->prawy = NULL;
	nowy_wezel->klucz = klucz;
	nowy_wezel->wspolczynnik_wywazenia = 0;
	poprzedni = NULL;
	biezacy = korzen;

cout << "Dodaje: " << klucz << endl;
ilosc_elementow++;
	while(biezacy)
	{
		if (biezacy->klucz == klucz) 
		{
			delete nowy_wezel;
			return 1;
		}
		poprzedni = biezacy;
		if (biezacy->klucz > klucz)
		{
			biezacy = biezacy->lewy;
		}
		else
		{
			biezacy = biezacy->prawy;
		}
	}


	if (!korzen) 
	{
		korzen = nowy_wezel;
		return 0;
	}
	else
	{
		if (poprzedni->klucz > klucz)
		{
			poprzedni->lewy = nowy_wezel;
		}
		else
		{
			poprzedni->prawy = nowy_wezel;
		}
	}



	if ( poprzedni->wspolczynnik_wywazenia )
	{
		poprzedni->wspolczynnik_wywazenia = 0;
		return 0;
	}

	

	if ( poprzedni->lewy == nowy_wezel )
		poprzedni->wspolczynnik_wywazenia = -1;
	else
		poprzedni->wspolczynnik_wywazenia = 1;

	cout << poprzedni->wspolczynnik_wywazenia << endl;
	przodek = ojciec ( korzen, poprzedni->klucz );

	//przodek = poprzedni;

	//bufor = przodek;

	while ( przodek )
	{
		if ( przodek->wspolczynnik_wywazenia )
			break;

		if ( przodek->lewy == poprzedni ) 
			przodek->wspolczynnik_wywazenia = -1;
		else
			przodek->wspolczynnik_wywazenia = 1;

		poprzedni = przodek;
		przodek = ojciec ( korzen, przodek->klucz);
	}

	//przodek = ojciec ( korzen, bufor->klucz );
	//poprzedni = bufor;
	//poprzedni = biezacy;

	if ( !przodek )
	{
		return 0;
	}

	if ( przodek->wspolczynnik_wywazenia == -1 )
	{	
		if ( przodek->prawy == poprzedni )
		{
			przodek->wspolczynnik_wywazenia = 0;
			return 0;
		}
	
		if ( poprzedni->wspolczynnik_wywazenia == 1 )
		{
			rotacja_lewa ( korzen, klucz );
			rotacja_prawa ( korzen, klucz );
		}
		else
			rotacja_prawa ( korzen, poprzedni->klucz );

		return 0;
	}
	else
	{
		if ( przodek->lewy == poprzedni )
		{
			przodek->wspolczynnik_wywazenia = 0;
			return 0;
		}

		if ( poprzedni->wspolczynnik_wywazenia == -1 )
		{
			rotacja_prawa ( korzen, klucz );
			rotacja_lewa ( korzen, klucz );
		}
		else
			rotacja_lewa ( korzen, poprzedni->klucz );

		return 0;
	}

	//AVL(korzen,klucz);
	//rekonstrukcja(korzen, klucz);
	//AVL(korzen, klucz);

	
	return 0;
}

void losuj(struct wezel *&korzen, int x)
{
	srand (time(0));
	int a;
	for (int i=0; i<x; i++)
	{
		a = rand()%100;
		if(dodaj(korzen,a) == 1) i--;
	}
}

void wyswietl(struct wezel *korzen)
{
		if (korzen != 0)
		{
			//wyswietl(korzen->lewy);
			cout << korzen->klucz << "	" << korzen->wspolczynnik_wywazenia << endl;
			if ( korzen->lewy || korzen->prawy )
			{
				if ( korzen->lewy )
					cout << "Lewy syn: " << korzen->lewy->klucz << "	";
				if ( korzen->prawy )
					cout << "Prawy syn: " << korzen->prawy->klucz;
				cout << endl << endl;
			}
			else
				cout << "Ten element jest lisciem" << endl << endl;
			wyswietl(korzen->lewy);
			wyswietl( korzen->prawy );


		}	
}

int znajdz(struct wezel *korzen, int x)
{
	int znalezione = 0;
	struct wezel *biezacy;
	biezacy = korzen;
	while(biezacy && znalezione == 0)
	{
		if(biezacy->klucz == x)
			znalezione = 1;
		else if(biezacy->klucz < x)
			{
				biezacy = biezacy->prawy;
			}
			else
			{
				biezacy = biezacy->lewy;
			}
	}
	return znalezione;
}

int usun(struct wezel *&korzen, int klucz)
{
	struct wezel *biezacy, *poprzedni, *do_usuniecia, *przed_usuwanym;
	do_usuniecia = korzen;
	poprzedni = korzen;

	while (do_usuniecia->klucz != klucz && (do_usuniecia->prawy || do_usuniecia->lewy))
	{
		poprzedni = do_usuniecia;
		if(do_usuniecia->klucz < klucz)
		{
			do_usuniecia = do_usuniecia->prawy;
		}
		else
		{
			do_usuniecia = do_usuniecia->lewy;
		}
	}
	
	if(do_usuniecia->klucz != klucz)
		return 1;
	
	if (!do_usuniecia->lewy && !do_usuniecia->prawy)
	{
		if (korzen == do_usuniecia)
		{
			korzen = 0;
			return 0;
		}

		if(do_usuniecia->klucz > poprzedni->klucz)
		{
			poprzedni->prawy = 0;
		}
		else
			{
				poprzedni->lewy = 0;
			}

	}

	if (do_usuniecia->lewy && !do_usuniecia->prawy)
	{		
		if (korzen == do_usuniecia)
		{
			korzen = do_usuniecia->lewy;
			return 0;

		}

		if(do_usuniecia->klucz > poprzedni->klucz)
		{
			poprzedni->prawy = do_usuniecia->lewy;
		}
		else
		{
			poprzedni->lewy = do_usuniecia->lewy;
		}

	}

	if (do_usuniecia->prawy && !do_usuniecia->lewy)
	{		
		if (korzen == do_usuniecia)
		{
			korzen = do_usuniecia->prawy;
			return 0;
		}

		if(do_usuniecia->klucz > poprzedni->klucz)
		{
			poprzedni->prawy = do_usuniecia->prawy;
		}
		else
			{
				poprzedni->lewy = do_usuniecia->prawy;
			}
		

	}

	if (do_usuniecia->prawy && do_usuniecia->lewy)
	{
		if (korzen != do_usuniecia)
			przed_usuwanym = poprzedni;
		biezacy = do_usuniecia->prawy;
		//poprzedni = do_usuniecia;
		while (biezacy->lewy)
		{
			przed_usuwanym = poprzedni;
			poprzedni = biezacy;
			biezacy = biezacy->lewy;
		}


		if (do_usuniecia->prawy != biezacy)
		{
			biezacy->prawy = do_usuniecia->prawy;		

		}

		biezacy->lewy = do_usuniecia->lewy;

		if (do_usuniecia != korzen)
		{
			if (biezacy->klucz < poprzedni->klucz)
				poprzedni->lewy = 0;
			else
				poprzedni->prawy = 0;
		}



		if (korzen == do_usuniecia)
			korzen = biezacy;
		else
			if (do_usuniecia->klucz > przed_usuwanym->klucz)
				przed_usuwanym->prawy = biezacy;
			else
				przed_usuwanym->lewy = biezacy;
	}

	return 0;
}

int rotacja_prawa(struct wezel *&korzen, int klucz)
{ 
	struct wezel *dziadzio, *tatus, *synek;

	dziadzio = korzen;
	tatus = korzen;
	synek = korzen;

	while (synek->klucz != klucz)
	{
		dziadzio = tatus;
		tatus = synek;
		if ( synek->klucz > klucz)
			synek = synek->lewy;
		else
			synek = synek->prawy;
	}

	if ( tatus->wspolczynnik_wywazenia == -1 )
	{
		tatus->wspolczynnik_wywazenia = 0;
		synek->wspolczynnik_wywazenia = 0;
	}
	else
	{
		tatus->wspolczynnik_wywazenia = 0;
		synek->wspolczynnik_wywazenia = 1;
	}

	if (synek == korzen || tatus->prawy == synek)
		return 1;

	tatus->lewy = synek->prawy;
	synek->prawy = tatus;

	if (tatus != dziadzio && dziadzio->lewy == tatus)
		dziadzio->lewy = synek;

	if (tatus != dziadzio && dziadzio->prawy == tatus )
		dziadzio->prawy = synek;	

	if ( tatus == dziadzio )
		korzen = synek;

	


	return 0;	
}

int rotacja_lewa(struct wezel *&korzen, int klucz)
{
	struct wezel *dziadzio, *tatus, *synek;

	dziadzio = korzen;
	tatus = korzen;
	synek = korzen;


	while (synek->klucz != klucz)
	{
		dziadzio = tatus;
		tatus = synek;
		if ( synek->klucz > klucz)
			synek = synek->lewy;
		else
			synek = synek->prawy;
	}

	if ( tatus->wspolczynnik_wywazenia == 1 )
	{
		synek->wspolczynnik_wywazenia = 0;
		tatus->wspolczynnik_wywazenia = 0;
	}
	else
	{
		synek->wspolczynnik_wywazenia = -1;
		tatus->wspolczynnik_wywazenia = 0;
	}

	if (synek == korzen || tatus->lewy == synek)
		return 1;

	tatus->prawy = synek->lewy;
	synek->lewy = tatus;

	if (tatus != dziadzio && dziadzio->prawy == tatus)
		dziadzio->prawy = synek;

	if (tatus != dziadzio && dziadzio->lewy == tatus )
		dziadzio->lewy = synek;	

	if ( tatus == dziadzio )
		korzen = synek;

	
	

	return 0;
}

void lista_liniowa( struct wezel *&korzen)
{
	struct wezel *tatus, *synek;

	synek = korzen;
	tatus = korzen;

	while ( tatus )
	{	
		if ( tatus->lewy )
		{
				synek = tatus->lewy;
				rotacja_prawa( korzen, synek->klucz );
				tatus = korzen;
		}
		else
			tatus = tatus->prawy;
	}
}

void wywazanie(long int ilosc_elementow, struct wezel *&korzen)
{
	long int m;
	struct wezel *tatus, *synek, *dziadzio;

	tatus = korzen;

	m = 1;
	while ( m <= ilosc_elementow ) m = 2 * m + 1;
	m = m /2;

	for( int i=0; i<(ilosc_elementow - m); i++ )
	{
		synek = tatus->prawy;
		if ( synek )
		{
			rotacja_lewa ( korzen, synek->klucz );
			tatus = synek->prawy;
		}
	}

	while ( m > 1 )
	{
		m = m/2;
		tatus = korzen;
		for ( int i=0; i<m; i++ )
		{
			synek = tatus->prawy;
			rotacja_lewa ( korzen, synek->klucz );
			tatus = synek->prawy;
		}
	}
}

wezel *&ojciec( struct wezel *&korzen, int klucz)
{
	struct wezel *tatus;
	struct wezel *biezacy;


	biezacy = korzen;
	tatus = NULL;

	while (biezacy->klucz != klucz)
	{
		tatus = biezacy;
		if (biezacy->klucz < klucz)
			biezacy = biezacy->prawy;
		else
			biezacy = biezacy->lewy;
	}

	return tatus;
}

int AVL(struct wezel *&korzen, int klucz)
{
	struct wezel *biezacy, *bufor, *rotowany;

	int bufor_klucza = klucz;

	biezacy = korzen;

	while (biezacy->klucz != klucz)
	{
		if ( biezacy->klucz > klucz )
			biezacy = biezacy->lewy;
		else 
			biezacy = biezacy->prawy;
	}

	biezacy = ojciec ( korzen, klucz );
	
	if ( !biezacy )																//Wstawienie korzenia - brak potomka;
		return 0;

	if ( biezacy->prawy && biezacy->lewy )										//Dostawienie liscia balansujacego swojego potomka do 0;
	{
		biezacy->wspolczynnik_wywazenia = 0;
		return 0;
	}

	if ( biezacy->prawy && !biezacy->lewy )										//Dostawienie lewego liscia;
		biezacy->wspolczynnik_wywazenia = 1;

	if ( !biezacy->prawy && biezacy->lewy )										//Dostawienie prawego liscia;
		biezacy->wspolczynnik_wywazenia = -1;

	biezacy = ojciec ( korzen, biezacy->klucz );

	while (biezacy)
	{
	if ( biezacy && biezacy->wspolczynnik_wywazenia == 1 )						//Ustawienie PRZODEK->PRAWY->X;
	{
		if ( biezacy->prawy->prawy && biezacy->prawy->prawy->klucz == klucz )
		{
			bufor = biezacy->prawy;
			rotacja_lewa ( korzen, biezacy->prawy->klucz );
			biezacy = bufor;
		}
		if ( biezacy->prawy->lewy && biezacy->prawy->lewy->klucz == klucz )
		{
			bufor = biezacy->prawy;
			rotowany = biezacy->prawy->lewy;
			rotacja_prawa ( korzen, rotowany->klucz );
			rotacja_lewa ( korzen, rotowany->klucz );
			biezacy = bufor;
			if ( biezacy = korzen )
				korzen = biezacy;
		}

		if ( !ojciec ( korzen, biezacy->klucz ) )								//Wywazenie wystapilo na samym szczycie drzewka;
			return 0;

		
			bufor = biezacy;
			biezacy = ojciec ( korzen, biezacy->klucz );
			if ( biezacy && biezacy->lewy == bufor )
				biezacy->wspolczynnik_wywazenia = -1;
			if ( biezacy && biezacy->prawy == bufor )
				biezacy->wspolczynnik_wywazenia = 1;
		}
		return 0;
	}

	while (biezacy)
	{	
	if ( biezacy && biezacy->wspolczynnik_wywazenia == -1 )						//Ustawienie PRZODEK->LEWEGO->X;
	{
		if ( biezacy->lewy->lewy && biezacy->lewy->lewy->klucz == klucz )
		{
			bufor = biezacy->lewy;
			rotacja_prawa ( korzen, biezacy->lewy->klucz );
			biezacy = bufor;
		}
		if ( biezacy->lewy->prawy && biezacy->lewy->prawy->klucz == klucz )
		{
			bufor = biezacy->lewy;
			rotowany = biezacy->lewy->prawy;
			rotacja_lewa ( korzen, rotowany->klucz );
			rotacja_prawa ( korzen, rotowany->klucz );
			biezacy = bufor;
			if ( biezacy == korzen )
				korzen = biezacy;
		}

		if ( !ojciec ( korzen, biezacy->klucz ) )									//Wywazenie nastapilo na samym szczycie drzewka;
			return 0;

		
			bufor = biezacy;
			biezacy = ojciec ( korzen, biezacy->klucz );
			if ( biezacy && biezacy->lewy == bufor )
				biezacy->wspolczynnik_wywazenia --;
			if ( biezacy && biezacy->prawy == bufor )
				biezacy->wspolczynnik_wywazenia ++;
		}
		return 0;
	}
}


void rekonstrukcja(struct wezel *&korzen, int klucz)
{
	struct wezel *biezacy, *rotowany;

	biezacy = ojciec(korzen, klucz);

	while ( biezacy )
	{
		if ( ojciec(korzen, biezacy->klucz) && ojciec ( korzen, biezacy->klucz)->wspolczynnik_wywazenia == 2 )
		{
			if ( biezacy->lewy && biezacy->lewy->klucz == klucz )
			{
				rotowany = biezacy->lewy;
				rotacja_prawa(korzen,rotowany->klucz);
				rotacja_lewa(korzen,rotowany->klucz);
			}
			if ( biezacy->prawy && biezacy->prawy->klucz == klucz )
				rotacja_lewa(korzen,biezacy->klucz);
		}

		if ( ojciec(korzen, biezacy->klucz) && ojciec ( korzen, biezacy->klucz)->wspolczynnik_wywazenia == -2 )
		{
			if ( biezacy->prawy && biezacy->prawy->klucz == klucz )
			{
				rotowany = biezacy->prawy;
				rotacja_lewa(korzen,rotowany->klucz);
				rotacja_prawa(korzen,rotowany->klucz);
			}
			if ( biezacy->lewy && biezacy->lewy->klucz == klucz )
				rotacja_prawa(korzen,biezacy->klucz);
		}

		klucz = biezacy->klucz;
		biezacy = ojciec(korzen, biezacy->klucz);
	}
}