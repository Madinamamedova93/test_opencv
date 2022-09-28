#pragma once

#include <iostream>
#include <set>


class ImageSets
{
public:

    ImageSets(const std::string& path);

    std::string getCurrentFile();
    std::string getNextFile();
    std::string getPrevFile();

    std::string Imgpath;
    std::set<std::string> filenames;
    std::string currentFile;

    ~ImageSets() {}
};

