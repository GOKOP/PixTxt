#pragma once

#include <pixtxt/Color.hpp>
#include <pixtxt/Position.hpp>

namespace pixtxt {

/// A pixel; in other words, a color on a specific position.
struct Pixel {
	Position pos;
	Color color;
};

}
