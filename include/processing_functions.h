#ifndef EVM_CPP_H
#define EVM_CPP_H

#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
Video processing functions
*/

// Color Magnification
int amplify_spatial_Gdown_temporal_ideal(string inFile, string outDir, double alpha, int level, 
	double fl, double fh, int samplingRate, double chromAttenuation);

// Motion Magnification
int amplify_spatial_lpyr_temporal_butter(string inFile, string outDir, double alpha, double lambda_c,
	double fl, double fh, int samplingRate, double chromAttenuation);

int amplify_spatial_lpyr_temporal_ideal(string inFile, string outDir, double alpha, double lambda_c, 
    double fl, double fh, double samplingRate, double chromAttenuation);

int amplify_spatial_lpyr_temporal_iir(string inFile, string outDir, double alpha, double lambda_c, 
    double r1, double r2, double chromAttenuation); // --NOT WORKING--

/*
Spatial filter functions
*/

vector<Mat> build_GDown_stack(vector<Mat> video_array, int startIndex, int endIndex, int level);

// vector<Mat> buildPyramidGpu(Mat frame, int maxlevel);

int maxPyrHt(int frameWidth, int frameHeight, int filterSizeX, int filterSizeY);

vector<vector<Mat>> build_Lpyr_stack(vector<Mat> video_array, int startIndex, int endIndex, int level);

vector<Mat> buildLpyrfromGauss(Mat image, int levels);

Mat reconLpyr(vector<Mat> pyr);

/*
Temporal filter functions
*/

vector<Mat> ideal_bandpassing(vector<Mat> input, int dim, double wl, double wh, int samplingRate);

vector<vector<Mat>> ideal_bandpassing_lpyr(vector<vector<Mat>>& input, int dim, double wl, double wh, double samplingRate);

#endif /* EVM_CPP_H */