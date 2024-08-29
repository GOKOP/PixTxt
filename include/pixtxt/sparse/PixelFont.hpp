#pragma once

#include <array>
#include <vector>
#include <string_view>
#include <pixtxt/Color.hpp>

namespace pixtxt::sparse {

/// Font to be used with pixtxt::sparse::PixelText.
class PixelFont {
public:
	// this is defined only for readability purposes
	// any value other than 3 is a lie so don't change it ever
	// and no this code can't be adapted to work with WOLED's RGBW layout
	// the way it works is completely different
	static constexpr int subpixels = 3;

	using PixelCharTemplate = std::vector<Color>;

	/// The constructor.
	///
	/// @param char_height: Height of characters in the font, in subpixels.
	/// @param filename: Name of the .pbm file from which the font is loaded.
	///     Each character in the file should be drawn as 3 x char_height pixels
	///     with white pixels as foreground and black pixels as background.
	///     The image should contain 16 rows of 16 characters (256 total) in ASCII order.
	///
	/// @throws pixtxt::PbmFileError: Thrown for any issues parsing the PBM file.
	/// @throws pixtxt::PixelFontError: Thrown if the font image has different dimensions
	///     than expected based on char_width and char_height.
	explicit PixelFont(int char_height, std::string_view filepath);

	inline const PixelCharTemplate& get_char(unsigned char key) const {
		return characters[key];
	}

private:
	int char_height;
	std::array<PixelCharTemplate, 256> characters;
};

}
