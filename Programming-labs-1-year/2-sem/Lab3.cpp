#include<iostream>
#include<ctime>
#include<iomanip>
#include<chrono>
#include<algorithm>
#include <random>
using namespace std;
const int SIZE = 1000, TESTS = 1000, NUMBER_OF_SORTS = 5;
long long copies = 0;
struct sort_algo {
	long double num_of_copies;
	long double nano_sec;
	const char* name;
};
void my_swap(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
	copies += 3;
}

// heap sort
void heapify(int arr[], int n, int root)
{
	int largest = root;
	int l = 2 * root + 1;
	int r = 2 * root + 2;
	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != root)
	{
		my_swap(arr[root], arr[largest]);
		heapify(arr, n, largest);
	}
}
void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	for (int i = n - 1; i >= 0; i--)
	{
		my_swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

// merge sort
void merge(int a[], int size_a, int b[], int size_b, int dest[]) {
	int a_p = 0, b_p = 0, i = 0;
	for (; a_p < size_a && b_p < size_b; i++) {
		if (a[a_p] < b[b_p]) {
			dest[i] = a[a_p];
			a_p++;
		}
		else {
			dest[i] = b[b_p];
			b_p++;
		}
		copies++;
	}
	for (; a_p < size_a; i++, a_p++) {
		dest[i] = a[a_p];
		copies++;
	}
	for (; b_p < size_b; i++, b_p++) {
		dest[i] = b[b_p];
		copies++;
	}
}
void merge_sort(int a[], int size) {
	if (size == 1) return;
	int mid = (size - 1) / 2, size_a1 = mid + 1, size_a2 = size - size_a1;
	int* a1 = new int[size_a1];
	int* a2 = new int[size_a2];
	for (int i = 0; i < size_a1; i++) {
		a1[i] = a[i];
		copies++;
	}
	for (int i = 0; i < size_a2; i++) {
		a2[i] = a[i + size_a1];
		copies++;
	}
	merge_sort(a1, size_a1);
	merge_sort(a2, size_a2);
	merge(a1, size_a1, a2, size_a2, a);
	delete[] a1;
	delete[] a2;
}

// 3-way quick-sort using Hoare’s partition
void partition(int a[], int l, int r, int& i, int& j, int mode) // mode = 0 - pivot = a[r], 1 - random pivot, 2 - median of three pivot   
{
	i = l - 1, j = r;
	if (mode == 1) {
		my_swap(a[r], a[l + rand() % (r - l + 1)]);
	}
	if (mode == 2) {
		int mid = (l + r) / 2;
		if (a[l] > a[mid])
			my_swap(a[l], a[mid]);
		if (a[r] < a[l])
			my_swap(a[r], a[l]);
		if (a[mid] < a[r])
			my_swap(a[r], a[mid]);
	}
	int pivot = a[r], left_border = l - 1, right_border = r; // a[l...left_border] = a[right_border...r] = pivot
	while (true) {
		do {
			i++;
		} while (a[i] < pivot);
		do {
			j--;
		} while (j > l && pivot < a[j]);
		if (i >= j)
			break;
		my_swap(a[i], a[j]);
		if (a[i] == pivot) {
			left_border++;
			my_swap(a[left_border], a[i]);
		}
		if (a[j] == pivot) {
			right_border--;
			my_swap(a[j], a[right_border]);
		}
	}
	my_swap(a[i], a[r]);
	j = i - 1;
	for (int k = l; k < left_border; k++, j--) {
		my_swap(a[k], a[j]);
	}
	i = i + 1;
	for (int k = r - 1; k > right_border; k--, i++) {
		my_swap(a[i], a[k]);
	}
}
void three_way_quicksort(int a[], int l, int r, int mode) // mode = 0 - pivot = a[r], 1 - random pivot, 2 - median of three pivot  
{
	if (r <= l)
		return;
	int i, j;
	partition(a, l, r, i, j, mode);
	three_way_quicksort(a, l, j, mode);
	three_way_quicksort(a, i, r, mode);
}
bool is_sorted(int a[]) {
	for (int i = 1; i < SIZE; i++) {
		if (a[i] < a[i - 1]) return false;
	}
	return true;
}
long double ex_time_of_sort(int a[], int mode) {
	copies = 0;
	int* t = new int[SIZE];
	for (int i = 0; i < SIZE; i++)
		t[i] = a[i];
	auto begin = std::chrono::high_resolution_clock::now();
	if (mode == 4) merge_sort(t, SIZE);
	if (mode == 3) heapSort(t, SIZE);
	else three_way_quicksort(t, 0, SIZE - 1, mode);
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	if (!is_sorted(t)) {
		cout << "mode " << mode << "is WRONG!\n";
		for (int i = 0; i < SIZE; i++)
			cout << t[i] << " ";
		exit(1);
	}
	delete[] t;
	return elapsed.count();
}

bool copies_cmp(sort_algo x, sort_algo y) {
	return x.num_of_copies < y.num_of_copies;
}
bool time_cmp(sort_algo x, sort_algo y) {
	return x.nano_sec < y.nano_sec;
}
void print_ans(sort_algo sort_algos[]) {
	for (int mode = 0; mode < NUMBER_OF_SORTS; mode++)
		cout << sort_algos[mode].name << ": avarage copies - " << fixed << setprecision(3) << sort_algos[mode].num_of_copies << ", avarage time - " << sort_algos[mode].nano_sec * 1e-6 << "ms\n";
	sort(sort_algos, sort_algos + NUMBER_OF_SORTS, copies_cmp);
	cout << "The least number of copies required by the " << sort_algos[0].name << '\n';
	sort(sort_algos, sort_algos + NUMBER_OF_SORTS, time_cmp);
	cout << "The least amount of time (non-expensive copies) required by the " << sort_algos[0].name << '\n';
	cout << "\n\n\n";
}
void print_sorted_array(int a[], int n, int mode) {
	int* t = new int[n];
	for (int i = 0; i < n; i++)
		t[i] = a[i];
	if (mode == 0) {
		cout << "3-way quicksort: ";
		three_way_quicksort(t, 0, n - 1, 0);
	}
	if (mode == 1) {
		cout << "3-way quicksort (random pivot): ";
		three_way_quicksort(t, 0, n - 1, 1);
	}
	if (mode == 2) {
		cout << "3-way quicksort (median of 3 pivot): ";
		three_way_quicksort(t, 0, n - 1, 2);
	}
	if (mode == 3) {
		cout << "heap sort: ";
		heapSort(t, n);
	}
	if (mode == 4) {
		cout << "merge sort: ";
		merge_sort(t, n);
	}
	for (int i = 0; i < n; i++) {
		cout << t[i] << " ";
	}
	cout << "\n";
}
int main() {
	sort_algo sort_algos[NUMBER_OF_SORTS];
	for (int mode = 0; mode < NUMBER_OF_SORTS; mode++) {
		sort_algos[mode].nano_sec = 0;
		sort_algos[mode].num_of_copies = 0;
		if (mode == 0) sort_algos[mode].name = "3-way quicksort";
		if (mode == 1) sort_algos[mode].name = "3-way quicksort (random pivot)";
		if (mode == 2) sort_algos[mode].name = "3-way quicksort (median of 3 pivot)";
		if (mode == 3) sort_algos[mode].name = "heap sort";
		if (mode == 4) sort_algos[mode].name = "merge sort";
	}
	int t = TESTS;
	//int a[SIZE];
	int* a = new int[SIZE];
	while (t--) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(-INT_MAX, INT_MAX);
		for (int i = 0; i < SIZE; i++) {
			a[i] = distrib(gen);
			//cout << a[i] << " ";
		}
		//cout << '\n';
		for (int mode = 0; mode < NUMBER_OF_SORTS; mode++) {
			sort_algos[mode].nano_sec += ex_time_of_sort(a, mode) / TESTS;
			sort_algos[mode].num_of_copies += long double(copies) / TESTS;
		}
	}
	cout << "SIZE = " << SIZE << " TESTS = " << TESTS << "\n";
	cout << "Comparision of sort algorithms:\n";
	cout << "Random data:\n";
	print_ans(sort_algos);
	cout << "Array of equal elements:\n";
	for (int i = 0; i < SIZE; i++) {
		a[i] = 0;
	}
	for (int mode = 0; mode < NUMBER_OF_SORTS; mode++) {
		sort_algos[mode].nano_sec = ex_time_of_sort(a, mode);
		sort_algos[mode].num_of_copies = long double(copies);
	}
	print_ans(sort_algos);
	cout << "Array of 3 different values (for example: 0,1,1,0,2,2,0):\n";
	t = TESTS;
	for (int mode = 0; mode < NUMBER_OF_SORTS; mode++) {
		sort_algos[mode].nano_sec = 0;
		sort_algos[mode].num_of_copies = 0;
	}
	while (t--) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, 2);
		for (int i = 0; i < SIZE; i++) {
			a[i] = distrib(gen);
		}
		for (int mode = 0; mode < NUMBER_OF_SORTS; mode++) {
			sort_algos[mode].nano_sec += ex_time_of_sort(a, mode) / TESTS;
			sort_algos[mode].num_of_copies += long double(copies) / TESTS;
		}
	}
	delete[] a;
	print_ans(sort_algos);
	/*
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < NUMBER_OF_SORTS; i++) {
		print_sorted_array(a, n, i);
	}
	*/
}
