#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void noise_gaussian();

int main(void)
{
	noise_gaussian();

	return 0;
}

void noise_gaussian()
{
	// lenna.bmp 파일을 그레이스케일 형식으로 불러와 src에 저장
	Mat src = imread("../../../lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	// 표준 편차 stddev 값이 10, 20, 30이 되도록 for 반복문을 수행
	for (int stddev = 10; stddev <= 30; stddev += 10) {

		// 평균이 0이고 표준 편차가 stddev인 가우시안 잡음을 생성하여 noise 행렬에 저장
		// noise 행렬은 부호 있는 정수형(CV_32SC1)을 사용하도록 미리 생성하여 randn() 함수에 전달
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, stddev);

		// 입력 영상 src에 가우시안 잡음 noise를 더하여 결과 영상 dst를 생성
		// dst 영상의 깊이는 CV_8U로 설정
		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);

		String desc = format("stddev = %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}