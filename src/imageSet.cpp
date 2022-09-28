#include "imageSet.h"

#include <iostream>
#include <queue>
#include <fstream>
#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

ImageSets::ImageSets(const std::string &path)
{
    Imgpath = path;
    fs::directory_entry directory{ path };
    for (const auto& entry : fs::directory_iterator{ directory })
    {
        filenames.insert(entry.path().string());
    }
    currentFile = *(filenames.begin());
}

std::string ImageSets::getCurrentFile()
{
    return currentFile;
}

std::string ImageSets::getNextFile()
{
    auto it = filenames.find(currentFile);
    it++;
    if (it == filenames.end())
        it = filenames.begin();
    currentFile = *it;

    return currentFile;
}

std::string ImageSets::getPrevFile()
{
    auto it = filenames.find(currentFile);
    if (it == filenames.begin())
        it = filenames.end();
    it--;
    currentFile = *it;

    return currentFile;
}