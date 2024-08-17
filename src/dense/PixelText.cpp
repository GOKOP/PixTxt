#include <dense/PixelText.hpp>
#include <dense/SubpixelColumns.hpp>
#include <algorithm>

namespace pixtxt::dense {

PixelText::PixelText(const PixelFont& font, std::string_view text, Position pos) {
	int current_subpixel = 0;
	int current_x = pos.x;
	std::array<Pixel, PixelFont::char_height> current_pixel_column = gen_pixel_column(pos);

	for(auto column : SubpixelColumns(&font, text)) {
		for(size_t i=0; i < column.size(); ++i) {
			auto& subpixel_ref = get_subpixel(current_pixel_column[i].color, current_subpixel);
			if(column[i]) subpixel_ref = 255;
		}

		++current_subpixel;
		if(current_subpixel <= 2) continue;

		std::ranges::copy(current_pixel_column, std::back_inserter(text_pixels));
		current_subpixel = 0;
		++current_x;
		current_pixel_column = gen_pixel_column({current_x, pos.y});
	}

	if(current_subpixel <= 2) std::ranges::copy(current_pixel_column, std::back_inserter(text_pixels));
}

uint8_t& PixelText::get_subpixel(Color& pixel, int index) const {
	switch(index) {
		case 0: return pixel.r;
		case 1: return pixel.g;
		case 2: return pixel.b;
		default: return pixel.r;
	}
}

std::array<Pixel, PixelFont::char_height> PixelText::gen_pixel_column(Position pos) const {
	return {
		Pixel { pos, Color(0,0,0) },
		Pixel { {pos.x, pos.y + 1}, Color(0,0,0) },
		Pixel { {pos.x, pos.y + 2}, Color(0,0,0) },
		Pixel { {pos.x, pos.y + 3}, Color(0,0,0) },
		Pixel { {pos.x, pos.y + 4}, Color(0,0,0) }
	};
}

}
