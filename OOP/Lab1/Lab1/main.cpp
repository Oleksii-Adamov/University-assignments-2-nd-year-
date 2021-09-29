#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<random>
#include<ctime>

enum quick_sort_mode { STANDART, RANDOM_PIVOT, MEDIAN_OF_THREE };

// abstract interface class
template<typename T>
class List {
public:
	virtual size_t Size() const = 0;
	virtual void PushBack(const T& value) = 0;
	virtual void PopBack() = 0;
	//virtual T& operator[] (size_t index) = 0;
	virtual const T& operator[] (size_t index) const = 0;
	virtual void Insert(const size_t pos, const T& value) = 0;
	virtual void Erase(const size_t pos) = 0;
	virtual void Print() const = 0;
	virtual void Free() { // ????????
		// do nothing (for library realizations)
	};
	// sort maybe
};

template<typename array_type, typename T>
class ArrayBasedList{
protected:
	array_type m_array;
	size_t m_size = 0;
public:
	/*void Print() {
		for (int i = 0; i < m_size; i++) {
			std::cout << m_array[i] << "\n";
		}
		std::cout << "---------------------------------\n";
	}*/
	virtual size_t Size() const = 0;
private:
	virtual void Replace_buffer(T* buffer) = 0;
public:
	void HeapSort(int begin_pos, int end_pos)
	{
		if (begin_pos < 0 || end_pos > Size()) exit(1);
		for (int i = (end_pos - begin_pos) / 2 + begin_pos - 1; i >= begin_pos; i--)
			Heapify(end_pos - begin_pos, i - begin_pos, begin_pos);
		for (int i = end_pos - 1; i >= begin_pos; i--)
		{
			std::swap(m_array[begin_pos], m_array[i]);
			Heapify(i - begin_pos, 0, begin_pos);
		}
	}
private:
	void Heapify(int end_pos, int root, int begin_pos)
	{
		int largest = root;
		int l = 2 * root + 1;
		int r = 2 * root + 2;
		if (l < end_pos && m_array[l + begin_pos] > m_array[largest + begin_pos])
			largest = l;

		if (r < end_pos && m_array[r + begin_pos] > m_array[largest + begin_pos])
			largest = r;
		if (largest != root)
		{
			std::swap(m_array[root + begin_pos], m_array[largest + begin_pos]);
			Heapify(end_pos, largest, begin_pos);
		}
	}
public:
	void MergeSort(int begin_pos, int end_pos) {
		if (end_pos - begin_pos < 2) return;
		int mid = (end_pos - begin_pos - 1) / 2 + begin_pos;
		MergeSort(begin_pos, mid + 1);
		MergeSort(mid + 1, end_pos);
		Merge(begin_pos, end_pos, mid + 1);
	}

private:
	void Merge(int begin_pos, int end_pos, int border) {
		T* new_array = new T[m_size];
		int i;
		for (i = 0; i < begin_pos; i++) {
			new_array[i] = m_array[i];
		}
		int a_p = begin_pos, b_p = border;
		for (i = begin_pos; a_p < border && b_p < end_pos; i++) {
			if (m_array[a_p] < m_array[b_p]) {
				new_array[i] = m_array[a_p];
				a_p++;
			}
			else {
				new_array[i] = m_array[b_p];
				b_p++;
			}
		}
		for (; a_p < border; i++, a_p++) {
			new_array[i] = m_array[a_p];
		}
		for (; b_p < end_pos; i++, b_p++) {
			new_array[i] = m_array[b_p];
		}
		for (; i < m_size; i++) {
			new_array[i] = m_array[i];
		}
		Replace_buffer(new_array);
	}
public:
	// 3-way quick-sort using Hoare’s partition
	void QuickSort(int l, int r, quick_sort_mode mode) {
		if (r <= l)
			return;
		int i, j;
		partition( l, r, i, j, mode);
		QuickSort(l, j, mode);
		QuickSort(i, r, mode);
	}
private:
	// Hoare’s partition
	void partition(int l, int r, int& i, int& j, quick_sort_mode mode)   
	{
		i = l - 1, j = r;
		switch (mode) {
		case RANDOM_PIVOT:
			std::swap(m_array[r], m_array[l + rand() % (r - l + 1)]);
			break;
		case MEDIAN_OF_THREE:
			int mid = (l + r) / 2;
			if (m_array[l] > m_array[mid])
				std::swap(m_array[l], m_array[mid]);
			if (m_array[r] < m_array[l])
				std::swap(m_array[r], m_array[l]);
			if (m_array[mid] < m_array[r])
				std::swap(m_array[r], m_array[mid]);
			break;
		}
		int pivot = m_array[r], left_border = l - 1, right_border = r; // a[l...left_border] = a[right_border...r] = pivot
		while (true) {
			do {
				i++;
			} while (m_array[i] < pivot);
			do {
				j--;
			} while (j > l && pivot < m_array[j]);
			if (i >= j)
				break;
			std::swap(m_array[i], m_array[j]);
			if (m_array[i] == pivot) {
				left_border++;
				std::swap(m_array[left_border], m_array[i]);
			}
			if (m_array[j] == pivot) {
				right_border--;
				std::swap(m_array[j], m_array[right_border]);
			}
		}
		std::swap(m_array[i], m_array[r]);
		j = i - 1;
		for (int k = l; k < left_border; k++, j--) {
			std::swap(m_array[k], m_array[j]);
		}
		i = i + 1;
		for (int k = r - 1; k > right_border; k--, i++) {
			std::swap(m_array[i], m_array[k]);
		}
	}
public:
	virtual void LibSort(size_t begin_pos, size_t end_pos/*, bool(*comp)(const T& x, const T& y)*/) = 0;
};

template<typename T>
class ArrayList : public List<T>, public ArrayBasedList<T*, T> { // can be more optimized by using std::move, but need to know more about it before using
private:
	size_t m_capacity = 0;
public:

	ArrayList() {
		Reallocate(2);
	}

	ArrayList(size_t n) {
		Reallocate(n);
		this->m_size = n;
	}

	~ArrayList() { // need to manage memory by your own because otherwise it won't be possible to pass it into functions
		// do nothing
	}

	void Free() override {
		DeleteList(this->m_array);
	}

	void Clear() {
		this->m_size = 0;
	}

	void Print() const override{
		for (int i = 0; i < this->m_size; i++) {
			std::cout << (this->m_array)[i] << "\n";
		}
		std::cout << "---------------------------------\n";
	}
private:

	void Replace_buffer(T* buffer) override {
		delete[] this->m_array;
		this->m_array = buffer;
	}

	void DeleteList(T* list) {
		delete[] list;
	}

	void Reallocate(size_t new_size) { // new_size > m_size
		if (new_size <= this->m_size) return;
		T* new_array = new T[new_size];
		for (int i = 0; i < this->m_size; i++) {
			new_array[i] = (this->m_array)[i];
		}
		if (this->m_size > 0)
			DeleteList(this->m_array);
		this->m_array = new_array;
		m_capacity = new_size;
	}

public:
	size_t Size() const override {
		return this->m_size;
	}

	void PushBack(const T& value) override { // passing by reference to avoid copying, double capacity when runout of it
		if (this->m_size >= m_capacity) {
			Reallocate(this->m_size + this->m_size);
		}
		(this->m_array)[this->m_size] = value;
		(this->m_size)++;
	}

	void PopBack() override {
		(this->m_size)--;
	}
	
	T& operator[] (size_t index) /*override*/ {
		return (this->m_array)[index];
	}

	const T& operator[] (size_t index) const override{
		return (this->m_array)[index];
	}

	void Insert(const size_t pos, const T& value) override{ // passing by reference to avoid copying
		if (pos > this->m_size) exit(1);
		T insert_value = value;
		for (size_t i = pos; i < this->m_size; i++) {
			T temp = (this->m_array)[i];
			(this->m_array)[i] = insert_value;
			insert_value = temp;
		}
		PushBack(insert_value);
	}

	void Erase(const size_t pos) override{
		if (pos >= this->m_size) exit(1);
		for (size_t i = pos; i < this->m_size - 1; i++) {
			(this->m_array)[i] = (this->m_array)[i + 1];
		}
		PopBack();
	}

	void LibSort(size_t begin_pos, size_t end_pos/*, bool(*comp)(const T& x, const T& y)*/) override {
		std::sort((this->m_array) + begin_pos, (this->m_array) + end_pos/*, comp*/);
	}
};

template<typename T>
class StdVectorList : public List<T>, public ArrayBasedList<std::vector<T>, T> {
public:
	StdVectorList() {
		// do nothing
	}

	StdVectorList(const size_t size) {
		(this->m_array).resize(size);
		this->m_size = size;
	}

	size_t Size() const override { 
		return this->m_size;
	}

	void Clear() {
		(this->m_array).clear();
		this->m_size = (this->m_array).size();
	}

	void Print() const override {
		for (int i = 0; i < this->m_size; i++) {
			std::cout << (this->m_array)[i] << "\n";
		}
		std::cout << "---------------------------------\n";
	}

private:
	void Replace_buffer(T* buffer) override {
		for (int i = 0; i < this->m_size; i++) {
			(this->m_array)[i] = buffer[i];
		}
		delete[] buffer;
	}
public:
	void PushBack(const T& value) override { //passing by reference to avoid copying
		(this->m_array).push_back(value);
		(this->m_size)++;
	}

	void PopBack() override {
		(this->m_array).pop_back();
		(this->m_size)--;
	}
private:
	bool check_access(size_t index) const{
		return index < this->m_size;
	}
public:
	T& operator[] (size_t index) /*override*/{
		if (!check_access(index)) {
			exit(3);
		}
		return (this->m_array)[index];
	}

	const T& operator[] (size_t index) const override {
		if (!check_access(index)) {
			exit(3);
		}
		return (this->m_array)[index];
	}

	void Insert(const size_t pos, const T& value) override { // passing by reference to avoid copying
		(this->m_array).insert((this->m_array).begin() + pos, value);
		(this->m_size)++;
	}

	void Erase(const size_t pos) override {
		(this->m_array).erase((this->m_array).begin() + pos);
		(this->m_size)--;
	}

	void LibSort(size_t begin_pos, size_t end_pos/*, bool(*comp)(const T& x, const T& y)*/) override {
		std::sort((this->m_array).begin() + begin_pos, (this->m_array).begin() + end_pos/*, comp*/);
	}
};

template<typename T>
class CircularLinkedList : List<T> {
private:
	struct Node {
		T data;
		Node* next;
		Node(T data, Node* next)
			: data(data), next(next) {

		}
		Node(T data)
			: data(data), next(nullptr) {
		
		}
	};
	Node* m_last_node;
	size_t m_size;
public:
	CircularLinkedList() {
		m_size = 0;
		m_last_node = nullptr;
	}

	size_t Size() const {
		return m_size;
	}

	Node* GetNode(const size_t pos) const {
		if (pos > m_size - 1) {
			exit(3);
		}
		int cur_pos = 0;
		Node* cur_node = m_last_node->next;
		while (cur_pos < pos) {
			cur_pos++;
			cur_node = cur_node->next;
		}
		return cur_node;
	}
	const T& operator[] (size_t index) const override {
		return (GetNode(index))->data;
	}
private:
	void InsertInEmpty(const T& value)
	{
		if (m_last_node != nullptr) exit(2);
		Node* new_node = new Node(value);
		m_last_node = new_node;
		m_last_node->next = m_last_node;
	}
public:
	void InsertAfter(Node* node, const T& value, size_t pos)
	{
		if (node == nullptr) {
			InsertInEmpty(value);
		}
		else {
			Node* new_node = new Node(value, node->next);
			node->next = new_node;
			if (pos != 0 && m_last_node == node) m_last_node = new_node;
		}
		m_size++;
	}

	void PushBack(const T& value) override {
		InsertAfter(m_last_node, value, m_size - 1);
	}
	void Insert(const size_t pos, const T& value) override {
		if (pos > m_size - 1) {
			exit(3);
		}
		if (pos == 0) {
			/*if (m_last_node == nullptr) InsertInEmpty(value);
			else {
				Node* new_node = new Node(value, m_last_node->next);
				m_last_node->next = new_node;
			}
			m_size++;*/
			InsertAfter(m_last_node, value, 0);
		}
		else
			InsertAfter(GetNode(pos - 1), value, pos);
	}
	void DeleteNextNode(Node* node, size_t pos)
	{
		if (node == nullptr) exit(2);
		Node* node_to_delete = node->next;
		if (node_to_delete == nullptr) exit(2);
		if (node_to_delete->next == node_to_delete) {
			m_last_node = nullptr;
		}
		else if (pos != 0 && node_to_delete == m_last_node) {
			node->next = node_to_delete->next;
			m_last_node = node;
		}
		else {
			node->next = node_to_delete->next;
		}
		delete node_to_delete;
		m_size--;
	}
	void PopBack() override {
		DeleteNextNode(GetNode(m_size - 2), m_size - 2);
	}
	void Erase(const size_t pos) override {
		if (pos > m_size - 1) {
			exit(3);
		}
		if (pos == 0) {
			DeleteNextNode(m_last_node, 0);
		}
		else 
			DeleteNextNode(GetNode(pos - 1), pos);
	}
	void Print() const override {
		if (m_last_node == nullptr) {
			return;
		}
		Node* cur_node;
		cur_node = m_last_node->next;
		do {
			std::cout << cur_node->data << "\n";
			cur_node = cur_node->next;
		} while (cur_node != m_last_node->next);
		std::cout << "------------------------\n";
	}
	void Free() override {
		Node* cur_node;
		cur_node = m_last_node->next;
		while (cur_node != m_last_node) {
			Node* next_node = cur_node->next;
			delete cur_node;
			cur_node = next_node;
		}
		delete m_last_node;
	}
};

template<typename T, template<typename> class L>
std::ostream& operator<<(std::ostream& stream, L<T>& list) { // cannot pass List because it's abstract - tso there is no polymorphism for interaces? Tried List<T>& list
	list.Print();
	return stream;
}

template<template<typename> class list_type>
bool is_sorted(list_type<int> list, int from, int to) {
	for (int i = from + 1; i < to; i++) {
		if (list[i] < list[i - 1]) return false;
	}
	return true;
}

enum sort_mode { HEAPSORT, MERGESORT, LIBSORT, QUICKSORT_STANDARD, QUICKSORT_RANDOM, QUICKSORT_MEDIAN}; // don't know enum classes yet

template<template<typename> class list_type>
bool check_sort(int size, sort_mode sort, int number_of_tests) {
	list_type<int> list;
	while (number_of_tests--) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(-INT_MAX, INT_MAX);
		for (int i = 0; i < size; i++) {
			list.PushBack(distrib(gen));
		}
		srand(time(0));
		int from = rand() % size, to = rand() % (size - from) + from;
		switch (sort)
		{
		case HEAPSORT:
			list.HeapSort(from, to);
			break;
		case MERGESORT:
			list.MergeSort(from, to);
			break;
		case LIBSORT:
			list.LibSort(from, to);
			break;
		case QUICKSORT_STANDARD:
			list.QuickSort(from, to, STANDART);
			break;
		case QUICKSORT_RANDOM:
			list.QuickSort(from, to, RANDOM_PIVOT);
			break;
		case QUICKSORT_MEDIAN:
			list.QuickSort(from, to, MEDIAN_OF_THREE);
			break;
		default:
			break;
		}
		if (!is_sorted<list_type>(list, from, to)) {
			std::cout << from << " " << to << " " << number_of_tests+1 << "\n";
			list.Print();
			list.Clear();
			return false;
		}
		list.Clear();
	}
	list.Free();
	return true;
}



int main() {
	/*if (check_sort<ArrayList>(1000, LIBSORT, 1000)) std::cout << "ArrayList.LibSort() - Ok\n";
	else std::cout << "ArrayList.LibSort() - Error\n";
	if (check_sort<ArrayList>(1000, HEAPSORT, 1000)) std::cout << "ArrayList.HeapSort() - Ok\n";
	else std::cout << "ArrayList.HeapSort() - Error\n";
	if (check_sort<ArrayList>(1000, MERGESORT, 1000)) std::cout << "ArrayList.MergeSort() - Ok\n";
	else std::cout << "ArrayList.MergeSort() - Error\n";
	if (check_sort<ArrayList>(1000, QUICKSORT_STANDARD, 1000)) std::cout << "ArrayList.QuickSort(STANDARD) - Ok\n";
	else std::cout << "ArrayList.QuickSort(STANDARD) - Error\n";
	if (check_sort<ArrayList>(1000, QUICKSORT_RANDOM, 1000)) std::cout << "ArrayList.QuickSort(RANDOM_PIVOT) - Ok\n";
	else std::cout << "ArrayList.QuickSort(RANDOM_PIVOT) - Error\n"; 
	if (check_sort<ArrayList>(1000, QUICKSORT_MEDIAN, 1000)) std::cout << "ArrayList.QuickSort(MEDIAN_OF_THREE) - Ok\n";
	else std::cout << "ArrayList.QuickSort(MEDIAN_OF_THREE) - Error\n";
	/*if (check_sort<StdVectorList>(1000, LIBSORT, 1000)) std::cout << "StdVectorList.LibSort() - Ok\n";
	else std::cout << "StdVectorList.LibSort() - Error\n";
	if (check_sort<StdVectorList>(1000, HEAPSORT, 1000)) std::cout << "StdVectorList.HeapSort() - Ok\n";
	else std::cout << "StdVectorList.HeapSort() - Error\n";
	if (check_sort<StdVectorList>(1000, MERGESORT, 1000)) std::cout << "StdVectorList.MergeSort() - Ok\n";
	else std::cout << "StdVectorList.MergeSort() - Error\n";
	if (check_sort<StdVectorList>(1000, QUICKSORT_STANDARD, 1000)) std::cout << "StdVectorList.QuickSort(STANDARD) - Ok\n";
	else std::cout << "StdVectorList.QuickSort(STANDARD) - Error\n";
	if (check_sort<StdVectorList>(1000, QUICKSORT_RANDOM, 1000)) std::cout << "StdVectorList.QuickSort(RANDOM_PIVOT) - Ok\n";
	else std::cout << "StdVectorList.QuickSort(RANDOM_PIVOT) - Error\n";
	if (check_sort<StdVectorList>(1000, QUICKSORT_MEDIAN, 1000)) std::cout << "StdVectorList.QuickSort(MEDIAN_OF_THREE) - Ok\n";
	else std::cout << "StdVectorList.QuickSort(MEDIAN_OF_THREE) - Error\n";*/
	//int n;
	//std::cin >> n;
	CircularLinkedList<std::string> array;
	array.PushBack("6");
	array.PushBack("55");
	array.PushBack("444");
	std::cout << array;
	std::cout << array;
	array.Insert(0, "1");
	std::cout << array;
	array.Insert(2, "3");
	std::cout << array;
	array.Insert(array.Size() - 1, "200");
	std::cout << array;
	array.PopBack();
	std::cout << array;
	array.Erase(2);
	std::cout << array;
	array.Erase(0);
	std::cout << array;
	array.Free();
}