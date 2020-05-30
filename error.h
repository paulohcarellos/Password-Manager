#pragma once
#include <string>

using namespace std;

class Error {

	string msg_;

public:

	Error(string msg) : msg_(msg) {}
	string message() { return msg_; }
};