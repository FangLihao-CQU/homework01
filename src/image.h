#ifndef IMAGE_H
#define IMAGE_H

typedef struct{
    int w,h,c;
    float *data;
} image;


// Basic operations
__declspec(dllexport) float get_pixel(image im, int x, int y, int c);
__declspec(dllexport) void set_pixel(image im, int x, int y, int c, float v);
__declspec(dllexport) image copy_image(image im);
__declspec(dllexport) image rgb_to_grayscale(image im);
__declspec(dllexport) void rgb_to_hsv(image im);
__declspec(dllexport) void hsv_to_rgb(image im);
__declspec(dllexport) void shift_image(image im, int c, float v);
__declspec(dllexport) void clamp_image(image im);


// Loading and saving
__declspec(dllexport) image make_image(int w, int h, int c);
__declspec(dllexport) image load_image(char *filename);
__declspec(dllexport) void save_image(image im, const char *name);
__declspec(dllexport) void free_image(image im);

#endif

