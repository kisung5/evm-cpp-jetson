#ifndef IM_CONV_H
#define IM_CONV_H

#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat im2double(Mat A);

Mat im2uint8(Mat A);

Mat rgb2ntsc(Mat A);

Mat ntsc2rgb(Mat A);

#endif /* IM_CONV_H */