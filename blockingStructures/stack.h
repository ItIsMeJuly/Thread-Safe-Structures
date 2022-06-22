#pragma once
#include <cstdlib>
#include <iostream>
#include <mutex>

template<typename T>
class stack {
	T* collection;
	std::mutex m;
	int count;

public:

	stack() {
		collection = (T*)malloc(sizeof(T));
		count = 0;
	}

	void push(T value) {
		std::lock_guard<std::mutex> lk{ m };
		++count;
		T* copy = (T*)realloc(collection, sizeof(T) * count );
		if (copy) {
			collection = copy;
		}
		*(collection + (count - 1)) = value;
	}

	T* pop() {
		std::lock_guard<std::mutex> lk{ m };
		if (count <= 0)
			return nullptr;
		T* copy = (T*)realloc(collection, sizeof(T) * count);
		--count;
		T retrive = *(collection + count);
		if (copy) {
			collection = copy;
		}
		return &retrive;
	}

	T* top() {
		if (count <= 0) {
			return nullptr;
		}
		auto v = *(collection + (count - 1));
		return &v;
	}

	int size() {
		std::lock_guard<std::mutex> lk{ m };
		return count;
	}
};