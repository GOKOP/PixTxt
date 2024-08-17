#include <SFML/Graphics.hpp>

#include "sparse/PixelText.hpp"
#include "dense/PixelText.hpp"

using namespace pixtxt;

class SfmlPixelText : public sf::Drawable {
	std::vector<sf::Vertex> pixels;
	sf::RectangleShape background;

	SfmlPixelText(const std::vector<Pixel>& source_pixels) {
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

	static SfmlPixelText sparse(const sparse::PixelFont& font, std::string_view text, Position pos) {
		return SfmlPixelText(sparse::PixelText(font, text, pos).get_pixels());
	}

	static SfmlPixelText dense(const dense::PixelFont& font, std::string_view text, Position pos) {
		return SfmlPixelText(dense::PixelText(font, text, pos).get_pixels());
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(background);
		target.draw(pixels.data(), pixels.size(), sf::Points);
	}

};

int main() {
	sparse::PixelFont font("font.pbm");
	dense::PixelFont dense_font("font.pbm");

	auto sparse_example = SfmlPixelText::sparse(font, "Sparse text example", {100, 350});
	auto dense_example = SfmlPixelText::dense(dense_font, "Dense text example", {100, 356});

	auto sparse_dis = SfmlPixelText::sparse(font, "Jebac disa kurwe orka!!!111", {100, 500});
	auto dense_dis = SfmlPixelText::dense(dense_font, "Jebac disa kurwe orka!!!111", {100, 506});

	auto text = SfmlPixelText::sparse(font, "1234567890 jebie mi dupa panie gac! ooomagad", {100, 100});
	auto text2 = SfmlPixelText::sparse(font, "megawonsz9 to jest turbogigakoxu. hellyeah", {100, 106});
	auto text3 = SfmlPixelText::sparse(font, "Morris? Nienawidze zydow, murzynow, pedalow, LGBT", {100, 200});

	auto line1 = SfmlPixelText::sparse(
		font,
		"Nie jest dopuszczalne traktowanie zatechlych uszu jako czegos normalnego.",
		{300, 100});
	auto line2 = SfmlPixelText::sparse(
		font,
		"To jest po prostu niezmiernie glupie, aby tolerowac takie zachowania w cywilizowanym spoleczenstwie.",
		{300, 106});
	auto line3 = SfmlPixelText::sparse(
		font,
		"Wszystkich ludzi ktorzy przejawiaja takie sklonnosci nalezy polewac obwicie sosem majonezowym w proszku,",
		{300, 112});
	auto line4 = SfmlPixelText::sparse(
		font,
		"a kazdego kto bedzie stawial opor przeturlac przez trawnik pana Gaca.",
		{300, 118});
	auto line5 = SfmlPixelText::sparse(
		font,
		"Oczywiscie nie bedzie to latwe zadanie - trzeba najpierw rozpuscic cale swiatowe zapasy gowna psa.",
		{300, 124});
	auto line6 = SfmlPixelText::sparse(
		font,
		"Nie wydaje mi sie, aby ONZ chcialo podjac jakies kroki w tym kierunku, zwlaszcza w trakcie szalejacej pandemii.",
		{300, 130});
	auto line7 = SfmlPixelText::sparse(
		font,
		"Nalezy jednak pamietac, ze ignorowanie problemu nie sprawi, ze ten przestanie istniec",
		{300, 136});
	auto line8 = SfmlPixelText::sparse(
		font,
		"i w koncu trzeba bedzie stawic mu czola.",
		{300, 142});

	auto dense_line1 = SfmlPixelText::dense(
		dense_font,
		"Nie jest dopuszczalne traktowanie zatechlych uszu jako czegos normalnego.",
		{300, 300});
	auto dense_line2 = SfmlPixelText::dense(
		dense_font,
		"To jest po prostu niezmiernie glupie, aby tolerowac takie zachowania w cywilizowanym spoleczenstwie.",
		{300, 306});
	auto dense_line3 = SfmlPixelText::dense(
		dense_font,
		"Wszystkich ludzi ktorzy przejawiaja takie sklonnosci nalezy polewac obwicie sosem majonezowym w proszku,",
		{300, 312});
	auto dense_line4 = SfmlPixelText::dense(
		dense_font,
		"a kazdego kto bedzie stawial opor przeturlac przez trawnik pana Gaca.",
		{300, 318});

	sf::RenderWindow window(sf::VideoMode(800, 600), "one pixel text", sf::Style::Close);
	window.setFramerateLimit(60);
	while(window.isOpen()) {
		window.clear(sf::Color::White);

		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) window.close();
		}

		window.draw(text);
		window.draw(text2);
		window.draw(text3);

		window.draw(line1);
		window.draw(line2);
		window.draw(line3);
		window.draw(line4);
		window.draw(line5);
		window.draw(line6);
		window.draw(line7);
		window.draw(line8);

		window.draw(dense_line1);
		window.draw(dense_line2);
		window.draw(dense_line3);
		window.draw(dense_line4);

		window.draw(sparse_example);
		window.draw(dense_example);

		window.draw(sparse_dis);
		window.draw(dense_dis);

		window.display();
	}
}
