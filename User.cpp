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
	friends = new HashTable<string>(51);
	pending = new LinkedListNavigator<string>();
}

User::~User() {
	delete name;
	delete userName;
	delete password;
	delete city;
	delete country;
	delete wall;

	delete friends;
	pending->DeleteList();
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
	friends->StartIterator();
	string* u;
	while ((u = friends->NextIterator()) != NULL) {
		str << "\nUsername: " << *u;
	}

	str << "\nPending requests:";
	pending->GoToHead();
	if (pending->GetCurrent() != NULL) {
		do {
			str << "\nUsername: " << *(pending->GetCurrent());
		} while (pending->Next());
	}

	str << "\nWall:";
	str << wall->GetAllPosts();

	return str.str();
}

bool User::AddFriend(std::string* name) {
	return friends->Add(*name, name);
}

bool User::AddPending(std::string* name) {
	pending->GoToHead();

	if (HasPending(*name)) return false;

	pending->AddTail(name);
	return true;
}

bool User::RemoveFriend(std::string name) {
	return friends->Remove(name) != NULL;
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
	return friends->Get(name) != NULL;
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

void User::Visit(LinkedListNavigator<User>* visitQueue, HashTable<UserAndPath>* visited, UserNetwork* network) {
	UserAndPath* me = visited->Get(GetUserName());

	LinkedListNavigator<string>* pathToMe = me->path;
	
	friends->StartIterator();
	string* f;
	while ((f = friends->NextIterator()) != NULL) {
		if (visited->Get(*f) == NULL) {
			User* friendUser = network->GetUser(*f);
			UserAndPath* friendAndPath = new UserAndPath(friendUser);
			LinkedListNavigator<string>* pathForFriend = friendAndPath->path;
			pathToMe->GoToTail();
			if (pathToMe->GetCurrent() != NULL) {
				do {
					pathForFriend->AddHead(new string(*(pathToMe->GetCurrent())));
				} while (pathToMe->Prev());
			}
			pathForFriend->AddHead(new string(GetUserName()));

			visited->Add(*f, friendAndPath);
			visitQueue->AddHead(friendUser);
		}
	}
}

#endif
