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
	template<typename T>
	void addTwoVectors(std::vector<T>& vec1, std::vector<T>& vec2) {
		for (T val : vec2)
			vec1.push_back(val);
	}
	template<typename T>
	void subtractTwoVectors(std::vector<T>& vec1, std::vector<T>& vec2) {
		vec1.erase(std::remove_if(vec1.begin(), vec1.end(),
			[&vec2](const T& val) {
				return std::find(vec2.begin(), vec2.end(), val) != vec2.end();
			}),
			vec1.end());
	}
	inline int mapNegOneOneToZeroOne(int val) {
		return (val + 1.0) / 2.0;
	}
}
#endif