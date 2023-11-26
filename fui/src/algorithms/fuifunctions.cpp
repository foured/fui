#include "fuifunctions.h"

template<typename T>
bool fui::fuifunctions::isVectorContainsValue(std::vector<T> vec, T value) {
	for (unsigned int i = 0, s = vec.size(); i < s; i++) {
		if (vec[i] == T) return true;
	}
	return false;
}