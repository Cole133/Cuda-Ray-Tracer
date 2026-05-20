## Week 1, Day 1 — May 15, 2026
- Project structure set up (CMake, src/, output/, docs/)
- Toolchain confirmed: g++ 15.2.0, CMake, ImageMagick
- Rendered first PPM gradient — Shirley Ch. 2
- 256×256, ~800 bytes, looks correct

Next session: vec3 class (Ch. 3). Will refactor main.cpp to use it.
Time: ~1h

## Week 1, Day 2 - May 16, 2026
- Worked through chapter three and made new vec3 class that holds position direction and colors with three entries
- Maded a color class two that stores and RGB value
- Made ray class that stores and arrow shotting from the camera and looks whats in said direction.

## Week 1, Day 3 - May 17, 2026
- Worked through chapter 6 - added hittable abstract class + hit_record for storing intersection info
- Made sphere class (inherits from hittable) that does the ray-sphere intersection math
- Started hittable_list to hold all the objects in the world
- Added rtweekend.h as an umbrella header (constants like pi/infinity, shared usings, common includes)
- Got two spheres in the world (small one + big "ground" sphere) with the normal-as-color visualization
- Added a Makefile so `make` builds, renders to the next render#.ppm, and opens it

## Week 1, Day 4 - May 19, 2026
- Worked through chapter 7 - Added camera class and refactored main around it

## Week 1, Day 5 - May 20, 2026
- Went back to chapter 6 and implemented interviel class
- Worked on chapter 8 adding antialiasing
