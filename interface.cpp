#include "interface.h"

#define CLEAR system("cls")
#define PAUSE cin.ignore();cin.get()

Interface::Interface(string pass, string key1, string key2) {

	password_ = pass;
	cypher_pass_ = Cypher(key1);
	cypher_names_ = Cypher(key2);
}

void Interface::start() {

	string pass;

	CLEAR;
	cout << endl;
	cout << " Password: ";
	cin >> pass;

	if (pass == password_)
		mainmenu();
}

void Interface::mainmenu() {

	string option;

	CLEAR;
	cout << endl;
	cout << " Password manager" << endl;
	cout << endl;
	cout << "  01 - Generate" << endl;
	cout << "  02 - Check" << endl;
	cout << "  03 - Remove" << endl;
	cout << endl;
	cout << "  Option: ";
	cin >> option;

	if (stoi(option) == 1) {

		generate_password();
	}

	else if (stoi(option) == 2) {

		load_password();
	}

	else if (stoi(option) == 3) {

		remove_password();
	}

	else {

		mainmenu();
	}
}

void Interface::generate_password() {

	int size;
	bool letters;
	bool numbers;
	bool uppercase;
	bool symbols;
	bool confirmatiom;

	string buffer;
	string password;

	CLEAR;
	cout << endl;
	cout << " Password Cypher" << endl;
	cout << endl;
	cout << "  Insert password size: ";
	cin >> buffer;

	try {

		size = stoi(buffer);
	}

	catch (invalid_argument) {

		cout << "  INVALID NUMBER" << endl;
		PAUSE;

		generate_password();
	}

	try {

		cout << endl;
		cout << "  Describe password (y/n)" << endl;
		cout << "   Letters: ";
		cin >> buffer;

		letters = answer_check(buffer);

		cout << "   Numbers: ";
		cin >> buffer;

		numbers = answer_check(buffer);

		cout << "   Uppercase: ";
		cin >> buffer;

		uppercase = answer_check(buffer);

		cout << "   Symbols: ";
		cin >> buffer;

		symbols = answer_check(buffer);
	}

	catch (Error) {

		cout << "  Invalid answer" << endl;
		PAUSE;

		generate_password();
	}

	if (letters == numbers and numbers == uppercase and uppercase == symbols and symbols == false) {

		cout << endl;
		cout << " Mission impossible!" << endl;

		PAUSE;
		generate_password();
	}

	else {

		password = cypher_pass_.password_generate(letters, numbers, uppercase, symbols, size);

		cout << endl;
		cout << "  Password: " << password << endl;
		cout << "  Confirm? ";
		cin >> buffer;

		try {

			if (answer_check(buffer))
				save_password(password);

			else
				generate_password();
		}

		catch (Error) {

			cout << "  Invalid answer" << endl;
			PAUSE;

			generate_password();
		}
	}
}

void Interface::save_password(string pass) {

	string name;
	string ans;

	ofstream out;
	out.open("data.dat", ios::app);

	CLEAR;
	cout << endl;
	cout << " Save password" << endl;
	cout << endl;
	cout << "  Insert name: ";
	cin.ignore();
	getline(cin, name);
	cout << "  Password: " << pass << endl;
	cout << "  Confirm? ";
	cin >> ans;

	try {

		if (answer_check(ans)) {

			out << cypher_names_.encrypt(name) << " " << cypher_pass_.encrypt(pass) << "\n";
			out.close();
			mainmenu();
		}

		else {

			out.close();
			save_password(pass);
		}
	}

	catch (Error) {

		cout << "  Invalid answer" << endl;
		PAUSE;

		save_password(pass);
	}
}

void Interface::load_password() {

	string line;

	ifstream in;
	in.open("data.dat");

	CLEAR;
	cout << endl;
	cout << " Passwords" << endl;
	cout << endl;

	in >> line;

	while (in) {

		cout << "  " << cypher_names_.decrypt(line);

		in >> line;

		cout << " - " << cypher_pass_.decrypt(line) << endl;

		in >> line;
	}

	in.close();

	PAUSE;
	mainmenu();
}

void Interface::remove_password() {

	int it = 1;
	int x;
	string line;
	string buffer;
	fstream editing;
	ofstream copy;

	editing.open("data.dat");
	copy.open("copy.dat");

	CLEAR;
	cout << endl;
	cout << " Remove password" << endl;
	cout << endl;

	editing >> line;

	while (editing) {

		cout << "  " << it++ << " - " << cypher_names_.decrypt(line);

		editing >> line;

		cout << " - " << cypher_pass_.decrypt(line) << endl;

		editing >> line;
	}

	cout << endl;
	cout << "  Select password to remove: ";
	cin >> buffer;

	x = stoi(buffer);

	if (x > 0 and x <= it) {

		editing.clear();
		editing.seekg(0, ios::beg);

		for (int i = 0; i < it; i++) {

			if (i != x - 1) {

				getline(editing, line);
				copy << line << "\n";
			}

			else
				getline(editing, line);
		}

		editing.close();
		copy.close();

		remove("data.dat");
		rename("copy.dat", "data.dat");
	}

	PAUSE;
	mainmenu();
}

bool Interface::answer_check(string str) {

	if (str == "y" || str == "Y")
		return true;

	else if (str == "n" || str == "N")
		return false;

	else
		throw Error("Invalid answer");
}
