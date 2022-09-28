#pragma once
#include <iostream>

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <mutex>

#include <Consumer.h>

class FileLoader
{

public:
    FileLoader(std::shared_ptr<Consumer> _consumer) : consumer(_consumer) {}

    void LoadFile(const std::string& filename);
    void Run();
    void stop();

private:
    std::queue<std::string> m_Queue;
    std::shared_ptr<Consumer> consumer;
    std::mutex mx;
    bool finished = false;
};
