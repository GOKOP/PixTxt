#include "PbmImage.hpp"
#include <fstream>
#include <cctype>
#include <charconv>
#include <pixtxt/PbmFileError.hpp>

namespace pixtxt {

PbmImage::PbmImage(const std::string_view filename): filename(filename) {
	std::ifstream file(filename.data(), std::ios::binary);
	if(!file.good()) throw PbmFileError(filename, ": Can't open file.");
	
	data = std::vector<uint8_t>(
		(std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	if(data[0] != 'P' || data[1] != '4' || !isspace(data[2])) {
		throw PbmFileError(filename, ": Invalid format: not a binary PBM file.");
	}

	int pos = skip_comment(3);

	auto [pos1, maybe_width] = read_num(pos);
	if(!maybe_width.has_value()) throw PbmFileError(filename, ": Invalid format: no width.");
	width = maybe_width.value();

	pos = skip_comment(increment_pos(pos1));

	auto [pos2, maybe_height] = read_num(pos);
	if(!maybe_height.has_value()) throw PbmFileError(filename, ": Invalid format: no height.");
	height = maybe_height.value();

	image_start_pos = skip_comment(increment_pos(pos2));
}

int PbmImage::skip_comment(int pos) const {
	if(data[pos] != '#') return pos;
	while(data[pos] != '\n' && data[pos] != '\r') {
		pos = increment_pos(pos);
	}
	return increment_pos(pos);
}

std::pair<int, std::optional<int>> PbmImage::read_num(int pos) const {
	std::string str;

	while(!isspace(data[pos])) {
		str.push_back(data[pos]);
		pos = increment_pos(pos);
	}

	int dest;
	auto result = std::from_chars(str.data(), str.data() + str.size(), dest);
	if(result.ec != std::errc() || result.ptr != str.data() + str.size()) return {pos, {}};

	return {pos, dest};
}

int PbmImage::increment_pos(int pos) const {
	++pos;
	// cast to shut up compiler warning about sign mismatch, it should be fine
	if(pos >= static_cast<int>(data.size())) {
		throw_file_too_short(pos);
	}
	return pos;
}

void PbmImage::throw_file_too_short(int pos) const {
	throw PbmFileError(
		filename,
		": Invalid format: file ends too soon. Expected ",
		std::to_string(pos),
		"th byte.");
}

Color PbmImage::get_pixel(int x, int y) const {
	int linear_pos = y * width + x;

	int byte_pos = image_start_pos + linear_pos / 8;
	if(byte_pos >= static_cast<int>(data.size())) {
		throw_file_too_short(byte_pos);
	}

	int pos_in_byte = linear_pos % 8;

	// the position must be reversed thus subtracting from 7
	uint8_t byte_mask = 1 << (7 - pos_in_byte);
	uint8_t masked_byte = data[byte_pos] & byte_mask;

	// the format specifies bit 1 as black and bit 0 as white
	if(masked_byte) return Color{0, 0, 0};
	return Color{255, 255, 255};
}

}
