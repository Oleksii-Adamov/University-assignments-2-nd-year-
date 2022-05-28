#include<iostream>
using namespace std;
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_ind = i;
        for (int j = i + 1; j < n; j++)
	        if (arr[j] < arr[min_ind])
	            min_ind = j;
        swap(arr[min_ind], arr[i]);
    }
}
