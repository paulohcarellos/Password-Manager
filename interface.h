#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "cypher.h"
#include "error.h"

using namespace std;

class Interface {

	string password_;
	Cypher cypher_pass_;
	Cypher cypher_names_;

public:

	Interface(string, string, string);
	void start();
	void mainmenu();
	void generate_password();
	void save_password(string);
	void load_password();
	void remove_password();
	bool answer_check(string);
};

