#include<cstdio>
#include<stdlib.h>
//using namespace std;
void erase_last_row(const char* name) {
	FILE *fp_input = fopen(name,"r");
	FILE *fp_temp = fopen("temp.txt","w");
	if (fp_input == NULL || fp_temp == NULL) exit(1);
	int c;
	int last_pos_in_result_file = 0;
	int i = 0;
	while ((c = getc(fp_input)) != EOF) {
		if (c == '\n') {
			last_pos_in_result_file = i;
		}
		i++;
	}
	rewind(fp_input);
	for (i = 0; i < last_pos_in_result_file; i++) {
		c = getc(fp_input);
		putc(c,fp_temp);
	}
	fclose(fp_input);
	fclose(fp_temp);
	remove(name);
	rename("temp.txt",name);
}
int main() {
	erase_last_row("input.txt");
}
