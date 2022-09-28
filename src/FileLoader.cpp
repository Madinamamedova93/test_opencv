#include <FileLoader.h>
#include <iostream>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <mutex>
#include <condition_variable>

using namespace cv;

void FileLoader::LoadFile(const std::string& filename)
{
    std::unique_lock<std::mutex> lk(mx);
    m_Queue.push(filename);
}

void FileLoader::Run()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(mx);
        if (!m_Queue.empty())
        {
            cv::Mat img = cv::imread(m_Queue.front());
            consumer->AddImage(img);
            m_Queue.pop();

        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (finished) break;
    }
    
}

void FileLoader::stop()
{
    finished = true;
}