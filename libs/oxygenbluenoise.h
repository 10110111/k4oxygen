#ifndef oxygen_blue_noise_h
#define oxygen_blue_noise_h

namespace Oxygen
{

/* Reference article: Bart Wronski, "Dithering part three – real world 2D quantization dithering"
 *  https://bartwronski.com/2016/10/30/dithering-part-three-real-world-2d-quantization-dithering/
 *  Sample code for the article can be seen at
 *  https://github.com/bartwronski/BlogPostsExtraMaterial/tree/master/DitheringPostSeries .
 *
 *  Blue noise generator is based on https://github.com/bartwronski/BlueNoiseGenerator (my fork
 *  that compiles and works on Linux/GCC: https://github.com/10110111/BlueNoiseGenerator ).
 *
 *  This array is the triangle-remapped blue noise taken from the
 *  generator output file "noise-triangle-remapped.txt".
 */
constexpr int BLUE_NOISE_TILE_WIDTH = 64;
extern const float blueNoiseTriangleRemapped[BLUE_NOISE_TILE_WIDTH][BLUE_NOISE_TILE_WIDTH];

}

#endif
