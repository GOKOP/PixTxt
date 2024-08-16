#pragma once

#include <SFML/Graphics/Vertex.hpp>
#include <array>

namespace sparse {

constexpr int subpixels = 3;
constexpr int pixel_char_height = 5;

using PixelChar = std::array<sf::Vertex, pixel_char_height>;
using PixelCharTemplate = std::array<sf::Color, pixel_char_height>;

}
