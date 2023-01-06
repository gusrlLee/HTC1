#include <iostream>
#include <vector>
#include <cmath>

void RGBtoHSV(uint8_t* src, int size, std::vector<float> &out) 
{
    for (int i=0; i<size; i+=3) {
        // R, G, B values are divided by 255
        // to change the range from 0..255 to 0..1
        float r = (*src) / 255.0;
        src++;
        float g = (*src) / 255.0;
        src++;
        float b = (*src) / 255.0;
        src++;
    
        // h, s, v = hue, saturation, value
        float cmax = std::max({r, g, b}); // maximum of r, g, b
        float cmin = std::min({r, g, b}); // minimum of r, g, b
        float diff = cmax - cmin; // diff of cmax and cmin.
        float h = -1, s = -1;
    
        // if cmax and cmax are equal then h = 0
        if (cmax == cmin)
            h = 0;
    
        // if cmax equal r then compute h
        else if (cmax == r)
            h = fmod(60 * ((g - b) / diff) + 360, 360);
    
        // if cmax equal g then compute h
        else if (cmax == g)
            h = fmod(60 * ((b - r) / diff) + 120, 360);
    
        // if cmax equal b then compute h
        else if (cmax == b)
            h = fmod(60 * ((r - g) / diff) + 240, 360);
    
        // if cmax equal zero
        if (cmax == 0)
            s = 0;
        else
            s = (diff / cmax);
    
        float v = cmax;

        out.push_back(h/360.0f);
        out.push_back(s);
        out.push_back(v);

    }
}

void HSVtoRGB()
{

}
