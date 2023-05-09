#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
    if (x <= 0)
        x = 0;
    if (y <= 0)
        y = 0;
    if (c <= 0)
        c = 0;
    if (x >= im.w)
        x = im.w;
    if (y >= im.h)
        y = im.h;
    if (c >= im.c)
        c = im.c;
    int location;
    float value;
    location = x + im.w * y + im.w * im.h * c; // 计算像素所在位置
    value = im.data[location];                 // 读出该位置像素值
    return value;                              // 返回像素值（为float型）
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    if (x <= 0)
        x = 0;
    if (y <= 0)
        y = 0;
    if (x >= im.w)
        x = im.w;
    if (y >= im.h)
        y = im.h;
    int location;
    location = x + im.w * y + im.w * im.h * c; // 计算像素所在位置
    im.data[location] = v;                     // 写入该位置像素值
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    // copy.data = im.data; // 可直接拷贝原图像数据，不用逐个读出
    // return copy;         // 返回拷贝后图像
    float value;
    for (int x = 0; x < im.w; x++)
    {
        for (int y = 0; y < im.h; y++)
        {
            for (int c = 0; c < im.c; c++)
            {
                value = get_pixel(im,x,y,c);
                set_pixel(copy,x,y,c,value);
            }
            
        }
    }
    return copy;
    
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    float value;
    for (int x = 0; x < im.w; x++)
    {
        for (int y = 0; y < im.h; y++)
        {
            value = 0.299 * get_pixel(im, x, y, 0) + 0.587 * get_pixel(im, x, y, 1) + 0.114 * get_pixel(im, x, y, 2); // 计算对应位置灰度值
            set_pixel(gray, x, y, 0, value);
        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    float value;
    for (int x = 0; x < im.w; x++)
    {
        for (int y = 0; y < im.h; y++)
        {
            value = v + get_pixel(im, x, y, c); // 计算变化后像素值
            set_pixel(im, x, y, c, value);
        }
    }
}

void clamp_image(image im)
{
    // TODO Fill this in
    float value;
    for (int x = 0; x < im.w; x++)
    {
        for (int y = 0; y < im.h; y++)
        {
            for (int c = 0; c < im.c; c++)
            {
                value = get_pixel(im, x, y, c); // 计算变化后像素值
                if (value > 1)
                {
                    value = 1;
                }
                if (value < 0)
                {
                    value = 0;
                }
                set_pixel(im, x, y, c, value);
            }
        }
    }
}

// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
} // 返回值为最大值

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
} // 返回值为最小值

void rgb_to_hsv(image im) // h:0-1.0 s:0.0-1.0 v:0.0-1.0
{
    // TODO Fill this in
    float r, g, b, h, s, v, hp, m, c;
    for (int x = 0; x < im.w; x++)
    {
        for (int y = 0; y < im.h; y++)
        {
            r = get_pixel(im, x, y, 0);
            g = get_pixel(im, x, y, 1);
            b = get_pixel(im, x, y, 2);
            v = three_way_max(r, g, b);
            m = three_way_min(r, g, b);
            c = v - m;
            if (v == 0)
            {
                s = 0;
            }
            else
            {
                s = c / v;
            }
            if (c == 0)
            {
                h = 0;
            }
            else
            {
                if (v == r)
                {
                    hp = (g - b) / c;
                }
                else if (v == g)
                {
                    hp = ((b - r) / c) + 2;
                }
                else if (v == b)
                {
                    hp = ((r - g) / c) + 4;
                }
                if (hp < 0)
                {
                    h = (hp / 6) + 1;
                }
                else
                {
                    h = (hp / 6);
                }
            }
            set_pixel(im, x, y, 0, h);
            set_pixel(im, x, y, 1, s);
            set_pixel(im, x, y, 2, v);
        }
    }
}

void hsv_to_rgb(image im) // h:0-1.0 s:0.0-1.0 v:0.0-1.0 hp:0-360
{
    // TODO Fill this in
    float h, s, v, r, g, b, hp;
    for (int x = 0; x < im.w; x++)
    {
        for (int y = 0; y < im.h; y++)
        {
            h = get_pixel(im, x, y, 0);
            s = get_pixel(im, x, y, 1);
            v = get_pixel(im, x, y, 2);
            hp = h * 360;
            if (s == 0)
            {
                r = g = b = v;
            }
            else
            {
                hp = hp / 60;
                int i = (int)hp;
                float C = hp - i;
                float X = v * (1 - s);
                float Y = v * (1 - s * C);
                float Z = v * (1 - s * (1 - C));
                switch (i)
                {
                case 0:
                    r = v;
                    g = Z;
                    b = X;
                    break;
                case 1:
                    r = Y;
                    g = v;
                    b = X;
                    break;
                case 2:
                    r = X;
                    g = v;
                    b = Z;
                    break;
                case 3:
                    r = X;
                    g = Y;
                    b = v;
                    break;
                case 4:
                    r = Z;
                    g = X;
                    b = v;
                    break;
                case 5:
                    r = v;
                    g = X;
                    b = Y;
                    break;
                }
            }
            set_pixel(im, x, y, 0, r);
            set_pixel(im, x, y, 1, g);
            set_pixel(im, x, y, 2, b);
        }
    }
} // 本函数参考了 https://baike.baidu.com/item/HSV%E9%A2%9C%E8%89%B2%E6%A8%A1%E5%9E%8B/21501482?fromtitle=HSV&fromid=547122

/*
20光电信息01 20202443 方立昊
遇到的主要问题：
1.对图像存储方式不清楚，通过‘速览定义’功能解决
2.对像素值范围不清楚，通过查阅文件、github解决
3.对变量类型不清楚，像素值应为float，使用int会损失精度，多次尝试以及阅读代码后解决
4.不了解rgb to hsv/hsv to rgb公式及算法，查阅资料后解决
*/