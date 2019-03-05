#include "OpenCV_Bridge.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "OpenCV_Bridge", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "OpenCV_Bridge", __VA_ARGS__))

extern "C" {
	float OpenCV_Bridge::Foopluginmethod() {
		cv::Mat img(10, 10, CV_8UC1);
		return img.rows * 1.0f;
	}

	void OpenCV_Bridge::GetRawImage(unsigned char * data, int width, int height){
		cv::Mat texture(height, width, CV_8UC4, data);
		//cv::cvtColor(texture, texture, cv::COLOR_BGRA2RGB);
		cv::cvtColor(texture, texture, cv::COLOR_BGRA2GRAY);
		cv::cvtColor(texture, texture, cv::COLOR_GRAY2RGBA);
		std::memcpy(data, texture.data, texture.total() * texture.elemSize());
	}
}
