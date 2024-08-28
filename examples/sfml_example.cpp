#include <SFML/Graphics.hpp>
#include <pixtxt/sparse/PixelText.hpp>
#include <pixtxt/dense/PixelText.hpp>

class SfmlPixelText : public sf::Drawable {
	std::vector<sf::Vertex> pixels;
	sf::RectangleShape background;

	SfmlPixelText(const std::vector<pixtxt::Pixel>& source_pixels) {
		for(auto pixel : source_pixels) {
			pixels.push_back(sf::Vertex(
				sf::Vector2f(pixel.pos.x, pixel.pos.y),
				sf::Color(pixel.color.r, pixel.color.g, pixel.color.b)));
		}

		float left = pixels.front().position.x;
		float top = pixels.front().position.y;
		float right = pixels.back().position.x;
		float bottom = pixels.back().position.y;

		background.setPosition({left - 1, top - 1});
		background.setSize({right - left + 3, bottom - top + 3});
		background.setFillColor(sf::Color::Black);
	}

public:

	static SfmlPixelText sparse(
			const pixtxt::sparse::PixelFont& font,
			std::string_view text,
			pixtxt::Position pos)
	{
		return SfmlPixelText(pixtxt::sparse::PixelText(font, text, pos).get_pixels());
	}

	static SfmlPixelText dense(
			const pixtxt::dense::PixelFont& font,
			std::string_view text,
			pixtxt::Position pos)
	{
		return SfmlPixelText(pixtxt::dense::PixelText(font, text, pos).get_pixels());
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(background);
		target.draw(pixels.data(), pixels.size(), sf::Points);
	}

};

int main() {
	pixtxt::sparse::PixelFont sparse_font(5, "font.pbm");
	pixtxt::dense::PixelFont dense_font(3, 5, "font.pbm");

	auto sparse_example = SfmlPixelText::sparse(sparse_font, "Sparse text example", {100, 100});
	auto dense_example = SfmlPixelText::dense(dense_font, "Dense text example", {100, 106});

	auto sparse_example_line1 = SfmlPixelText::sparse(
		sparse_font,
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed sed feugiat nunc,",
		{300, 100});
	auto sparse_example_line2 = SfmlPixelText::sparse(
		sparse_font,
		"id feugiat nibh. Donec ex massa, vulputate quis viverra id, tempus eget ipsum.",
		{300, 106});
	auto sparse_example_line3 = SfmlPixelText::sparse(
		sparse_font,
		"Nulla vel elit ligula. Etiam vitae tincidunt elit. Curabitur consequat congue nulla,",
		{300, 112});
	auto sparse_example_line4 = SfmlPixelText::sparse(
		sparse_font,
		"sed elementum nibh tempus in. Aliquam in ligula nunc.",
		{300, 118});
	auto sparse_example_line5 = SfmlPixelText::sparse(
		sparse_font,
		"Integer id augue vitae ligula faucibus faucibus at nec neque. Nulla facilisi.",
		{300, 124});

	auto dense_example_line1 = SfmlPixelText::dense(
		dense_font,
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed sed feugiat nunc,",
		{300, 200});
	auto dense_example_line2 = SfmlPixelText::dense(
		dense_font,
		"id feugiat nibh. Donec ex massa, vulputate quis viverra id, tempus eget ipsum.",
		{300, 206});
	auto dense_example_line3 = SfmlPixelText::dense(
		dense_font,
		"Nulla vel elit ligula. Etiam vitae tincidunt elit. Curabitur consequat congue nulla,",
		{300, 212});
	auto dense_example_line4 = SfmlPixelText::dense(
		dense_font,
		"sed elementum nibh tempus in. Aliquam in ligula nunc.",
		{300, 218});
	auto dense_example_line5 = SfmlPixelText::dense(
		dense_font,
		"Integer id augue vitae ligula faucibus faucibus at nec neque. Nulla facilisi.",
		{300, 224});

	sf::RenderWindow window(sf::VideoMode(500, 300), "one pixel text", sf::Style::Close);
	window.setFramerateLimit(60);
	while(window.isOpen()) {
		window.clear(sf::Color::White);

		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) window.close();
		}

		window.draw(sparse_example);
		window.draw(dense_example);

		window.draw(sparse_example_line1);
		window.draw(sparse_example_line2);
		window.draw(sparse_example_line3);
		window.draw(sparse_example_line4);
		window.draw(sparse_example_line5);

		window.draw(dense_example_line1);
		window.draw(dense_example_line2);
		window.draw(dense_example_line3);
		window.draw(dense_example_line4);
		window.draw(dense_example_line5);

		window.display();
	}
}
