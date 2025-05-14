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
		throw std::runtime_error("Nem siker�lt megnyitni a" + Fname+ " file-t");
	}

	arak.open(Aruname);
	if (!arak.is_open()) {
		f.close();
		throw std::runtime_error("Nem siker�lt megnyitni a" + Aruname + " file-t");
	}
}

Beolvas::~Beolvas()
{
	if (f.is_open())
		f.close();
	if (arak.is_open())
		arak.close();
	
}
//Term�kt�pus eld�nt�s:
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

	//v�s�rolt term�kek/v�r�sl�sok filev�g�nek ellen�rz�se
	bool Beolvas::isFeof()
	{
		return f.eof();
	}

	//maga a beolvas�s folyamata:
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
		if (termeknev == "")	//v�s�rl�sok k�z�tt �res sor
		{
			penztar.vasarlas_vege();
			return;
		}

		if (termeknev == "Z�R�S")		//napi z�r�st Z�R�S fel�rat jelzi
		{
			penztar.vasarlas_vege();
			penztar.zarNap();
			return;
		}

		
		double price=0;
		while (!arak.eof())
		{
			arak >> tmp>>price;
			
			if (termeknev == tmp)		//megkeress�k a term�k �r�t az �rlist�t tartalmaz� file-b�l
			{
				arak.clear(); //flagek t�rl�se
				arak.seekg(ios::beg);	//f�jl elej�re �ll�t�sa
				break;

			}
		}
		if (termeknev != tmp)
		{
			throw std::runtime_error("Hiba az adatokban!");
		}
		if (LedigCmp(termeknev))			//Term�kt�pus sz�tv�laszt�sa
		{
			Ledig uj;
			double weight;
			cout << "A " << termeknev << " sulya:";				//felhaszn�l�t�l bek�rj�k a term�k s�ly�t
			cin >> weight;
			uj.setName(termeknev);			//be�ll�tjuk a tagv�ltoz�k �rt�k�t
			uj.setPriceperKilo(price);
			uj.setWeight(weight);
			uj.setLedig(true);
			penztar.setTermek(uj);		//eddigiekhez f�zz�k
			return;
			
		}
		DbAras uj;
		uj.setName(termeknev);
		uj.setPricePerDb(price);
		uj.setNum(1);				//be�ll�tjuk a tagv�ltoz�k �rt�k�t
		penztar.setTermek(uj);		//eddigiekhez f�zz�k
		arak.clear();
		arak.seekg(ios::beg);
	}
