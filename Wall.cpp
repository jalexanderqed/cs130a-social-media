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
      if (*(c->GetTime()) == time) {
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

bool AddPost(WallPost* wp){
  WallPost* c;
  list->GoToHead();
  if ((c = list->GetCurrent()) != NULL) {
    do {
      if (*(c->GetTime()) == *(wp->GetTime())) {
	return false;
      }
    } while (list->Next());
  }

  list->AddTail(wp);
  return true;
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
