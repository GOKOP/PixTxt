#include <pixtxt/dense/PixelFont.hpp>
#include <pixtxt/PixelFontError.hpp>
#include "../PbmImage.hpp"

namespace pixtxt::dense {

PixelFont::PixelFont(int char_width, int char_height, std::string_view filename):
	char_width(char_width),
	char_height(char_height)
{
	PbmImage font_image(filename);

	static constexpr int chars_in_row = 16;

	int expected_width = chars_in_row * char_width;
	int expected_height = (characters.size() / chars_in_row) * char_height;

	if(font_image.get_width() != expected_width || font_image.get_height() != expected_height) {
		throw PixelFontError(
			filename,
			": Wrong dimensions; expected ",
			std::to_string(expected_width),
			"x",
			std::to_string(expected_height));
	}

	for(size_t i=0; i < characters.size(); ++i) {
		characters[i].resize(char_width * char_height);

		int x = (i % chars_in_row) * char_width;
		int y = (i / chars_in_row) * char_height;

		for(int j=0; j < char_width; ++j) {
			for(int k=0; k < char_height; ++k) {
				characters[i][k * char_width + j] =
					font_image.get_pixel(j + x, k + y) == Color{255, 255, 255};
			}
		}
	}
}

const PixelFont::Char& PixelFont::get_char(unsigned char key) const {
	return characters[key];
}

}
