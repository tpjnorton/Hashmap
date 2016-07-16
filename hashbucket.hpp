#include <string>
#include <mutex>

struct dataElem
{
	int data;
	std::string key;
	// default constructor gives empty element
	dataElem()
	{
		data = 0;
		key = "";
	}
};

// this class represents each bucket in the table.
// Sepearate chaining by dynamically BEB-resized
// arrays is used to resolve collisions. Each bucket
// contains a distinct mutex, thus threads can simultaneously
// write to serparate buckets in the hash table, yet each bucket
// is locked on access
class HashBucket
{
	public:
	std::mutex mutex;
	
	void insElem(dataElem newElem);
	int findElem(std::string key);
	void delElem(std::string key);
	void resize();
	HashBucket();
	~HashBucket();
	size_t size;
	dataElem *elemList;
	
	private:
	int lastIndex;
};