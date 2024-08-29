# PixTxt

![Zoomed in photo of a computer screen with individual pixels visible; RGB subpixels create the text "sparse text example" and "dense text example" where in the second one they're closer together](https://raw.githubusercontent.com/GOKOP/PixTxt/master/readme.png)

PixTxt is a C++17 library for generating text with letters as thin as a single pixel.
It relies on the screen having the RGB subpixel layout, which means that OLED users are out of luck.
It's made to be agnostic of rendering backends by only providing a list of pixels (color + position) which you then have to put on screen using some other means.
Provided examples show how this can be done with SFML and libspng.
The library itself has no additional dependencies.

## Why

idk

## Usage

The library contains two "versions": sparse and dense.
A character in sparse text is always the same column of pixels,
and there's a full pixel gap between characters.
This means that characters for sparse text are necessarily three wide,
because they have to fit in a single pixel.
In dense text the gap between characters has the width of only a single subpixel.
Because of this, the pixel grid is irrelevant with dense text (only subpixels matter)
and there's no limitation on the width of characters.

The font is read from an image in the PBM format. (binary, not ASCII)
The font in font.pbm is used in the examples;
the image may look incomprehensible because there are no gaps between characters and all characters
that I couldn't or didn't bother drawing are filled in, but it's just 3x5 characters
(this is configurable, for dense text at least), the foreground is white and background is black.
The image size should be 16x16 characters, so for 3x5 characters it should be 48x80.

## Why PBM and not PNG or something normal?

It's an image format so simple that I could easily parse it by hand,
and it's monochromatic so it's tiny despite having no compression.
The benefit of this is that PixTxt doesn't depend on any image handling library.
Your favourite image editor certainly supports PBM so don't worry about that.

## Show me some code already

```cpp
#include <pixtxt/sparse/PixelText.hpp>
#include <pixtxt/dense/PixelText.hpp>

int main() {
    // you can configure sparse text character height, but width is always 3
    pixtxt::sparse::PixelFont sparse_font(5, "font.pbm");
    // there's no such limitation for dense text
    pixtxt::dense::PixelFont dense_font(3, 5, "font.pbm");
    
    // font, text, position in pixels
    pixtxt::sparse::PixelText sparse_text(sparse_font, "very small text", {10, 10});
    pixtxt::dense::PixelText dense_text(dense_font, "no one's gonna be able to read this", {10, 16});

    // do whatever you want with this
    std::vector<pixtxt::Pixel> sparse_pixels = sparse_text.get_pixels();
    std::vector<pixtxt::Pixel> dense_pixels = dense_text.get_pixels();
}
```

More practical examples that show how to use this library with other libraries can be found in the examples directory.

## Building

To build the SFML and libspng examples you need SFML and libspng.
Currently there's no install step, idk how that works. I'll add it later, maybe.
Public headers are in the `include` directory.
If you have Doxygen installed and CMake can find it, documentation will be built.
Otherwise it won't. If it was then it's under `build/docs`.

```bash
mkdir build && cd build

# default setup: shared library, no examples
cmake ..
# build as a static lib
cmake .. -DPIXTXT_STATIC_LIB
# build the SFML example
cmake .. -DPIXTXT_SFML_EXAMPLE
# build the libspng example
cmake .. -DPIXTXT_SPNG_EXAMPLE

cmake --build .
```

## Limitations

- ASCII only
- Not at all suitable for embedded (ironically the only place where it could pretend to be useful)

## Documentation

Generated with Doxygen

https://gokop.github.io/PixTxt/
