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

	int skip_comment(int pos) const;
	std::pair<int, std::optional<int>> read_num(int pos) const;

public:

	explicit PbmImage(const std::string_view filename);
	Color get_pixel(int x, int y) const;
};

}
