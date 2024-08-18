#pragma once

#include <pixtxt/Pixel.hpp>
#include <pixtxt/sparse/PixelFont.hpp>
#include <vector>

namespace pixtxt::sparse {

class PixelText {
	std::vector<Pixel> text;

	void push_char(const PixelFont::PixelCharTemplate& char_template, Position pos);

public:
	explicit PixelText(const PixelFont& font, std::string_view text, Position pos);

	inline const std::vector<Pixel>& get_pixels() const { return text; }
};

}
