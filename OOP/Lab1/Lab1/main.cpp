#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

// abstract interface class
class List {

};

template<typename T>
class ArrayList { // can be more optimized by using std::move, but need to know more about it before using
private:
	T* m_array = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
public:

	ArrayList() {
		Reallocate(2);
	}

	ArrayList(size_t n) {
		Reallocate(n);
		m_size = n;
	}

	~ArrayList() {
		delete[] m_array;
	}

private:
	void Reallocate(size_t new_size) { // new_size > m_size
		if (new_size <= m_size) return;
		T* new_array = new T[new_size];
		for (int i = 0; i < m_size; i++) {
			new_array[i] = m_array[i];
		}
		delete[] m_array;
		m_array = new_array;
		m_capacity = new_size;
	}

public:
	size_t Size() const {
		return m_size;
	}
	void PushBack(const T& value) { // passing by reference to avoid copying, double capacity when runout of it
		if (m_size >= m_capacity) {
			Reallocate(m_size + m_size);
		}
		m_array[m_size] = value;
		m_size++;
	}

	void PopBack() {
		m_size--;
	}
	
	T& operator[] (size_t index) {
		return m_array[index];
	}

	const T& operator[] (size_t index) const {
		return m_array[index];
	}

	void Insert(size_t pos, const T& value) { // passing by reference to avoid copying
		if (pos > m_size) exit(1);
		T insert_value = value;
		for (size_t i = pos; i < m_size; i++) {
			T temp = m_array[i];
			m_array[i] = insert_value;
			insert_value = temp;
		}
		PushBack(insert_value);
	}

	void Erase(size_t pos) {
		if (pos >= m_size) exit(1);
		for (size_t i = pos; i < m_size - 1; i++) {
			m_array[i] = m_array[i + 1];
		}
		PopBack();
	}

	void LibSort(size_t begin_pos, size_t end_pos/*, bool(*comp)(const T& x, const T& y)*/) {
		std::sort(m_array + begin_pos, m_array + end_pos/*, comp*/);
	}

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
};

class CircularLinkedList {

};

template<typename T>
class StdVectorList {
private:
	std::vector<T> m_vector;
	std::vector<T>* m_vector_ptr = &m_vector;
public:
	StdVectorList() {
		// do nothing
	}

	StdVectorList(size_t size) {
		m_vector.resize(size);
	}

	size_t Size() const{ 
		return m_vector.size();
	}

	void PushBack(const T& value) { //passing by reference to avoid copying
		m_vector.push_back(value);
	}

	void PopBack() {
		m_vector.pop_back();
	}

	T& operator[] (size_t index) {
		return m_vector[index];
	}

	const T& operator[] (size_t index) const {
		return m_vector[index];
	}

	void Insert(size_t pos, const T& value) { // passing by reference to avoid copying
		m_vector.insert(m_vector.begin() + pos, value);
	}

	void Erase(size_t pos) {
		m_vector.erase(m_vector.begin() + pos);
	}

	void LibSort(size_t begin_pos, size_t end_pos/*, bool(*comp)(const T& x, const T& y)*/) {
		std::sort(m_vector.begin() + begin_pos, m_vector.begin() + end_pos/*, comp*/);
	}

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
		std::vector<T> new_vector(m_size);
		int i;
		for (i = 0; i < begin_pos; i++) {
			new_vector[i] = new_vector[i];
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
		for (; i < m_size; i++) {
			new_vector[i] = m_vector[i];
		}
		delete[] m_array;
		m_array = new_array;
	}
	*/
};

	void QuickSort() {

	}

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

int main() {
	//int n;
	//std::cin >> n;
	ArrayList<std::string> array(3);
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
	array.MergeSort(0, 3);
	std::cout << array;
	array.MergeSort(3, 6);
	std::cout << array;
	array.MergeSort(0, array.Size());
	std::cout << array;
}