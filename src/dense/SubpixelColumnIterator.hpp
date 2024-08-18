#pragma once

#include <string_view>
#include <array>
#include <pixtxt/dense/PixelFont.hpp>

namespace pixtxt::dense {

class SubpixelColumnIterator {
	const PixelFont* font;
	std::string_view text;

	int current_char = 0;
	int current_column_in_char = 0;

public:

	inline SubpixelColumnIterator(const PixelFont* font, std::string_view text):
		font(font), text(text) {}

	// pseudoconstructor
	static SubpixelColumnIterator past_the_end(const PixelFont* font, std::string_view text);

	friend bool operator==(const SubpixelColumnIterator& lhs, const SubpixelColumnIterator& rhs);

	// iterator stuff
	
	using difference_type = std::ptrdiff_t;
	using value_type = std::array<bool, PixelFont::char_height>;

	value_type operator*() const;
	SubpixelColumnIterator& operator++();
	inline void operator++(int) { ++*this; }

};

static_assert(std::input_iterator<SubpixelColumnIterator>);

}
