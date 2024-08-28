#pragma once

#include <array>
#include <vector>
#include <string_view>

namespace pixtxt::dense {

class PixelFont {
public:
	using Char = std::vector<bool>;

	explicit PixelFont(int char_width, int char_height, std::string_view filename);

	const Char& get_char(unsigned char key) const;
	inline int get_char_width() const { return char_width; }
	inline int get_char_height() const { return char_height; }

private:
	int char_width;
	int char_height;
	std::array<Char, 256> characters;
};

}
