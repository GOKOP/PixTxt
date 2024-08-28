#pragma once

#include <sstream>

namespace pixtxt {

template<typename... Strings>
std::string concat_as_strings(const Strings&... strings) {
	std::ostringstream ss;
	((ss << strings),...);

	return ss.str();
}
}
