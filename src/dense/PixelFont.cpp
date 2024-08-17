#include <dense/PixelFont.hpp>
#include <PbmImage.hpp>

namespace pixtxt::dense {

PixelFont::PixelFont(std::string_view filename) {
	PbmImage font_image(filename);

	static constexpr int chars_in_row = 16;

	for(size_t i=0; i < characters.size(); ++i) {
		int x = (i % chars_in_row) * char_width;
		int y = (i / chars_in_row) * char_height;

		for(int j=0; j < char_width; ++j) {
			for(int k=0; k < char_height; ++k) {
				characters[i][k * char_width + j] =
					font_image.get_pixel(j + x, k + y) == Color(255, 255, 255);
			}
		}
	}
}

const PixelFont::Char& PixelFont::get_char(unsigned char key) const {
	return characters[key];
}

}
