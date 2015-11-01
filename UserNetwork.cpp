#ifndef __USER_NETWORK_CPP__
#define __USER_NETWORK_CPP__

#include "UserNetwork.h"

UserNetwork::UserNetwork() {
  users = new LinkedListNavigator<User>();
}

UserNetwork::UserNetwork(string in){
  
}

UserNetwork::~UserNetwork() {
  users->DeleteList();
  delete users;
}

bool UserNetwork::AddUser(User* u) {
  User* c;
  if ((c = users->GetCurrent()) != NULL) {
    do {
      if (c->GetUserName() == u->GetUserName()) {
	return false;
      }
    } while (users->Next());
  }
  users->AddTail(u);
  return true;
}

User* UserNetwork::RemoveUser(string userName) {
  User* c;
  if ((c = users->GetCurrent()) != NULL) {
    do {
      if (c->GetUserName() == userName) {
	return users->RemoveCurrent()->GetValue();
      }
    } while (users->Next());
  }
  return NULL;
}

User* UserNetwork::GetUser(string userName) {
  User* c;
  if ((c = users->GetCurrent()) != NULL) {
    do {
      if (c->GetUserName() == userName) {
	return c;
      }
    } while (users->Next());
  }
  return NULL;
}

string UserNetwork::GetAllUsers() {
  User* c;
  string allUsers = "";
  users->GoToHead();
  if ((c = users->GetCurrent()) != NULL) {
    do {     
      allUsers += c->GetFullDescription();
    } while (users->Next());
  }

  return allUsers;
}

#endif
