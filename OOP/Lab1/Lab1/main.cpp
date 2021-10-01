#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<random>
#include<ctime>
#include <bitset>
#include <cstdlib>
enum quick_sort_mode { STANDART, RANDOM_PIVOT, MEDIAN_OF_THREE }; // don't know enum classes yet
enum sort_mode { HEAPSORT, MERGESORT, LIBSORT, QUICKSORT_STANDARD, QUICKSORT_RANDOM, QUICKSORT_MEDIAN, LISTMERGESORT };
// abstract interface class
template<typename T>
class List {
public:
	virtual size_t Size() const = 0;
	virtual void PushBack(const T& value) = 0;
	virtual void PopBack() = 0;
	virtual const T& operator[] (size_t index) const = 0;
	virtual void Insert(const size_t pos, const T& value) = 0;
	virtual void Erase(const size_t pos) = 0;
	virtual void Print() const = 0;
	virtual void Free() {
		// do nothing (for library realizations)
	};
	virtual void Clear() = 0;
};

template<typename array_type, typename T>
class ArrayBasedList{
protected:
	array_type m_array;
	size_t m_size = 0;
public:
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
		size_t i;
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

	bool IsSorted(int from, int to) {
		for (int i = from + 1; i < to; i++) {
			if (m_array[i] < m_array[i - 1]) return false;
		}
		return true;
	}

	template<template<typename> class list_type>
	static bool CheckSort(int size, sort_mode sort, int number_of_tests) {
		list_type<int> list;
		while (number_of_tests--) {
			srand(time(0));
			for (int i = 0; i < size; i++) {
				list.PushBack(rand());
			}
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
			if (!list.IsSorted(from, to)) {
				std::cout << from << " " << to << " " << number_of_tests + 1 << "\n";
				list.Print();
				list.Clear();
				return false;
			}
			list.Clear();
		}
		list.Free();
		return true;
	}
};

template<typename T>
class ArrayList : public List<T>, public ArrayBasedList<T*, T> { // can be more optimized by using std::move, but need to know more about it before using.
	// Also I cannot understand why i cannot access m_size, but can this->m_size. In IPv4 class it works fine.
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

	void Clear() override {
		this->m_size = 0;
	}

	void Print() const override{
		for (size_t i = 0; i < this->m_size; i++) {
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
		for (size_t i = 0; i < this->m_size; i++) {
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

	void Clear() override {
		(this->m_array).clear();
		this->m_size = (this->m_array).size();
	}

	void Print() const override {
		for (size_t i = 0; i < this->m_size; i++) {
			std::cout << (this->m_array)[i] << "\n";
		}
		std::cout << "---------------------------------\n";
	}

private:
	void Replace_buffer(T* buffer) override {
		for (size_t i = 0; i < this->m_size; i++) {
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

	Node** GetLastNodePtr() {
		return &m_last_node;
	}

	Node* GetNode(const size_t pos) const {
		if (pos > m_size - 1) {
			exit(3);
		}
		size_t cur_pos = 0;
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
	void InsertAfter(Node* node, const T& value, bool is_first)
	{
		if (node == nullptr) {
			InsertInEmpty(value);
		}
		else {
			Node* new_node = new Node(value, node->next);
			node->next = new_node;
			if (!is_first && m_last_node == node) m_last_node = new_node;
		}
		m_size++;
	}

	void PushBack(const T& value) override {
		if (m_size == 0) InsertAfter(m_last_node, value, true);
		else InsertAfter(m_last_node, value, false);
	}
	void Insert(const size_t pos, const T& value) override {
		if (pos > m_size - 1) {
			exit(3);
		}
		if (pos == 0) {
			InsertAfter(m_last_node, value, true);
		}
		else
			InsertAfter(GetNode(pos - 1), value, false);
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
		m_last_node = nullptr;
		m_size = 0;
	}
	void Clear() override {
		Free();
	}
private:
	/*void Split(Node* source, Node** front_ptr, Node** back_ptr)
	{
		Node* fast;
		Node* slow;
		slow = source;
		fast = source->next;

		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		/* 'slow' is before the midpoint in the list, so split it in two
		at that point. 
		*front_ptr = source;
		*back_ptr = slow->next;
		slow->next = NULL;
	}*/
	void Split(Node* source_last, Node** front_last_ptr, Node** mid_last_ptr)
	{
		Node* fast;
		Node* slow;
		slow = source_last->next;
		fast = slow->next;
		while (fast->next != source_last->next) {
			fast = fast->next;
			if (fast->next != source_last->next) {
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front_last_ptr = slow;
		*mid_last_ptr = fast;
		Node* first = source_last->next;
		fast->next = slow->next;
		slow->next = first;
	}
	Node* MergeStep(Node* front, size_t front_size, Node* mid, size_t mid_size) {
		Node* result = nullptr;
		if (front_size == 0) return mid;
		if (mid_size == 0) return front;
		if (front->data < mid->data) {
			result = front;
			result->next = MergeStep(front->next, front_size - 1, mid, mid_size);
		}
		else {
			result = mid;
			result->next = MergeStep(front, front_size, mid->next, mid_size - 1);
		}
		return result;
	}
	Node* Merge(Node* front_last, size_t front_size, Node* mid_last, size_t mid_size)
	{
		Node* result_head = MergeStep(front_last->next, front_size, mid_last->next, mid_size);
		Node* result_tail = result_head;
		for (size_t i = 0; i < front_size + mid_size - 1; i++) {
			result_tail = result_tail->next;
		}
		result_tail->next = result_head;
		return result_tail;
	}
public:
	void MergeSort(Node** last_ptr, size_t size)
	{
		Node* last = *last_ptr;
		Node* front_last;
		Node* mid_last;
		if (size < 2) {
			return;
		}
		Split(last, &front_last, &mid_last);
		size_t size_front = size / 2, size_mid = size - size_front;
		MergeSort(&front_last, size_front);
		MergeSort(&mid_last, size_mid);
		*last_ptr = Merge(front_last, size_front, mid_last, size_mid);
	}
private:
	bool is_sorted() {
		if (m_size < 2) {
			return true;
		}
		Node* cur_node = m_last_node->next, * next_node = cur_node->next;
		do {
			if (next_node->data < cur_node->data) {
				return false;
			}
			cur_node = cur_node->next;
			next_node = cur_node->next;
		} while (next_node != m_last_node->next);
		return true;
	}
public:
	static bool CheckSort(size_t size, size_t number_of_tests) {
		CircularLinkedList<T> list;
		while (number_of_tests--) {
			srand(time(0));
			for (size_t i = 0; i < size; i++) {
				list.PushBack(rand());
			}
			list.MergeSort(&list.m_last_node, list.Size());
			if (!list.is_sorted()) {
				std::cout << "Wrong sort\n";
				list.Print();
				return false;
			}
			list.Free();
		}
		return true;
	}
};

template<typename T, template<typename> class L>
std::ostream& operator<<(std::ostream& stream, L<T>& list) { // cannot pass List because it's abstract - tso there is no polymorphism for interaces? Tried List<T>& list
	list.Print();
	return stream;
}

unsigned short ToHexDigit(char hex_digit) {
	if (hex_digit >= '0' && hex_digit <= '9') return (hex_digit - '0');
	if (hex_digit >= 'a' && hex_digit <= 'f') return (hex_digit - 'a' + 10);
	if (hex_digit >= 'A' && hex_digit <= 'F') return (hex_digit - 'A' + 10);
	exit(5);
}
int FromHexStringToDecInt(const char* hex) {
	size_t size = strlen(hex);
	int result = 0;
	int multiplier = 1;
	for (short i = size - 1; i >= 0; i--) {
		result += multiplier * ToHexDigit(hex[i]);
		multiplier *= 16;
	}
	return result;
}

template<unsigned char BITS, unsigned char NUMBER_OF_GROUPS>
class IP {
protected:
	std::bitset<BITS> m_mask;
	std::bitset<BITS> m_net_mask;
	std::bitset<BITS> m_subnet_mask;
	unsigned char m_subnet_bits;
	bool m_is_subnet;
	const unsigned char NUMBER_OF_BITS_IN_GROUP = BITS / NUMBER_OF_GROUPS;
	void Init_Net_and_Subnet_Mask() {
		m_net_mask.reset();
		for (unsigned char i = 0; i < m_subnet_bits; i++) {
			m_net_mask.set(BITS - 1 - i);
		}
		m_subnet_mask = (m_mask & m_net_mask);
	}
	void InitFromArray(unsigned short int octet[NUMBER_OF_GROUPS], unsigned char subnet_bits) {
		m_subnet_bits = subnet_bits;
		unsigned char cur_bit = 0, host_bits = BITS - subnet_bits;
		m_is_subnet = true;
		// find mask
		for (int i = NUMBER_OF_GROUPS - 1; i >= 0; i--) {
			unsigned short int dec = octet[i];
			for (unsigned char j = 0; j < NUMBER_OF_BITS_IN_GROUP; dec /= 2, cur_bit++, j++) { // write in bitset in reverse order - because bitset handles it(cout)
				m_mask[cur_bit] = dec % 2;
				if (m_mask[cur_bit] && cur_bit < host_bits) {
					m_is_subnet = false;
				}
			}
		}
		Init_Net_and_Subnet_Mask();
		std::cout << m_mask << "\n" << m_net_mask << "\n" << m_subnet_mask << "\n" << m_is_subnet << "\n------------------\n";
	}
	void InitFromString(const char* string, const char separetor, int(*convert_group_from_string_func)(const char*)) { // from string
		unsigned short groups[NUMBER_OF_GROUPS];
		unsigned char string_pos = 0, num_pos = 0, groups_pos = 0;
		char a[5];
		for (; string[string_pos] != '\0'; string_pos++) {
			if (string[string_pos] == separetor || string[string_pos] == '/') {
				a[num_pos] = '\0';
				groups[groups_pos] = convert_group_from_string_func(a);
				num_pos = 0;
				groups_pos++;
			}
			else {
				a[num_pos] = string[string_pos];
				num_pos++;
			}
		}
		a[num_pos] = '\0';
		unsigned char subnetbits = atoi(a);
		InitFromArray(groups, subnetbits);
	}
public:
	char GetSubnetBits() {
		return m_subnet_bits;
	}
	bool IsSubnet() {
		return m_is_subnet;
	}
	bool IsInSubnet(IP<BITS, NUMBER_OF_GROUPS> subnet) {
		if (!subnet.IsSubnet()) exit(4);
		return ((m_subnet_bits == subnet.GetSubnetBits()) && (m_subnet_mask == subnet.m_mask));
	}
};

class IPv4 : public IP<32, 4> {
public:
	IPv4() = delete;
	IPv4(const char* string) { // from string
		InitFromString(string, '.', atoi);
	}
	IPv4(unsigned short octet[4], unsigned char subnet_bits) {
		InitFromArray(octet, subnet_bits);
	}
};

class IPv6 : public IP<128, 8> {
public:
	IPv6() = delete;

	IPv6(unsigned short groups[8], unsigned char subnet_bits) {
		InitFromArray(groups, subnet_bits);
	}
	IPv6(const char* string) { // from string
		InitFromString(string, ':', FromHexStringToDecInt);
	}
};
int main() {
	if (CircularLinkedList<int>::CheckSort(1000, 1000)) std::cout << "CircularLinkedList.MergeSort() - Ok\n";
	else std::cout << "CircularLinkedList.MergeSort() - Error\n";
	if (ArrayList<int>::CheckSort<ArrayList>(1000, LIBSORT, 1000)) std::cout << "ArrayList.LibSort() - Ok\n";
	else std::cout << "ArrayList.LibSort() - Error\n";
	if (ArrayList<int>::CheckSort<ArrayList>(1000, HEAPSORT, 1000)) std::cout << "ArrayList.HeapSort() - Ok\n";
	else std::cout << "ArrayList.HeapSort() - Error\n";
	if (ArrayList<int>::CheckSort<ArrayList>(1000, MERGESORT, 1000)) std::cout << "ArrayList.MergeSort() - Ok\n";
	else std::cout << "ArrayList.MergeSort() - Error\n";
	if (ArrayList<int>::CheckSort<ArrayList>(1000, QUICKSORT_STANDARD, 1000)) std::cout << "ArrayList.QuickSort(STANDARD) - Ok\n";
	else std::cout << "ArrayList.QuickSort(STANDARD) - Error\n";
	if (ArrayList<int>::CheckSort<ArrayList>(1000, QUICKSORT_RANDOM, 1000)) std::cout << "ArrayList.QuickSort(RANDOM_PIVOT) - Ok\n";
	else std::cout << "ArrayList.QuickSort(RANDOM_PIVOT) - Error\n";
	if (ArrayList<int>::CheckSort<ArrayList>(1000, QUICKSORT_MEDIAN, 1000)) std::cout << "ArrayList.QuickSort(MEDIAN_OF_THREE) - Ok\n";
	else std::cout << "ArrayList.QuickSort(MEDIAN_OF_THREE) - Error\n";
	if (StdVectorList<int>::CheckSort<StdVectorList>(1000, LIBSORT, 1000)) std::cout << "StdVectorList.LibSort() - Ok\n";
	else std::cout << "StdVectorList.LibSort() - Error\n";
	if (StdVectorList<int>::CheckSort<StdVectorList>(1000, HEAPSORT, 1000)) std::cout << "StdVectorList.HeapSort() - Ok\n";
	else std::cout << "StdVectorList.HeapSort() - Error\n";
	if (StdVectorList<int>::CheckSort<StdVectorList>(1000, MERGESORT, 1000)) std::cout << "StdVectorList.MergeSort() - Ok\n";
	else std::cout << "StdVectorList.MergeSort() - Error\n";
	if (StdVectorList<int>::CheckSort<StdVectorList>(1000, QUICKSORT_STANDARD, 1000)) std::cout << "StdVectorList.QuickSort(STANDARD) - Ok\n";
	else std::cout << "StdVectorList.QuickSort(STANDARD) - Error\n";
	if (StdVectorList<int>::CheckSort<StdVectorList>(1000, QUICKSORT_RANDOM, 1000)) std::cout << "StdVectorList.QuickSort(RANDOM_PIVOT) - Ok\n";
	else std::cout << "StdVectorList.QuickSort(RANDOM_PIVOT) - Error\n";
	if (StdVectorList<int>::CheckSort<StdVectorList>(1000, QUICKSORT_MEDIAN, 1000)) std::cout << "StdVectorList.QuickSort(MEDIAN_OF_THREE) - Ok\n";
	else std::cout << "StdVectorList.QuickSort(MEDIAN_OF_THREE) - Error\n";
	CircularLinkedList<std::string> list;
	list.PushBack("6");
	list.PushBack("55");
	list.PushBack("444");
	std::cout << list;
	std::cout << list;
	list.Insert(0, "1");
	std::cout << list;
	list.Insert(2, "3");
	std::cout << list;
	list.Insert(list.Size() - 1, "200");
	std::cout << list;
	list.MergeSort(list.GetLastNodePtr(), list.Size());
	std::cout << list;
	list.PopBack();
	std::cout << list;
	list.Erase(2);
	std::cout << list;
	list.Erase(0);
	std::cout << list;
	list.Free();
	IPv4 ip4("192.168.0.15/24");
	unsigned short subnet_octet[4];
	subnet_octet[0] = 192;
	subnet_octet[1] = 168;
	subnet_octet[2] = 0;
	subnet_octet[3] = 0;
	IPv4 subnet(subnet_octet, 24);
	std::cout << ip4.IsInSubnet(subnet) << "\n---------------------------\n";
	IPv4 ip41("192.168.2.0/24");
	std::cout << ip41.IsInSubnet(subnet) << "\n---------------------------\n";
	unsigned short group[8];
	group[0] = 0x1203;
	group[1] = 0x890f;
	group[2] = group[3] = group[4] = group[5] = group[6] = group[7] = 0x000;
	IPv6 ip6_subnet(group, 32); // 1203:890f:0000:0000:0000:0000:0000:0000/32
	IPv6 ip6("1203:890f:1000:0000:0030:0000:0ff0:0000/32");
	std::cout << ip6.IsInSubnet(ip6_subnet) << "\n---------------------------\n";
}