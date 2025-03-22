#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void filter_bilateral();

int main(void)
{
	filter_bilateral();

	return 0;
}

void filter_bilateral()
{
	Mat src = imread("../../../lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 그레이스케일 레나 영상 src에 평균이 0이고 표준 편차가 5인 가우시안 잡음 추가
	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);
	add(src, noise, src, Mat(), CV_8U);

	// 표준 편차가 5인 가우시안 필터링을 수행하여 dst1에 저장
	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	// 색 공간의 표준 편차는 10, 좌표 공간의 표준 편차는 5를 사용하는 양방향 필터링을 수행하여 dst2에 저장
	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);

	// src, dst1, dst2 영상을 모두 화면에 출력
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}