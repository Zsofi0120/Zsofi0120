#include "Beolvas.h"
#include<iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include"Product.h"
#include "DbAras.h"
#include "Ledig.h"
#include "penztargep.h"

using namespace std;


Beolvas::Beolvas(std::string Fname, std::string Aruname)
{
	f.open(Fname);
	if (!f.is_open()) {
		throw std::runtime_error("Nem sikerült megnyitni a" + Fname+ " file-t");
	}

	arak.open(Aruname);
	if (!arak.is_open()) {
		f.close();
		throw std::runtime_error("Nem sikerült megnyitni a" + Aruname + " file-t");
	}
}

Beolvas::~Beolvas()
{
	if (f.is_open())
		f.close();
	if (arak.is_open())
		arak.close();
	
}
//Terméktípus eldöntés:
	bool Beolvas::LedigCmp(string product)
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

	bool Beolvas::isReady() const {
		return f.is_open() && f.good();
	}												

	//vásárolt termékek/váráslások filevégének ellenõrzése
	bool Beolvas::isFeof()
	{
		return f.eof();
	}

	//maga a beolvasás folyamata:
	void Beolvas::feldolgoz(penztargep& penztar)
	{
		string termeknev;
		string tmp;
		if (!(Beolvas::isReady()))
		{
			if(f.is_open())
				f.close();
			throw runtime_error("Hiba a file-lal!");
		}
		getline(f, termeknev);
		if (termeknev == "")	//vásárlások között üres sor
		{
			penztar.vasarlas_vege();
			return;
		}

		if (termeknev == "ZÁRÁS")		//napi zárást ZÁRÁS felírat jelzi
		{
			penztar.vasarlas_vege();
			penztar.zarNap();
			return;
		}

		
		double price=0;
		while (!arak.eof())
		{
			arak >> tmp>>price;
			
			if (termeknev == tmp)		//megkeressük a termék árát az árlistát tartalmazó file-ból
			{
				arak.clear(); //flagek törlése
				arak.seekg(ios::beg);	//fájl elejére állítása
				break;

			}
		}
		if (termeknev != tmp)
		{
			throw std::runtime_error("Hiba az adatokban!");
		}
		if (LedigCmp(termeknev))			//Terméktípus szétválasztása
		{
			Ledig uj;
			double weight;
			cout << "A " << termeknev << " sulya:";				//felhasználótól bekérjük a termék súlyát
			cin >> weight;
			uj.setName(termeknev);			//beállítjuk a tagváltozók értékét
			uj.setPriceperKilo(price);
			uj.setWeight(weight);
			uj.setLedig(true);
			penztar.setTermek(uj);		//eddigiekhez fûzzük
			return;
			
		}
		DbAras uj;
		uj.setName(termeknev);
		uj.setPricePerDb(price);
		uj.setNum(1);				//beállítjuk a tagváltozók értékét
		penztar.setTermek(uj);		//eddigiekhez fûzzük
		arak.clear();
		arak.seekg(ios::beg);
	}
