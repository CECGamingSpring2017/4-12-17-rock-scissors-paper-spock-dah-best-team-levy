#include <iostream>
using namespace std;

void nuke(double attack, double orb, double nuked);



int main() {
	double attack = 0;
	double orb = 0;
	double nuked = 0;
	cout << "What is your attack" << endl;
	cin >> attack;

	cout << "What is your orb stat" << endl;
	cin >> orb;



	nuke(attack, orb, nuked);
}

void nuke(double attack, double orb, double nuked) {
	nuked = (attack*(1 + (0.3 * orb)) + 3000);
	cout << nuked;
}