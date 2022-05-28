#include<iostream>
using namespace std;
void bubbleSort(int array[], int size) {
	bool is_swapped = true;
	for (int step = 0; step < size - 1 && is_swapped; step++) {
		is_swapped = false;
		for (int i = 0; i < size - step - 1; i++) {
		  if (array[i] > array[i + 1]) {
		    swap(array[i], array[i + 1]);
		    is_swapped = true;
		  }
		}
	}
}
