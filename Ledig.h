#pragma once
#include "Product.h"
class Ledig:public Product
{
	double PriceperKilo=0;
	double weight=0;

public:
	Ledig() = default;
	Ledig(std::string, double, bool, double, double);
	Ledig(const Ledig&);
	void setWeight(double);
	void setPriceperKilo(double);
	double getWeight() const;
	double getPriceperKilo()const;
	double getPrice()const;
	


};

