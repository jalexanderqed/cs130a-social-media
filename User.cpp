#ifndef __USER_CPP__
#define __USER_CPP__

#include "User.h"

User::User(string* n, string* un, string* p, string* c, string* co) {
	name = n;
	userName = un;
	password = p;
	city = c;
	country = co;
	wall = new Wall(un);
}

User::~User() {
	delete name;
	delete userName;
	delete password;
	delete city;
	delete country;
	delete wall;
}

string User::GetFullDescription() {
	string str = "";
	str += "Name: ";
	str += *name;
	str += "\nUsername: ";
	str += *userName;
	str += "\nPassword: ";
	str += *password;
	str += "\nCity: ";
	str += *city;
	str += "\nCountry: ";
	str += *country;
	str += "\nWall:\n";
	str += wall->GetAllPosts();

	return str;
}

#endif
