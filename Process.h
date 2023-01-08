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

void HSVtoRGB(float* src, int size, std::vector<uint8_t> &out) 
{
    int i;
    double f, p, q, t;
    double r = 0, g = 0, b=0;

    for (int n=0; n<size; n+=3) 
    {
        float H = (int)(*src * 360.0f);
        src++;
        float S = *src;
        src++;
        float V = *src;
        src++;

        if ( S == 0 ) 
        {
            r = V;
            g = V;
            b = V;
        }
        else
        {
            if (H == 360)
                H = 0;
            else 
                H = H / 60;

            i = (int)trunc(H);
            f = H - i;
            
            p = V * (1.0 - S);
            q = V * (1.0 - (S * f));
            t = V * (1.0 - (S * (1.0 - f)));

            switch (i)
            {
                case 0:
                    r = V;
                    g = t;
                    b = p;
                    break;

                case 1:
                    r = q;
                    g = V;
                    b = p;
                    break;

                case 2:
                    r = p;
                    g = V;
                    b = t;
                    break;

                case 3:
                    r = p;
                    g = q;
                    b = V;
                    break;

                case 4:
                    r = t;
                    g = p;
                    b = V;
                    break;

                default:
                    r = V;
                    g = p;
                    b = q;
                    break;
            }
            out.push_back((uint8_t)(r*255.0f));
            out.push_back((uint8_t)(g*255.0f));
            out.push_back((uint8_t)(b*255.0f));
        }
    }
}
