#include <iostream>
template <class T>
struct Node {
	T value;
	Node* next;
};
template <class T>
class List {
public:
	Node<T>* head;
	Node<T>* tail;
	Node<T>* previous;
	Node<T>* current;
	size_t size;
public:
	List();
	~List();

	void insert_first(T data);
	void insert_current(T data);
	void insert_last(T data);
	void delete_head();
	void delete_current();
	void next();
	void zero();
	void set_current(T data) { current->value = data; }

	bool is_empty();
	T get_current();
};
template <class T>
List<T>::List() {
	head = new Node<T>();
	tail = previous = current = head;
	size = 0;
}
template <class T>
bool
List<T>::is_empty() {
	return head == nullptr;
}

template <class T>
void
List<T>::insert_first(T data) {
	Node<T>* tmp = new Node<T>();
	tmp->value = data;
	tmp->next = head;
	head = tmp;
	current = head;
	size++;
	if (size == 1) {
		previous = head;
		tail = head;
	}
}
template <class T>
void
List<T>::insert_last(T data) {
	if (size > 0) {
		Node<T>* tmp = new Node<T>();
		tmp->value = data;
		tail->next = tmp;
		tail = tmp;
		current = tail;
		size++;
	}
	else {
		insert_first(data);
	}
}
template <class T>
void
List<T>::insert_current(T data) {
	if (size == 0) {
		insert_first(data);
		previous = head;
	}
	else if (previous == tail) {
		insert_last(data);
		previous = tail;
	}
	else {
		Node<T>* tmp = new Node<T>();
		tmp->value = data;
		tmp->next = current;
		current = tmp;
		previous->next = tmp;
		size++;
	}
}
template <class T>
void
List<T>::delete_head() {
	if (is_empty()) {
		return;
	}
	Node<T>* tmp = head;
	head = head->next;
	delete tmp;
	size--;
}
template <class T>
void
List<T>::delete_current() {
	if (is_empty()) {
		return;
	}
	if (head == current) {
		delete_head();
		current = head;
	}
	else {
		Node<T>* tmp = current;
		current = current->next;
		if (previous != nullptr) {
			previous->next = current;
		}
		delete tmp;
		size--;
	}
	
}
template <class T>
T
List<T>::get_current() {
	if (current == nullptr) {
		throw "List is empty";
	}
	return current->value;
}
template <class T>
void
List<T>::zero() {
	previous = tail;
	current = head;
}
template <class T>
void
List<T>::next() {
	previous = current;
	current = current->next;
}
template <class T>
List<T>::~List() {
	while (head != tail) {
		Node<T>* tmp = head;
		head = head->next;
		delete tmp;
	}
}