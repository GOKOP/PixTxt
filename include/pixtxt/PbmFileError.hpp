#pragma once

#include <stdexcept>
#include <pixtxt/string_util.hpp>

namespace pixtxt {

class PbmFileError : public std::runtime_error {
public:
	template<typename... Strings>
	explicit PbmFileError(const Strings&... strings):
		std::runtime_error(concat_as_strings(strings...)) {}
};

}
