#include<iostream>
#include<windows.h>
using namespace std;
const int MAXSIZE = 100000;
void reverse(int a[], int arr_size) {
	for (int i = 0; i < arr_size/2; i++) {
		int temp = a[i];
		a[i] = a[arr_size - 1 - i];
		a[arr_size - 1 - i] = temp;
	}
}
void prepare(int a[], int &arr_size, int point, bool negative) {
	reverse(a,arr_size);
	// видаляємо ведучі нулі
	while(a[arr_size-1] == 0 && arr_size > point + 1) arr_size--;
}
void write_longnum(int a[], int arr_size, int point, bool negative) {
	if (arr_size == 1 && a[0] == 0) {
		cout << 0 << "\n";
		return;
	}
	if (negative) cout << '-';
	int end = 0;
	while(end < point && a[end] == 0) { // выдкидаю зайві нулі в кінці числа після крапки
		end++;
	}
	for (int i = arr_size - 1; i >= end; i--) {
		cout << a[i];
		if (point != end && i == point) cout << '.';
	}
	cout << "\n";
}
bool is_greater(int a[], int a_size, int point_a, int b[], int b_size, int point_b) {
	if(a_size-point_a > b_size-point_b) {
		return true;
	}
	if(a_size-point_a < b_size-point_b) {
		return false;
	} 
	int a_pos = a_size-1, b_pos = b_size-1;
	while(a_pos >= 0 || b_pos >= 0) {
		if (a_pos < 0) return false;
		if (b_pos < 0) return true;
		if(a[a_pos] == b[b_pos]) {
			a_pos--;
			b_pos--;
			continue;
		}
		return a[a_pos] > b[b_pos];
	}
	return false;
}
void addition(int a[], int a_size, int point_a, bool negative_a, int b[], int b_size, int point_b, bool negative_b, int c[], int &c_size, int &point, bool &negative);
void subtraction(int a[], int a_size, int point_a, bool negative_a, int b[], int b_size, int point_b, bool negative_b, int c[], int &c_size, int &point, bool &negative) {
	if (negative_a ^ negative_b) {
		addition(a,a_size,point_a,negative_a,b,b_size,point_b,!negative_b,c,c_size,point,negative);
		return;
	}
	if (negative_a && negative_b) {
		subtraction(b,b_size,point_b,!negative_b,a,a_size,point_a,!negative_a,c,c_size,point,negative);
		return;
	}
	point = max(point_a,point_b);
	int start = 0, delay_a = 0, delay_b = 0;
	for (int i = 0; i <= max(a_size+point_a,b_size+point_b); i++) { // обнуляєм масив
			c[i] = 0;
	}
	if (is_greater(b,b_size,point_b,a,a_size,point_a)) {
		negative = true;
		// Не ефективно використовувати рекурсію, бо масиви це вказівники, і щоб рекурсія коректно працювала потрібно передати копії масивів, що збільшить витрати пам'яті, тому просто перевисуєм код нижче з заміною a на b 
		if (point_b < point_a) {
			for (int i = 0; i < point_a-point_b; i++) {
				int s = -a[i];
				c[i] += s;
				if (c[i]<0) {
					c[i]+=10;
					c[i+1]--;
				}
			}
			delay_b = point_a-point_b;
			start = point_a-point_b;
		}
		if (point_a < point_b) {
			for (int i = 0; i < point_b-point_a; i++) {
				c[i] = b[i];
			}
			delay_a = point_b-point_a;
			start = point_b-point_a;
		}
		// добавляєм ведучі нулі
		if (b_size+delay_b > a_size+delay_a) {
			for (int i = a_size; i < a_size+(b_size+delay_b-a_size-delay_a); i++) {
				a[i] = 0;
			}
		}
		c_size = max(b_size+delay_b,a_size+delay_a);
		// віднімаємо
		for (int i = start; i < c_size; i++) {
			int s = b[i-delay_b] - a[i-delay_a];
			c[i] += s;
			if (c[i]<0) {
				c[i]+=10;
				c[i+1]--;
			} 
		}
		// видалення ведучих нулів
		while(c[c_size-1]==0 && c_size > point + 1) c_size--;
		if (c_size == point + 1) {
			c_size = 1;
			for (int i = 0; i < point + 1; i++) {
				if (c[i] != 0) {
					c_size = point + 1;
					break;
				}
			}
		}
		return;
	}
	negative = false;
	// приводимо до одної кількості цифр після крапки
	if (point_a < point_b) {
		for (int i = 0; i < point_b-point_a; i++) {
			int s = -b[i];
			c[i] += s;
			if (c[i]<0) {
				c[i]+=10;
				c[i+1]--;
			}
		}
		delay_a = point_b-point_a;
		start = point_b-point_a;
	}
	if (point_b < point_a) {
		for (int i = 0; i < point_a-point_b; i++) {
			c[i] = a[i];
		}
		delay_b = point_a-point_b;
		start = point_a-point_b;
	}
	// добавляєм ведучі нулі
	if (a_size+delay_a > b_size+delay_b) {
		for (int i = b_size; i < b_size+(a_size+delay_a-b_size-delay_b); i++) {
			b[i] = 0;
		}
	}
	c_size = max(a_size+delay_a,b_size+delay_b);
	// віднімаємо
	for (int i = start; i < c_size; i++) {
		int s = a[i-delay_a] - b[i-delay_b];
		c[i] += s;
		if (c[i]<0) {
			c[i]+=10;
			c[i+1]--;
		} 
	}
	// видалення ведучих нулів
	while(c[c_size-1]==0 && c_size > point + 1) c_size--;
	if (c_size == point + 1) {
		c_size = 1;
		for (int i = 0; i < point + 1; i++) {
			if (c[i] != 0) {
				c_size = point + 1;
				break;
			}
		}
	}
}
void addition(int a[], int a_size, int point_a, bool negative_a, int b[], int b_size, int point_b, bool negative_b, int c[], int &c_size, int &point, bool &negative) {
	// розбираємось с знаком
	if (!negative_a && negative_b) {
		subtraction(a,a_size,point_a,negative_a,b,b_size,point_b,!negative_b,c,c_size,point,negative);
		return;
	}
	if (negative_a && !negative_b) {
		subtraction(b,b_size,point_b,negative_b,a,a_size,point_a,!negative_a,c,c_size,point,negative);
		return;
	}
	if (!negative_a && !negative_b) {
		negative = false;
	} 
	if (negative_a && negative_b) {
		negative = true;
	}
	point = max(point_a,point_b);
	for (int i = 0; i <= max(a_size+point_a,b_size+point_b); i++) { // обнуляєм масив
			c[i] = 0;
	}
	int start = 0, delay_a = 0, delay_b = 0;
	// приводимо до одної кількості цифр після крапки
	if (point_a < point_b) {
		for (int i = 0; i < point_b-point_a; i++) {
			c[i] = b[i];
		}
		delay_a = point_b-point_a;
		start = point_b-point_a;
	}
	if (point_b < point_a) {
		for (int i = 0; i < point_a-point_b; i++) {
			c[i] = a[i];
		}
		delay_b = point_a-point_b;
		start = point_a-point_b;
	}
	// добавляєм ведучі нулі
	if (a_size+delay_a > b_size+delay_b) {
		for (int i = b_size; i < b_size+(a_size+delay_a-b_size-delay_b); i++) {
			b[i] = 0;
		}
	}
	if (a_size+delay_a < b_size+delay_b) {
		for (int i = a_size; i < a_size+(b_size+delay_b-a_size-delay_a); i++) {
			a[i] = 0;
		}
	}
	c_size = max(a_size+delay_a,b_size+delay_b);
	// додаємо
	for (int i = start; i < c_size; i++) {
		int s = a[i-delay_a] + b[i-delay_b];
		c[i] += s;
		c[i+1] += c[i]/10;
		c[i]%=10; 
	}
	if (c[c_size] != 0) c_size++;
	else {
		while(c[c_size-1]==0 && c_size > point + 1) c_size--;
		if (c_size == point + 1) {
			c_size = 1;
			for (int i = 0; i < point + 1; i++) {
				if (c[i] != 0) {
					c_size = point + 1;
					break;
				}
			}
		}
	}
}
void multiplicate(int a[], int a_size, int point_a, bool negative_a, int b[], int b_size, int point_b, bool negative_b, int c[], int &c_size, int &point, bool &negative) {
	for(int i = 0; i < a_size + b_size; i++) { // обнуляєм масив
		c[i] = 0;
	}
	point = point_a + point_b; // кількість цифр після крапки
	negative = (negative_a ^ negative_b); // знак добутку 
	bool is_zero = true;
	for (int i = 0; i < b_size; i++) { // множення
		int pos = i;
		for (int j = 0; j < a_size; j++) {
			int m = b[i] * a[j];
			c[pos] += m;
			c[pos+1] += c[pos]/10;
			c[pos]%=10;
			pos++;
		}
	}
	// підраховуємо кількість цифр добутку
	if(c[a_size + b_size-1] != 0) {
		c_size = a_size + b_size;
	}
	else {
			c_size = a_size + b_size - 1;
			while(c[c_size-1]==0 && c_size > point + 1) c_size--;
			if (c_size == point + 1) {
				c_size = 1;
				for (int i = 0; i < point + 1; i++) {
					if (c[i] != 0) {
						c_size = point + 1;
						break;
					}
				}
			}
	}
}
int main() {
	SetConsoleOutputCP(1251);
	int a[MAXSIZE], b[MAXSIZE], result[2*MAXSIZE], point_a = 0, point_b = 0, point_result, i = 0, a_size = 0, b_size = 0, result_size;
	bool point = false, first = true, negative_a = false, negative_b = false, negative_result;
	cout << "Введіть два дійсні числа, для відокремлення дробової частини використовуйте крапку\n";
	while(true) { // ввод данних
		char c;
		cin.get(c);
		if (c >= '0' && c <= '9') {
			if (first) {
				a[i] = c - '0';
				a_size++;
				if (point) {
					point_a++;
				}
			}
			else {
				b_size++;
				b[i] = c - '0';
				if (point) {
					point_b++;
				}
			}
			i++;
		}
		else if (c == '.') {
			point = true;
		}
		else if (c == '-') {
			if (first) {
				negative_a = true;
			}
			else {
				negative_b = true;
			}
		}
		else if (c == ' ' || c == '\n') {
			if (!first) break;
			first = false;
			point = false;
			i = 0;
		}
	}
	prepare(a, a_size, point_a, negative_a);
	prepare(b, b_size, point_b, negative_b);
	write_longnum(a, a_size, point_a, negative_a);
	write_longnum(b, b_size, point_b, negative_b);
	multiplicate(a, a_size, point_a, negative_a, b, b_size, point_b, negative_b, result, result_size, point_result, negative_result);
	cout << "Їх добуток:\n";
	write_longnum(result, result_size, point_result, negative_result);
	addition(a, a_size, point_a, negative_a, b, b_size, point_b, negative_b, result, result_size, point_result, negative_result);
	cout << "Їх сума:\n";
	write_longnum(result, result_size, point_result, negative_result);
	subtraction(a, a_size, point_a, negative_a, b, b_size, point_b, negative_b, result, result_size, point_result, negative_result);
	cout << "Їх різниця:\n";
	write_longnum(result, result_size, point_result, negative_result);
}
