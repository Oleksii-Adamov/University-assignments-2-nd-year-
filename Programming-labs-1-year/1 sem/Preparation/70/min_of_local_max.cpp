//#include<iostream>
//using namespace std;
struct element {
	double value;
	int index;
};
// ���� ����� ��������� �� ������� �������� ����� ����� ������
element find_min_of_local_max(double arr[], int size) {
	element min = {0.0,-1};
	// ���� ����� ��������� �������� �� ���� ��������, ���� ���������� �������� � �������� -1, �� ����������� ��� ��, �� ������� �������� �� ��������
	for (int i = 1; i < size - 1; i++) {
		if (arr[i] > arr[i-1] && arr[i] > arr[i+1]) {
			if (min.index == -1 || arr[i] < min.value) {
				min.index = i;
				min.value = arr[i];
			}
		}
	}
	return min;
}
/*int main() {
	int n;
	std::cin >> n;
	double *a = new double [n];
	for (int i = 0; i < n; i++) std::cin >> a[i];
	element ans = find_min_of_local_max(a,n);
	std::cout << ans.value << " " << ans.index;
	delete[] a;
}*/
