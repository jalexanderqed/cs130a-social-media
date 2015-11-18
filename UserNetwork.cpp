#ifndef __USER_NETWORK_CPP__
#define __USER_NETWORK_CPP__

#include "UserNetwork.h"

UserNetwork::UserNetwork() {
	users = new HashTable<User>(51);
}

UserNetwork::~UserNetwork() {
	delete users;
	delete users;
}

bool UserNetwork::AddUser(User* u) {
	return users->Add(u->GetName(), u);
}

User* UserNetwork::RemoveUser(string userName) {
	users->StartIterator();
	User* u;
	while ((u = users->NextIterator()) != NULL) {
		u->RemoveFriend(userName);
		u->RemovePending(userName);
	}

	return users->Remove(userName);
}

User* UserNetwork::GetUser(string userName) {
	return users->Get(userName);
}

string UserNetwork::GetAllUsers() {
	ostringstream allUsers;
	users->StartIterator();
	User* u;
	while ((u = users->NextIterator()) != NULL) {
		allUsers << u->GetFullDescription();
	}

	return allUsers.str();
}

LinkedListNavigator<string>* UserNetwork::SearchUsers(string name) {
	string searchLower = LowerString(name);
	LinkedListNavigator<string>* ret = new LinkedListNavigator<string>();

	users->StartIterator();
	User* u;
	while ((u = users->NextIterator()) != NULL) {
		if (LowerString(u->GetUserName()).find(searchLower) != string::npos) {
			ret->AddTail(new string(u->GetUserName()));
		}
	}

	return ret;
}

#endif
