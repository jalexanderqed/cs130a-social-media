#ifndef __WALLPOST_CPP__
#define __WALLPOST_CPP__
#include "WallPost.h"

WallPost::WallPost(std::string* p, time_t* t, int r) {
	post = p;
	time = t;
	rating = r;
}

std::string WallPost::GetFullPost() {
	std::string fullPost = "";
	fullPost += "\nPost:\n";
	fullPost += *post;
	return fullPost;
}

WallPost::~WallPost() {
	delete post;
	delete time;
}

#endif