#pragma once
#include <vector>
#include "Point.h"
class List
{
	size_t size;
	struct Node
	{
		Point point;
		Node * next;
		Node(const Point & p) : point(p.x, p.y, p.z), next(nullptr){}
	};
	Node * first;
	Node * find(const size_t);
	void push(const Point &, const size_t);
	void push(const List &, const size_t);
	void pop(const size_t);
	void multiply(const int);

public:
	List();
	List(std::vector<Point>);
	List(const List& list);
	~List() {
		Node* tmp;
		tmp = first;
		Node* last = nullptr;
		while (tmp != last) {
			first = tmp->next;
			delete tmp;
			tmp = first;
		}
		delete last;
		size = 0;
	}

	enum Error
	{
		SUCCESS,
		LIST_EMPTY,
		INDEX_OUT_OF_BOUNDS
	};

	Error pop_front();
	Error pop_back();
	Error push_back(const Point&);
	Error find(Point&, const std::size_t);
	Error insert(const Point&, const std::size_t);
	size_t getSize();
	List operator+(const List&);
	List& operator+=(const List&);
	List& operator=(const List&);
	List operator--(int);
	List operator*(int);
	Point& operator[](int);
	List operator++(int);
	List& operator<<(const List&);
};



