#include <sparse/PixelFont.hpp>

namespace pixtxt::sparse {

PixelFont::PixelFont(const std::string& filepath) {
	sf::Image font_image;
	font_image.loadFromFile(filepath);

	static constexpr int total_chars = 256;
	static constexpr int chars_in_row = 16;

	for(int i=0; i < total_chars; ++i) {
		int x = (i % chars_in_row) * subpixels;
		int y = (i / chars_in_row) * char_height;

		for(int j=0; j < char_height; ++j) {
			int red = font_image.getPixel(x, y + j) == sf::Color::White ? 255 : 0;
			int green = font_image.getPixel(x + 1, y + j) == sf::Color::White ? 255 : 0;
			int blue = font_image.getPixel(x + 2, y + j) == sf::Color::White ? 255 : 0;

			characters[i][j] = sf::Color(red, green, blue);
		}
	}
}

}
