#include "QuerySolver.h"

using namespace std;

/* NU MODIFICATI */
QuerySolver::QuerySolver() 
{
  server = Server::GetInstance();
}

/* NU MODIFICATI */
QuerySolver::~QuerySolver()
{
  if (server != nullptr) 
  {
    server = nullptr;
  }
}

list<Product*> QuerySolver::Query_3a()
{
  list<Product*> allproducts;
  allproducts=server->getProductsList();
  list<Product*> res;
  for(list<Product*>::iterator it=allproducts.begin();it!=allproducts.end();it++)
  {
    if((*it)->getCategory()=="espressor" && (*it)->getProductType()=="redus")
    {
      res.push_back((*it));
    }
  }
  return res;
}

list<User*> QuerySolver::Query_3b()
{
  list<User*> allusers;
  allusers=server->getUsersList();
  list<User*> res;
  for(list<User*>::iterator it=allusers.begin();it!=allusers.end();it++)
  {
    if((*it)->getUserType()=="nonPremium" && (*it)->getTransportCost()<=11.5)
    {
      res.push_back((*it));
    }
  }
  return res;
}

list<Product*> QuerySolver::Query_3c()
{
  list<Product*> allproducts;
  allproducts=server->getProductsList();
  list<Product*> res;
  for(list<Product*>::iterator it=allproducts.begin();it!=allproducts.end();it++)
  {
    if((*it)->getProductType()=="resigilat")
    {
      NonFoodProduct* p1;
      p1=dynamic_cast<NonFoodProduct*>((*it));
      if(p1!=nullptr)
      {
        ReturnedProduct* p2;
        p2=dynamic_cast<ReturnedProduct*>(p1);
        if(p2!=nullptr)
        {
          if(p2->getReason()=="lipsa_accesorii")
          {
            res.push_back(p2);
          }
        }
      }
    }
  }
  res.sort(Utility::compareNonFoodProductsPrice);
  return res;
}

list<Product*> QuerySolver::Query_3d()
{
  list<Product*> allproducts;
  allproducts=server->getProductsList();
  list<Product*> res;
  for(list<Product*>::iterator it=allproducts.begin();it!=allproducts.end();it++)
  {
    if((*it)->getProductType()=="alimentar")
    {
      res.push_back((*it));
    }
  } 
  res.sort(Utility::compareFoodProducts);
  return res;
}

list<User*> QuerySolver::Query_3e()
{
  list<User*> allusers;
  list<User*> res;
  int k=1,max=0;
  string maxCounty;
  allusers=server->getUsersList();
  allusers.sort(Utility::compareUsersCounty);
  for(list<User*>::iterator it=allusers.begin();it!=next(allusers.begin(),allusers.size()-1);it++)
  {
    list<User*>::iterator it2;
    it2=next(it,1);
    if((*it)->getDeliveryData().getCounty().compare((*it2)->getDeliveryData().getCounty())==0)
    {
      k++;
      if(k>max)
      {
        max=k;
        maxCounty=(*it)->getDeliveryData().getCounty();
      }
    }
    else k=1;
  }
  for(list<User*>::iterator it=allusers.begin();it!=allusers.end();it++)
  {
    if((*it)->getDeliveryData().getCounty()==maxCounty && (*it)->getDeliveryData().getBlock()=="-" && (*it)->getDeliveryData().getApartment()==0 && (*it)->getBillingData().getBlock()=="-" && (*it)->getBillingData().getApartment()==0)
        res.push_back((*it));
  }
  res.sort(Utility::compareUsersID);
  return res;
}

list<User*> QuerySolver::Query_3f()
{
  list<User*> allusers;
  list<Product*> products;
  list<User*> res;
  list<PremiumUser*> premiumusers;
  allusers=server->getUsersList();
  products=server->getProductsList();
  for(list<User*>::iterator it=allusers.begin();it!=allusers.end();it++)
  {
    if((*it)->getUserType()=="premium")
    {
      PremiumUser *p1;
      p1=dynamic_cast<PremiumUser*>((*it));
      if(p1!=nullptr)
      {
        premiumusers.push_back(p1);
      }
    }
  }
  for(list<PremiumUser*>::iterator it=premiumusers.begin();it!=premiumusers.end();it++)
  {
    map<int, int> discounts;
    discounts=(*it)->getDiscounts();
    for(map<int,int>::iterator it1=discounts.begin();it1!=discounts.end();it1++)
    {
      for(list<Product*>::iterator it2=products.begin();it2!=products.end();it2++)
        {
          if(it1->first==(*it2)->getId() && ((*it2)->getCategory()=="imprimanta" || (*it2)->getCategory()=="telefon"))
          {
            res.push_back((*it));
          }
        }
    }
  }
  res.unique(); 
  return res;
}