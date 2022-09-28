#include <iostream>
#include <set>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <algorithm>
#include <thread>

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>

#include <imageSet.h>
#include <FileLoader.h>
#include <Consumer.h>

using namespace std;
using namespace cv;
namespace fs = boost::filesystem;

/*class ImageSets
{
public:

    ImageSets(const std::string& path)
    {
        Imgpath = path;
        fs::directory_entry directory{ path };
        for (const auto& entry : fs::directory_iterator{ directory })
        {
            filenames.insert(entry.path().string());
        }
        currentFile = *(filenames.begin());
    }

    std::string getCurrentFile()
    {
        return currentFile;
    }

    std::string getNextFile()
    {
        auto it = filenames.find(currentFile);
        it++;
        if (it == filenames.end())
            it = filenames.begin();
        currentFile = *it;

        return currentFile;
    }

    std::string getPrevFile()
    {
        auto it = filenames.find(currentFile);
        if (it == filenames.begin())
            it = filenames.end();
        it--;
        currentFile = *it;

        return currentFile;
    }

    std::string Imgpath;
    std::set<std::string> filenames;
    std::string currentFile;

    ~ImageSets() {}
};


class Consumer
{
public:
    void AddImage(cv::Mat& image)
    {
        m_Queue.push(image);
    }

    void Run()
    {
        while (true)
        {
            if (!m_Queue.empty())
            {
                cv::Mat img = m_Queue.front();
                cv::imshow("consumer image", img);
                m_Queue.pop();
                key = cv::waitKeyEx();
                cout << "Key: " << key;
            }


        }
    }

    int getKey()
    {
        return key;
    }

    void resetKey()
    {
        key = 0;
    }

private:
    std::queue<cv::Mat> m_Queue;
    int key = 0;
};



class FileLoader
{

public:
    FileLoader(std::shared_ptr<Consumer> _consumer) : consumer(_consumer) {}

    void LoadFile(const std::string& filename)
    {
        m_Queue.push(filename);
    }

    void Run()
    {
        std::string filename;
        while (true)
        {
            if (!m_Queue.empty())
            {
                cv::Mat img = cv::imread(m_Queue.front());
                consumer->AddImage(img);
                m_Queue.pop();

            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }


private:
    std::queue<std::string> m_Queue;
    std::shared_ptr<Consumer> consumer;
};*/


int main(int argc, char* argv[])
{

    if (argc > 1)
    {
        ImageSets imgSt(argv[1]);

        auto consumer = std::make_shared<Consumer>();
        auto fileLoader = std::make_shared<FileLoader>(consumer);

        std::thread loaderThread([&fileLoader]() -> void {fileLoader->Run(); });
        std::thread consumerThread([&consumer]() -> void {consumer->Run(); });

        fileLoader->LoadFile(imgSt.getCurrentFile());

        while (true)
        {
            int key = consumer->getKey();

            if (key == 2555904)
            {
                cout << ">> " << endl;
                fileLoader->LoadFile(imgSt.getNextFile());
                consumer->resetKey();
            }
            else if (key == 2424832)
            {
                fileLoader->LoadFile(imgSt.getPrevFile());
                consumer->resetKey();
            }
            else if (key == 56778)
            {
                fileLoader->stop();
                consumer->stop();
            }

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        loaderThread.join();

        consumerThread.join();
        cout << "join" << endl;

        cv::destroyAllWindows();
    }
    else {
        std::cout << "Not arguments" << std::endl;
        return 0;
    }

    return 0;

}
