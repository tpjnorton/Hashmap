#include <iostream>
#include <thread>
#include "hashmap.hpp"

//tests for insert,delete and lookup operations in single-threaded mode
//as well as concurrency tests

static const int num_threads = 10;

//used to ensure output is readable
std::mutex mutexForTest;
// In this second test,each thread stores its
// thread number * 2 in the map then reads this
// value back. An extra lock has been included 
// (but commented out) to unscramble unreadable 
// ouput caused by multiple threads simultaneously 
// wanting to output test results.
void concurrencyTest(int tid,HashMap h)
{
	thread_local std::string g = "thr" + std::to_string(tid);

	h.ins(g, tid*2);
	int k = h.lookup(g);

	
	// mutexForTest.lock();
	std::cout <<"thread " << tid << ": Mapped \" " << g <<" to value " << tid*2 << std::endl;
	std::cout << "Stored value for "<< g << " is: " << k << std::endl;
	// mutexForTest.unlock();

}


// This first test checks all supported operations 
// in single-threaded mode: insert, lookup, delete
// and resize.
int main(void)
{
	HashMap h(2000);
	
	std::cout << "\n-------------single-thread operation test---------------" << std::endl;
	std::cout << "Mapping \"hello\" to value \"4\"" << std::endl;
	h.ins("hello", 4);
	int k = h.lookup("hello");
	std::cout << "Stored value for \"hello\" is: " << k << std::endl;

    std::cout << "Mapping \"thursday\" to value \"7\"" << std::endl;
	h.ins("thursday", 7);
	k = h.lookup("thursday");
	std::cout << "Stored value for \"thursday\" is: " << k << std::endl;

	std::cout << "Overwriting mapping for \"hello\" to value \"5\"" << std::endl;
	h.ins("hello", 5);
	k = h.lookup("hello");
	std::cout << "Stored value for \"hello\" is: " << k << std::endl;

	std::cout << "Deleting mapping for \"hello\"" << std::endl;
	h.del("hello");
	h.del("thursday");
	k = h.lookup("hello");
	std::cout << "Stored value for \"hello\" is: " << k << std::endl;


	h.resize(2);


	std::cout << "--------------------------------------------------------" << std::endl;

	std::cout << "\n--------------Thread-Safety Tests-----------------------\n" << std::endl;


	std::thread t[num_threads];
	// fork threads, give them each an integer id
	// and perform concurrent access test
	for (int i=0;i<num_threads; i++)
	{
		t[i] = std::thread(concurrencyTest, i+1,h);
	}


    for (int i=0;i<num_threads; i++)
	{
		t[i].join();
	}



	return 0;
}