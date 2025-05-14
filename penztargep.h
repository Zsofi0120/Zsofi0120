#pragma once
#include "Product.h"
#include "vector"

class penztargep
{
	std::vector<std::unique_ptr<Product>>termek;
	double napi_eddigi_össz = 0;  //összbevétel a nap
	int vasarlok = 0;   //vásárlók száma
	double kedvezmeny = 0;
	double összKedvezmeny = 0;
	
public:
	~penztargep();
	void vasarlas_vege(); //Blokk kiírása, összár
	void setTermek( Product&);  //Új termék beolvasása 
	void zarNap();   //Napi zárás


};