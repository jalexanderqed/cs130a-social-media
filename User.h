#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <ctime>
#include "Wall.h"

class User {
private:
	Wall* wall;
	string* name;
	string* userName;
	string* password;
	string* city;
	string* country;

public:
	User(string* n, string* un, string* p, string* c, string* co);
	User(string s);
	~User();
	string GetFullDescription();

	inline string GetUserName() { return *userName; }
	inline string GetName() { return *name; }
	inline string GetPassword() { return *password; }
	inline string GetCity() { return *city; }
	inline string GetCountry() { return *country; }
	inline Wall* GetWall() { return wall; }
};

#endif
