#include "LRUCache.h"
#include <algorithm>

using namespace std;

LRUCache::LRUCache(int capacity)
{
	this->capacity=capacity;
	lru.reserve(capacity);
	size=0;
}

vector<int> LRUCache::processRequests(vector<int> requestsNo)
{
	lru.push_back(requestsNo[0]);
	for(unsigned long int i=1;i<requestsNo.size();i++)
	{
		unsigned long int k=0;
		int pos;
		for(unsigned long int j=0;j<lru.size();j++)
		{
			if(requestsNo[i]!=lru[j])
			{
				k++;
			}
			else pos=j;
		}
		if(lru.size()<lru.capacity())
		{
			if(k==lru.size())
			{
				vector<int>::iterator it;
				it=lru.begin();
				lru.insert(it,requestsNo[i]);
			}
			else if(k!=0)
			{
				lru.erase(lru.begin()+pos);
				vector<int>::iterator it;
				it=lru.begin();
				lru.insert(it,requestsNo[i]);
			}
		}
		else
		{
			if(k==lru.size())
			{
				lru.pop_back();
				vector<int>::iterator it;
				it=lru.begin();
				lru.insert(it,requestsNo[i]);
			}
			else if(k!=0)
			{
				lru.erase(lru.begin()+pos);
				vector<int>::iterator it;
				it=lru.begin();
				lru.insert(it,requestsNo[i]);
			}
		}
	}
	return lru;
}

int LRUCache::getCapacity()
{
	return capacity;
}

int LRUCache::getSize()
{
	return size;
}

vector<int> LRUCache::getLRU()
{
	return lru;
}

int LRUCache::getLRUCapacity()
{
	capacity=lru.capacity();
	return capacity;
}

void LRUCache::setCapacity(int capacity)
{
	this->capacity=capacity;
	lru.reserve(capacity);
}

void LRUCache::setLRU(vector<int> aux)
{
	lru=aux;
}
