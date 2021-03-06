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

WallPost* Wall::RemovePostByTime(string time) {
	WallPost* c;
	list->GoToHead();
	if ((c = list->GetCurrent()) != NULL) {
		do {
			if (*(list->GetCurrent()->GetTime()) == time) {
				DLinkedListNode<WallPost>* n = list->RemoveCurrent();
				WallPost* wp = n->GetValue();
				n->SetValue(NULL);
				delete n;
				return wp;
			}
		} while (list->Next());
	}
	return NULL;
}

WallPost* Wall::GetPostByTime(string time) {
	WallPost* c;
	list->GoToHead();
	if ((c = list->GetCurrent()) != NULL) {
		do {
			if (*(list->GetCurrent()->GetTime()) == time) {
				return list->GetCurrent();
			}
		} while (list->Next());
	}
	return NULL;
}

bool Wall::AddPost(WallPost* wp) {
	WallPost* c;
	list->GoToHead();
	if ((c = list->GetCurrent()) != NULL) {
		do {
			if (*(list->GetCurrent()->GetTime()) == *(wp->GetTime())) {
				return false;
			}
		} while (list->Next());
	}

	list->AddTail(wp);
	return true;
}

string Wall::GetAllPosts() {
	WallPost* c;
	ostringstream allPosts;
	list->GoToHead();
	if ((c = list->GetCurrent()) != NULL) {
		do {
			allPosts << list->GetCurrent()->GetFullPost();
		} while (list->Next());
	}
	allPosts << '\n';

	return allPosts.str();
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
