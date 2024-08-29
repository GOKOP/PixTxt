#pragma once

#include <pixtxt/Pixel.hpp>
#include <pixtxt/sparse/PixelFont.hpp>
#include <vector>

namespace pixtxt::sparse {

class PixelText {
	std::vector<Pixel> text;

	void push_char(const PixelFont::PixelCharTemplate& char_template, Position pos);

public:
	/// @param font: Font to use.
	/// @param text: The text to generate.
	/// @param pos: Position, in pixels, where the text should be located.
	///     Resulting pixels will be positioned according to this.
	explicit PixelText(const PixelFont& font, std::string_view text, Position pos);

	/// Retrieve the generated pixel data.
	/// The first pixel is guaranteed to be on the top left of the text,
	/// and the last pixel is guaranteed to be on the bottom right.
	///
	/// @return Const reference to the vector where pixel data is stored.
	inline const std::vector<Pixel>& get_pixels() const { return text; }
};

}
