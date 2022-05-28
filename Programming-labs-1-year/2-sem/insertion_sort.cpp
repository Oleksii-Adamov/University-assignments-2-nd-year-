void insertionSort(int arr[], int n)
{
	for (int i = 1; i < n; i++) {
	    int key = arr[i], j;
	    /* Move elements of arr[0..i-1], that are
	    greater than key, to one position ahead
	    of their current position */
	    for (j = i - 1; j >= 0 && arr[j] > key; j--) {
	        arr[j + 1] = arr[j];
	        j = j - 1;
	    }
	    arr[j + 1] = key;
	}
}
 
