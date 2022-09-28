#pragma once

#include <iostream>
#include <queue>
#include <opencv2/core.hpp>


using namespace cv;

class Consumer
{
public:
    void AddImage(cv::Mat& image);
    void Run();
    int getKey();
    void resetKey();
    void stop();

private:
    std::queue<cv::Mat> m_Queue;
    int key = 0;
    std::mutex mx;
    bool finished = false;
};