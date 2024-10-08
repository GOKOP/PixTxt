#include "SubpixelColumnIterator.hpp"

namespace pixtxt::dense {

SubpixelColumnIterator::value_type SubpixelColumnIterator::operator*() const {
	if(current_column_in_char == -1) { // gap between characters
		return {}; // this zero-initializes the array thus it's all `false`
	}

	auto character = font->get_char(text[current_char]);

	value_type result;
	result.resize(font->get_char_height());
	for(size_t i=0; i < result.size(); ++i) {
		result[i] = character[i * font->get_char_width() + current_column_in_char];
	}

	return result;
}

SubpixelColumnIterator SubpixelColumnIterator::past_the_end(
		const PixelFont* font,
		std::string_view text)
{
	SubpixelColumnIterator iter(font, text);
	iter.current_column_in_char = -1;
	iter.current_char = -1;
	return iter;
}

SubpixelColumnIterator& SubpixelColumnIterator::operator++() {
	++current_column_in_char;
	if(current_column_in_char < font->get_char_width()) return *this;

	current_column_in_char = -1; // gap between characters
	++current_char;
	// shut up the warning about different signs (shhh the cast is fine trust me bro)
	if(static_cast<size_t>(current_char) < text.size()) return *this;

	current_char = -1;
	current_column_in_char = -1;
	return *this;
}

bool operator==(const SubpixelColumnIterator& lhs, const SubpixelColumnIterator& rhs) {
	return lhs.font == rhs.font 
		&& lhs.text == rhs.text
		&& lhs.current_char == rhs.current_char
		&& lhs.current_column_in_char == rhs.current_column_in_char;
}

bool operator!=(const SubpixelColumnIterator& lhs, const SubpixelColumnIterator& rhs) {
	return lhs.current_char != rhs.current_char
		|| lhs.current_column_in_char != rhs.current_column_in_char
		|| lhs.text != rhs.text
		|| lhs.font != rhs.font;
}

}
