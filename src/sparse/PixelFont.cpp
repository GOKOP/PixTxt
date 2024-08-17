#include <sparse/PixelFont.hpp>
#include <PbmImage.hpp>

namespace pixtxt::sparse {

PixelFont::PixelFont(std::string_view filepath) {
	PbmImage font_image(filepath);

	static constexpr int total_chars = 256;
	static constexpr int chars_in_row = 16;

	for(int i=0; i < total_chars; ++i) {
		int x = (i % chars_in_row) * subpixels;
		int y = (i / chars_in_row) * char_height;

		for(int j=0; j < char_height; ++j) {
			int red = font_image.get_pixel(x, y + j) == Color(255, 255, 255) ? 255 : 0;
			int green = font_image.get_pixel(x + 1, y + j) == Color(255, 255, 255) ? 255 : 0;
			int blue = font_image.get_pixel(x + 2, y + j) == Color(255, 255, 255) ? 255 : 0;

			characters[i][j] = Color(red, green, blue);
		}
	}
}

}
