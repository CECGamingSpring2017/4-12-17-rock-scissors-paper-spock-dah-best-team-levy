#include <iostream>
#include <time.h>
using namespace std;

int main() {
	int stat[7];
	srand(time(NULL));
	for (int i = 0; i < 7; i++) {
		stat[i] = rand() % 10 + 1;
	}
	cout << "S: " << stat[0] << endl;
	cout << "P: " << stat[1] << endl;
	cout << "E: " << stat[2] << endl;
	cout << "C: " << stat[3] << endl;
	cout << "I: " << stat[4] << endl;
	cout << "A: " << stat[5] << endl;
	cout << "L: " << stat[6] << endl;
}