#pragma once

#include <vector>
#include <pixtxt/Pixel.hpp>
#include <pixtxt/dense/PixelFont.hpp>

namespace pixtxt::dense {

class PixelText {
	std::vector<Pixel> text_pixels;

	uint8_t& get_subpixel(Color& pixel, int index) const;
	std::vector<Pixel> gen_pixel_column(Position pos, int height) const;

public:

	/// @param font: Font to use.
	/// @param text: The text to generate.
	/// @param pos: Position, in pixels, where the text should be located.
	///     Resulting pixels will be positioned according to this.
	PixelText(const PixelFont& font, std::string_view text, Position pos);

	/// Retrieve the generated pixel data.
	/// The first pixel is guaranteed to be on the top left of the text,
	/// and the last pixel is guaranteed to be on the bottom right.
	///
	/// @return Const reference to the vector where pixel data is stored.
	inline const std::vector<Pixel>& get_pixels() const { return text_pixels; };
};

}
