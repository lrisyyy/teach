#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "无法打开摄像头" << endl;
        return -1;
    }

    cv::Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        cv::imshow("camera", frame);
        if (cv::waitKey(1) == 27) // 按ESC退出
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
