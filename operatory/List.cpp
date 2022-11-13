#include "List.h"
#include <iostream>
using namespace std;

List::List() : size(0), first(nullptr) {}
List::Node * List::find(const size_t idx)
{
	Node * node = first;

	for (size_t i = 0; i < idx; i++)
	{
		node = node->next;
	}

	return node;
}

void List::push(const Point & point, const size_t idx)
{
	if (idx == 0)
	{
		Node * tail = first;
		first = new Node(point);
		first->next = tail;
	}
	else
	{
		Node * prev = find(idx - 1);
		Node * tail = prev->next;
		prev->next = new Node(point);
		prev->next->next = tail;
	}
	size++;
}

void List::push(const List& list, const size_t idx)
{
	List copy(list);
	Node* it = copy.first;
	if (idx == 0)
	{
		Node* tail = first;
		Node* last = nullptr;
		if (it)
		{
			first = new Node(it->point);
			last = first;
			it = it->next;
		}
		while (it)
		{
			last->next = new Node(it->point);
			last = last->next;
			it = it->next;
		}
		if (last) last->next = tail;
	}
	else
	{
		Node* prev = find(idx - 1);
		Node* tail = prev->next;
		while (it)
		{
			prev->next = new Node(it->point);
			prev = prev->next;
			it = it->next;
		}
		prev->next = tail;
	}
	size += copy.size;
}

void List::multiply(const int x)
{
	List copy(*this);

	if(x>=0){
	for (int i = 0; i < x-1; i++)
	{
		push(copy, size);
	}
	if (x==0)
	{
		this->~List();
	}
	}
}

void List::pop(const size_t idx)
{
	if (idx == 0)
	{
		Node* tail = first->next;
		delete first;
		first = tail;
	}
	else
	{
		Node* prev = find(idx - 1);
		Node* tail = prev->next->next;
		delete prev->next;
		prev->next = tail;
	}
	size--;
}



List::Error List::pop_back()
{
	List::Error error = List::Error::SUCCESS;
	
	if (size == 0)
	{
		error = List::Error::LIST_EMPTY;
	}
	else
	{
		pop(size-1);
	}

	return error;
}


List::Error List::pop_front()
{
	List::Error error = List::Error::SUCCESS;

	if (size == 0)
	{
		error = List::Error::LIST_EMPTY;
	}
	else
	{
		pop(0);
	}

	return error;
}

List::Error List::push_back(const Point& point)
{
	List::Error error = List::Error::SUCCESS;
	if (size == 0)
	{
		Node* tail = first;
		first = new Node(point);
		first->next = tail;
	}
	else
	{
		Node* prev = find(size - 1);
		Node* tail = prev->next;
		prev->next = new Node(point);
		prev->next->next = tail;
	}
	size++;

	return Error();
}

List::Error List::find(Point& point, const size_t idx)
{
	List::Error error = List::Error::SUCCESS;

	if (size > 0) {

		if (idx < size) {
			error = List::Error::SUCCESS;
			Node* tmp = find(idx);
			point = tmp->point;
		}
		else if (idx >= size) {
			error = List::Error::INDEX_OUT_OF_BOUNDS;
		}
	}

	else if(size==0) {
		error = List::Error::LIST_EMPTY;
	}
	return error;
}

List::Error List::insert(const Point& point, const std::size_t idx)
{
	List::Error error = List::Error::INDEX_OUT_OF_BOUNDS;
	if (idx <= size) {
		push(point, idx);
		error = List::Error::SUCCESS;
	}
	return error;
}




List::List(std::vector<Point> vektor)
{
	int size = vektor.size();

	for (int i = 0; i < size; i++)
	{
		push(vektor[i], i);
	}
}

List::List(const List & list) : size(list.size), first(nullptr)
{
	Node * it = list.first;
	Node * last = first;
	if (it)
	{
		first = new Node(it->point);
		last = first;
		it = it->next;
	}
	while (it)
	{
		last->next = new Node(it->point);
		last = last->next;
		it = it->next;
	}
}



size_t List::getSize()
{
	return size;
}

List List::operator+(const List& list)
{
	List copy(*this);
	copy.push(list, copy.size);
	return copy;
}

List& List::operator+=(const List& list)
{
	push(list, size);
	return *this;
}

List & List::operator=(const List & list)
{
	List copy(list);
	this->~List();
	push(copy, 0);
	return *this;
}

List List::operator--(int)
{
	List copy(*this);
	pop_back();
	return copy;
}

List List::operator*(int x)
{
	multiply(x);
	return *this;
}

Point& List::operator[](int x)
{
	Point punkt;
	find(punkt, x);
	return punkt;
}

List List::operator++(int)
{
	this->~List();
	return *this;
}

//deklaracja w main: lista<<lista;

List& List::operator<<(const List&)
{
	List copy(*this);
	Point tmp;
	for (int i = 0; i < copy.size; i++)
	{
		find(tmp, i);
		cout << tmp.x<<" "<< tmp.y<<" " << tmp.z<<" " << endl;
	}
	return copy;
}



