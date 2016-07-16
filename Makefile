all:

	g++ -O3 -std=c++11 -pthread -lpthread -Wl,--no-as-needed main.cpp hashmap.cpp hashbucket.cpp -o hashmap 


clean:

	rm -f hashmap

remake:

	rm -f hashmap
	g++ -O3 -std=c++11 -pthread -lpthread -Wl,--no-as-needed main.cpp hashmap.cpp hashbucket.cpp -o hashmap 

debug:

	g++ -O3 -g -std=c++11 -pthread -lpthread -Wl,--no-as-needed main.cpp hashmap.cpp hashbucket.cpp -o hashmap 