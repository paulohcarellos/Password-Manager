#include "cypher.h"

Cypher::Cypher() {

	key_ = "12345";
}

Cypher::Cypher(string key) {

	key_ = key;
}

string Cypher::password_generate(bool letters, bool numbers, bool uppercase, bool symbols, int size) {

	string sort;
	string password;
	vector<string> characters = { {"0123456789"},{"qwertyuiopasdfghjklzxcvbnm"},{"QWERTYUIOPASDFGHJKLZXCVBNM"},{"!@#$%&*"} };
	
	bool valid = false;

	srand(time(NULL));

	if (numbers)
		sort += "0";

	if (letters)
		sort += "1";

	if (uppercase)
		sort += "2";

	if (symbols)
		sort += "3";

	while (!valid) {

		password.clear();

		bool has_number = false;
		bool has_letter = false;
		bool has_uppercase = false;
		bool has_symbol = false;

		for (int i = 0; i < size; i++) {

			int sorting = rand() % sort.size();
			int type = sort[sorting] - 48;
			
			if (type == 0) {

				password += characters[type][rand() % 10];
				has_number = true;
			}
			
			if (type == 1) {

				password += characters[type][rand() % 26];
				has_letter = true;
			}

			if (type == 2) {

				password += characters[type][rand() % 26];
				has_uppercase = true;
			}

			if (type == 3) {

				password += characters[type][rand() % 7];
				has_symbol = true;
			}
		}

		if (numbers == has_number and letters == has_letter and uppercase == has_uppercase and symbols == has_symbol)
			valid = true;
	}

	return password;
}

string Cypher::encrypt(string plaintext) {

	int it = 0;
	string cyphertext;

	for (char i : plaintext) {

		int x = i + key_[it++];

		if (x < 100)
			cyphertext += '0';

		cyphertext += to_string(x);

		if (it == key_.size())
			it = 0;
	}

	return cyphertext;
}

string Cypher::decrypt(string cyphertext) {

	int it = 0;
	string plaintext;

	for (int i = 0, size = cyphertext.size(); i < size; i += 3) {

		string cell;

		for (int j = i; j < i + 3; j++)
			cell += cyphertext[j];

		char x = stoi(cell);

		plaintext += x - key_[it++];

		if (it == key_.size())
			it = 0;
	}

	return plaintext;
}