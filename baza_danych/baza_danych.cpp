// Kó³ko i krzy¿yk.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream> //obs³uga plików
#include <Windows.h> // zawiera funkcje sleep()
#include <ctype.h> //wyjatki, obs³uga klawiatury
using namespace std;

struct student{
	int id;
	string nazwisko;
	string imie;
	string specjalnosc;
	double srednia;
};

void start();

//#################################################################################
void czysc_ekran() // czyœci ekran, zostaje tylko tekst poczatkowy
{ 
    system("cls"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // ustawia kolor znaku
    cout<<"Witaj w mojej pierwszej bazie danych!\n"
		<<"       Baza danych studentow\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
//#################################################################################
void co_dalej() // wyœwietla komunikat
{ 
    cout<<"Co chcesz teraz zrobic?\n"
		<<"1) Powrot do menu glownego.\n"
		<<"2) Wyjscie.\n";
	int co_dalej;

	for(;;){
	cin>>co_dalej;
	try{if(cin.fail()) throw "Wpisano inny znak niz cyfre...";
	if(co_dalej!=1 && co_dalej!=2)throw "Wpisano nieodpowiednia cyfre...";}
	catch(char* str) 
	{cout<<"\n Typ wyjatku: "<<str;
	cout<<"\nWpisz dane jeszcze raz!: ";
	cin.clear(); cin.sync(); continue;}
	break;
	}

	if(co_dalej == 1)
	{
		start();
	}
	else;
}
//#################################################################################
void utworz() // tworzy plik i dodaje pierwsze osoby.
{
	czysc_ekran();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout<<"Utworzenie nowej bazy danych spowoduje usuniecie \nstarej i zawartych tam informacji!!!\n"
		<<"Czy chcesz kontynuowac? [T/N]: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	char kont;

	for(;;){
	cin>>kont;
	try{if(kont!='T' && kont!='t' && kont!='N' && kont!='n') throw "Wpisano nieodpowiednia znak...";}
	catch(char* str) 
	{cout<<"\n Typ wyjatku: "<<str;
	cout<<"\nWpisz dane jeszcze raz!: ";
	cin.clear(); cin.sync(); continue;}
	break;
	}

	cout<<"\n";
	if(kont=='t' || kont=='T')
	{
	cout<<"Ilu studentow chcesz dodac?\n";
	int ilu; 
	
	for(;;){
	cin>>ilu;
	try{if(cin.fail()) throw "Wpisano inny znak niz cyfre...";}
	catch(char* str) 
	{cout<<"\n Typ wyjatku: "<<str;
	cout<<"\nWpisz dane jeszcze raz!: ";
	cin.clear(); cin.sync(); continue;}
	break;
	}

	ofstream plik1;
	plik1.open("Id.txt", ios::out | ios::trunc); // plik w którym przechowuje siê id do nadania nawet jeœli usunie siê kogoœ z bazy
	plik1<<ilu<<endl;
	plik1.close();

	student * dane_studenta = new student[ilu]; // dane_tudenta - tablica dynamiczna struktur.
	ofstream plik;
	plik.open("Studenci.txt",ios::out | ios::trunc);

	for(int i=0; i<ilu; i++)
	{
		dane_studenta[i].id=i+1;
		plik<<dane_studenta[i].id<<endl;
		cout<<"Podaj dane studenta nr. "<<i+1
			<<"\nNazwisko: ";
			cin>>dane_studenta[i].nazwisko;
				if (dane_studenta[i].nazwisko[0]>='a' && dane_studenta[i].nazwisko[0]<='z') // zmiana pierwszej litery na du¿¹ co otem u³atwi sortowanie itp
				{dane_studenta[i].nazwisko[0]= dane_studenta[i].nazwisko[0]-32;}
			plik<<dane_studenta[i].nazwisko<<endl;
		cout<<"Imie: ";
			cin>>dane_studenta[i].imie;
				if (dane_studenta[i].imie[0]>='a' && dane_studenta[i].imie[0]<='z') 
				{dane_studenta[i].imie[0]= dane_studenta[i].imie[0]-32;}
			plik<<dane_studenta[i].imie<<endl;
		cout<<"Specjalnosc: ";
			cin>>dane_studenta[i].specjalnosc;
				if (dane_studenta[i].specjalnosc[0]>='a' && dane_studenta[i].specjalnosc[0]<='z') 
				{dane_studenta[i].specjalnosc[0]= dane_studenta[i].specjalnosc[0]-32;}
			plik<<dane_studenta[i].specjalnosc<<endl;
		cout<<"Srednia ocen: ";
		for(;;){//######################################################################
		cin>>dane_studenta[i].srednia;
		try{if(cin.fail()) throw "Wpisano inny znak niz cyfre znak...";
		if(dane_studenta[i].srednia<2.0 || dane_studenta[i].srednia>5.0)throw "Wpisano nieodpowiednia ocene... Zakres to 2.0-5.0";}
		catch(char* str) 
		{cout<<"\n Typ wyjatku: "<<str;
		cout<<"\nWpisz dane jeszcze raz!: ";
		Sleep(2500); cin.clear(); cin.sync(); continue;}
		break;
		}
		plik<<dane_studenta[i].srednia<<endl;
		plik<<"\n\n";
	}
	plik.close();
	delete [] dane_studenta; // usuwamy obiekt !!! popraw jakby co.
	czysc_ekran();
	co_dalej();
	}
	else
		co_dalej();
}
//#################################################################################
int ile_rekordow()// zlicza ile rekordów/studentów juz jest w pliku
{
	int dolicz=0, id;
	string nazwisko, imie, specjalnosc;
	double srednia;
		
	fstream plik;
	plik.open("Studenci.txt", ios::in);
	while(!plik.eof()) // eof s³u¿y do sprawdzania, czy wskaŸnik pliku znajduje siê na koñcu pliku
	{
		plik>>id;
		plik>>nazwisko;
		plik>>imie;
		plik>>specjalnosc;
		plik>>srednia;
		dolicz++;
	} 
	plik.close();
	return dolicz;
}
//#################################################################################
void dodaj()
{
	czysc_ekran();
	cout<<"Ilu studentow chcesz dopisac do bazy ?\n";
	int ilu, id;
	for(;;)
	{
	cin>>ilu;
	try{if(cin.fail()) throw "Wpisano nieodpowiedni znak...";}
	catch(char* str) 
	{cout<<"\n Typ wyjatku: "<<str;
	cout<<"\nWpisz dane jeszcze raz!: ";
	cin.clear(); cin.sync(); continue;}
	break;
	}
				
	ifstream plik1;
	plik1.open("Id.txt", ios::in);
	while(!plik1.eof())
	{
		plik1>>id;
	} 
	plik1.close();
	student * dane_studenta = new student[ilu]; // dane_tudenta - tablica dynamiczna struktur.
	fstream plik;
	plik.open("Studenci.txt", ios::in | ios::out | ios::app);	
	for(int i=0;i<ilu;i++)
	{
		id++;
		dane_studenta[i].id=id;
		plik<<dane_studenta[i].id<<endl;
		cout<<"Podaj dane studenta nr. "<<id
			<<"\nNazwisko: ";
			cin>>dane_studenta[i].nazwisko;
				if (dane_studenta[i].nazwisko[0]>='a' && dane_studenta[i].nazwisko[0]<='z') // zmiana pierwszej litery na du¿¹ co otem u³atwi sortowanie itp
				{dane_studenta[i].nazwisko[0]= dane_studenta[i].nazwisko[0]-32;}
			plik<<dane_studenta[i].nazwisko<<endl;
		cout<<"Imie: ";
			cin>>dane_studenta[i].imie;
				if (dane_studenta[i].imie[0]>='a' && dane_studenta[i].imie[0]<='z') 
				{dane_studenta[i].imie[0]= dane_studenta[i].imie[0]-32;}
			plik<<dane_studenta[i].imie<<endl;
		cout<<"Specjalnosc: ";
			cin>>dane_studenta[i].specjalnosc;
				if (dane_studenta[i].specjalnosc[0]>='a' && dane_studenta[i].specjalnosc[0]<='z') 
				{dane_studenta[i].specjalnosc[0]= dane_studenta[i].specjalnosc[0]-32;}
			plik<<dane_studenta[i].specjalnosc<<endl;
		cout<<"Srednia ocen: ";
		for(;;){//######################################################################
		cin>>dane_studenta[i].srednia;
		try{if(cin.fail()) throw "Wpisano inny znak niz cyfre znak...";
		if(dane_studenta[i].srednia<2.0 || dane_studenta[i].srednia>5.0)throw "Wpisano nieodpowiednia ocene... Zakres to 2.0-5.0";}
		catch(char* str) 
		{cout<<"\n Typ wyjatku: "<<str;
		cout<<"\nWpisz dane jeszcze raz!: ";
		cin.clear(); cin.sync(); continue;}
		break;
		}
		plik<<dane_studenta[i].srednia<<endl;
		plik<<"\n\n";
	}
	plik.close();
	ofstream plik2;
	plik2.open("Id.txt", ios::out | ios::trunc);
	plik2<<id<<endl;
	plik2.close();
	delete [] dane_studenta;
	czysc_ekran();
	co_dalej();
}
//#################################################################################
void odczyt_z_pliku(student *dane_studenta,int n)
{
		ifstream plik;
		plik.open("Studenci.txt", ios::in);
		if(plik.good() == true)
		{
			for(int i=0;i<n;i++)
			{
				plik>>dane_studenta[i].id;
				plik>>dane_studenta[i].nazwisko;
				plik>>dane_studenta[i].imie;
				plik>>dane_studenta[i].specjalnosc;
				plik>>dane_studenta[i].srednia;
			}
		}
		else {cout<<"Nie udalo siê otworzyæ pliku!";}
		plik.close();
}
//#################################################################################
void wyswietl(student * dane_studenta,int n)
{
		czysc_ekran();
		for(int i=0;i<n;i++)
		{
			cout<<"Nr."<<dane_studenta[i].id<<endl;
			cout<<"Nazwisko :         "<<dane_studenta[i].nazwisko<<endl;
			cout<<"Imie :             "<<dane_studenta[i].imie<<endl;
			cout<<"Specjalnosc :      "<<dane_studenta[i].specjalnosc<<endl;
			cout<<"Srednia ocen :     "<<dane_studenta[i].srednia<<endl;
			cout<<"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n";
		}
}
//#################################################################################
int tablica_wybrane(student * wybrane, student * dane_studenta, int min, int max, int ilu) //int
{
		int pomoc=0;
			for(int i=0;i<ilu;i++)
			{
				if(dane_studenta[i].id>=min && dane_studenta[i].id<=max)
				{
					wybrane[pomoc].id=dane_studenta[i].id;
					wybrane[pomoc].nazwisko=dane_studenta[i].nazwisko;
					wybrane[pomoc].imie=dane_studenta[i].imie;
					wybrane[pomoc].specjalnosc=dane_studenta[i].specjalnosc;
					wybrane[pomoc].srednia=dane_studenta[i].srednia;
					pomoc++;
				}
			}
			return pomoc;
}
//#################################################################################
void sortuj(student * dane_studenta,int n)
{
	int sort=0;
	do
	{
	cout<<"Sortuj rosnaco wedlug:\n"
		<<"1) Id.  2) Nazwiska  3) Imienia  4) Specjalnosci 5) Sredniej\n\n"
		<<"Sortuj malejaco wedlug:\n"
		<<"11) Id.  12) Nazwiska  13) Imienia  14) Specjalnosci 15) Sredniej\n\n"
		<<"8) Powrot do menu\n"
		<<"9) wyjscie\n";
	for(;;){
	cin>>sort;
	try{if(cin.fail()) throw "Wpisano inny znak niz cyfre znak...";
	if(sort!=1 && sort!=2 && sort!=3 && sort!=4 && sort!=5 && sort!=8 && sort!=9 && sort!=11 && sort!=12 && sort!=13 && sort!=14 && sort!=15)throw "Wpisano zla cyfre...";}
	catch(char* str) 
	{cout<<"\n Typ wyjatku: "<<str;
	cout<<"\nWpisz dane jeszcze raz!: ";
	cin.clear(); cin.sync(); continue;}
	break;
	}
	
	if(sort == 1)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n-1;++j)
			{
				if(dane_studenta[j].id > dane_studenta[j+1].id)
				{
					swap(dane_studenta[j].id, dane_studenta[j+1].id);
					swap(dane_studenta[j].nazwisko, dane_studenta[j+1].nazwisko);
					swap(dane_studenta[j].imie, dane_studenta[j+1].imie);
					swap(dane_studenta[j].specjalnosc, dane_studenta[j+1].specjalnosc);
					swap(dane_studenta[j].srednia, dane_studenta[j+1].srednia);
	}}}
	wyswietl(dane_studenta,n);
	}
	else if(sort == 2)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n-1;++j)
			{
				if(dane_studenta[j].nazwisko > dane_studenta[j+1].nazwisko)
				{
					swap(dane_studenta[j].id, dane_studenta[j+1].id);
					swap(dane_studenta[j].nazwisko, dane_studenta[j+1].nazwisko);
					swap(dane_studenta[j].imie, dane_studenta[j+1].imie);
					swap(dane_studenta[j].specjalnosc, dane_studenta[j+1].specjalnosc);
					swap(dane_studenta[j].srednia, dane_studenta[j+1].srednia);
				}}}wyswietl(dane_studenta,n);
	}
	else if(sort == 3)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n-1;++j)
			{
				if(dane_studenta[j].imie > dane_studenta[j+1].imie)
				{
					swap(dane_studenta[j].id, dane_studenta[j+1].id);
					swap(dane_studenta[j].nazwisko, dane_studenta[j+1].nazwisko);
					swap(dane_studenta[j].imie, dane_studenta[j+1].imie);
					swap(dane_studenta[j].specjalnosc, dane_studenta[j+1].specjalnosc);
					swap(dane_studenta[j].srednia, dane_studenta[j+1].srednia);
				}}}wyswietl(dane_studenta,n);
	}
	else if(sort == 4)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n-1;++j)
			{
				if(dane_studenta[j].specjalnosc > dane_studenta[j+1].specjalnosc)
				{
					swap(dane_studenta[j].id, dane_studenta[j+1].id);
					swap(dane_studenta[j].nazwisko, dane_studenta[j+1].nazwisko);
					swap(dane_studenta[j].imie, dane_studenta[j+1].imie);
					swap(dane_studenta[j].specjalnosc, dane_studenta[j+1].specjalnosc);
					swap(dane_studenta[j].srednia, dane_studenta[j+1].srednia);
				}}}wyswietl(dane_studenta,n);
	}
	else if(sort == 5)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n-1;++j)
			{
				if(dane_studenta[j].srednia > dane_studenta[j+1].srednia)
				{
					swap(dane_studenta[j].id, dane_studenta[j+1].id);
					swap(dane_studenta[j].nazwisko, dane_studenta[j+1].nazwisko);
					swap(dane_studenta[j].imie, dane_studenta[j+1].imie);
					swap(dane_studenta[j].specjalnosc, dane_studenta[j+1].specjalnosc);
					swap(dane_studenta[j].srednia, dane_studenta[j+1].srednia);
				}}}wyswietl(dane_studenta,n);
	}
	else if(sort == 11)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n-1;++j)
			{
				if(dane_studenta[j].id < dane_studenta[j+1].id)
				{
					swap(dane_studenta[j].id, dane_studenta[j+1].id);
					swap(dane_studenta[j].nazwisko, dane_studenta[j+1].nazwisko);
					swap(dane_studenta[j].imie, dane_studenta[j+1].imie);
					swap(dane_studenta[j].specjalnosc, dane_studenta[j+1].specjalnosc);
					swap(dane_studenta[j].srednia, dane_studenta[j+1].srednia);
	}}}wyswietl(dane_studenta,n);
	}
	else if(sort == 12)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n-1;++j)
			{
				if(dane_studenta[j].nazwisko < dane_studenta[j+1].nazwisko)
				{
					swap(dane_studenta[j].id, dane_studenta[j+1].id);
					swap(dane_studenta[j].nazwisko, dane_studenta[j+1].nazwisko);
					swap(dane_studenta[j].imie, dane_studenta[j+1].imie);
					swap(dane_studenta[j].specjalnosc, dane_studenta[j+1].specjalnosc);
					swap(dane_studenta[j].srednia, dane_studenta[j+1].srednia);
				}}}wyswietl(dane_studenta,n);
	}
	else if(sort == 13)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n-1;++j)
			{
				if(dane_studenta[j].imie < dane_studenta[j+1].imie)
				{
					swap(dane_studenta[j].id, dane_studenta[j+1].id);
					swap(dane_studenta[j].nazwisko, dane_studenta[j+1].nazwisko);
					swap(dane_studenta[j].imie, dane_studenta[j+1].imie);
					swap(dane_studenta[j].specjalnosc, dane_studenta[j+1].specjalnosc);
					swap(dane_studenta[j].srednia, dane_studenta[j+1].srednia);
				}}}wyswietl(dane_studenta,n);
	}
	else if(sort == 14)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n-1;++j)
			{
				if(dane_studenta[j].specjalnosc < dane_studenta[j+1].specjalnosc)
				{
					swap(dane_studenta[j].id, dane_studenta[j+1].id);
					swap(dane_studenta[j].nazwisko, dane_studenta[j+1].nazwisko);
					swap(dane_studenta[j].imie, dane_studenta[j+1].imie);
					swap(dane_studenta[j].specjalnosc, dane_studenta[j+1].specjalnosc);
					swap(dane_studenta[j].srednia, dane_studenta[j+1].srednia);
				}}}wyswietl(dane_studenta,n);
	}
	else if(sort == 15)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n-1;++j)
			{
				if(dane_studenta[j].srednia < dane_studenta[j+1].srednia)
				{
					swap(dane_studenta[j].id, dane_studenta[j+1].id);
					swap(dane_studenta[j].nazwisko, dane_studenta[j+1].nazwisko);
					swap(dane_studenta[j].imie, dane_studenta[j+1].imie);
					swap(dane_studenta[j].specjalnosc, dane_studenta[j+1].specjalnosc);
					swap(dane_studenta[j].srednia, dane_studenta[j+1].srednia);
				}}}wyswietl(dane_studenta,n);
	}
	}while(sort!=9 && sort!=8);
	if (sort==8)
	{start();}
	else ;
}
//#################################################################################
void wyszukaj()
{
	czysc_ekran();
	cout<<"Weglug jakich kryteriow chcesz wyszukiwac?\n"
		<<"1) Id.\n"<<"2) Nazwiska.\n"<<"3) Imienia.\n"<<"4) Specjalnosci.\n"<<"5) Sredniej.\n\n"<<"6) Powrot\n";
	int wyb; 
	for(;;){
	cin>>wyb;
	try{if(cin.fail()) throw "Wpisano inny znak niz cyfre...";
	if(wyb!=1 && wyb!=2 && wyb!=3 && wyb!=4 && wyb!=5 && wyb!=6)throw "Wpisano nieodpowiednia cyfre...";}
	catch(char* str) 
	{cout<<"\n Typ wyjatku: "<<str;
	cout<<"\nWpisz dane jeszcze raz!: ";
	cin.clear(); cin.sync(); continue;}
	break;
	}

	int ile = ile_rekordow()-1;
	student * dane_studenta = new student[ile];
	odczyt_z_pliku(dane_studenta,ile);

	if(wyb == 1)
	{
		cout<<"Podaj Id. studenta: ";
		int id; 
		for(;;){
		cin>>id;
		try{if(cin.fail()) throw "Wpisano inny znak niz cyfre...";}
		catch(char* str) 
		{cout<<"\n Typ wyjatku: "<<str;
		cout<<"\nWpisz dane jeszcze raz!: ";
		cin.clear(); cin.sync(); continue;}
		break;
		}


		int sprawdz=0;
		for(int i=0;i<ile;++i)
		{
			if(dane_studenta[i].id == id)
			{
				cout<<"Nr."<<dane_studenta[i].id<<endl;
				cout<<"Nazwisko :         "<<dane_studenta[i].nazwisko<<endl;
				cout<<"Imie :             "<<dane_studenta[i].imie<<endl;
				cout<<"Specjalnosc :      "<<dane_studenta[i].specjalnosc<<endl;
				cout<<"Srednia ocen :     "<<dane_studenta[i].srednia<<endl;
				cout<<"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n";
				sprawdz++;  //sprawdzam czy w bazie jest wgl taki student
			}
		}
		delete [] dane_studenta;
		if(sprawdz !=0)
		{
			co_dalej();
		}
		else if(sprawdz == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ustawia kolor znaku
			cout<<"Brak w bazie studenta o Id.: "<<id<<"!";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // przywrace domyœlny kolor dalszej czêœci
			Sleep(2500);
			czysc_ekran();
			co_dalej();
		}
	}
	else if(wyb == 2)
	{
		cout<<"Podaj nazwisko studenta: ";
		string nazwisko; cin>>nazwisko;

		int sprawdz=0;
		for(int i=0;i<ile;++i)
		{
			if(dane_studenta[i].nazwisko == nazwisko)
			{
				cout<<"Nr."<<dane_studenta[i].id<<endl;
				cout<<"Nazwisko :         "<<dane_studenta[i].nazwisko<<endl;
				cout<<"Imie :             "<<dane_studenta[i].imie<<endl;
				cout<<"Specjalnosc :      "<<dane_studenta[i].specjalnosc<<endl;
				cout<<"Srednia ocen :     "<<dane_studenta[i].srednia<<endl;
				cout<<"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n";
				sprawdz++;  //sprawdzam czy w bazie jest wgl taki student
			}
		}
		delete [] dane_studenta;
		if(sprawdz !=0)
		{
			co_dalej();
		}
		else if(sprawdz == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ustawia kolor znaku
			cout<<"Brak w bazie studenta o nazwisku: "<<nazwisko<<"!";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // przywrace domyœlny kolor dalszej czêœci
			Sleep(2500);
			czysc_ekran();
			co_dalej();
		}
	}
	else if(wyb == 3)
	{
		cout<<"Podaj imie studenta: ";
		string imie; cin>>imie;

		int sprawdz=0;
		for(int i=0;i<ile;++i)
		{
			if(dane_studenta[i].imie == imie)
			{
				cout<<"Nr."<<dane_studenta[i].id<<endl;
				cout<<"Nazwisko :         "<<dane_studenta[i].nazwisko<<endl;
				cout<<"Imie :             "<<dane_studenta[i].imie<<endl;
				cout<<"Specjalnosc :      "<<dane_studenta[i].specjalnosc<<endl;
				cout<<"Srednia ocen :     "<<dane_studenta[i].srednia<<endl;
				cout<<"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n";
				sprawdz++;  //sprawdzam czy w bazie jest wgl taki student
			}
		}
		delete [] dane_studenta;
		if(sprawdz !=0)
		{
			co_dalej();
		}
		else if(sprawdz == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ustawia kolor znaku
			cout<<"Brak w bazie studenta o imieniu: "<<imie<<"!";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // przywrace domyœlny kolor dalszej czêœci
			Sleep(2500);
			czysc_ekran();
			co_dalej();
		}
	}
	else if(wyb == 4)
	{
		cout<<"Podaj specjalnosc studenta: ";
		string spec; cin>>spec;

		int sprawdz=0;
		for(int i=0;i<ile;++i)
		{
			if(dane_studenta[i].specjalnosc == spec)
			{
				cout<<"Nr."<<dane_studenta[i].id<<endl;
				cout<<"Nazwisko :         "<<dane_studenta[i].nazwisko<<endl;
				cout<<"Imie :             "<<dane_studenta[i].imie<<endl;
				cout<<"Specjalnosc :      "<<dane_studenta[i].specjalnosc<<endl;
				cout<<"Srednia ocen :     "<<dane_studenta[i].srednia<<endl;
				cout<<"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n";
				sprawdz++;  //sprawdzam czy w bazie jest wgl taki student
			}
		}
		delete [] dane_studenta;
		if(sprawdz !=0)
		{
			co_dalej();
		}
		else if(sprawdz == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ustawia kolor znaku
			cout<<"Brak w bazie studenta o specjalnosci: "<<spec<<"!";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // przywrace domyœlny kolor dalszej czêœci
			Sleep(2500);
			czysc_ekran();
			co_dalej();
		}
	}
	else if(wyb == 5)
	{
		cout<<"Podaj srednia studenta: ";
		int srednia; 
		for(;;){
		cin>>srednia;
		try{if(cin.fail()) throw "Wpisano inny znak niz cyfre...";}
		catch(char* str) 
		{cout<<"\n Typ wyjatku: "<<str;
		cout<<"\nWpisz dane jeszcze raz!: ";
		cin.clear(); cin.sync(); continue;}
		break;
		}

		int sprawdz=0;
		for(int i=0;i<ile;++i)
		{
			if(dane_studenta[i].srednia == srednia)
			{
				cout<<"Nr."<<dane_studenta[i].id<<endl;
				cout<<"Nazwisko :         "<<dane_studenta[i].nazwisko<<endl;
				cout<<"Imie :             "<<dane_studenta[i].imie<<endl;
				cout<<"Specjalnosc :      "<<dane_studenta[i].specjalnosc<<endl;
				cout<<"Srednia ocen :     "<<dane_studenta[i].srednia<<endl;
				cout<<"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n";
				sprawdz++;  //sprawdzam czy w bazie jest wgl taki student
			}
		}
		delete [] dane_studenta;
		if(sprawdz !=0)
		{
			co_dalej();
		}
		else if(sprawdz == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ustawia kolor znaku
			cout<<"Brak w bazie studenta o sredniej: "<<srednia<<"!";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // przywrace domyœlny kolor dalszej czêœci
			Sleep(2500);
			czysc_ekran();
			co_dalej();
		}
	}
	else if(wyb == 6)
	{
		start();
	}
}
//#################################################################################
void edytuj()
{
	char again='t';
	do{
	czysc_ekran();
	cout<<"Podaj Id. studenta, ktorego dane chcesz edytowac: ";
	int id;
	for(;;){
	cin>>id;
	try{if(cin.fail()) throw "Wpisano inny znak niz cyfre...";}
	catch(char* str) 
	{cout<<"\n Typ wyjatku: "<<str;
	cout<<"\nWpisz dane jeszcze raz!: ";
	cin.clear(); cin.sync(); continue;}
	break;
	}
	
	int ile = ile_rekordow()-1;
	student * dane_studenta = new student[ile];
	odczyt_z_pliku(dane_studenta,ile);
	czysc_ekran();
	for(int i=0;i<ile;i++)
	{
		if(dane_studenta[i].id==id)
		{
			cout<<"Podaj nowe dane studenta nr. "<<id
				<<"\nNazwisko: ";
			//id--;

			cin>>dane_studenta[i].nazwisko;
			cout<<"Imie: ";
			cin>>dane_studenta[i].imie;
			cout<<"Specjalnosc: ";
			cin>>dane_studenta[i].specjalnosc;
			cout<<"Srednia ocen: ";
			for(;;){
			cin>>dane_studenta[i].srednia;
			try{if(cin.fail()) throw "Wpisano inny znak niz cyfre...";
			if(dane_studenta[i].srednia<2.0 || dane_studenta[i].srednia>5.0)throw "Wpisano nieodpowiednia ocene... Zakres to 2.0-5.0";}
			catch(char* str) 
			{cout<<"\n Typ wyjatku: "<<str;
			cout<<"\nWpisz dane jeszcze raz!: ";
			cin.clear(); cin.sync(); continue;}
			break;
			}

			fstream plik;
			plik.open("Studenci.txt", ios::in | ios::out | ios::trunc);
			for(int i=0;i<ile;i++)
				{
					plik<<dane_studenta[i].id<<endl;
					plik<<dane_studenta[i].nazwisko<<endl;
					plik<<dane_studenta[i].imie<<endl;
					plik<<dane_studenta[i].specjalnosc<<endl;
					plik<<dane_studenta[i].srednia<<endl;
					plik<<"\n\n";
				}
			plik.close();
			delete [] dane_studenta;

			cout<<"Chcesz jeszcze edytowac dane studentow? [t/n]\n";
			for(;;){
			cin>>again;
			try{if(cin.fail()) throw "Wpisano inny znak niz litera...";
			if(again!='T' && again!='t' && again!='N' && again!='n')throw "Wpisano nieodpowiednia litera...";}
			catch(char* str) 
			{cout<<"\n Typ wyjatku: "<<str;
			cout<<"\nWpisz dane jeszcze raz!: ";
			cin.clear(); cin.sync(); continue;}
			break;
			}
		break;
		}
		else if(i==ile-1 && dane_studenta[i].id!=id)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"Brak studenta o podanym id do edycji!\n"
				<<"Chcesz edytowac dane innych studentow? [t/n]: ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			for(;;){
			cin>>again;
			try{if(cin.fail()) throw "Wpisano inny znak niz litera...";
			if(again!='T' && again!='t' && again!='N' && again!='n')throw "Wpisano nieodpowiednia litera...";}
			catch(char* str) 
			{cout<<"\n Typ wyjatku: "<<str;
			cout<<"\nWpisz dane jeszcze raz!: ";
			cin.clear(); cin.sync(); continue;}
			break;
			}
		}
	}
	}while(again == 't' || again == 'T');
	start();
}
//#################################################################################
void usun()
{
	char again='t';
	do{
	czysc_ekran();
	cout<<"Podaj Id. studenta, ktorego dane chcesz usunac: ";
	int id; 
	for(;;){
	cin>>id; 
	try{if(cin.fail()) throw "Wpisano inny znak niz cyfra...";}
	catch(char* str) 
	{cout<<"\n Typ wyjatku: "<<str;
	cout<<"\nWpisz dane jeszcze raz!: ";
	cin.clear(); cin.sync(); continue;}
	break;
	}
		
	int ile = ile_rekordow()-1;
	student * dane_studenta = new student[ile];
	odczyt_z_pliku(dane_studenta,ile);
	czysc_ekran();
	char usun;
	int licznik=0;
	for(int i=0;i<ile;i++)
	{
		if(dane_studenta[i].id==id && i<ile-1)
		{licznik=i;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"Czy napewno chcesz usunac dane tego studenta:\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout<<"Nr."<<dane_studenta[i].id<<endl
			<<"Nazwisko :         "<<dane_studenta[i].nazwisko<<endl
			<<"Imie :             "<<dane_studenta[i].imie<<endl
			<<"Specjalnosc :      "<<dane_studenta[i].specjalnosc<<endl
			<<"Srednia ocen :     "<<dane_studenta[i].srednia<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"[T/N]: ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		for(;;){
		cin>>usun;
		try{if(cin.fail()) throw "Wpisano inny znak niz litera...";
		if(usun!='T' && usun!='t' && usun!='N' && usun!='n')throw "Wpisano nieodpowiednia litera...";}
		catch(char* str) 
		{cout<<"\n Typ wyjatku: "<<str;
		cout<<"\nWpisz dane jeszcze raz!: ";
		cin.clear(); cin.sync(); continue;}
		break;
		}
		if(usun == 'T' || usun == 't')
		{
			for(int i=licznik;i<ile;i++)
			{
				dane_studenta[licznik].id=dane_studenta[licznik+1].id;	
				dane_studenta[licznik].nazwisko=dane_studenta[licznik+1].nazwisko;			
				dane_studenta[licznik].imie=dane_studenta[licznik+1].imie;			
				dane_studenta[licznik].specjalnosc=dane_studenta[licznik+1].specjalnosc;
				dane_studenta[licznik].srednia=dane_studenta[licznik+1].srednia;
			}
			ile--;	
			fstream plik;
			plik.open("Studenci.txt", ios::in | ios::out | ios::trunc);
			for(int i=0;i<ile;i++)
				{
					plik<<dane_studenta[i].id<<endl;
					plik<<dane_studenta[i].nazwisko<<endl;
					plik<<dane_studenta[i].imie<<endl;
					plik<<dane_studenta[i].specjalnosc<<endl;
					plik<<dane_studenta[i].srednia<<endl;
					plik<<"\n\n";
				}
			plik.close();
			delete [] dane_studenta;
		break;
		}
		}
		else if(dane_studenta[i].id==id && i==ile-1)
		{
			licznik=i;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"Czy napewno chcesz usunac dane tego studenta:\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout<<"Nr."<<dane_studenta[i].id<<endl
				<<"Nazwisko :         "<<dane_studenta[i].nazwisko<<endl
				<<"Imie :             "<<dane_studenta[i].imie<<endl
				<<"Specjalnosc :      "<<dane_studenta[i].specjalnosc<<endl
				<<"Srednia ocen :     "<<dane_studenta[i].srednia<<endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout<<"[T/N]: ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			for(;;){
			cin>>usun;
			try{if(cin.fail()) throw "Wpisano inny znak niz litera...";
			if(usun!='T' && usun!='t' && usun!='N' && usun!='n')throw "Wpisano nieodpowiednia litera...";}
			catch(char* str) 
			{cout<<"\n Typ wyjatku: "<<str;
			cout<<"\nWpisz dane jeszcze raz!: ";
			cin.clear(); cin.sync(); continue;}
			break;
			}
			if(usun == 'T' || usun == 't')
				{
						ile--;	
			fstream plik;
			plik.open("Studenci.txt", ios::in | ios::out | ios::trunc);
			for(int i=0;i<ile;i++)
				{
					plik<<dane_studenta[i].id<<endl;
					plik<<dane_studenta[i].nazwisko<<endl;
					plik<<dane_studenta[i].imie<<endl;
					plik<<dane_studenta[i].specjalnosc<<endl;
					plik<<dane_studenta[i].srednia<<endl;
					plik<<"\n\n";
				}
			plik.close();
			delete [] dane_studenta;
		break;

		}
		else if(i==ile-1 && dane_studenta[i].id!=id)
		{cout<<"Brak Studenta o podanym Id!!!"; goto brak;}
	}}
		brak:
		cout<<"Chcesz usunac dane innego? [t/n]\n";
		for(;;){
		cin>>again;
		try{if(cin.fail()) throw "Wpisano inny znak niz litera...";
		if(again!='T' && again!='t' && again!='N' && again!='n')throw "Wpisano nieodpowiednia litere...";}
		catch(char* str) 
		{cout<<"\n Typ wyjatku: "<<str;
		cout<<"\nWpisz dane jeszcze raz!: ";
		cin.clear(); cin.sync(); continue;}
		break;
		}
	}while(again == 't' || again == 'T');
			czysc_ekran();
			co_dalej();
}
//#################################################################################
void start()
{ 
    czysc_ekran();
	cout<<"Co chcesz zrobic:\n"
		<<" 1) Utworzyc nowa baze do pliku\n"
		<<" 2) Dodac nowego studenta\n"
		<<" 3) Wyswietlic dane studenta/ow\n"
		<<" 4) Wyszukac studenta/ow\n"
		<<" 5) Edytowac dane studenta\n"
		<<" 6) Usunac studenta\n"
		<<" 7) Wyjsc\n\n";

	cout<<"Wpisz cyfre 1-7 i zatwierdz enterem: ";
	int wybor; 
	for(;;){
	cin>>wybor;
	try{if(cin.fail()) throw "Wpisano inny znak niz cyfra...";
	if(wybor!=1 && wybor!=2 && wybor!=3 && wybor!=4 && wybor!=5 && wybor!=6 && wybor!=7)throw "Wpisano nieodpowiednia cyfre...";}
	catch(char* str) 
	{cout<<"\n Typ wyjatku: "<<str;
	cout<<"\nWpisz dane jeszcze raz!: ";
	cin.clear(); cin.sync(); continue;}
	break;
	}

	if(wybor == 1) 
	{ 
            utworz();
    }
    else if(wybor == 2) 
	{ 
            dodaj();
    } 
	else if(wybor == 3) 
	{ 
           czysc_ekran();
			cout<<"1) Wyswietlanie wszystkich studentow.\n"
				<<"2) Wyswietlanie poszczegolnych studentow.\n"
				<<"3) Powrot.\n";
			int wyb;

			for(;;){
			cin>>wyb;
			try{if(cin.fail()) throw "Wpisano inny znak niz cyfra...";
			if(wyb!=1 && wyb!=2 && wyb!=3)throw "Wpisano nieodpowiednia cyfre...";}
			catch(char* str) 
			{cout<<"\n Typ wyjatku: "<<str;
			cout<<"\nWpisz dane jeszcze raz!: ";
			cin.clear(); cin.sync(); continue;}
			break;
			}
			
			if (wyb == 1)
			{
				int n = ile_rekordow()-1;
				student * dane_studenta = new student[n];
				odczyt_z_pliku(dane_studenta,n);
				wyswietl(dane_studenta,n);
				sortuj(dane_studenta,n);
				delete [] dane_studenta;
			}
			else if(wyb == 2)
			{ 
				int min, max, roznica;
				cout<<"Podaj przedzial id studentow do wyswietlenia:\n"
					<<"Id min: ";
				for(;;){
				cin>>min;
				try{if(cin.fail()) throw "Wpisano inny znak niz cyfra...";}
				catch(char* str) 
				{cout<<"\n Typ wyjatku: "<<str;
				cout<<"\nWpisz dane jeszcze raz!: ";
				cin.clear(); cin.sync(); continue;}
				break;
				}
				cout<<"\nId max: ";
				for(;;){
				cin>>max;
				try{if(cin.fail()) throw "Wpisano inny znak niz cyfra...";}
				catch(char* str) 
				{cout<<"\n Typ wyjatku: "<<str;
				cout<<"\nWpisz dane jeszcze raz!: ";
				Sleep(2500); cin.clear(); cin.sync(); continue;}
				break;
				}
				int ile = ile_rekordow()-1;
				student * dane_studenta = new student[ile];
				odczyt_z_pliku(dane_studenta,ile);
				student * wybrane = new student[ile];
				roznica=tablica_wybrane(wybrane,dane_studenta,min,max, ile);
				wyswietl(wybrane,roznica);
				sortuj(wybrane,roznica);
				delete [] dane_studenta;
				delete [] wybrane;
			}
			else 
			{
				start();
			}
    } 
	else if(wybor == 4) 
	{ 
            wyszukaj();
    }
	else if(wybor == 5) 
	{ 
            edytuj();
    }
	else if(wybor == 6) 
	{ 
            usun();
    }
	else if (wybor == 7) ; //wyjscie
}
//#################################################################################
int _tmain(int argc, _TCHAR* argv[])
{
	start();
	return 0;
}