#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "tinyxml2.h"
#include <iostream>
#include <string.h>

#include "include/spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"



class xmlParser
{
private:
    tinyxml2::XMLElement* root;
    int index;
public:
    xmlParser();

    int createXML();
    void addCmd(tinyxml2::XMLDocument& doc);
    void addCmd(tinyxml2::XMLDocument& doc, std::string& xInfo, std::string& yInfo, std::string& zInfo,
                std::string& DecInfo);
};

#endif // XMLPARSER_H
