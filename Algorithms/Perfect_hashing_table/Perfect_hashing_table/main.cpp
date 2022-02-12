#include<fstream>
#include"hash_table.h"
int main() {
	int n, m, q;
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	in >> n >> m >> q;
	double* arr = new double[n];
	for (int i = 0; i < n; i++) {
		in >> arr[i];
	}
	hash_table table(m, arr, n);
	table.visualize(arr, n, out);
	for (int i = 0; i < q; i++) {
		double value;
		in >> value;
		if (table.contains(value)) {
			out << "Array/Hash table contains " << value << "\n";
		}
		else {
			out << "Array/Hash table DOESN'T contain " << value << "\n";
		}
	}
	delete[] arr;
}