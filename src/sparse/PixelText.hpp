#pragma once

#include "PixelFont.hpp"
#include <vector>

namespace sparse {

class PixelText: public sf::Drawable {
public:
	using PixelChar = std::array<sf::Vertex, PixelFont::char_height>;

	explicit PixelText(const PixelFont& font, std::string_view text, sf::Vector2i pos);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<PixelChar> text;

	PixelChar generate_char(PixelFont::PixelCharTemplate char_template, sf::Vector2i pos);
};

}
