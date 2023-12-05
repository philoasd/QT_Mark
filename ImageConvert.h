#pragma once

#include <QObject>
#include <QImage>
#include <pylon/PylonIncludes.h>
#include <opencv2/opencv.hpp>

class ImageConvert : public QObject
{
	Q_OBJECT

public:
	ImageConvert(QObject* parent);
	~ImageConvert();

	// 将Basler图像转换为QImage
	static QImage ConvertBalserToQImage(const Pylon::CGrabResultPtr& ptrGrabResult);

	// 将Mat图像转换为QImage
	static QImage ConverMatToQImage(cv::Mat& mat);

	// 将QImage转换为Mat图像
	static cv::Mat ConvertQImageToMat(QImage& image);
};
