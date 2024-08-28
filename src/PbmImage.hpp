#pragma once

#include <vector>
#include <string_view>
#include <optional>
#include <pixtxt/Color.hpp>

namespace pixtxt {

// This is for reading binary ("P4") PBM files: https://netpbm.sourceforge.net/doc/pbm.html
// PBM file is a dead simple image format which I could parse without any dependencies
// and it's monochrome so it's tiny despite the lack of compression

class PbmImage {
	std::vector<uint8_t> data;
	int width;
	int height;
	int image_start_pos;

	std::string_view filename; // kept for exception messages

	int skip_comment(int pos) const;
	std::pair<int, std::optional<int>> read_num(int pos) const;
	int increment_pos(int pos) const;

	void throw_file_too_short(int error_pos) const;

public:

	explicit PbmImage(const std::string_view filename);

	inline int get_width() const { return width; }
	inline int get_height() const { return height; }
	Color get_pixel(int x, int y) const;
};

}
