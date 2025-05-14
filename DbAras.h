#pragma once
#include "Product.h"
class DbAras: public Product
{
	int num=0;
	double PricePerDb=0;
	
public:
	DbAras() = default;
	DbAras(std::string, double,bool, double, int);
	DbAras( const DbAras&);
	double getPrice() const;
	int getNum()const;
	double getPricePerDb()const;
	void setPricePerDb(double);
	void setNum(int);
	
	
};

