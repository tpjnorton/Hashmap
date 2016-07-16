#include <string>
#include "hashbucket.hpp"

// class to represent the hashmap as a whole
class HashMap
{
	public:
		void ins(std::string key, int data);
		int  lookup(std::string key);
		void del(std::string key);
		unsigned hash(std::string key);
		void resize(size_t newSize);
		HashMap();
		HashMap(int mSize);
	private:
		int mapSize;
		HashBucket* map;
};