#pragma once

#include <SFML/Graphics.hpp>
#include "definitions.hpp"

namespace sparse {

class PixelFont {
	std::array<PixelCharTemplate, 256> characters;

public:
	explicit PixelFont(const std::string& filepath);
	PixelChar create_char(unsigned char key, sf::Vector2i pos) const;
};

}
