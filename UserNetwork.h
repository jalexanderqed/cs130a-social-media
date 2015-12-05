#ifndef __USER_NETWORK_H__
#define __USER_NETWORK_H__

#include "User.h"
#include "LinkedListNavigator.h"
#include <string>
#include "Util.h"

class User;

class UserNetwork {
private:
	HashTable<User>* users;

public:
	UserNetwork();
	~UserNetwork();
	bool AddUser(User* u);
	User* RemoveUser(string userName);
	User* GetUser(string userName);
	string GetAllUsers();
	string GetAllUserNames();
	LinkedListNavigator<string>* SearchUsers(string name);
	LinkedListNavigator<string>* FindPath(string start, string end);
	LinkedListNavigator<string>* FindThreePath(string start);

	int NumUsers() { return users->Size(); }
};

#endif
