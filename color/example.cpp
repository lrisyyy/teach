// 引入OpenCV头文件，用来处理图片
#include <opencv2/opencv.hpp>
// 引入输入输出头文件，用来打印提示文字
#include <iostream>
// 引入vector，用来存放拆分出来的图片通道
#include <vector>

// 简化写法，后面不用每次都写cv::、std::
using namespace cv;
using namespace std;

int main()
{
    // ---------------------- 第一步：读取图片 ----------------------
    // 图片放在 color/img/test.jpg
    // 我们在build文件夹运行程序，../ 代表回到上一级（color文件夹）
    Mat src_img = imread("../img/bd7fe7ee54507801f55134c84526e8cf.jpg");

    // 判断：如果图片是空的，说明没读到图片
    if (src_img.empty())
    {
        cout << "错误：图片读取失败！检查文件名、路径！" << endl;
        // 程序直接结束
        return -1;
    }
    cout << "图片读取成功！" << endl;


    // ---------------------- 第二步：设置色彩增益参数 ----------------------
    // 是你之前选好的参数：R=1.30  G=0.63  B=1.20
    // OpenCV里图片通道顺序是 B  G  R，一定要记牢！
    float gain_B = 1.01f;   // 蓝色通道放大倍数
    float gain_G = 0.63f;   // 绿色通道放大倍数（压低绿色）
    float gain_R = 1.07f;   // 红色通道放大倍数


    // ---------------------- 第三步：把图片转成浮点型，防止计算溢出 ----------------------
    // CV_32FC3：3个通道、浮点数格式，方便小数相乘调色
    Mat float_img;
    src_img.convertTo(float_img, CV_32FC3);


    // ---------------------- 第四步：拆分B、G、R三个通道 ----------------------
    vector<Mat> channel_list;
    split(float_img, channel_list);
    // channel_list[0] = B 蓝色
    // channel_list[1] = G 绿色
    // channel_list[2] = R 红色


    // ---------------------- 第五步：分别调色（乘增益系数） ----------------------
    channel_list[0] = channel_list[0] * gain_B;
    channel_list[1] = channel_list[1] * gain_G;
    channel_list[2] = channel_list[2] * gain_R;


    // ---------------------- 第六步：把调好的三个通道合并回去 ----------------------
    Mat corrected_float;
    merge(channel_list, corrected_float);


    // ---------------------- 第七步：限制像素范围0~255 ----------------------
    // 调色之后数值可能超过255或者小于0，会发白发黑，要截断
    corrected_float = max(corrected_float, 0.0f);
    corrected_float = min(corrected_float, 255.0f);

    // 转回普通图片格式 8位uchar，才能保存和显示
    Mat result_img;
    corrected_float.convertTo(result_img, CV_8UC3);


    // ---------------------- 第八步：保存处理后的图片 ----------------------
    // 输出到color文件夹下，名字叫 out.jpg
    imwrite("../out.jpg", result_img);
    cout << "调色完成！图片已经保存为 out.jpg" << endl;


    // ---------------------- 第九步：显示原图和效果图（Wayland可能弹不出窗口） ----------------------
    imshow("原图", src_img);
    imshow("色彩校正之后", result_img);

    // 等待按下任意按键，窗口才关闭
    waitKey(0);
    // 销毁所有图片窗口
    destroyAllWindows();


    return 0;
}
