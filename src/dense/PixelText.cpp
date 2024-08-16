#include "PixelText.hpp"
#include "SubpixelColumns.hpp"

namespace dense {

PixelText::PixelText(const PixelFont& font, std::string_view text, sf::Vector2i pos) {
	int current_subpixel = 0;
	int current_x = pos.x;
	std::array<sf::Vertex, PixelFont::char_height> current_pixel_column = gen_pixel_column(pos);

	for(auto column : SubpixelColumns(&font, text)) {
		for(size_t i=0; i < column.size(); ++i) {
			auto& subpixel_ref = get_subpixel(current_pixel_column[i].color, current_subpixel);
			if(column[i]) subpixel_ref = 255;
		}

		++current_subpixel;
		if(current_subpixel <= 2) continue;

		std::ranges::copy(current_pixel_column, std::back_inserter(text_pixels));
		current_subpixel = 0;
		++current_x;
		current_pixel_column = gen_pixel_column({current_x, pos.y});
	}

	if(current_subpixel <= 2) std::ranges::copy(current_pixel_column, std::back_inserter(text_pixels));
}

sf::Uint8& PixelText::get_subpixel(sf::Color& pixel, int index) const {
	switch(index) {
		case 0: return pixel.r;
		case 1: return pixel.g;
		case 2: return pixel.b;
		default: return pixel.r;
	}
}

std::array<sf::Vertex, PixelFont::char_height> PixelText::gen_pixel_column(sf::Vector2i pos) const {
	return {
		sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::Black),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 1), sf::Color::Black),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 2), sf::Color::Black),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 3), sf::Color::Black),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 4), sf::Color::Black)
	};
}

void PixelText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	int background_x = text_pixels.front().position.x - 1;
	int background_y = text_pixels.front().position.y - 1;
	int background_width = text_pixels.back().position.x - background_x + 2;
	int background_height = text_pixels.back().position.y - background_y + 2;

	sf::RectangleShape background(sf::Vector2f(background_width, background_height));
	background.setPosition(background_x, background_y);
	background.setFillColor(sf::Color::Black);

	target.draw(background, states);
	target.draw(text_pixels.data(), text_pixels.size(), sf::Points, states);
}

}
