
#include <Consumer.h>

#include <iostream>
#include <set>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>


void Consumer::AddImage(cv::Mat& image)
{
    std::unique_lock<std::mutex> lk(mx);
    m_Queue.push(image);
}

void Consumer::Run()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(mx);
        if (!m_Queue.empty())
        {
            cv::Mat img = m_Queue.front();
            cv::imshow("consumer image", img);
            m_Queue.pop();
            key = cv::waitKeyEx();
        }

        if (finished) break;
    }
}

void Consumer::stop()
{
    finished = true;
}

int Consumer::getKey()
{
    return key;
}

void Consumer::resetKey()
{
    key = 0;
}
