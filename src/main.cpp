#include <SFML/Graphics.hpp>
#include "sparse/PixelText.hpp"

int main() {
	sparse::PixelFont font("font.png");

	sparse::PixelText text(font, "1234567890 jebie mi dupa panie gac! ooomagad", {100, 100});
	sparse::PixelText text2(font, "megawonsz9 to jest turbogigakoxu. hellyeah", {100, 106});
	sparse::PixelText text3(font, "Morris? Nienawidze zydow, murzynow, pedalow, LGBT", {100, 200});

	sparse::PixelText line1(
		font,
		"Nie jest dopuszczalne traktowanie zatechlych uszu jako czegos normalnego.",
		{300, 100});
	sparse::PixelText line2(
		font,
		"To jest po prostu niezmiernie glupie, aby tolerowac takie zachowania w cywilizowanym spoleczenstwie.",
		{300, 106});
	sparse::PixelText line3(
		font,
		"Wszystkich ludzi ktorzy przejawiaja takie sklonnosci nalezy polewac obwicie sosem majonezowym w proszku,",
		{300, 112});
	sparse::PixelText line4(
		font,
		"a kazdego kto bedzie stawial opor przeturlac przez trawnik pana Gaca.",
		{300, 118});
	sparse::PixelText line5(
		font,
		"Oczywiscie nie bedzie to latwe zadanie - trzeba najpierw rozpuscic cale swiatowe zapasy gowna psa.",
		{300, 124});
	sparse::PixelText line6(
		font,
		"Nie wydaje mi sie, aby ONZ chcialo podjac jakies kroki w tym kierunku, zwlaszcza w trakcie szalejacej pandemii.",
		{300, 130});
	sparse::PixelText line7(
		font,
		"Nalezy jednak pamietac, ze ignorowanie problemu nie sprawi, ze ten przestanie istniec",
		{300, 136});
	sparse::PixelText line8(
		font,
		"i w koncu trzeba bedzie stawic mu czola.",
		{300, 142});


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

		window.display();
	}
}
