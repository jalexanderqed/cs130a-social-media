#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include <locale>

using namespace std;

inline string LowerString(string str) {
	const char* cStr = str.c_str();
	char* ret = new char[str.length() + 1];
	ret[str.length()] = '\0';
	for (int i = 0; i < str.length; i++) {
		ret[i] = tolower(cStr[i]);
	}

	return string(ret);
}

#endif