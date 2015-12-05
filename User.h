#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <ctime>
#include "Wall.h"
#include "HashTable.h"
#include "UserNetwork.h"

class User;
class UserNetwork;

struct UserAndPath {
public:
	User* user;
	LinkedListNavigator<string>* path;

	UserAndPath(User* u) {
		user = u;
		path = new LinkedListNavigator<string>();
	}

	~UserAndPath() {
		if (path != NULL) {
			path->DeleteList();
			delete path;
		}
	}
};

class User {
private:
	Wall* wall;
	string* name;
	string* userName;
	string* password;
	string* city;
	string* country;
	HashTable<string>* friends;
	LinkedListNavigator<string>* pending;

public:
	User(string* n, string* un, string* p, string* c, string* co);
	~User();
	string GetFullDescription();
	bool AddFriend(std::string* name);
	bool AddPending(std::string* name);
	bool RemoveFriend(std::string name);
	bool RemovePending(std::string name);
	bool HasFriend(std::string name);
	bool HasPending(std::string name);
	void Visit(LinkedListNavigator<User>* visitQueue, HashTable<UserAndPath>* visited, UserNetwork* network);

	inline string GetUserName() { return *userName; }
	inline string GetName() { return *name; }
	inline string GetPassword() { return *password; }
	inline string GetCity() { return *city; }
	inline string GetCountry() { return *country; }
	inline Wall* GetWall() { return wall; }
	inline HashTable<string>* GetFriends(){ return friends; }
	inline LinkedListNavigator<string>* GetPending(){ return pending; }
};

#endif
