#include <pixtxt/dense/PixelText.hpp>
#include "SubpixelColumns.hpp"
#include <algorithm>

namespace pixtxt::dense {

PixelText::PixelText(const PixelFont& font, std::string_view text, Position pos) {
	int current_subpixel = 0;
	int current_x = pos.x;
	std::vector<Pixel> current_pixel_column = gen_pixel_column(pos, font.get_char_height());

	for(auto column : SubpixelColumns(&font, text)) {
		for(size_t i=0; i < column.size(); ++i) {
			auto& subpixel_ref = get_subpixel(current_pixel_column[i].color, current_subpixel);
			if(column[i]) subpixel_ref = 255;
		}

		++current_subpixel;
		if(current_subpixel <= 2) continue;

		std::copy(
			current_pixel_column.begin(),
			current_pixel_column.end(),
			std::back_inserter(text_pixels));

		current_subpixel = 0;
		++current_x;
		current_pixel_column = gen_pixel_column({current_x, pos.y}, font.get_char_height());
	}

	if(current_subpixel <= 2) {
		std::copy(
			current_pixel_column.begin(),
			current_pixel_column.end(),
			std::back_inserter(text_pixels));
	}
}

uint8_t& PixelText::get_subpixel(Color& pixel, int index) const {
	switch(index) {
		case 0: return pixel.r;
		case 1: return pixel.g;
		case 2: return pixel.b;
		default: return pixel.r;
	}
}

std::vector<Pixel> PixelText::gen_pixel_column(Position pos, int height) const {
	std::vector<Pixel> res;
	for(int i=0; i < height; ++i) {
		res.push_back(Pixel { {pos.x, pos.y + i}, Color { 0, 0, 0 } });
	}

	return res;
}

}
