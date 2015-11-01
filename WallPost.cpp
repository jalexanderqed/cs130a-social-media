#ifndef __WALLPOST_CPP__
#define __WALLPOST_CPP__
#include "WallPost.h"

WallPost::WallPost(std::string* p, std::string* t, int r) {
  post = p;
  time = t;
  rating = r;
}

std::string WallPost::GetFullPost() {
  std::ostringstream fullPost;
  fullPost << "Rating: " << rating;
  fullPost << "\nTime: " << *time;
  fullPost << "\nPost:\n";
  fullPost << *post;
  return fullPost.str();
}

WallPost::~WallPost() {
  delete post;
  delete time;
}

#endif
