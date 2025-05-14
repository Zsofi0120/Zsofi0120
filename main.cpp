#define _CRTDOG_MAP_ALLOC
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Beolvas.h"
#include"Product.h"
#include "DbAras.h"
#include "Ledig.h"
#include "penztargep.h"
using namespace std;

int main()
{
	penztargep penztar;
	try {
		std::string filename1 = "vasarlas.txt";
		std::string filename2 = "arlista.txt";
		Beolvas beolvaso(filename1, filename2);

		while (!beolvaso.isFeof())
		{
			beolvaso.feldolgoz(penztar);
		}
		_CrtDumpMemoryLeaks();
	
		}
	
	catch (const std::runtime_error& exeption)
	{

		std::cerr << "Rendszerhiba: " << exeption.what()
			<< '\n';
		return 1;
	}
	catch (const std::bad_alloc& exeption)
	{
		std::cerr << "Rendszerhiba: Hiba a memóriafoglalásban!" << '\n';
		return 1;
	}

return 0;

}

