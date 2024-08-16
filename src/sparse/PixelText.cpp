#include "PixelText.hpp"

namespace sparse {

PixelText::PixelText(const PixelFont& font, std::string_view text, sf::Vector2i pos) {
	for(char character : text) {
		this->text.push_back(generate_char(font.get_char(character), pos));
		pos.x += 2;
	}
}

void PixelText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for(auto& character : text) {
		auto background_top_left = character[0].position - sf::Vector2f(1, 1);

		sf::RectangleShape background(
			sf::Vector2f(3, PixelFont::char_height + 2));
		background.setFillColor(sf::Color::Black);
		background.setPosition(background_top_left);

		target.draw(background, states);
		target.draw(character.data(), character.size(), sf::Points, states);
	}
}

PixelText::PixelChar PixelText::generate_char(
		const PixelFont::PixelCharTemplate& char_template,
		sf::Vector2i pos)
{
	return {
		sf::Vertex(sf::Vector2f(pos.x, pos.y), char_template[0]),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 1), char_template[1]),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 2), char_template[2]),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 3), char_template[3]),
		sf::Vertex(sf::Vector2f(pos.x, pos.y + 4), char_template[4]),
	};
}

}
