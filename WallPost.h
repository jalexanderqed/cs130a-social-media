#ifndef __WALLPOST_H__
#define __WALLPOST_H__

#include <string>
#include <ctime>
#include <sstream>

/* Class to hold a single wall post from a user, including the time the post was
 * made, the text it contains, the user who made it, and whether the post has been
 * edited.
*/
class WallPost {
private:
	std::string* post;
	std::string* time;
	int rating;
	bool edited = false;
	std::string* poster;

public:
	// Each wall post is initialized with the text it contains and the time at which
	// it was made. The text of the post can be changed, but the time it was made
	// should not be (setter method is provided because it is required by the project spec).
	WallPost(std::string* p, std::string* t, std::string* po, int r);
	WallPost(std::string* p, std::string* t, std::string* po, int r, bool e);
	// Returns a formatted version of the post with its time and text.
	std::string GetFullPost();
	~WallPost();

	inline std::string GetText() { return *post; }
	inline std::string* GetTime() { return time; }
	inline bool IsEdited() { return edited; }

	// SetText will only be called if the post is changed after it is initialized,
	// in which case "edited" is set to true.
	inline void SetText(std::string* p) { edited = true; post = p; }
	inline void SetTime(std::string* t) { time = t; }
	inline void SetRating(int r) { rating = r; }
	inline void IncrementRating() { rating++; }
	inline int GetRating() { return rating; }
};

#endif
