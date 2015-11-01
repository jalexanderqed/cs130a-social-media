#ifndef __WALL_CPP__
#define __WALL_CPP__

#include "Wall.h"

Wall::Wall(string* u) {
	list = new LinkedListNavigator<WallPost>();
	user = u;
}

Wall::~Wall() {
	list->DeleteList();
	delete list;
}

WallPost* Wall::RemovePost(string contents) {
	WallPost* c;
	list->GoToHead();
	if ((c = list->GetCurrent()) != NULL) {
		do {
			if (c->GetText() == contents) {
				return list->RemoveCurrent()->GetValue();
			}
		} while (list->Next());
	}
	return NULL;
}

string Wall::GetAllPosts() {
	WallPost* c;
	string allPosts = "";
	list->GoToHead();
	if ((c = list->GetCurrent()) != NULL) {
		do {
			allPosts += list->GetCurrent()->GetFullPost();
			allPosts += "\n-----\n";
		} while (list->Next());
	}

	return allPosts;
}

void Wall::RemoveAllPosts() {
	list->GoToHead();
	while (list->GetCurrent() != NULL) {
		delete list->RemoveHead();
		list->GoToHead();
	}
}

bool Wall::ReadPosts(string posts) {
	return false;
}

#endif