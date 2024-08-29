#pragma once

#include <stdexcept>
#include <pixtxt/string_util.hpp>

namespace pixtxt {

/// Exception thrown while parsing invalid PBM files.
class PbmFileError : public std::runtime_error {
public:
	template<typename... Strings>
	explicit PbmFileError(const Strings&... strings):
		std::runtime_error(concat_as_strings(strings...)) {}
};

}
