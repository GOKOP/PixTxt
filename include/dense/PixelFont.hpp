#pragma once

#include <array>
#include <string>

namespace pixtxt::dense {

class PixelFont {
public:
	static constexpr int char_height = 5;
	static constexpr int char_width = 3;

	using Char = std::array<bool, char_width * char_height>;

	explicit PixelFont(const std::string& filename);
	const Char& get_char(unsigned char key) const;

private:
	std::array<Char, 256> characters;
};

}
