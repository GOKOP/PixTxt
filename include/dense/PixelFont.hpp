#pragma once

#include <array>
#include <string_view>

namespace pixtxt::dense {

class PixelFont {
public:
	static constexpr int char_height = 5;
	static constexpr int char_width = 3;

	using Char = std::array<bool, char_width * char_height>;

	explicit PixelFont(std::string_view filename);
	const Char& get_char(unsigned char key) const;

private:
	std::array<Char, 256> characters;
};

}
