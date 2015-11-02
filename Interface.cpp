#ifndef __INTERFACE_CPP__
#define __INTERFACE_CPP__

#include "Interface.h"

using namespace std;

bool saveToFile(UserNetwork* network, string fileName) {
  ofstream myfile;
  myfile.open(fileName);
  myfile << network->GetAllUsers();
  myfile.close();
  return true;
}

bool IsLegal(string str) {
  return str != "";
}

int ReadInt() {
  string input = "";
  getline(cin, input);
  return atoi(input.c_str());
}

string ReadString() {
  string input = "";
  getline(cin, input);
  return input;
}

string* GetSafeString(string type) {
  string* t = new string(ReadString());
  while (!IsLegal(*t)) {
    cout << "That is not a legal " << type << ". Please reenter:" << endl;
    delete t;
    t = new string(ReadString());
  }
  return t;
}

void AddPost(User* u) {
  cout << "Enter text for post:\n";
  string* t = GetSafeString("post");

  time_t now = time(NULL);
  tm * ptm = localtime(&now);
  char buffer[50];
  strftime(buffer, 50, "%d-%m-%Y %I:%M:%S", ptm);

  u->GetWall()->AddPost(new WallPost(t, new string(buffer), 0));
}

void SearchForUser(UserNetwork* n) {
  cout << "Enter user search string: ";
  string* t = GetSafeString("search string");

  LinkedListNavigator<string>* results = n->SearchUsers(*t);

  results->GoToHead();
  if (results->GetCurrent() != NULL) {
    cout << "Results:" << endl;
    do {
      cout << "Username: " << *(results->GetCurrent()) << endl;
    } while (results->Next());
  }
  else {
    cout << "No users found." << endl;
  }

  delete t;
  delete results;
}

void AddFriend(User* u, UserNetwork* n) {
  cout << "Enter username of user to add: ";
  User* target = n->GetUser(ReadString());
  if (target != NULL && target->GetName() != u->GetName()) {
    if (target->AddPending(new string(u->GetUserName()))) {
      cout << "Sent request to user " << target->GetUserName() << endl;
    }
    else {
      cout << "Sorry, it looks like you're already friends." << endl;
    }
  }
  else {
    cout << "Sorry, I couldn't find that user." << endl;
  }
  cout << endl;
}

void PrintPending(User* u) {
  cout << "\nPending requests:";
  LinkedListNavigator<string>* pending = u->GetPending();
  pending->GoToHead();
  if (pending->GetCurrent() != NULL) {
    do {
      cout << "\nUsername: " << *(pending->GetCurrent());
    } while (pending->Next());
  }
  cout << endl;
}

void PrintFriends(User* u) {
  cout << "\nMy friends:";
  LinkedListNavigator<string>* friends = u->GetFriends();
  friends->GoToHead();
  if (friends->GetCurrent() != NULL) {
    do {
      cout << "\nUsername: " << *(friends->GetCurrent());
    } while (friends->Next());
  }
  cout << endl;
}

void AcceptPending(User* u, UserNetwork* n) {
  cout << "Enter username of user to add as a friend: ";
  User* target = n->GetUser(ReadString());
  if (target != NULL && u->HasPending(target->GetUserName()) && !u->HasFriend(target->GetUserName())) {
    target->AddFriend(new string(u->GetUserName()));
    u->AddFriend(new string(target->GetUserName()));
    u->RemovePending(target->GetUserName());
    cout << "Successfully added friend " << target->GetUserName() << endl;
  }
  else {
    cout << "Sorry, I couldn't find that user." << endl;
  }
  cout << endl;
}

void RemoveFriend(User* u, UserNetwork* n) {
  cout << "Enter username of friend to remove: ";
  User* target = n->GetUser(ReadString());
  if (target != NULL && u->HasFriend(target->GetUserName())) {
    u->RemoveFriend(target->GetUserName());
    target->RemoveFriend(u->GetUserName());
    cout << "Successfully removed friend " << target->GetUserName() << endl;
  }
  else {
    cout << "Sorry, I couldn't find that user." << endl;
  }
  cout << endl;
}

bool DeleteProfile(User* u, UserNetwork* n) {
  cout << "Are you sure you want to delete your profile permanently? (y/n)" << endl;
  if (ReadString() == "y") {
    cout << "Deleting profile." << endl;
    User* rem = n->RemoveUser(u->GetUserName());
    if (rem != NULL) delete rem;
    return true;
  }
  return false;
}

void RemovePost(User* u) {
  cout << "Enter time of post to remove, as printed with command 'p': ";
  WallPost* target = u->GetWall()->RemovePostByTime(ReadString());
  if (target != NULL) {
    delete target;
    cout << "Removed wall post." << endl;
  }
  else {
    cout << "Sorry, I couldn't find that post." << endl;
  }
}

void LoggedIn(User* u, UserNetwork* n) {
  while (true) {
    cout << "\nCommands:" << endl;
    cout << "a: add post to my wall" << endl;
    cout << "p: print my wall" << endl;
    cout << "s: search for users" << endl;
    cout << "f: send friend request" << endl;
    cout << "pp: print my pending friend requests" << endl;
    cout << "pf: print my list of friends" << endl;
    cout << "af: accept pending friend request" << endl;
    cout << "rf: remove friend" << endl;
    cout << "dm: delete my profile" << endl;
    cout << "rp: remove a wall post" << endl;
    cout << "q: logout" << endl;
    cout << "\nCommand: ";

    string command = ReadString();

    if (command == "a")
      AddPost(u);
    else if (command == "p")
      cout << "\n" << u->GetWall()->GetAllPosts() << endl;
    else if (command == "f")
      AddFriend(u, n);
    else if (command == "s")
      SearchForUser(n);
    else if (command == "pp")
      PrintPending(u);
    else if (command == "pf")
      PrintFriends(u);
    else if (command == "af")
      AcceptPending(u, n);
    else if (command == "rf")
      RemoveFriend(u, n);
    else if (command == "rp")
      RemovePost(u);
    else if (command == "dm") {
      if (DeleteProfile(u, n)) break;
    }
    else if (command == "q")
      break;
  }

  saveToFile(n, "data.txt");
  cout << endl;
}

void Login(UserNetwork* network) {
  cout << "Enter username: ";
  string n = ReadString();
  cout << "Enter password: ";
  string p = ReadString();

  User* u = network->GetUser(n);

  if (u != NULL) {
    if (u->GetPassword() == p) {
      cout << endl;
      LoggedIn(u, network);
    }
    else {
      cout << "\nSorry, wrong password." << endl;
    }
  }
  else {
    cout << "\nSorry, I couldn't find that user." << endl;
  }
  cout << endl;
}

void addUser(UserNetwork* network) {
  cout << "Enter user's real name: ";
  string* n = GetSafeString("name");

  cout << "Enter username: ";
  string* un = GetSafeString("username");

  cout << "Enter password: ";
  string* p = GetSafeString("password");

  cout << "Enter user's city: ";
  string* c = GetSafeString("city");

  cout << "Enter user's country: ";
  string* co = GetSafeString("country");

  User* user = new User(n, un, p, c, co);
  bool added = network->AddUser(user);

  if (!added) {
    cout << "Sorry, a user with that name already exits." << endl;
    delete user;
  }
}

void remove(UserNetwork* network) {
  cout << "Enter username of user to remove: ";
  User* u = network->RemoveUser(ReadString());
  if (u != NULL) {
    cout << "Removed user " + u->GetName() << endl;
    delete u;
  }
  else {
    cout << "Sorry, I couldn't find that user." << endl;
  }
  cout << endl;
}

void print(UserNetwork* network) {
  cout << network->GetAllUsers() << endl << endl;
}

void printUser(UserNetwork* network) {
  cout << "Enter username of user to print: ";
  User* u = network->GetUser(ReadString());
  if (u != NULL) {
    cout << "\n" << u->GetFullDescription() << endl;
  }
  else {
    cout << "Sorry, I couldn't find that user." << endl;
  }
  cout << endl;
}

WallPost* WallPostFromString(string &in) {
  string post;
  string time;
  int rating;
  bool edited;

  if (in.find("Rating: ") != 0) {
    return NULL;
  }
  rating = atoi(in.substr(8, in.find('\n') - 8).c_str());
  in = in.substr(in.find('\n') + 1);

  if (in.find("Time: ") != 0) {
    return NULL;
  }
  time = in.substr(6, in.find('\n') - 6).c_str();
  in = in.substr(in.find('\n') + 1);

  if (in.find("Is edited: ") != 0) {
    return NULL;
  }
  string ed = in.substr(11, in.find('\n') - 11).c_str();
  edited = ed == "true";
  in = in.substr(in.find('\n') + 1);

  if (in.find("Post:") != 0) {
    return NULL;
  }
  in = in.substr(in.find('\n') + 1);

  post = in.substr(0, in.find('\n'));
  in = in.substr(in.find('\n') + 1);

  if (in.find("-----") != 0) {
    return NULL;
  }
  in = in.substr(in.find('\n') + 1);

  return new WallPost(new string(post), new string(time), rating, edited);
}

User* UserFromString(string &in) {
  string name;
  string userName;
  string password;
  string city;
  string country;

  if (in.find("Name: ") != 0) {
    return NULL;
  }
  name = in.substr(6, in.find('\n') - 6);
  in = in.substr(in.find('\n') + 1);

  if (in.find("Username: ") != 0) {
    return NULL;
  }
  userName = in.substr(10, in.find('\n') - 10);
  in = in.substr(in.find('\n') + 1);

  if (in.find("Password: ") != 0) {
    return NULL;
  }
  password = in.substr(10, in.find('\n') - 10);
  in = in.substr(in.find('\n') + 1);

  if (in.find("City: ") != 0) {
    return NULL;
  }
  city = in.substr(6, in.find('\n') - 6);
  in = in.substr(in.find('\n') + 1);

  if (in.find("Country: ") != 0) {
    return NULL;
  }
  country = in.substr(9, in.find('\n') - 9);
  in = in.substr(in.find('\n') + 1);

  User* u = new User(new string(name), new string(userName), new string(password), new string(city), new string(country));

  if (in.find("Friends:") != 0) {
    delete u;
    return NULL;
  }
  in = in.substr(in.find('\n') + 1);
  while (in.find("Username: ") == 0) {
    u->AddFriend(new string(in.substr(10, in.find('\n') - 10)));
    in = in.substr(in.find('\n') + 1);
  }

  if (in.find("Pending requests:") != 0) {
    delete u;
    return NULL;
  }
  in = in.substr(in.find('\n') + 1);
  while (in.find("Username: ") == 0) {
    u->AddPending(new string(in.substr(10, in.find('\n') - 10)));
    in = in.substr(in.find('\n') + 1);
  }

  if (in.find("Wall:") != 0) {
    delete u;
    return NULL;
  }
  in = in.substr(in.find('\n') + 1);

  WallPost* wp;
  while ((wp = WallPostFromString(in)) != NULL) {
    u->GetWall()->AddPost(wp);
  }

  return u;
}

UserNetwork* UserNetworkFromString(string in) {
  UserNetwork* users = new UserNetwork();
  User* u;
  while ((u = UserFromString(in)) != NULL) {
    users->AddUser(u);
  }
  return users;
}

UserNetwork* ReadFromFile(string fileName) {
  string line;
  ostringstream s;
  ifstream myfile(fileName);
  if (myfile.is_open())
    {
      while (getline(myfile, line))
	{
	  s << line << '\n';
	}
      myfile.close();
    }
  string inString = s.str();
  return UserNetworkFromString(inString);
}

int RunInterface() {
  UserNetwork* network = ReadFromFile("data.txt");
  if (network->NumUsers() == 0) {
    cout << "Could not read any users from file." << endl;
  }

  while (true) {
    cout << "\nCommands:" << endl;
    cout << "l: login" << endl;
    cout << "a: add user" << endl;
    cout << "r: remove user" << endl;
    cout << "p: print users" << endl;
    cout << "pu: print user" << endl;
    cout << "q: quit" << endl;
    cout << "\nCommand: ";

    string command = ReadString();

    if (command == "l")
      Login(network);
    else if (command == "a")
      addUser(network);
    else if (command == "r")
      remove(network);
    else if (command == "p")
      print(network);
    else if (command == "pu")
      printUser(network);
    else if (command == "q")
      break;
  }

  saveToFile(network, "data.txt");

  cout << "Exiting . . ." << endl;
  return 0;
}

#endif
