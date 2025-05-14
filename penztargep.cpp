
#include "penztargep.h"
#include "Ledig.h"
#include "DbAras.h"
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>

using namespace std;

bool LedigCmp(std::string product)		//NEM TAGF�GGV., kim�r�s term�kek t�mbje, a beolvasott term�kkel hasonl�tja �ssze (db- vagy t�meg�ras)
{
	std::string arrayLedig[] = { "banan","alma","korte","krumpli","hagyma","retek","paradicsom", "csirkemell","csirkecomb","marhalapocka","sertescomb","farhat" };
	int NumOfLedig = 12;
	for (int i = 0; i < NumOfLedig; i++)
	{
		if (product == arrayLedig[i])
			return true;
	}
	return false;
}
//Term�kbef�z�s a t�mbbe
void penztargep::setTermek( Product& uj)
{
	
	for (int i = 0; i < termek.size(); i++)					//van-e m�r ilyen term�k, akkor nem �jra felvessz�l
	{
		if (((*termek[i]).getName() == (uj.getName())))
		{
			if ((*termek[i]).getledig())					//t�pusz�tv�laszt�s
			{
				Ledig* pTermek = static_cast<Ledig*>(&*termek[i]);
				Ledig* pUj = static_cast<Ledig*>(&uj);
				pTermek->setWeight(pUj->getWeight() + pTermek->getWeight());
				return;
			}
			DbAras* pTermek2 = static_cast<DbAras*>(&*termek[i]);
			DbAras* pUj2 = static_cast<DbAras*>(&uj);
			pTermek2->setNum(pTermek2->getNum() + 1);
			return;
		}
	}
	if (uj.getledig())						//t�pusz�tv�laszt�s
	{
		const Ledig* pUj3 = static_cast<const Ledig*>(&uj);
		termek.push_back(std::make_unique<Ledig>(*pUj3));		//vektor v�g�re sz�r�s
		return;
	}
	const DbAras* pUj4 = static_cast<const DbAras*>(&uj);
	termek.push_back(std::make_unique<DbAras>(*pUj4));
}



penztargep::~penztargep()
{
	termek.clear();
}

//Egy v�s�rl�s lez�r�rsa-> blokk + dokument�s�s
void penztargep::vasarlas_vege()
{
	std::cout << "\n~~Blokk~~\n";
	double sum = 0;
	for (int i = 0; i < termek.size(); i++)
	{
		std::cout << (*termek[i]).getName() << " " << (*termek[i]).getPrice() << " Ft\n";
		sum += ((*termek[i]).getPrice());
	}
	//Kedvezm�nyek kezel�se
	if (sum > 10000)
	{
		kedvezmeny += sum * 0.1;			//10.000 Ft v�s�rl�sa eset�n 10% kedvezm�ny
	}
	for (int i = 0; i < termek.size	(); i++)
	{
		DbAras* dbaras = static_cast<DbAras*>(&*termek[i]);
		if ((*termek[i]).getName() == "szalami")	//minden m�sodik 50% kedvezm�ny
		{
			DbAras* pTermek3 = static_cast<DbAras*>(&*termek[i]);
			if (pTermek3->getNum() > 1)
				if (pTermek3->getNum() % 2 == 0)
				{
					kedvezmeny += pTermek3->getPrice() * 0.25; 
					
				}

			kedvezmeny += pTermek3->getPricePerDb() * (pTermek3->getNum() - 1) * 0.25;
		}
		if ((*termek[i]).getName() == "alma")
		{
			Ledig* pTermek4 = static_cast<Ledig*>(&*termek[i]);
			kedvezmeny += pTermek4->getPrice() * 0.15;		//15% kedvezm�ny az alm�ra
		}

	}
	cout << "Kedvezmeny:" << kedvezmeny << '\n';
	std::cout << "Vegosszeg: " << (sum-kedvezmeny)<<"Ft\n" << "~~~~~~~~~~~~\n\n";
	napi_eddigi_�ssz += sum;
	vasarlok++;
	�sszKedvezmeny += kedvezmeny;
	kedvezmeny = 0;
	sum = 0;
	termek.clear();
	
}
//P�nzt�r z�r�sa
void penztargep::zarNap()
{
	std::cout << "~~~~~~~~~~~~~~\nNapi eladas:" << napi_eddigi_�ssz << "Ft\nVasarlak szama: " << vasarlok << "\nOsszesen ervenyesitett kedvezmeny: " << �sszKedvezmeny<<"Ft\n~~~~~~~~~~~~~~\n";
	termek.clear();
}