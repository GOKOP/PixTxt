#include <vector>
#include <fstream>
#include <spng.h>
#include <pixtxt/sparse/PixelText.hpp>
#include <pixtxt/dense/PixelText.hpp>

class PixtxtWriter {
	std::vector<pixtxt::Pixel> pixels;
	int background_left;
	int background_top;
	int background_right;
	int background_bottom;

	// assumes RGB format (no alpha)
	int image_byte_pos(int x, int y, int image_width) {
		return 3 * (y * image_width + x);
	}

	PixtxtWriter(const std::vector<pixtxt::Pixel> pixels) {
		this->pixels = pixels;
		background_left = pixels.front().pos.x - 1;
		background_top = pixels.front().pos.y - 1;
		background_right = pixels.back().pos.x + 1;
		background_bottom = pixels.back().pos.y + 1;
	}

public:

	static PixtxtWriter sparse(
			const pixtxt::sparse::PixelFont& font,
			std::string_view text,
			pixtxt::Position pos)
	{
		return PixtxtWriter(pixtxt::sparse::PixelText(font, text, pos).get_pixels());
	}

	static PixtxtWriter dense(
			const pixtxt::dense::PixelFont& font,
			std::string_view text,
			pixtxt::Position pos)
	{
		return PixtxtWriter(pixtxt::dense::PixelText(font, text, pos).get_pixels());
	}

	// assumes RGB format (no alpha)
	void write_to_image(std::vector<uint8_t>& data, int image_width, int image_height) {

		for(int x = background_left; x <= background_right; ++x) {
			for(int y = background_top; y <= background_bottom; ++y) {
				int byte_pos = image_byte_pos(x, y, image_width);
				data[byte_pos] = 0;
				data[byte_pos + 1] = 0;
				data[byte_pos + 2] = 0;
			}
		}

		for(const auto& pixel : pixels) {
			int byte_pos = image_byte_pos(pixel.pos.x, pixel.pos.y, image_width);
			data[byte_pos] = pixel.color.r;
			data[byte_pos + 1] = pixel.color.g;
			data[byte_pos + 2] = pixel.color.b;
		}
	}
};

int main() {
	// generate some text
	
	pixtxt::sparse::PixelFont sparse_font(5, "font.pbm");
	pixtxt::dense::PixelFont dense_font(3, 5, "font.pbm");

	auto sparse_example = PixtxtWriter::sparse(sparse_font, "Sparse text example", {100, 100});
	auto dense_example = PixtxtWriter::dense(dense_font, "Dense text example", {100, 106});

	auto sparse_example_line1 = PixtxtWriter::sparse(
		sparse_font,
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed sed feugiat nunc,",
		{300, 100});
	auto sparse_example_line2 = PixtxtWriter::sparse(
		sparse_font,
		"id feugiat nibh. Donec ex massa, vulputate quis viverra id, tempus eget ipsum.",
		{300, 106});
	auto sparse_example_line3 = PixtxtWriter::sparse(
		sparse_font,
		"Nulla vel elit ligula. Etiam vitae tincidunt elit. Curabitur consequat congue nulla,",
		{300, 112});
	auto sparse_example_line4 = PixtxtWriter::sparse(
		sparse_font,
		"sed elementum nibh tempus in. Aliquam in ligula nunc.",
		{300, 118});
	auto sparse_example_line5 = PixtxtWriter::sparse(
		sparse_font,
		"Integer id augue vitae ligula faucibus faucibus at nec neque. Nulla facilisi.",
		{300, 124});

	auto dense_example_line1 = PixtxtWriter::dense(
		dense_font,
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed sed feugiat nunc,",
		{300, 200});
	auto dense_example_line2 = PixtxtWriter::dense(
		dense_font,
		"id feugiat nibh. Donec ex massa, vulputate quis viverra id, tempus eget ipsum.",
		{300, 206});
	auto dense_example_line3 = PixtxtWriter::dense(
		dense_font,
		"Nulla vel elit ligula. Etiam vitae tincidunt elit. Curabitur consequat congue nulla,",
		{300, 212});
	auto dense_example_line4 = PixtxtWriter::dense(
		dense_font,
		"sed elementum nibh tempus in. Aliquam in ligula nunc.",
		{300, 218});
	auto dense_example_line5 = PixtxtWriter::dense(
		dense_font,
		"Integer id augue vitae ligula faucibus faucibus at nec neque. Nulla facilisi.",
		{300, 224});

	// generate raw image data

	uint32_t width = 500;
	uint32_t height = 300;
	int subpixels = 3;

	std::vector<uint8_t> image_data(width * height * subpixels, 255);

	sparse_example.write_to_image(image_data, width, height);
	dense_example.write_to_image(image_data, width, height);

	sparse_example_line1.write_to_image(image_data, width, height);
	sparse_example_line2.write_to_image(image_data, width, height);
	sparse_example_line3.write_to_image(image_data, width, height);
	sparse_example_line4.write_to_image(image_data, width, height);
	sparse_example_line5.write_to_image(image_data, width, height);

	dense_example_line1.write_to_image(image_data, width, height);
	dense_example_line2.write_to_image(image_data, width, height);
	dense_example_line3.write_to_image(image_data, width, height);
	dense_example_line4.write_to_image(image_data, width, height);
	dense_example_line5.write_to_image(image_data, width, height);

	// generate PNG with spng
	
	spng_ctx* enc = spng_ctx_new(SPNG_CTX_ENCODER);
	spng_set_option(enc, SPNG_ENCODE_TO_BUFFER, 1);
	
	spng_ihdr ihdr { width, height, 8, SPNG_COLOR_TYPE_TRUECOLOR };
	spng_set_ihdr(enc, &ihdr);
	spng_encode_image(enc, image_data.data(), image_data.size(), SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);

	size_t png_size;
	int error;
	char* png = static_cast<char*>(spng_get_png_buffer(enc, &png_size, &error));
	spng_ctx_free(enc);

	// write the PNG to a file

	std::ofstream output("result.png", std::ios::out | std::ios::binary);
	output.write(png, png_size);

	free(png);
}
