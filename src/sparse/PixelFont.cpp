#include "PixelFont.hpp"

namespace sparse {

PixelFont::PixelFont(const std::string& filepath) {
	sf::Image font_image;
	font_image.loadFromFile(filepath);

	static constexpr int total_chars = 256;
	static constexpr int chars_in_row = 16;

	for(int i=0; i < total_chars; ++i) {
		int x = (i % chars_in_row) * subpixels;
		int y = (i / chars_in_row) * pixel_char_height;

		for(int j=0; j < pixel_char_height; ++j) {
			int red = font_image.getPixel(x, y + j) == sf::Color::White ? 255 : 0;
			int green = font_image.getPixel(x + 1, y + j) == sf::Color::White ? 255 : 0;
			int blue = font_image.getPixel(x + 2, y + j) == sf::Color::White ? 255 : 0;

			characters[i][j] = sf::Color(red, green, blue);
		}
	}
}

PixelChar PixelFont::create_char(unsigned char key, sf::Vector2i pos) const {
	return {
		sf::Vertex(sf::Vector2f(pos.x, pos.y), characters[key][0]),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 1), characters[key][1]),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 2), characters[key][2]),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 3), characters[key][3]),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 4), characters[key][4]),
	};
}

}
