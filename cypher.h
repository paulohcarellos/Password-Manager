#pragma once
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Cypher {

	string key_;

public:

	Cypher();
	Cypher(string);
	string password_generate(bool, bool, bool, bool, int);
	string encrypt(string);
	string decrypt(string);
};

