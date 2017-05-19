#include <iostream>
using namespace std;
bool horoscope(int month);

int main() {
	int month;

	cout << "What month are you born in?" << endl;
	cout << "Ex. January is 1, Feb is 2" << endl;
	cin >> month; 
	if (horoscope(month) == 1) {
		cout << "ITS YOUR SIGN RIGHT NOW, SO YOU SUCK" << endl;
	}
}

bool horoscope(int month) {
	if (month == 1) {
		cout<<"Your sign is Capricorn" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
	else if (month == 2) {
		cout << "Your sign is Aquarius" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
	else if (month == 3) {
		cout << "Your sign is Pisces" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
	else if (month == 4) {
		cout << "Your sign is Aries" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 1;
	}
	else if (month == 5) {
		cout << "Your sign is Tourus" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
	else if (month == 6) {
		cout << "Your sign is Gemini" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
	else if (month == 7) {
		cout << "Your sign is Cancer" << endl;
		cout << "You will maybe get Cancer" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
	else if (month == 8) {
		cout << "Your sign is Leo" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
	else if (month == 9) {
		cout << "Your sign is Virgo" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
	else if (month == 10) {
		cout << "Your sign is Libra" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
	else if (month == 11) {
		cout << "Your sign is Scorpio" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
	else if (month == 12) {
		cout << "Your sign is Sagittarius" << endl;
		cout << "You will fail like Jamie" << endl;
		cout << "#Palpatine #TheSenate #Order66" << endl;
		return 0;
	}
}

