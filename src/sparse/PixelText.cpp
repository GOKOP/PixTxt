#include <sparse/PixelText.hpp>

namespace pixtxt::sparse {

PixelText::PixelText(const PixelFont& font, std::string_view text, Position pos) {
	for(char character : text) {
		push_char(font.get_char(character), pos);
		pos.x += 2;
	}
}

void PixelText::push_char(
		const PixelFont::PixelCharTemplate& char_template,
		Position pos)
{
	text.push_back({ pos, char_template[0] });
	text.push_back({ {pos.x, pos.y + 1}, char_template[1] });
	text.push_back({ {pos.x, pos.y + 2}, char_template[2] });
	text.push_back({ {pos.x, pos.y + 3}, char_template[3] });
	text.push_back({ {pos.x, pos.y + 4}, char_template[4] });
}

}
