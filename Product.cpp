#include "Product.h"
#include <iostream>

Product::Product(std::string pName, double pPrice, bool pLedig): name(pName), price(pPrice), ledig(pLedig)
{
}

Product::Product(const Product&other): name(other.getName()), price(other.getPrice()), ledig(other.getledig())
{
}

std::string Product::getName()const
{
    return name;
}

bool Product::getledig() const
{
    return ledig;
}

void Product::setLedig(bool cmp)
{
    ledig = cmp;
}

void Product::setName(std::string other)
{
    name = other;
}


double Product::getPrice()const
{
    return price;
}

