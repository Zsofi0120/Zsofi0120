#pragma once
#include <iostream>
class Product
{protected:
	std::string name;
	double price=0;
	bool ledig=false;
public:
	Product()=default;
	Product(std::string, double, bool);
	Product( const Product&);
	std::string getName()const;
	bool getledig()const;
	void setLedig(bool);
	void setName(std::string);
	double getPrice()const;
	
	
};

