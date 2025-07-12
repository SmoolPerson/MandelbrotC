#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "./lodepng.h"

// precomputed rgb values with max saturation/brightness
const int r_val[360] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 250, 246, 242, 237, 233, 229, 225, 221, 216, 212, 208, 203, 199, 195, 191, 187, 182, 178, 174, 169, 165, 161, 157, 153, 148, 144, 140, 135, 131, 127, 123, 118, 114, 110, 106, 101, 97, 93, 89, 84, 80, 76, 72, 67, 63, 59, 55, 50, 46, 42, 38, 33, 29, 25, 21, 16, 12, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 12, 16, 21, 25, 29, 34, 38, 42, 46, 50, 55, 59, 63, 68, 72, 76, 80, 84, 89, 93, 97, 102, 106, 110, 114, 118, 123, 127, 131, 136, 140, 144, 148, 152, 157, 161, 165, 170, 174, 178, 182, 186, 191, 195, 199, 204, 208, 212, 216, 220, 225, 229, 233, 238, 242, 246, 250, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
const int g_val[360] = {0, 4, 8, 12, 16, 21, 25, 29, 33, 38, 42, 46, 51, 55, 59, 63, 67, 72, 76, 80, 85, 89, 93, 97, 102, 106, 110, 114, 119, 123, 127, 131, 136, 140, 144, 148, 153, 157, 161, 165, 170, 174, 178, 182, 187, 191, 195, 199, 204, 208, 212, 216, 221, 225, 229, 233, 238, 242, 246, 250, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 250, 246, 242, 237, 233, 229, 225, 221, 216, 212, 208, 203, 199, 195, 191, 187, 182, 178, 174, 169, 165, 161, 157, 153, 148, 144, 140, 135, 131, 127, 123, 119, 114, 110, 106, 101, 97, 93, 89, 85, 80, 76, 72, 67, 63, 59, 55, 51, 46, 42, 38, 33, 29, 25, 21, 17, 12, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const int b_val[360] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 12, 17, 21, 25, 29, 34, 38, 42, 46, 51, 55, 59, 63, 68, 72, 76, 80, 85, 89, 93, 97, 102, 106, 110, 114, 119, 123, 127, 131, 136, 140, 144, 148, 153, 157, 161, 165, 170, 174, 178, 182, 187, 191, 195, 199, 204, 208, 212, 216, 221, 225, 229, 233, 238, 242, 246, 250, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 250, 246, 242, 237, 233, 229, 225, 221, 216, 212, 208, 203, 199, 195, 191, 187, 182, 178, 174, 169, 165, 161, 157, 153, 148, 144, 140, 135, 131, 127, 123, 119, 114, 110, 106, 101, 97, 93, 89, 85, 80, 76, 72, 67, 63, 59, 55, 51, 46, 42, 38, 33, 29, 25, 21, 17, 12, 8, 4};

int ANTI_ALIASING = 1;
// number of points to choose while doing anti aliasing
int ANTI_ALIASING_NUM_PTS = 12;
double COLOR_STEP_MULTIPLIER = 0.5;
int COLOR_OFFSET = 240;
char *OUTPUT_FILENAME = "mandelbrot.png";
// max iterations for mandelbrot
int MAX_ITER = 675;
// how far to go until you stop the loop and return
int CUTOFF = 2;
// how many pixels in one unit?
int PIXELS_PER_SQUARE = 4096;
// how big do u want the view to be?
double width_min = -2;
double width_max = 0.5;
double height_min = -1;
double height_max = 1;
int WIDTH;
int HEIGHT;

// func to calc whether point is part of mandelbrot
// returns num of iters if not in the set, and returns -1 if in the set
// takes cx (real part of c) and cy (complex part of c) as params
double mandelbrot(double cx, double cy) {
    double zx = 0;
    double zy = 0;
    // calculating squared versions ahead of time so that we don't need to calculate them twice
    double zx2 = zx * zx;
    double zy2 = zy * zy;

    // Bulb checking: https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#Cardioid_/_bulb_checking
    double cx14 = cx - 0.25;
    double cy2 = cy * cy;
    double q = (cx14)*(cx14) + cy2;
    if (sqrt(q) - 2 * q + 0.25 >= cx) {
        return 0;
    }
    if ((cx + 1)*(cx + 1) + cy2 <= 0.0625) {
        return 0;
    }
    double magnitude;
    for (size_t i = 1; i < MAX_ITER; ++i) {
        // This is bounds check; if the distance of x and y from origin is > 2, then point escaped
        magnitude = sqrt(zx2 + zy2);
        if (magnitude > 2) {
            // smoothing using logs, https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#Continuous_(smooth)_coloring
            return i + 1 - log(log(magnitude))/log(2);
        }
        // Instead of using a single complex object, we split it up into two real equations for slight optimization
        zy = 2 * (zx) * zy + cy;
        zx = zx2 - zy2 + cx;
        zx2 = zx * zx;
        zy2 = zy * zy;
    }
    // if point does not escape, then its in the set, so return -1
    return 0;
}

// helper function to lerp
float lerp(double a, double b, double t) {
    return a + t * (b - a);
}

typedef struct {
    float r;
    float g;
    float b;
} rgb_type;

// color a hue based on how many iterations it took
rgb_type calculate_hue(double mandelbrot_val) {
    rgb_type rgb;
    double hue_val;
    double between;
    int floorv;
    int ceilv;
    // transform the mandelbrot_val to a desirable scale between 0 and 360
    hue_val = fmod((mandelbrot_val*COLOR_STEP_MULTIPLIER + COLOR_OFFSET), 360.0);
    // we have to lerp now, floor and ceiling are the values in between the returned value
    floorv = (int)floor(hue_val);
    ceilv = (int)ceil(hue_val);
    between = fmod(mandelbrot_val, 1);

    // Ensure array bounds
    if (floorv < 0) floorv = 0;
    if (floorv >= 360) floorv = 359;
    if (ceilv < 0) ceilv = 0;
    if (ceilv >= 360) ceilv = 359;

    rgb.r = lerp(r_val[floorv], r_val[ceilv], between);
    rgb.g = lerp(g_val[floorv], g_val[ceilv], between);
    rgb.b = lerp(b_val[floorv], b_val[ceilv], between);
    return rgb;
}

void get_and_set_pixel_color(int imagex, int imagey, unsigned char *rgb_data) {
    rgb_type rgb;
    int rgb_write_index = (imagey * WIDTH + imagex) * 4;
    
    double step = 1.0/PIXELS_PER_SQUARE;

    double cx = width_min + imagex * step;
    double cy = height_min + imagey * step;

    double mandelbrot_val;
    if (ANTI_ALIASING) {
        // The implementation here is to select some values at a random offset, and avg them
        double anti_aliasing_sum = 0.0;
        for (size_t i = 0; i < ANTI_ALIASING_NUM_PTS; ++i) {

            double rand_x_offset = ((double)rand()/(double)RAND_MAX)/PIXELS_PER_SQUARE;
            double rand_y_offset = ((double)rand()/(double)RAND_MAX)/PIXELS_PER_SQUARE;
            double randomized_cx = cx + rand_x_offset;
            double randomized_cy = cy + rand_y_offset;
            anti_aliasing_sum += mandelbrot(randomized_cx, randomized_cy);
        }
        mandelbrot_val = anti_aliasing_sum/ANTI_ALIASING_NUM_PTS;
    }
    else {
        mandelbrot_val = mandelbrot(cx, cy);
    }
    // If mandelbrot is part of set, color black, else, color a hue based on how many iterations it took
    if (mandelbrot_val == 0) {
        rgb_data[rgb_write_index] = 0;
        rgb_data[rgb_write_index+1] = 0;
        rgb_data[rgb_write_index+2] = 0;
        rgb_data[rgb_write_index+3] = 255;
    } else {
        rgb = calculate_hue(mandelbrot_val);

        rgb_data[rgb_write_index] = (unsigned char)rgb.r;
        rgb_data[rgb_write_index+1] = (unsigned char)rgb.g;
        rgb_data[rgb_write_index+2] = (unsigned char)rgb.b;
        rgb_data[rgb_write_index+3] = 255;
    }
}

// I'm just using this function for various tasks, i should maybe split it up more
int main() {
    // Seed rng gen
    srand(time(NULL));

    // get the difference between max and min to get the mathematical length, then multiply by the pixel rate to get the real size
    // typecast to int since img dim needs to be whole number
    WIDTH = (int)(fabs(width_max - width_min) * PIXELS_PER_SQUARE);
    HEIGHT = ((int)(fabs(height_max - height_min) * PIXELS_PER_SQUARE));
    // lot going on here; it is an unsigned char since rgb data is one byte array, and we multiply by 3 for the red, green, and blue values
    unsigned char *rgb_data = malloc(WIDTH * HEIGHT * 4);
    if (!rgb_data) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    int percent, past_percent = -1;
    for (size_t x = 0; x < WIDTH; ++x) {

        // print progress bar
        percent = (x * 100) / WIDTH;
        if (percent > past_percent) {
            printf("\r %d percent done", percent);
            fflush(stdout);
            past_percent = percent;
        }

        for (size_t y = 0; y < HEIGHT; ++y) {
            // Where exactly should the byte be written in the array? multiply the y by the width to get all rows till now, and add x as the offset
            get_and_set_pixel_color(x, y, rgb_data);
        }
    }
    // Cleanup and writing data
    printf("\n");
    unsigned error = lodepng_encode32_file(OUTPUT_FILENAME, rgb_data, WIDTH, HEIGHT);
    if (error) printf("PNG encode error %u: %s\n", error, lodepng_error_text(error));
    free(rgb_data);
    return 0;
}