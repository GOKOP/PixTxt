#include <pixtxt/sparse/PixelFont.hpp>
#include <pixtxt/PixelFontError.hpp>
#include "../PbmImage.hpp"

namespace pixtxt::sparse {

PixelFont::PixelFont(int char_height, std::string_view filepath): char_height(char_height) {
	PbmImage font_image(filepath);

	static constexpr int chars_in_row = 16;

	int expected_width = chars_in_row * subpixels;
	int expected_height = (characters.size() / chars_in_row) * char_height;

	if(font_image.get_width() != expected_width || font_image.get_height() != expected_height) {
		throw PixelFontError(
			filepath,
			": Wrong dimensions; expected ",
			std::to_string(expected_width),
			"x",
			std::to_string(expected_height));
	}

	for(size_t i=0; i < characters.size(); ++i) {
		characters[i].resize(char_height);

		int x = (i % chars_in_row) * subpixels;
		int y = (i / chars_in_row) * char_height;

		for(int j=0; j < char_height; ++j) {
			uint8_t red = font_image.get_pixel(x, y + j) == Color{255, 255, 255} ? 255 : 0;
			uint8_t green = font_image.get_pixel(x + 1, y + j) == Color{255, 255, 255} ? 255 : 0;
			uint8_t blue = font_image.get_pixel(x + 2, y + j) == Color{255, 255, 255} ? 255 : 0;

			characters[i][j] = Color{red, green, blue};
		}
	}
}

}
