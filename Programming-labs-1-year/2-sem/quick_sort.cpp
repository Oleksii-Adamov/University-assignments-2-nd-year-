#include<iostream>
using namespace std;
const int SIZE = 1000;
// 3-way quick-sort using Hoare’s partition
void partition(int a[], int l, int r, int& i, int& j)
{
    i = l - 1, j = r;
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
        swap(a[i], a[j]);
        if (a[i] == pivot) {
            left_border++;
            swap(a[left_border], a[i]);
        }
        if (a[j] == pivot) {
            right_border--;
            swap(a[j], a[right_border]);
        }
    }
    swap(a[i], a[r]);
    j = i - 1;
    for (int k = l; k < left_border; k++, j--)
        swap(a[k], a[j]);
    i = i + 1;
    for (int k = r - 1; k > right_border; k--, i++)
        swap(a[i], a[k]);
}
void quicksort(int a[], int l, int r)
{
    if (r <= l)
        return;
    int i, j;
    partition(a, l, r, i, j);
    quicksort(a, l, j);
    quicksort(a, i, r);
}
int main() {
    int n, a[SIZE];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    quicksort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
}
