#include<fstream>
#include<set>
using namespace std;
int main() {
	ifstream in1 ("input1.txt");
	ifstream in2 ("input2.txt");
	if (!in1.is_open() || !in2.is_open()) {
		return 1;
	}
	ofstream out("output.txt");
	char s[256];
	set<string> words;
	while(in1 >> s) {
		if (!(s[0] == 'a' || s[0] == 'A')) {
			if (words.count(s) == 0) {
				words.insert(s);
				out << s << " ";
			}
		}
	}
	while(in2 >> s) {
		if (words.count(s) == 0) {
			words.insert(s);
			out << s << " ";
		}
	}
	in1.close();
	in2.close();
	out.close();
}
