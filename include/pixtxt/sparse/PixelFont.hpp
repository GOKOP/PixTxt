#pragma once

#include <array>
#include <vector>
#include <string_view>
#include <pixtxt/Color.hpp>

namespace pixtxt::sparse {

class PixelFont {
public:
	// this is defined only for readability purposes
	// any value other than 3 is a lie so don't change it ever
	// and no this code can't be adapted to work with WOLED's RGBW layout
	// the way it works is completely different
	static constexpr int subpixels = 3;

	using PixelCharTemplate = std::vector<Color>;

	explicit PixelFont(int char_height, std::string_view filepath);

	inline const PixelCharTemplate& get_char(unsigned char key) const {
		return characters[key];
	}

private:
	int char_height;
	std::array<PixelCharTemplate, 256> characters;
};

}
