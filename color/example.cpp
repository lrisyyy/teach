#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // 把题目给的绿调图片重命名为 green.jpg，放到代码同一目录
    Mat src = imread("green.jpg");
    if (src.empty())
    {
        cout << "图片读取失败！检查文件名和路径" << endl;
        return -1;
    }

    // 拆分BGR三个通道
    vector<Mat> channels;
    split(src, channels);
    Mat B = channels[0];
    Mat G = channels[1];
    Mat R = channels[2];

    // 校正系数，可以肉眼微调
    G *= 0.65;   // 压低过强的绿色
    R *= 1.20;   // 提升红色
    B *= 1.15;   // 提升蓝色

    // 合并通道得到校正后的图片
    vector<Mat> new_channels;
    new_channels.push_back(B);
    new_channels.push_back(G);
    new_channels.push_back(R);
    Mat dst;
    merge(new_channels, dst);

    // 窗口显示原图 & 结果
    imshow("原图(偏绿)", src);
    imshow("色彩校正后", dst);

    // 保存输出图片
    imwrite("correct_result.jpg", dst);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
