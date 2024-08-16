#pragma once

#include "PixelFont.hpp"
#include <vector>

namespace sparse {

class PixelText: public sf::Drawable {
	std::vector<PixelChar> text;

public:
	explicit PixelText(const PixelFont& font, std::string_view text, sf::Vector2i pos);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}
