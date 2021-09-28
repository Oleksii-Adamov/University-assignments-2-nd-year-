#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<random>
#include<ctime>

// abstract interface class
template<typename T>
class List {
public:
	virtual size_t Size() const = 0;
	virtual void PushBack(const T& value) = 0;
	virtual void PopBack() = 0;
	virtual T& operator[] (size_t index) = 0;
	virtual const T& operator[] (size_t index) const = 0;
	virtual void Insert(const size_t pos, const T& value) = 0;
	virtual void Erase(const size_t pos) = 0;
	//virtual void Print() = 0;
	virtual void Free() { // ????????
		// do nothing (for library realizations)
	};
	// sort maybe
};

template<typename array_type>
class ArrayBasedList{
protected:
	array_type m_array;
	size_t m_size = 0;
public:
	void Print() {
		for (int i = 0; i < m_size; i++) {
			std::cout << m_array[i] << "\n";
		}
		std::cout << "---------------------------------\n";
	}
	virtual size_t Size() const = 0;
	//virtual array_type GetArray() = 0;
protected:
	/*void Update() {
		m_array = GetArray();
		m_size = Size();
	}*/
public:
	// void Print
	void HeapSort(int begin_pos, int end_pos)
	{
		//Update();
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
};

template<typename T>
class ArrayList : public List<T>, public ArrayBasedList<T*> { // can be more optimized by using std::move, but need to know more about it before using
private:
	//T* m_array = nullptr;
	//size_t m_size = 0;
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

private:
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

	/*T* GetArray() override {
		return m_array;
	}*/

	void PushBack(const T& value) override { // passing by reference to avoid copying, double capacity when runout of it
		if (this->m_size >= m_capacity) {
			Reallocate(this->m_size + this->m_size);
		}
		(this->m_array)[this->m_size] = value;
		//m_array[m_size] = value;
		(this->m_size)++;
	}

	void PopBack() override {
		(this->m_size)--;
	}
	
	T& operator[] (size_t index) override {
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

	/*void Print() override {
		for (int i = 0; i < this->m_size; i++) {
			std::cout << (this->m_array)[i] << "\n";
		}
		std::cout << "---------------------------------\n";
	}*/

	void LibSort(size_t begin_pos, size_t end_pos/*, bool(*comp)(const T& x, const T& y)*/) {
		std::sort((this->m_array) + begin_pos, (this->m_array) + end_pos/*, comp*/);
	}
/*
public:
	void HeapSort(int begin_pos, int end_pos)
	{
		if (begin_pos < 0 || end_pos > m_size) exit(1);
		for (int i = end_pos / 2 - 1; i >= begin_pos; i--)
			Heapify(end_pos, i);
		for (int i = end_pos - 1; i >= begin_pos; i--)
		{
			std::swap(m_array[begin_pos], m_array[i]);
			Heapify(i, begin_pos);
		}
	}
private:
	void Heapify(int end_pos, int root)
	{
		int largest = root;
		int l = 2 * root + 1;
		int r = 2 * root + 2;
		if (l < end_pos && m_array[l] > m_array[largest])
			largest = l;

		if (r < end_pos && m_array[r] > m_array[largest])
			largest = r;
		if (largest != root)
		{
			std::swap(m_array[root], m_array[largest]);
			Heapify(end_pos, largest);
		}
	}
	*/
	/*
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
		delete[] m_array;
		m_array = new_array;
	}
	*/
};

class CircularLinkedList {

};

template<typename T>
class StdVectorList : public List<T>, public ArrayBasedList<std::vector<T>> {
private:
	//std::vector<T> m_vector;
	//std::vector<T>* m_vector_ptr = &m_vector;
public:
	StdVectorList() {
		// do nothing
	}

	StdVectorList(const size_t size) {
		(this->m_array).resize(size);
		this->m_size = size;
	}

	size_t Size() const{ 
		return this->m_size;
	}

	void Clear() {
		(this->m_array).clear();
		this->m_size = (this->m_array).size();
	}

	void PushBack(const T& value) { //passing by reference to avoid copying
		(this->m_array).push_back(value);
		(this->m_size)++;
	}

	void PopBack() {
		(this->m_array).pop_back();
		(this->m_size)--;
	}

	T& operator[] (size_t index) {
		return (this->m_array)[index];
	}

	const T& operator[] (size_t index) const {
		return (this->m_array)[index];
	}

	void Insert(const size_t pos, const T& value) { // passing by reference to avoid copying
		(this->m_array).insert((this->m_array).begin() + pos, value);
		(this->m_size)++;
	}

	void Erase(const size_t pos) {
		(this->m_array).erase((this->m_array).begin() + pos);
		(this->m_size)--;
	}

	void LibSort(size_t begin_pos, size_t end_pos/*, bool(*comp)(const T& x, const T& y)*/) {
		std::sort((this->m_array).begin() + begin_pos, (this->m_array).begin() + end_pos/*, comp*/);
	}
/*
public:
	void HeapSort(int begin_pos, int end_pos)
	{
		if (begin_pos < 0 || end_pos > m_vector.size()) exit(1);
		for (int i = end_pos / 2 - 1; i >= begin_pos; i--)
			Heapify(end_pos, i);
		for (int i = end_pos - 1; i >= begin_pos; i--)
		{
			std::swap(m_vector[begin_pos], m_vector[i]);
			Heapify(i, begin_pos);
		}
	}
private:
	void Heapify(int end_pos, int root)
	{
		int largest = root;
		int l = 2 * root + 1;
		int r = 2 * root + 2;
		if (l < end_pos && m_vector[l] > m_vector[largest])
			largest = l;

		if (r < end_pos && m_vector[r] > m_vector[largest])
			largest = r;
		if (largest != root)
		{
			std::swap(m_vector[root], m_vector[largest]);
			Heapify(end_pos, largest);
		}
	}
	*/
	/*
public:
	void MergeSort(int begin_pos, int end_pos) {
		if (end_pos - begin_pos < 2 || begin_pos > end_pos) return;
		int mid = (end_pos - begin_pos - 1) / 2 + begin_pos;
		MergeSort(begin_pos, mid + 1);
		MergeSort(mid + 1, end_pos);
		Merge(begin_pos, end_pos, mid + 1);
	}
private:
	void Merge(int begin_pos, int end_pos, int border) {
		std::vector<T> new_vector(m_vector.size());
		int i;
		for (i = 0; i < begin_pos; i++) {
			new_vector[i] = m_vector[i];
		}
		int a_p = begin_pos, b_p = border;
		for (i = begin_pos; a_p < border && b_p < end_pos; i++) {
			if (m_vector[a_p] < m_vector[b_p]) {
				new_vector[i] = m_vector[a_p];
				a_p++;
			}
			else {
				new_vector[i] = m_vector[b_p];
				b_p++;
			}
		}
		for (; a_p < border; i++, a_p++) {
			new_vector[i] = m_vector[a_p];
		}
		for (; b_p < end_pos; i++, b_p++) {
			new_vector[i] = m_vector[b_p];
		}
		for (; i < m_vector.size(); i++) {
			new_vector[i] = m_vector[i];
		}
		m_vector = new_vector; // double copying, maybe I can replace m_vector, with pointer to a vector, but it will complicate the code
	}
	*/
};

template<typename T, template<typename> class L>
std::ostream& operator<<(std::ostream& stream, L<T>& array) {
	size_t size = array.Size();
	for (size_t i = 0; i < array.Size(); i++) {
		stream << array[i] << "\n";
	}
	stream << "-----------------------\n";
	return stream;
}

template<template<typename> class list_type>
bool is_sorted(list_type<int> list, int from, int to) {
	for (int i = from + 1; i < to; i++) {
		if (list[i] < list[i - 1]) return false;
	}
	return true;
}

enum sort_mode { HEAPSORT, MERGESORT, LIBSORT }; // don't know enum classes yet

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
			break;
		case LIBSORT:
			list.LibSort(from, to);
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
	if (check_sort<ArrayList>(1000, LIBSORT, 1000)) std::cout << "ArrayList.LibSort() - Ok\n";
	else std::cout << "ArrayList.LibSort() - Error\n";
	if (check_sort<ArrayList>(1000, HEAPSORT, 1000)) std::cout << "ArrayList.HeapSort() - Ok\n";
	else std::cout << "ArrayList.HeapSort() - Error\n";
	if (check_sort<StdVectorList>(1000, LIBSORT, 1000)) std::cout << "StdVectorList.LibSort() - Ok\n";
	else std::cout << "StdVectorList.LibSort() - Error\n";
	if (check_sort<StdVectorList>(1000, HEAPSORT, 1000)) std::cout << "StdVectorList.HeapSort() - Ok\n";
	else std::cout << "StdVectorList.HeapSort() - Error\n";
	//int n;
	//std::cin >> n;
	StdVectorList<std::string> array(3);
	array[0] = "9";
	array[1] = "8";
	array[2] = "7";
	array.PushBack("6");
	array.PushBack("55");
	array.PushBack("444");
	std::cout << array;
	array.PopBack();
	std::cout << array;
	array.Erase(2);
	std::cout << array;
	array.Insert(0, "1");
	std::cout << array;
	array.Insert(2, "3");
	std::cout << array;
	array.HeapSort(0, 3);
	std::cout << array;
	array.HeapSort(3, 6);
	std::cout << array;
	array.HeapSort(0, array.Size());
	std::cout << array;
}