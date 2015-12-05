#ifndef __USER_NETWORK_CPP__
#define __USER_NETWORK_CPP__

#include "UserNetwork.h"

UserNetwork::UserNetwork() {
	users = new HashTable<User>(51);
	//cout << "Capacity of users table at initialization: " << users->Capacity() << endl;
}

UserNetwork::~UserNetwork() {
	if (users != NULL)
		delete users;
}

bool UserNetwork::AddUser(User* u) {
	return users->Add(u->GetUserName(), u);
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

string UserNetwork::GetAllUserNames() {
	ostringstream allUsers;
	users->StartIterator();
	User* u;
	while ((u = users->NextIterator()) != NULL) {
		allUsers << u->GetUserName() << "\n";
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

LinkedListNavigator<string>* UserNetwork::FindPath(string start, string end) {
	User* startU = users->Get(start);
	if (startU == NULL || start == end) return NULL;
	HashTable<UserAndPath>* visited = new HashTable<UserAndPath>(NumUsers());
	LinkedListNavigator<User>* visitQueue = new LinkedListNavigator<User>();
	visitQueue->AddHead(startU);

	UserAndPath* found;
	visited->Add(start, new UserAndPath(startU));

	while ((found = visited->Get(end)) == NULL) {
		if (visitQueue->Length() <= 0) {
			delete visitQueue;
			delete visited;
			return NULL;
		}
		DLinkedListNode<User>* n = visitQueue->RemoveTail();
		User* next = n->GetValue();
		n->SetValue(NULL);
		delete n;
		next->Visit(visitQueue, visited, this);
	}

	LinkedListNavigator<string>* path = found->path;
	found->path = NULL;
	visitQueue->RemoveReferences();
	visitQueue->DeleteList();
	delete visitQueue;
	delete visited;

	path->AddHead(new string(end));
	return path;
}

#endif
