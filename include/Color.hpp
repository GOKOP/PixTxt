#pragma once
#include <cstdint>

namespace pixtxt {

struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;

	inline friend bool operator==(const Color& lhs, const Color& rhs) {
		return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
	}
};

}
