#pragma once
#include<unordered_map>
#include<list>

class LRUCache {
private:
	std::list<std::pair<int, int>> dq;
	std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;
	int capacity;

public:
	LRUCache(int cache_Size) : capacity(cache_Size) {
		dq.clear();
		map.clear();
	}

	~LRUCache() {
		dq.clear();
		map.clear();
	}


	int get(int key) {
		//todo impl
		if (map.find(key) == map.end()) {
			return -1;
		}
		else {
			std::pair<int, int> nodeVal = *map[key];

			dq.erase(map[key]);

			dq.push_front(nodeVal);

			map[key] = dq.begin();

			return nodeVal.second;
		}
	}


	void put(int key, int value) {
		//todo impl
		//if key already exists
		if (map.find(key) != map.end()) {

			std::pair<int, int> nodeVal = *map[key];

			nodeVal.second = value;
			dq.erase(map[key]);

			dq.push_front(nodeVal);
			map[key] = dq.begin();
		}
		else {
			if (dq.size() == capacity) {

				std::pair<int, int> nodeVal = dq.back();

				map.erase(nodeVal.first);

				dq.pop_back();

			}

			std::pair<int, int> nodeVal = std::make_pair(key, value);

			dq.push_front(nodeVal);

			map[key] = dq.begin();
		}
	}

};