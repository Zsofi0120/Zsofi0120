#include "DbAras.h"





DbAras::DbAras(std::string pName = " ", double pPrice = 0, bool pLedig = false, double pPricePerDb = 0, int pNum = 0) : Product(pName, pPrice, pLedig),  num(pNum), PricePerDb(pPricePerDb)
{
}

DbAras::DbAras(const DbAras& other) :Product(other),PricePerDb(other.PricePerDb),num(other.num)
{
}
double DbAras::getPrice() const
{
    return price;
}

int DbAras::getNum()const
{
    return num;
}

double DbAras::getPricePerDb()const
{
    return PricePerDb;
}

void DbAras::setPricePerDb(double pPrice)
{
    PricePerDb = pPrice;
   
}


void DbAras::setNum(int pNum)
{
    num = pNum;
    price = pNum * PricePerDb;
}





