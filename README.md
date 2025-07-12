# MandelbrotC
A mandelbrot image generator in less than 200 lines of C code. Supports features like anti-aliasing and color smoothing. The images mandelbrot.png and seahorse.png were rendered using this program. CLI usage and GPU support planned.
Usage:
Linux and macOS: run ./run.sh and make sure lodepng.c and lodepng.h are in the same dir. Customize the constants at the top of the C file.

Windows: I don't have a windows machine to test, but compiling should be the same (?) and just run the .exe file that shows up.

# Credits
https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set -- described all the algorithms I used
lodepng - Gave me an easy way to write image data to a PNG
Pezzza's work (https://www.youtube.com/@PezzzasWork) -- I was inspired by the random approach he took to anti-aliasing
3Blue1Brown -- For inspriing me to do this in the first place
https://github.com/Inseckto/HSV-to-RGB/blob/master/HSV2RGB.c -- Gave me the C implementation I used to make the precomputed rgb taables

:)
