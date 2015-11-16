#ifndef __WALLPOST_CPP__
#define __WALLPOST_CPP__
#include "WallPost.h"

WallPost::WallPost(std::string* p, std::string* t, std::string* po, int r) {
  post = p;
  time = t;
  rating = r;
  poster = po;
}

WallPost::WallPost(std::string* p, std::string* t, std::string* po, int r, bool e) {
	post = p;
	time = t;
	rating = r;
	edited = e;
	poster = po;
}

std::string WallPost::GetFullPost() {
  std::ostringstream fullPost;
  fullPost << "Rating: " << rating;
  fullPost << "\nPosted by: " << *poster;
  fullPost << "\nTime: " << *time;
  fullPost << "\nIs edited: " << (edited ? "true" : "false");
  fullPost << "\nPost:\n";
  fullPost << *post;
  return fullPost.str();
}

WallPost::~WallPost() {
  delete post;
  delete time;
  delete poster;
}

#endif
