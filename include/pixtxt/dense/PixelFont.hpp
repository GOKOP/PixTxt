#pragma once

#include <array>
#include <vector>
#include <string_view>

namespace pixtxt::dense {

/// Font to be used with pixtxt::dense::PixelText.
class PixelFont {
public:
	using Char = std::vector<bool>;

	/// The constructor.
	///
	/// @param char_width: Width of characters in the font, in subpixels.
	/// @param char_height: Height of characters in the font, in subpixels.
	/// @param filename: Name of the .pbm file from which the font is loaded.
	///     Each character in the file should be drawn as char_width x char_height pixels
	///     with white pixels as foreground and black pixels as background.
	///     The image should contain 16 rows of 16 characters (256 total) in ASCII order.
	///
	/// @throws pixtxt::PbmFileError: Thrown for any issues parsing the PBM file.
	/// @throws pixtxt::PixelFontError: Thrown if the font image has different dimensions
	///     than expected based on char_width and char_height.
	explicit PixelFont(int char_width, int char_height, std::string_view filename);

	const Char& get_char(unsigned char key) const;
	inline int get_char_width() const { return char_width; }
	inline int get_char_height() const { return char_height; }

private:
	int char_width;
	int char_height;
	std::array<Char, 256> characters;
};

}
