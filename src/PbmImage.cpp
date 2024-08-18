#include "PbmImage.hpp"
#include <fstream>
#include <cctype>
#include <charconv>

namespace pixtxt {

PbmImage::PbmImage(const std::string_view filename) {
	std::ifstream file(filename.data(), std::ios::binary);
	// todo: check if good
	
	data = std::vector<uint8_t>(
		(std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	if(data[0] != 'P' || data[1] != '4' || isspace(data[2])) {
		// bad format
	}

	int pos = skip_comment(3);

	auto [pos1, maybe_width] = read_num(pos);
	width = maybe_width.value();

	pos = skip_comment(++pos1);

	auto [pos2, maybe_height] = read_num(pos);
	height = maybe_height.value();

	image_start_pos = skip_comment(++pos2);
}

int PbmImage::skip_comment(int pos) const {
	if(data[pos] != '#') return pos;
	while(data[pos] != '\n' && data[pos] != '\r') {
		++pos;
	}
	return ++pos;
}

std::pair<int, std::optional<int>> PbmImage::read_num(int pos) const {
	std::string str;

	while(!isspace(data[pos])) {
		str.push_back(data[pos]);
		++pos;
	}

	int dest;
	auto result = std::from_chars(str.data(), str.data() + str.size(), dest);
	if(result.ec != std::errc() || result.ptr != str.data() + str.size()) return {pos, {}};

	return {pos, dest};
}

Color PbmImage::get_pixel(int x, int y) const {
	int linear_pos = y * width + x;
	int byte_pos = image_start_pos + linear_pos / 8;
	int pos_in_byte = linear_pos % 8;

	// the position must be reversed thus subtracting from 7
	uint8_t byte_mask = 1 << (7 - pos_in_byte);
	uint8_t masked_byte = data[byte_pos] & byte_mask;

	// the format specifies bit 1 as black and bit 0 as white
	if(masked_byte) return Color(0, 0, 0);
	return Color(255, 255, 255);
}

}
