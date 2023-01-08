#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

#include "Process.h"

const float HueBaseColor[16] = {
    0, 
    1*22.5, 
    2*22.5, 
    3*22.5, 
    4*22.5, 
    5*22.5, 
    6*22.5, 
    7*22.5, 
    8*22.5, 
    9*22.5, 
    10*22.5, 
    11*22.5
};

const int32_t g_table[8][4] = {
    {  2,  8,   -2,   -8 },
    {  5, 17,   -5,  -17 },
    {  9, 29,   -9,  -29 },
    { 13, 42,  -13,  -42 },
    { 18, 60,  -18,  -60 },
    { 24, 80,  -24,  -80 },
    { 33, 106, -33, -106 },
    { 47, 183, -47, -183 }
};

int main(int argc, char* argv[]) 
{
    // -----------------------------------------------------------------------------------------------------
    // init 
    if (argc < 3) 
    {
        std::cout << "./HTC [INPUT] [OUTPUT]" << std::endl;
        return -1;
    }
    std::string input = argv[1];
    std::string output = argv[2];
    std::vector<uint8_t> src;
    std::vector<float> hsv_src;
    
    // read image data
    cv::Mat input_image = cv::imread(input.c_str());
    for(int j=0; j<input_image.rows; j++) 
    {
        for (int i=0; i<input_image.cols; i++) 
        {
            src.push_back((int)input_image.at<cv::Vec3b>(j,i)[2]); // red
            src.push_back((int)input_image.at<cv::Vec3b>(j,i)[1]); // green
            src.push_back((int)input_image.at<cv::Vec3b>(j,i)[0]); // blue
        }
    }

    std::cout << "src size = " << src.size() << std::endl;
    // convert RGB to HSV color space
    RGBtoHSV(src.data(), src.size(), hsv_src);
    std::vector<uint8_t> cvt_src;
    HSVtoRGB(hsv_src.data(), hsv_src.size(), cvt_src);

    for (int i=0; i<cvt_src.size(); i+=3) {
        uint8_t r = (int)(cvt_src[i + 0]);
        uint8_t g = (int)(cvt_src[i + 1]);
        uint8_t b = (int)(cvt_src[i + 2]);

        printf("r = %d\n", r);
        printf("g = %d\n", g);
        printf("b = %d\n", b);

        r = (int)(src[i + 0]);
        g = (int)(src[i + 1]);
        b = (int)(src[i + 2]);
        
        printf("=========================================================\n");
        printf("r = %d\n", r);
        printf("g = %d\n", g);
        printf("b = %d\n", b);
        printf("=========================================================\n");

        if (i > 9) break;
    }

        // ----------------------------------------------------------------------------------------------------- 
    // cv::imshow("window", image);
    // cv::waitKey();
    return 0;
}
