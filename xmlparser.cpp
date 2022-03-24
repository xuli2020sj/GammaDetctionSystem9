#include "xmlparser.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace tinyxml2;
using namespace std;
xmlParser::xmlParser()
{
}

int xmlParser::createXML()
{

    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    spdlog::set_level(spdlog::level::info); // Set global log level to debug
    spdlog::debug("This message should be displayed..");


    auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
    spdlog::get("basic_logger")->info("xxxxxx");
    logger->warn("文件记录");



    tinyxml2::XMLDocument doc;
    tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration("控制指令列表");
    doc.InsertFirstChild(declaration);
    root = doc.NewElement("commands");

    addCmd(doc);
    doc.InsertEndChild(root);
    return doc.SaveFile("cmdQueue.xml");
    //6.保存xml文件
}

void xmlParser::addCmd(XMLDocument& doc)
{
    XMLElement* childNodeCmd = doc.NewElement("command");
    childNodeCmd->SetAttribute("Index", "001");
    root->InsertEndChild(childNodeCmd);

    XMLElement* childNodeDescription = doc.NewElement("description");
    XMLText* contentDescription = doc.NewText("start Axis");
    childNodeDescription->InsertEndChild(contentDescription);
    childNodeCmd->InsertEndChild(childNodeDescription);


    XMLElement* childNodeInfoX = doc.NewElement("XInfo");
    XMLText* childNodeCmdInfoX = doc.NewText("P500 S10");
    childNodeInfoX->InsertFirstChild(childNodeCmdInfoX);
    childNodeCmd->InsertEndChild(childNodeInfoX);


    XMLElement* childNodeInfoY = doc.NewElement("yInfo");
    XMLText* childNodeCmdInfoY = doc.NewText("P500 S10");
    childNodeInfoY->InsertFirstChild(childNodeCmdInfoY);
    childNodeCmd->InsertEndChild(childNodeInfoY);

    XMLElement* childNodeInfoZ = doc.NewElement("zInfo");
    XMLText* childNodeCmdInfoZ = doc.NewText("P500 S10");
    childNodeInfoZ->InsertFirstChild(childNodeCmdInfoZ);
    childNodeCmd->InsertEndChild(childNodeInfoZ);

    XMLElement* childNodeInfoDetector = doc.NewElement("DetectorInfo");
    XMLText* childNodeCmdInfoDetector = doc.NewText("100");
    childNodeInfoDetector->InsertFirstChild(childNodeCmdInfoDetector);
    childNodeCmd->InsertEndChild(childNodeInfoDetector);
}

void xmlParser::addCmd(tinyxml2::XMLDocument& doc, std::string& xInfo, std::string& yInfo, std::string& zInfo,
            std::string& DecInfo) {
    XMLElement* childNodeCmd = doc.NewElement("command");
    childNodeCmd->SetAttribute("Index", "001");
    root->InsertEndChild(childNodeCmd);

    XMLElement* childNodeDescription = doc.NewElement("description");
    XMLText* contentDescription = doc.NewText("start Axis");
    childNodeDescription->InsertEndChild(contentDescription);
    childNodeCmd->InsertEndChild(childNodeDescription);


    XMLElement* childNodeInfoX = doc.NewElement("XInfo");
    XMLText* childNodeCmdInfoX = doc.NewText(xInfo.c_str());
    childNodeInfoX->InsertFirstChild(childNodeCmdInfoX);
    childNodeCmd->InsertEndChild(childNodeInfoX);


    XMLElement* childNodeInfoY = doc.NewElement("yInfo");
    XMLText* childNodeCmdInfoY = doc.NewText(yInfo.c_str());
    childNodeInfoY->InsertFirstChild(childNodeCmdInfoY);
    childNodeCmd->InsertEndChild(childNodeInfoY);

    XMLElement* childNodeInfoZ = doc.NewElement("zInfo");
    XMLText* childNodeCmdInfoZ = doc.NewText(zInfo.c_str());
    childNodeInfoZ->InsertFirstChild(childNodeCmdInfoZ);
    childNodeCmd->InsertEndChild(childNodeInfoZ);

    XMLElement* childNodeInfoDetector = doc.NewElement("DetectorInfo");
    XMLText* childNodeCmdInfoDetector = doc.NewText(DecInfo.c_str());
    childNodeInfoDetector->InsertFirstChild(childNodeCmdInfoDetector);
    childNodeCmd->InsertEndChild(childNodeInfoDetector);
}


