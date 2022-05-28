#include<cstdio>
#include<stdlib.h>
void delete_empty_rows(const char* name) {
	FILE *fp_read = fopen(name, "r");
	FILE *fp_write = fopen("temp.txt", "w");
	if (fp_read == NULL || fp_write == NULL) exit(1);
	char c, prev_char = '\n';
	while ((c = fgetc(fp_read)) != EOF) {
		if (!(c == '\n' && prev_char == '\n')) {
			fputc(c,fp_write); 
		}
		prev_char = c;
	}
	fclose(fp_read);
	fclose(fp_write);
	remove(name);
	rename("temp.txt", name);
}
int main() {
	delete_empty_rows("input.txt");
}
