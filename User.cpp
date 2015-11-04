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
	friends = new LinkedListNavigator<string>();
	pending = new LinkedListNavigator<string>();
}

User::~User() {
	delete name;
	delete userName;
	delete password;
	delete city;
	delete country;
	delete wall;

	friends->DeleteList();
	pending->DeleteList();
	delete friends;
	delete pending;
}

string User::GetFullDescription() {
	ostringstream str;
	str << "Name: ";
	str << *name;
	str << "\nUsername: ";
	str << *userName;
	str << "\nPassword: ";
	str << *password;
	str << "\nCity: ";
	str << *city;
	str << "\nCountry: ";
	str << *country;

	str << "\nFriends:";
	friends->GoToHead();
	if (friends->GetCurrent() != NULL) {
		do {
			str << "\nUsername: " << *(friends->GetCurrent());
		} while (friends->Next());
	}

	str << "\nPending requests:";
	pending->GoToHead();
	if (pending->GetCurrent() != NULL) {
		do {
			str << "\nUsername: " << *(pending->GetCurrent());
		} while (pending->Next());
	}

	str << "\nWall:\n";
	str << wall->GetAllPosts();

	return str.str();
}

bool User::AddFriend(std::string* name) {
	friends->GoToHead();

	if (HasFriend(*name)) return false;

	friends->AddTail(name);
	return true;
}

bool User::AddPending(std::string* name) {
	pending->GoToHead();

	if (HasPending(*name)) return false;

	pending->AddTail(name);
	return true;
}

bool User::RemoveFriend(std::string name) {
	friends->GoToHead();

	if (friends->GetCurrent() != NULL) {
		do {
			if (*(friends->GetCurrent()) == name) {
				delete friends->RemoveCurrent();
				return true;
			}
		} while (friends->Next());
	}

	return false;
}

bool User::RemovePending(std::string name) {
	pending->GoToHead();

	if (pending->GetCurrent() != NULL) {
		do {
			if (*(pending->GetCurrent()) == name) {
				delete pending->RemoveCurrent();
				return true;
			}
		} while (pending->Next());
	}

	return false;
}

bool User::HasFriend(std::string name) {
	friends->GoToHead();

	if (friends->GetCurrent() != NULL) {
		do {
			if (*(friends->GetCurrent()) == name) {
				return true;
			}
		} while (friends->Next());
	}

	return false;
}

bool User::HasPending(std::string name) {
	pending->GoToHead();

	if (pending->GetCurrent() != NULL) {
		do {
			if (*(pending->GetCurrent()) == name) {
				return true;
			}
		} while (pending->Next());
	}

	return false;
}

#endif
