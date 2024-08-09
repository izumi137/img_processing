#pragma once
#include "libs.h"
class Func
{
public:
	int rbg2gray(const cv::Mat& srcImage, cv::Mat& dstImage);
	int brightness(const cv::Mat& srcImage, cv::Mat& dstImage, int c);
	int constrast(const cv::Mat& srcImage, cv::Mat& dstImage, int c);
	int avg(const cv::Mat& srcImage, cv::Mat& dstImage, int k);
	int med(const cv::Mat& srcImage, cv::Mat& dstImage, int k);
	int gau(const cv::Mat& srcImage, cv::Mat& dstImage, int k);
	int sobel(const cv::Mat& srcImage, cv::Mat& dstImage);
	int laplace(const cv::Mat& srcImage, cv::Mat& dstImage);
};

