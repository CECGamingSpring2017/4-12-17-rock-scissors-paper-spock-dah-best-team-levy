#include <iostream>
using namespace std;

void attackc(double damage, double level, double power, double attack, double defence, double modifier);



int main() {
	double damage = 0;
	double level = 0;
	double power = 0;
	double attack = 0;
	double defence = 0;
	double modifier = 0;

	//cout << "What is your damage" << endl;
	//cin >> damage;

	cout << "What is your level" << endl;
	cin >> level;

	cout << "What is your power" << endl;
	cin >> power;

	cout << "What is your attack" << endl;
	cin >> attack;

	cout << "What is your defence" << endl;
	cin >> defence;

	cout << "What is your modifier" << endl;
	cin >> modifier;

	attackc(damage, level, power, attack, defence, modifier);
}

void attackc(double damage, double level, double power, double attack, double defence, double modifier){
	damage = (((((((((2 * level) / 5) + 2)*power)*attack) / defence) / 50) + 2)*modifier);
	cout << damage;
}