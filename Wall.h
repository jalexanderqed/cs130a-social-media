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
	WallPost* RemovePost(string contents);
	string GetAllPosts();
	bool ReadPosts(string posts);
	void RemoveAllPosts();

	inline string* GetUser() { return user; }
	inline void ChangeUser(string* u) { user = u; }
	inline void AddPost(WallPost* wp) { list->AddTail(wp); }
};

#endif