#ifndef __USER_NETWORK_CPP__
#define __USER_NETWORK_CPP__

#include "UserNetwork.h"

UserNetwork::UserNetwork() {
	users = new LinkedListNavigator<User>();
}

UserNetwork::~UserNetwork() {
	users->DeleteList();
	delete users;
}

bool UserNetwork::AddUser(User* u) {
	users->GoToHead();
	if ((users->GetCurrent()) != NULL) {
		do {
			if (users->GetCurrent()->GetUserName() == u->GetUserName()) {
				return false;
			}
		} while (users->Next());
	}
	users->AddTail(u);
	return true;
}

User* UserNetwork::RemoveUser(string userName) {
	users->GoToHead();
	if ((users->GetCurrent()) != NULL) {
		do {
			users->GetCurrent()->RemoveFriend(userName);
			users->GetCurrent()->RemovePending(userName);
		} while (users->Next());
	}

	users->GoToHead();
	if ((users->GetCurrent()) != NULL) {
		do {
			if (users->GetCurrent()->GetUserName() == userName) {
				return users->RemoveCurrent()->GetValue();
			}
		} while (users->Next());
	}
	return NULL;
}

User* UserNetwork::GetUser(string userName) {
	users->GoToHead();
	if ((users->GetCurrent()) != NULL) {
		do {
			if (users->GetCurrent()->GetUserName() == userName) {
				return users->GetCurrent();
			}
		} while (users->Next());
	}
	return NULL;
}

string UserNetwork::GetAllUsers() {
	string allUsers = "";
	users->GoToHead();
	if ((users->GetCurrent()) != NULL) {
		do {
			allUsers += users->GetCurrent()->GetFullDescription();
		} while (users->Next());
	}

	return allUsers;
}

LinkedListNavigator<string>* UserNetwork::SearchUsers(string name) {
	string searchLower = LowerString(name);
	LinkedListNavigator<string>* ret = new LinkedListNavigator<string>();
	users->GoToHead();
	if ((users->GetCurrent()) != NULL) {
		do {
			if (LowerString(users->GetCurrent()->GetUserName()).find(searchLower) != string::npos) {
				ret->AddTail(new string(users->GetCurrent()->GetUserName()));
			}
		} while (users->Next());
	}

	return ret;
}

#endif
