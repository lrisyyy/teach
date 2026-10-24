#include <opencv2/opencv.hpp>
#include <iostream>

// 封装 myCamera 类
class myCamera
{
public:
    // 公有成员：只有【构造函数、析构函数、read函数】
    // 构造函数：打开摄像头
    myCamera()
    {
        // 双系统自适应：Windows和Ubuntu都用0号设备
        cap_.open(0);
        if (!cap_.isOpened())
        {
            std::cerr << "摄像头打开失败！" << std::endl;
        }
    }

    // 析构函数：程序结束自动释放摄像头资源
    ~myCamera()
    {
        if (cap_.isOpened())
        {
            cap_.release();
        }
        cv::destroyAllWindows();
    }

    // read函数：读取一帧画面，参数传出去图像
    bool read(cv::Mat &frame_)
    {
        return cap_.read(frame_);
    }

private:
    // 私有变量！名字必须以下划线 _ 结尾
    cv::VideoCapture cap_;
};


int main()
{
    // 创建摄像头对象，自动调用构造函数打开摄像头
    myCamera cam;

    cv::Mat frame_;
    while (true)
    {
        // 调用read读画面
        if (!cam.read(frame_))
        {
            std::cerr << "读取画面失败" << std::endl;
            break;
        }

        // 显示画面
        cv::imshow("Camera", frame_);

        // ESC键退出
        int key = cv::waitKey(1);
        if (key == 27)
        {
            break;
        }
    }

    return 0;
}
