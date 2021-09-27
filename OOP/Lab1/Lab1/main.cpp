#include<iostream>
#include<vector>
#include<algorithm>

// abstract interface class
class List {

};

class ArrayList {
	
};

class CircularLinkedList {

};

template<typename T>
class StdVectorList {
private:
	std::vector<T> m_data;
public:
	StdVectorList() {
		// do nothing
	}

	StdVectorList(size_t size) {
		m_data.resize(size);
	}

	size_t Size() const{ 
		return m_data.size();
	}

	void PushBack(T a) {
		m_data.push_back(a);
	}

	void PopBack() {
		m_data.pop_back();
	}

	void Insert(size_t pos, size_t value) {
		m_data.insert(m_data.begin() + pos, value);
	}

	void Erase(size_t pos) {
		m_data.erase(m_data.begin() + pos);
	}

	T& operator[] (size_t index) {
		return m_data[index];
	}

	const T& operator[] (size_t index) const {
		return m_data[index];
	}

	void LibSort(size_t begin_pos, size_t end_pos/*, bool(*comp)(const T& x, const T& y)*/) {
		std::sort(m_data.begin() + begin_pos, m_data.begin() + end_pos/*, comp*/);
	}

	void QuickSort() {

	}

	void MergeSort() {

	}

	void HeapSort() {

	}

};

template<typename T>
std::ostream& operator<<(std::ostream& stream, StdVectorList<T>& array) {
	size_t size = array.Size();
	if (size > 0) {
		stream << array[0];
	}
	for (size_t i = 1; i < array.Size(); i++) {
		stream << ", " << array[i];
	}
	stream << "\n-----------------------\n";
	return stream;
}

int main() {
	int n;
	//std::cin >> n;
	StdVectorList<int> array(3);
	array[0] = 9;
	array[1] = 8;
	array[2] = 7;
	array.PushBack(6);
	array.PushBack(5);
	array.PushBack(4);
	std::cout << array;
	array.PopBack();
	std::cout << array;
	array.Erase(2);
	std::cout << array;
	array.LibSort(0, 3);
	std::cout << array;
	array.LibSort(0, array.Size());
	std::cout << array;
}