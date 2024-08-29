#pragma once

#include <stdexcept>
#include <pixtxt/string_util.hpp>

namespace pixtxt {

/// Exception thrown for issues while generating sparse or dense PixelFont from an image.
class PixelFontError: public std::runtime_error {
public:
	template<typename... Strings>
	explicit PixelFontError(const Strings&... strings):
		std::runtime_error(concat_as_strings(strings...)) {}

};

}
