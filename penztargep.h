#pragma once
#include "Product.h"
#include "vector"

class penztargep
{
	std::vector<std::unique_ptr<Product>>termek;
	double napi_eddigi_�ssz = 0;  //�sszbev�tel a nap
	int vasarlok = 0;   //v�s�rl�k sz�ma
	double kedvezmeny = 0;
	double �sszKedvezmeny = 0;
	
public:
	~penztargep();
	void vasarlas_vege(); //Blokk ki�r�sa, �ssz�r
	void setTermek( Product&);  //�j term�k beolvas�sa 
	void zarNap();   //Napi z�r�s


};