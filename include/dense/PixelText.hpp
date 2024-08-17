#pragma once

#include <SFML/Graphics.hpp>
#include <dense/PixelFont.hpp>

namespace pixtxt::dense {

class PixelText : public sf::Drawable {
	std::vector<sf::Vertex> text_pixels;

	sf::Uint8& get_subpixel(sf::Color& pixel, int index) const;
	std::array<sf::Vertex, PixelFont::char_height> gen_pixel_column(sf::Vector2i pos) const;

public:

	PixelText(const PixelFont& font, std::string_view text, sf::Vector2i pos);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}
