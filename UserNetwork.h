#ifndef __USER_NETWORK_H__
#define __USER_NETWORK_H__

#include "User.h"
#include "LinkedListNavigator.h"
#include <string>
#include "Util.h"

class UserNetwork {
private:
	LinkedListNavigator<User>* users;

public:
	UserNetwork();
	~UserNetwork();
	bool AddUser(User* u);
	User* RemoveUser(string userName);
	User* GetUser(string userName);
	string GetAllUsers();
	LinkedListNavigator<string>* SearchUsers(string name)
};

#endif
