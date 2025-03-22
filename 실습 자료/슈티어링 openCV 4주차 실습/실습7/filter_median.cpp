#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void filter_median();

int main(void)
{
	filter_median();

	return 0;
}

void filter_median()
{
	Mat src = imread("../../../lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// src 영상에서 10%에 해당하는 픽셀 값을 0 또는 255로 설정
	int num = (int)(src.total() * 0.1);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i % 2) * 255;
	}

	// 표준 편차가 1인 가우시안 필터링을 수행하여 dst1에 저장
	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);

	// 크기가 3인 미디언 필터를 실행하여 dst2에 저장
	Mat dst2;
	medianBlur(src, dst2, 3);

	// src, dst1, dst2 영상을 모두 화면에 출력
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}