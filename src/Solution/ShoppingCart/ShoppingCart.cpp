#include "ShoppingCart.h"

ShoppingCart::ShoppingCart()
{
	this->payMethod = "-";
}

ShoppingCart::ShoppingCart(const string &payMethod)
{
	this->payMethod=payMethod;
}

string &ShoppingCart::getPayMethod()
{
	return payMethod;
}

void ShoppingCart::setPayMethod(const string &payMethod)
{
	this->payMethod=payMethod;
}

void ShoppingCart::addProduct(int id, int quantity)
{
	pair<int,int> aux(id,quantity);
	shoppingCart.insert(aux);
}

void ShoppingCart::raiseQuantity(int id, int quantity)
{
	shoppingCart.find(id)->second+=quantity;
}

void ShoppingCart::lowerQuantity(int id, int quantity)
{
	shoppingCart.find(id)->second-=quantity;
}

int ShoppingCart::getQuantity(int productID)
{
	map<int,int>::iterator x;
	x=shoppingCart.find(productID);
	if(x==shoppingCart.end())
	{
		return -1;
	}
	else return x->second;
}

void ShoppingCart::deleteProduct(int productID)
{
	shoppingCart.erase(shoppingCart.find(productID));
}

map<int, int> &ShoppingCart::getShoppingCart()
{
	return shoppingCart;
}

void ShoppingCart::displayShoppingCart()
{
	throw("undefined");
}

json ShoppingCart::toJSON()
{
  return json(*this);
}