#pragma once
extern "C" {
	namespace OpenCV_Bridge
	{
		float Foopluginmethod();
		void GetRawImage(unsigned char *data, int width, int height);
	};
}

