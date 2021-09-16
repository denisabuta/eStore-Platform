#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "../Solution/Product/NonFoodProduct.h"
#include "../Solution/Product/FoodProduct.h"
#include "../Solution/User/User.h"

class Utility{

public:
static bool compareNonFoodProductsPrice(Product*, Product*);
static bool compareFoodProducts(Product*, Product*);
static bool compareUsersCounty(User*, User*);
static bool compareUsersID(User*, User*);
};