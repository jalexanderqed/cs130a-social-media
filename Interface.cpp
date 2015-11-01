#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <fstream>

#include "UserNetwork.h"

using namespace std;

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

void addPost(User* u) {
	cout << "Enter text for post:\n";
	string* t = new string(ReadString());
	time_t* tim = new time_t();
	time(tim);
	u->GetWall()->AddPost(new WallPost(t, tim, 0));
}

void loggedIn(User* u) {
	while (true) {
		cout << "\nCommands:" << endl;
		cout << "a: add post to my wall" << endl;
		cout << "p: print my wall" << endl;
		cout << "q: logout" << endl;
		cout << "\nCommand: ";

		string command = ReadString();

		if (command == "a")
			addPost(u);
		else if (command == "p")
			cout << "\n" << u->GetWall()->GetAllPosts() << endl;
		else if (command == "q")
			break;
	}
	cout << endl;
}

void login(UserNetwork* network) {
	cout << "Enter username: ";
	string n = ReadString();
	cout << "Enter password: ";
	string p = ReadString();

	User* u = network->GetUser(n);

	if (u != NULL) {
		if (u->GetPassword() == p) {
			cout << endl;
			loggedIn(u);
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

void add(UserNetwork* network) {
	cout << "Enter user's real name: ";
	string* n = new string(ReadString());
	cout << "Enter username: ";
	string* un = new string(ReadString());
	cout << "Enter password: ";
	string* p = new string(ReadString());
	cout << "Enter user's city: ";
	string* c = new string(ReadString());
	cout << "Enter user's country: ";
	string* co = new string(ReadString());

	bool added = network->AddUser(new User(n, un, p, c, co));

	if (!added)
		cout << "Sorry, a user with that name already exits." << endl;
	cout << endl;
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

bool saveToFile(UserNetwork* network) {
	ofstream myfile;
	myfile.open("data.txt");
	myfile << network->GetAllUsers();
	myfile.close();
	return true;
}

int main(int argc, char** argv) {
	UserNetwork* network = new UserNetwork();

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
			login(network);
		else if (command == "a")
			add(network);
		else if (command == "r")
			remove(network);
		else if (command == "p")
			print(network);
		else if (command == "pu")
			printUser(network);
		else if (command == "q")
			break;
	}

	saveToFile(network);

	cout << "Exiting . . ." << endl;
	return 0;
}
