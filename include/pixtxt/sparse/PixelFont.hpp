#pragma once

#include <array>
#include <string_view>
#include <pixtxt/Color.hpp>

namespace pixtxt::sparse {

class PixelFont {
public:
	static constexpr int char_height = 5;

	// this is defined only for readability purposes
	// any value other than 3 is a lie so don't change it ever
	// and no this code can't be adapted to work with WOLED's RGBW layout
	// the way it works is completely different
	static constexpr int subpixels = 3;

	using PixelCharTemplate = std::array<Color, char_height>;

	explicit PixelFont(std::string_view filepath);

	inline const PixelCharTemplate& get_char(unsigned char key) const {
		return characters[key];
	}

private:
	std::array<PixelCharTemplate, 256> characters;
};

}
