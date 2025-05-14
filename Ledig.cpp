#include "Ledig.h"
#include "Product.h"


Ledig::Ledig(std::string pName=" ", double pPrice=0, bool pLedig=false, double pPiricePerKilo=0, double pWeight=0) : Product(pName, pPrice, pLedig), PriceperKilo(pPiricePerKilo), weight(pWeight)
{
}

Ledig::Ledig(const Ledig&other): Product(other), weight(other.getWeight()), PriceperKilo(other.getPriceperKilo())
{
	


	
}

double Ledig::getPrice()const
{
	return price;
}


void Ledig::setWeight(double other)
{
	weight = other;
	price = weight * PriceperKilo;
}

double Ledig::getPriceperKilo()const
{
	return PriceperKilo;
}

void Ledig::setPriceperKilo(double pPriceperKilo)
{
	PriceperKilo = pPriceperKilo;
}

double Ledig::getWeight()const
{
	return weight;

}

