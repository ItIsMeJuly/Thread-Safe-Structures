#pragma once
#include <mutex>
#include <condition_variable>


template<typename T>
class deque {

	template<typename T>
	struct node {
		node<T>* next;
		node<T>* prev;
		T value;

		node(T val) : value(val), next(nullptr), prev(nullptr) {}
	};

	node<T>* head;
	node<T>* tail;
	std::mutex m;
	std::condition_variable cv;
	int count;


public:

	deque() : head(nullptr), tail(nullptr), count(0){}

	void pushFront(T val) {
		std::lock_guard<std::mutex> lck(m);
		if (count <= 0) {
			node<T>* temp = new node<T>{ val };
			head = temp;
			tail = head;
			cv.notify_one();
			count++;
			return;
		}
		node<T>* temp = new node<T>{ val };
		temp->next = head;
		head->prev = temp;
		head = temp;
		count++;
		cv.notify_one();
	}

	T* popFront_wait() {
		std::unique_lock<std::mutex> lck{ m };
		cv.wait(lck, [this]{return count > 0; });
		node<T>* temp = head;
		T val = head->value;
		head = head->next;
		count--;
		delete temp;
		return &val;
	}

	T* popFront() {
		std::lock_guard<std::mutex> lck{ m };
		if (count <= 0)
			return nullptr;
		node<T>* temp = head;
		T val = head->value;
		head = head->next;
		count--;
		delete temp;
		return &val;
	}


	void pushBack(T val) {
		std::lock_guard<std::mutex> lck{ m };
		if (count <= 0) {
			node<T>* temp = new node<T>{ val };
			head = temp;
			tail = head;
			count++;
			cv.notify_one();
			return;
		}
		node<T>* temp = new node<T>{ val };
		tail->next = temp;
		temp->prev = tail;
		tail = tail->next;
		cv.notify_one();
	}

	T* popBack_wait() {
		std::unique_lock<std::mutex> lck{ m };
		cv.wait(lck, [this] {return count > 0; });
		node<T>* temp = tail;
		T val = temp->value;
		tail = tail->prev;
		count--;
		delete temp;
		return &val;
	}

	int getSize() {
		return count;
	}

	T* popBack() {
		std::lock_guard<std::mutex> lck{ m };
		if (count <= 0)
			return nullptr;
		node<T>* temp = tail;
		T val = temp->value;
		tail = tail->prev;
		count--;
		delete temp;
		return &val;
	}

	void traverse() {
		if (count <= 0) {
			return;
		}
		std::lock_guard<std::mutex> lck{ m };
		node<T>* temp = head;
		do {
			std::cout << temp->value;
			temp = temp->next;
		} while (temp != tail);
	}

	int findIndex(int value) {
		if (count <= 0) {
			return;
		}
		std::lock_guard<std::mutex> lck{ m };
		int i = 0;
		node<T>* temp = head;
		do {
			if (temp->value == value)
				break;
			temp = temp->next;
			i++;
		} while (temp != tail);
		return i;
	}

};
