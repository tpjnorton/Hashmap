#include "hashmap.hpp"
#include <iostream>

// default Constructor
HashMap::HashMap()
{
	mapSize = 100;
	map = new HashBucket[mapSize];
}

// Constructor for variable map-size
HashMap::HashMap(int mSize)
{
	mapSize = mSize;
	map = new HashBucket[mapSize];
}

// generic home-grown hash function to convert
// the string into some numeric representation
unsigned HashMap::hash(std::string key)
{
	size_t l = key.length();
	unsigned h = 0;


	// key before hash is product of all characters
	// casted to unsigned
	for (int i = 0; i<l; i++)
	{
		h *= (unsigned)key[i];
	}

	for (int i = 0; i<10; i++)
	{
		h = ((h * 512353 + 0xfaecb) * 11) % mapSize;
	}
	return h;	
}

// create a new data element for the bucket's collision list
void HashMap::ins(std::string key, int data)
{
	unsigned addr = hash(key);

	dataElem d;

	d.key = key;
	d.data = data;

	map[addr].insElem(d);
}

// locate the bucket then search through for element
int HashMap::lookup(std::string key)
{
	unsigned addr = hash(key);
	
	int k = map[addr].findElem(key);
	return k;
}

// locate the key-element pair then delete key
void HashMap::del(std::string key)
{
	unsigned addr = hash(key);
	map[addr].delElem(key);
}


// resize by making a new table and rehashing all entries from previous table
// and storing them in the new table, then redirecting the pointer to the new table
// whilst deleting the old table

void HashMap::resize(size_t newSize)
{
	int oldMapSize = mapSize;
	HashBucket* map2 = new HashBucket[mapSize];
	mapSize = newSize;
	for (int i = 0; i < oldMapSize; i++)
	{
		for (int j = 0; j < map[i].size; j++)
		{
			if (map[i].elemList[j].key != "")
			{
					unsigned addr = hash(map[i].elemList[j].key);

					dataElem d;

					d.key = map[i].elemList[j].key;
					d.data = map[i].elemList[j].data;

					map2[addr].insElem(d);
			}

		}
	}
	HashBucket* oldMap = map;
	map = map2;
	// delete[] oldMap;

}