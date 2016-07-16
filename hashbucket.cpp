#include "hashbucket.hpp"
#include <iostream>


HashBucket::HashBucket()
{
    size = 16;
    elemList = new dataElem[16];
    lastIndex = 0;
}

HashBucket::~HashBucket()
{
    delete(elemList);
}


// returns value associated with searched-for
// key, returns 0 otherwise
int HashBucket::findElem(std::string key)
{
    
    mutex.lock();
    for(int i=0;i<=lastIndex;i++)
    {
        if (key.compare(elemList[i].key) == 0)
        {
            mutex.unlock();
            return elemList[i].data ;
        }
    }
    // return 0 to behave like STL map

    mutex.unlock();
    return 0;
}

// search for key and clear the key-value pair
// iff it exists, otherwise do nothing
void HashBucket::delElem(std::string key)
{
    mutex.lock();
    for(int i=0;i<size;i++)
    {
        if (key == elemList[i].key)
        {
            elemList[i].key = "";
            elemList[i].data = 0;
            mutex.unlock();
            return;
        }
    }

    // if there's nothing to delete, unlock the mutex and output error msg
    std::cout << "deletion failed; no entry matching that key" << std::endl;
    mutex.unlock();
}


// if the bucket is full we BEB-resize bucket
// if the key already exists overwrite the value
// else append the value to the first empty space
// of the bucket list
void HashBucket::insElem(dataElem newElem)
{   
    int i = 0;
    mutex.lock();
    if (lastIndex == size-1)
    {
        resize();
    }

    for(i=0;i<=lastIndex;i++)
    {
        if (newElem.key == elemList[i].key)
        {
            elemList[i].data = newElem.data;
            mutex.unlock();
            return;
        }

        else if (elemList[i].key == "" && elemList[i].data == 0)
        {
            elemList[i].key = newElem.key;
            elemList[i].data = newElem.data;
            mutex.unlock();
            return;

        }
    }

    lastIndex++;
    elemList[lastIndex] = newElem;
    mutex.unlock();
    return;
}


// BEB (Binary Exponential Backoff) bucket resizing
// thus as enough collisions occur to fill a bucket
// we double the bucket-size, exponentially decreasing
// the likelihood of filling a bucket. This way buckets
// are contiguous in memory for faster searching (cache optimisation)
void HashBucket::resize()
{
    mutex.lock();
    size *= 2;
    dataElem* d = new dataElem[size];
    std::copy( elemList, elemList+std::min(size/2,size), d);
    delete[] elemList;
    elemList = d;
    mutex.unlock();
}

