#pragma once
#include <iostream>
#include <fstream>
#include "penztargep.h"
using namespace std;


class Beolvas
{
	ifstream f;
	ifstream arak;

public:
	Beolvas(string, string);
	~Beolvas();
	static bool LedigCmp(string);
	bool isReady()const;
	bool isFeof();
	void feldolgoz(penztargep &penzar);

};

