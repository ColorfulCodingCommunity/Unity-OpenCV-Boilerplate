// OpenCV_Bridge_Windows_Dll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;


extern "C" float __declspec(dllexport) __stdcall Foopluginmethod() {
	cv::Mat img(10, 10, CV_8UC1);
	return img.rows * 1.0f;
}

extern "C" void __declspec(dllexport) __stdcall GetRawImage(unsigned char * data, int width, int height) {
	cv::Mat texture(height, width, CV_8UC4, data);
	//cv::cvtColor(texture, texture, cv::COLOR_BGRA2RGB);
	cv::cvtColor(texture, texture, cv::COLOR_BGRA2GRAY);
	cv::cvtColor(texture, texture, cv::COLOR_GRAY2RGBA);
	std::memcpy(data, texture.data, texture.total() * texture.elemSize());
}
