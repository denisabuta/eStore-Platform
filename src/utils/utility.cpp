#include "utility.h"

bool Utility::compareNonFoodProductsPrice(Product *prod1,Product *prod2)
{
    NonFoodProduct *p1,*p2;
    p1=dynamic_cast<NonFoodProduct*>(prod1);
    p2=dynamic_cast<NonFoodProduct*>(prod2);
    if(p1->getPrice()<p2->getPrice()) 
        return true;
    else return false;
}

bool Utility::compareFoodProducts(Product *prod1, Product *prod2)
{
    if(prod1->getName()<prod2->getName())
        return true;
    if(prod1->getName()>prod2->getName())
        return false;
    FoodProduct *p1,*p2;
    p1=dynamic_cast<FoodProduct*>(prod1);
    p2=dynamic_cast<FoodProduct*>(prod2);
    if(p1->getCountryOfOrigin()<p2->getCountryOfOrigin())
        return true;
    if(p1->getCountryOfOrigin()>p2->getCountryOfOrigin())
        return false;
    if(p1->getLeiPerKg()<p2->getLeiPerKg())
        return true;
    else return false;
}

bool Utility::compareUsersCounty(User *usr1, User *usr2)
{
    if(usr1->getDeliveryData().getCounty()<usr2->getDeliveryData().getCounty())
        return true;
    if(usr1->getDeliveryData().getCounty()>usr2->getDeliveryData().getCounty())
        return false;
    return false;
}

bool Utility::compareUsersID(User *usr1,User *usr2)
{
    if(usr1->getUserID()<usr2->getUserID())
        return true;
    else return false;
}