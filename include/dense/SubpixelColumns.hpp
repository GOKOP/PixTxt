#pragma once

#include <dense/SubpixelColumnIterator.hpp>

namespace pixtxt::dense {

// class to iterate over subpixels columns in the text according to the font
// not much here, all the magic happens in SubpixelColumnIterator

class SubpixelColumns {
	const PixelFont* font;
	std::string_view text;

public:

	inline SubpixelColumns(const PixelFont* font, std::string_view text):
		font(font), text(text) {}

	inline SubpixelColumnIterator begin() const {
		return SubpixelColumnIterator(font, text);
	}

	inline SubpixelColumnIterator end() const {
		return SubpixelColumnIterator::past_the_end(font, text);
	}
};

}
