#ifndef FUIFUNCTIONS
#define FUIFUNCTIONS

#include <vector>

namespace fui {
	template<typename T>
	bool isVectorContainsValue(const std::vector<T>& vec, T value) {
		for (const T& elem : vec) {
			if (elem == value) return true;
		}
		return false;
	}
	template<typename T>
	void addElementToStartOfVector(std::vector<T>* vec, T value) {
		vec->insert(vec->begin(), value);
	}
	template<typename T>
	void removeValueFromVector(std::vector<T>* vec, T value) {
		vec->erase(std::remove(vec->begin(), vec->end(), value), vec->end());
	}
}
#endif