#ifndef __WALL_H__
#define __WALL_H__

#include <string>
#include <ctime>
#include "WallPost.h"
#include "LinkedListNavigator.h"

class Wall {
private:
	LinkedListNavigator<WallPost>* list;
	string* user;

public:
	Wall(string* u);
	~Wall();
	WallPost* RemovePostByTime(string time);
	WallPost* GetPostByTime(string time);
	string GetAllPosts();
	bool ReadPosts(string posts);
	void RemoveAllPosts();
	bool AddPost(WallPost* wp);

	inline string* GetUser() { return user; }
	inline void ChangeUser(string* u) { user = u; }
};

#endif
