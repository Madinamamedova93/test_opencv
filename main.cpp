#include <iostream>
#include <thread>

#include <imageSet.h>
#include <FileLoader.h>
#include <Consumer.h>

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;


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
