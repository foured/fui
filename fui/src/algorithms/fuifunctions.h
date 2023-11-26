#ifndef FUIFUNCTIONS
#define FUIFUNCTIONS

#include <vector>

namespace fui {
	class fuifunctions
	{
	public:
		template<typename T>
		static bool isVectorContainsValue(std::vector<T> vec, T value);
	};
}
#endif