#include<fstream>
using namespace std;
int main() {
	ifstream in ("input.txt");
	ofstream out ("output.txt");
	char c;
	while(in>>c) {
		out<<c;
	}
	in.close();
	out.close();
}
