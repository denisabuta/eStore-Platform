#include "Server.h"

using namespace std;

/* NU MODIFICATI */
Server::Server(){}

/* NU MODIFICATI */
Server *Server::GetInstance()
{
	if (!instance)
	{
		instance = new Server;
	}

	return instance;
}

/* NU MODIFICATI */
Server::~Server()
{
	if (instance != NULL)
		instance = NULL;

	if (!__UserID__ProductsCart__.empty())
		__UserID__ProductsCart__.clear();
}

void Server::set__UserID__ProductsCart__()
{
	list<User*>::iterator it;
	for(it=usr.begin();it!=usr.end();++it)
	{
		__UserID__ProductsCart__[(*it)->getUserID()]=new ShoppingCart();
	}
}

list<Product *> &Server::getProductsList()
{
	return prod;
}

list<User *> &Server::getUsersList()
{
	return usr;
}

map<int, ShoppingCart *> Server::get__UserID__ProductsCart__()
{
	return __UserID__ProductsCart__;
}

bool Server::requestAddProduct(int userID, int productID, int quantity)
{
	if(quantity<=0)
		return false;
	else
	{
		int k=0,q=0;
		for(list<User*>::iterator it=usr.begin();it!=usr.end();it++)
		{
			if((*it)->getUserID()==userID)
			{
				k=1;
			}
		}
		for(list<Product*>::iterator it=prod.begin();it!=prod.end();it++)
		{
			if((*it)->getId()==productID)
			{
				q=1;
			}
		}
		if(k==0 || q==0)
			return false;
		else
		{
			//daca produsul nu exista in cos
			if((*__UserID__ProductsCart__.find(userID)->second).getQuantity(productID)==-1)
			{
				//verificam daca cantitatea de produs pe care vrem sa o adaugam este disponibila
				//daca da adaugam produsul in cos, daca nu nu se poate indeplini request-ul
				for(list<Product*>::iterator it=prod.begin();it!=prod.end();it++)
				{
					if((*it)->getId()==productID)
					{
						if((*it)->checkQuantity(quantity)==0)
							return false;
						else
						{
							__UserID__ProductsCart__.find(userID)->second->addProduct(productID,quantity);
							(*it)->decreaseQuantity(quantity);
							return true;
						}
					}
				}
			}
			//daca produsul exista deja in cos
			//crestem cantitatea lui doar daca aceasta este disponibila pe server
			else
			{
				for(list<Product*>::iterator it=prod.begin();it!=prod.end();it++)
				{
					if((*it)->getId()==productID)
					{
						if((*it)->checkQuantity(quantity)==0)
							return false;
						else
						{
							__UserID__ProductsCart__.find(userID)->second->raiseQuantity(productID,quantity);
							(*it)->decreaseQuantity(quantity);
							return true;
						}
					}
				}
			}
		 }
	}
	return false;
}

bool Server::requestDeleteProduct(int userID, int productID, int quantity)
{
	if(quantity<=0)
		return false;
	else
	{
		int k=0,q=0;
		for(list<User*>::iterator it=usr.begin();it!=usr.end();it++)
		{
			if((*it)->getUserID()==userID)
			{
				k=1;
			}
		}
		for(list<Product*>::iterator it=prod.begin();it!=prod.end();it++)
		{
			if((*it)->getId()==productID)
			{
				q=1;
			}
		}
		if(k==0 || q==0)
			return false;
		else
		{
			if((*__UserID__ProductsCart__.find(userID)->second).getQuantity(productID)==-1)
			{
				return false;
			}
			else
			{
				for(list<Product*>::iterator it=prod.begin();it!=prod.end();it++)
				{
					if((*it)->getId()==productID)
					{
						//daca cantitatea produsului de sters este mai mica sau egala decat cantitatea pe care dorim sa o stergem
						if(quantity>=__UserID__ProductsCart__.find(userID)->second->getQuantity(productID))
						{
							__UserID__ProductsCart__.find(userID)->second->lowerQuantity(productID, __UserID__ProductsCart__.find(userID)->second->getQuantity(productID));
							__UserID__ProductsCart__.find(userID)->second->deleteProduct(productID);
							(*it)->increaseQuantity(quantity);
						}
						else
						{
							__UserID__ProductsCart__.find(userID)->second->lowerQuantity(productID, quantity);
							(*it)->increaseQuantity(quantity);
						}
					}
				}
			}
		}
	}
	return false;
}

/* NU MODIFICATI */
void Server::populateProducts(const json &input)
{
	prod = ObjectFactory::getProductList(input["shoppingCart"]);
}

/* NU MODIFICATI */
void Server::populateUsers(const json &input)
{
	usr = ObjectFactory::getUserList(input["useri"]);
}