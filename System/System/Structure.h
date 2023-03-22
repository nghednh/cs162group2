#pragma once
#include <string>
using namespace std;
struct Staff {
	string name;
	string username;
	string password;
	Staff* staffNext;
};
