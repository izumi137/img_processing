#include "Func.h"

double PI = 3.14;

template<typename T>
T saturate_cast(double value) {
	if (value > std::numeric_limits<T>::max()) return std::numeric_limits<T>::max();
	else if (value < std::numeric_limits<T>::min()) return std::numeric_limits<T>::min();
	//T a = std::numeric_limits<T>::min();
	//T b = std::numeric_limits<T>::max();
	//std::cout << a;
	return static_cast<T>(value);
}


template<typename T>
void insertionSort(T *arr, int n)
{
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

template<typename T>
T median(T* arr, int n)
{
	insertionSort(arr, n);
	return arr[(n + 1) / 2];
}

int Func::rbg2gray(const cv::Mat& srcImage, cv::Mat& dstImage)
{
	if (srcImage.empty()) return 0;
	
	int height = srcImage.rows;
	int width = srcImage.cols;
	dstImage = cv::Mat(height, width, CV_8UC1);

	int nSrcChannels = srcImage.channels();
	int nDstChannels = dstImage.channels();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			uchar blue = srcImage.at<cv::Vec3b>(y, x)[0];
			uchar green = srcImage.at<cv::Vec3b>(y, x)[1];
			uchar red = srcImage.at<cv::Vec3b>(y, x)[2];
			dstImage.at<uchar>(y, x) = saturate_cast<uchar>(blue * 0.11 + green * 0.59 + red * 0.3);
		}

			
	}
	return 1;
}



int Func::brightness(const cv::Mat& srcImage, cv::Mat& dstImage, int c)
{
	if (srcImage.empty()) return 0;

	int height = srcImage.rows;
	int width = srcImage.cols;
	int Channels = srcImage.channels();
	dstImage = cv::Mat(height, width, CV_8UC3);
	

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			for (int z = 0; z < Channels; z++)
			{
				cv::Vec3b values = srcImage.at<cv::Vec3b>(y, x);
				/*dstImage.at<cv::Vec3b>(y, x)[0] = saturate_cast<uchar>(static_cast<double>(values[0]) + c);
				dstImage.at<cv::Vec3b>(y, x)[1] = saturate_cast<uchar>(static_cast<double>(values[1]) + c);
				dstImage.at<cv::Vec3b>(y, x)[2] = saturate_cast<uchar>(static_cast<double>(values[2]) + c);*/
				dstImage.at<cv::Vec3b>(y, x)[z] = saturate_cast<uchar>(static_cast<double>(values[z]) + c);
			}
				

	//cv::Mat(srcImage.rows, srcImage.cols, CV_8UC3);

	//dstImage = srcImage + c;
	return 1;
}

int Func::constrast(const cv::Mat& srcImage, cv::Mat& dstImage, int c)
{
	if (srcImage.empty()) return 0;

	int height = srcImage.rows;
	int width = srcImage.cols;
	int Channels = srcImage.channels();
	dstImage = srcImage.clone();


	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			for (int z = 0; z < Channels; z++)
			{
				cv::Vec3b values = srcImage.at<cv::Vec3b>(y, x);
				/*dstImage.at<cv::Vec3b>(y, x)[0] = saturate_cast<uchar>(static_cast<double>(values[0]) * c);
				dstImage.at<cv::Vec3b>(y, x)[1] = saturate_cast<uchar>(static_cast<double>(values[1]) * c);
				dstImage.at<cv::Vec3b>(y, x)[2] = saturate_cast<uchar>(static_cast<double>(values[2]) * c);*/
				dstImage.at<cv::Vec3b>(y, x)[z] = saturate_cast<uchar>(static_cast<double>(values[z]) * c);
			}
	//dstImage = srcImage * c;
	return 1;
}

int Func::avg(const cv::Mat& srcImage, cv::Mat& dstImage, int k)
{
	if (srcImage.empty()) return 0;

	dstImage = srcImage.clone();	
	if (k % 2 == 0 || k <= 0)
	{
		std::cout << "k must be an odd number";
		return 1;
	}
	int height = srcImage.rows;
	int width = srcImage.cols;
	int Channels = srcImage.channels();

	

	if (k == 1) return 1;
	int n = (int)(k / 2);

	for (int y = n; y < height-n; y++)
	{
		for (int x = n; x < width-n; x++)
			for (int z = 0; z < Channels; z++)
			{
				int tmp = 0;
				//cv::Vec3b values = srcImage.at<cv::Vec3b>(y, x);
				for (int i = y - n; i < y + n + 1; i++)
				{
					for (int j = x - n; j < x + n + 1; j++)
					{
						tmp += srcImage.at<cv::Vec3b>(i, j)[z];
						//int check = tmp;
					}
					//std::cout << std::endl;
				}
				//uchar check2 = saturate_cast<uchar>((double(tmp / k / k)));
				dstImage.at<cv::Vec3b>(y, x)[z] = saturate_cast<uchar>((double (tmp/k/k)));
			}
	}
	return 1;
}

int Func::med(const cv::Mat& srcImage, cv::Mat& dstImage, int k)
{
	if (srcImage.empty()) return 0;

	dstImage = srcImage.clone();
	if (k % 2 == 0 || k <= 0)
	{
		std::cout << "k must be an odd number";
		return 1;
	}
	int height = srcImage.rows;
	int width = srcImage.cols;
	int Channels = srcImage.channels();


	if (k == 1) return 1;
	int n = (int)(k / 2);

	for (int y = n; y < height - n; y++)
	{
		for (int x = n; x < width - n; x++)
			for (int z = 0; z < Channels; z++)
			{
				uchar *value_arr = new uchar[k*k];
				int count = 0;
				for (int i = y - n; i < y + n + 1; i++)
				{
					for (int j = x - n; j < x + n + 1; j++)
					{
						value_arr[count] = srcImage.at<cv::Vec3b>(i, j)[z];
						count++;
					}
				}
				dstImage.at<cv::Vec3b>(y, x)[z] = saturate_cast<uchar>((double)median(value_arr, k * k));
			}
	}
	return 1;
}


cv::Mat gaussianKernel(int size, double sigma) {
	cv::Mat kernel(size, size, CV_64F);
	double sum = 0.0;
	int halfSize = size / 2;

	for (int y = -halfSize; y <= halfSize; ++y) 
	{
		for (int x = -halfSize; x <= halfSize; ++x) 
		{
			double r2 = x * x + y * y;
			double s = 2.0 * sigma * sigma;
			double value = std::exp(-r2 / s) / (2 * CV_PI * sigma);
			kernel.at<double>(y + halfSize, x + halfSize) = value;
			sum += value;
		}
	}

	// Normalize the kernel
	kernel /= sum;

	return kernel;
}

cv::Mat normalize(cv::Mat src)
{
	double sum = 0;
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			sum += src.at<double>(y, x);
	//std::cout << "check sum: " << sum << std::endl;
	return src/sum;
}


int Func::gau(const cv::Mat& srcImage, cv::Mat& dstImage, int k)
{
	if (srcImage.empty()) return 0;

	dstImage = srcImage.clone();
	if (k % 2 == 0 || k <= 0)
	{
		std::cout << "k must be an odd number";
		return 1;
	}
	int height = srcImage.rows;
	int width = srcImage.cols;
	int Channels = srcImage.channels();

	double sigma = 1.0;
	cv::Mat kernel = gaussianKernel(k, sigma);
	kernel = normalize(kernel);
		

	if (k == 1) return 1;
	int n = (int)(k / 2);

	for (int y = n; y < height - n; y++)
	{
		for (int x = n; x < width - n; x++)
			for (int z = 0; z < Channels; z++)
			{
				double sum = 0.0;
				for (int i = -n; i <= n; i++)
					for (int j = -n; j <= n; j++)
						sum += srcImage.at<cv::Vec3b>(y + i, x + j)[z] * kernel.at<double>(i + n, j + n);
					dstImage.at<cv::Vec3b>(y, x)[z] = saturate_cast<uchar>((double)sum);
			}
	}
	return 1;
}

int Func::sobel(const cv::Mat& srcImage, cv::Mat& dstImage)
{
	// Sobel kernels
	double sobelKernelX[3][3] = {{-1, 0, 1},
								{-2, 0, 2},
								{-1, 0, 1}};

	double sobelKernelY[3][3] = {{-1, -2, -1},
								{ 0,  0,  0},
								{ 1,  2,  1}};
	int n = 1;
	
	//cv::Mat gray;
	rbg2gray(srcImage, dstImage);

	cv::Mat dx = dstImage.clone(), dy = dstImage.clone();
	
	for (int y = n; y < srcImage.rows - n; y++)
		for (int x = n; x < srcImage.cols - n; x++)
		{
			double xvalue = 0;
			double yvalue = 0;
			for (int i  = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
				{
					xvalue += dstImage.at<uchar>(y + i, x + j) * sobelKernelX[i + 1][j + 1];
					yvalue += dstImage.at<uchar>(y + i, x + j) * sobelKernelY[i + 1][j + 1];
				}
			
			dx.at<uchar>(y, x) = saturate_cast<uchar>(xvalue);
			dy.at<uchar>(y, x) = saturate_cast<uchar>(yvalue);
		}

	double max = 0;
	for (int y = 0; y < dstImage.rows - n; y++)
		for (int x = 0; x < dstImage.cols - n; x++)
		{
			double xvalue = dx.at<uchar>(y, x);
			double yvalue = dy.at<uchar>(y, x);
			uchar value = saturate_cast<uchar>(std::sqrt(xvalue * xvalue + yvalue * yvalue));
			dstImage.at<uchar>(y, x) = value;
			if (max < value)
				max = value;
		}
	
	for (int y = 0; y < dstImage.rows - n; y++)
		for (int x = 0; x < dstImage.cols - n; x++)
		{
			uchar value = dstImage.at<uchar>(y, x);
			if (value > max * 0.15)
				dstImage.at<uchar>(y, x) = value;
			else
				dstImage.at<uchar>(y, x) = 0;
		}

	return 1;
}

int Func::laplace(const cv::Mat& srcImage, cv::Mat& dstImage)
{

	rbg2gray(srcImage, dstImage);
	cv::Mat gray = dstImage.clone();
	double laplacianKernel[3][3] = { {-1,  -1, -1},
									{-1, 8, -1},
									{-1,  -1, -1} };
	int n = 1;
	for (int y = n; y < srcImage.rows - n; y++)
		for (int x = n; x < srcImage.cols - n; x++)
		{
			double value = 0;
			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
				{
					value += gray.at<uchar>(y + i, x + j) * laplacianKernel[i + 1][j + 1];
				}

			dstImage.at<uchar>(y, x) = saturate_cast<uchar>(value);
		}

	return 1;
}
