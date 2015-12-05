#ifndef __WALLPOST_CPP__
#define __WALLPOST_CPP__
#include "WallPost.h"

WallPost::WallPost(std::string* p, std::string* t, std::string* po, int r) {
  post = p;
  time = t;
  rating = r;
  poster = po;
  responses = new LinkedListNavigator<WallPost>();
}

WallPost::WallPost(std::string* p, std::string* t, std::string* po, int r, bool e) {
  post = p;
  time = t;
  rating = r;
  edited = e;
  poster = po;
  responses = new LinkedListNavigator<WallPost>();
}

std::string WallPost::GetFullPost() {
  std::ostringstream fullPost;
  fullPost << "\nRating: " << rating;
  fullPost << "\nPosted by: " << *poster;
  fullPost << "\nTime: " << *time;
  fullPost << "\nIs edited: " << (edited ? "true" : "false");
  fullPost << "\nPost:\n";
  fullPost << *post;
  fullPost << "\nResponses:";

  WallPost* c;
  responses->GoToHead();
  if ((c = responses->GetCurrent()) != NULL) {
    do {
      fullPost << responses->GetCurrent()->GetFullPost();
    } while (responses->Next());
  }
  fullPost << "\n-----";
  
  return fullPost.str();
}

WallPost::~WallPost() {
  delete post;
  delete time;
  delete poster;
  responses->DeleteList();
  delete responses;
}

bool WallPost::AddResponse(WallPost* wp){
  WallPost* c;
  responses->GoToHead();
  if ((c = responses->GetCurrent()) != NULL) {
    do {
      if (*(responses->GetCurrent()->GetTime()) == *(wp->GetTime())) {
	return false;
      }
    } while (responses->Next());
  }

  responses->AddTail(wp);
  return true;
}

WallPost* WallPost::RemoveResponseByTime(std::string time){
  WallPost* c;
  responses->GoToHead();
  if ((c = responses->GetCurrent()) != NULL) {
    do {
      if (*(responses->GetCurrent()->GetTime()) == time) {
	DLinkedListNode<WallPost>* n = responses->RemoveCurrent();
	WallPost* wp = n->GetValue();
	n->SetValue(NULL);
	delete n;
	return wp;
      }
    } while (responses->Next());
  }

  return NULL;
}

#endif
