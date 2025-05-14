
#include "penztargep.h"
#include "Ledig.h"
#include "DbAras.h"
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>

using namespace std;

bool LedigCmp(std::string product)		//NEM TAGFÜGGV., kimérõs termékek tömbje, a beolvasott termékkel hasonlítja össze (db- vagy tömegáras)
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
//Termékbefûzés a tömbbe
void penztargep::setTermek( Product& uj)
{
	
	for (int i = 0; i < termek.size(); i++)					//van-e már ilyen termék, akkor nem újra felvesszül
	{
		if (((*termek[i]).getName() == (uj.getName())))
		{
			if ((*termek[i]).getledig())					//típuszétválasztás
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
	if (uj.getledig())						//típuszétválasztás
	{
		const Ledig* pUj3 = static_cast<const Ledig*>(&uj);
		termek.push_back(std::make_unique<Ledig>(*pUj3));		//vektor végére szúrás
		return;
	}
	const DbAras* pUj4 = static_cast<const DbAras*>(&uj);
	termek.push_back(std::make_unique<DbAras>(*pUj4));
}



penztargep::~penztargep()
{
	termek.clear();
}

//Egy vásárlás lezárársa-> blokk + dokumentásás
void penztargep::vasarlas_vege()
{
	std::cout << "\n~~Blokk~~\n";
	double sum = 0;
	for (int i = 0; i < termek.size(); i++)
	{
		std::cout << (*termek[i]).getName() << " " << (*termek[i]).getPrice() << " Ft\n";
		sum += ((*termek[i]).getPrice());
	}
	//Kedvezmények kezelése
	if (sum > 10000)
	{
		kedvezmeny += sum * 0.1;			//10.000 Ft vásárlása esetén 10% kedvezmény
	}
	for (int i = 0; i < termek.size	(); i++)
	{
		DbAras* dbaras = static_cast<DbAras*>(&*termek[i]);
		if ((*termek[i]).getName() == "szalami")	//minden második 50% kedvezmény
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
			kedvezmeny += pTermek4->getPrice() * 0.15;		//15% kedvezmény az almára
		}

	}
	cout << "Kedvezmeny:" << kedvezmeny << '\n';
	std::cout << "Vegosszeg: " << (sum-kedvezmeny)<<"Ft\n" << "~~~~~~~~~~~~\n\n";
	napi_eddigi_össz += sum;
	vasarlok++;
	összKedvezmeny += kedvezmeny;
	kedvezmeny = 0;
	sum = 0;
	termek.clear();
	
}
//Pénztár zárása
void penztargep::zarNap()
{
	std::cout << "~~~~~~~~~~~~~~\nNapi eladas:" << napi_eddigi_össz << "Ft\nVasarlak szama: " << vasarlok << "\nOsszesen ervenyesitett kedvezmeny: " << összKedvezmeny<<"Ft\n~~~~~~~~~~~~~~\n";
	termek.clear();
}