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

	PixelText(const PixelFont& font, std::string_view text, Position pos);
	inline const std::vector<Pixel>& get_pixels() const { return text_pixels; };
};

}
