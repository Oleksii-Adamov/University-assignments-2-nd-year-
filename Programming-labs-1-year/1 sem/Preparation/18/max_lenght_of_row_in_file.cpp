#include<cstdio>
#include<stdlib.h>
//#include<iostream>
//using namespace std;
int max_length_of_row_in_file(const char* name) {
	FILE *fp = fopen(name,"r");
	if (fp == NULL) exit(1);
	int c;
	int maxi = 0, now = 0;
	while((c = fgetc(fp)) != EOF) {
		if (c == '\n') {
			if (now > maxi) {
				maxi = now;
			}
			now = 0;
		}
		else now++;
	}
	fclose(fp);
	return maxi;
}
int main() {
	//cout << max_length_of_row_in_file("input.txt");
}
