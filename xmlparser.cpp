#include "xmlparser.h"


using namespace tinyxml2;
using namespace std;
xmlParser::xmlParser()
{
    XMLDocument doc;
    doc.SaveFile( "foo.xml" );
}

int xmlParser::createXML()
{

    tinyxml2::XMLDocument doc;
    //1.添加声明
    tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration();
    doc.InsertFirstChild(declaration);

    //2.创建根节点
    tinyxml2::XMLElement* root = doc.NewElement("commands");
    doc.InsertEndChild(root);

    //3.创建子节点
    tinyxml2::XMLElement* childNodeCom = doc.NewElement("command");
    tinyxml2::XMLElement* childNodeDescription = doc.NewElement("description");
    //tinyxml2::XMLElement* childNodeTeaGender = doc.NewElement("gender");

    //4.为子节点增加内容
    tinyxml2::XMLText* contentStu = doc.NewText("start");
    childNodeCom->InsertFirstChild(contentStu);

    tinyxml2::XMLText* contentDescription = doc.NewText("start PLC");
    childNodeDescription->InsertFirstChild(contentDescription);

    //tinyxml2::XMLText* contentGender = doc.NewText("man");
    //childNodeTeaGender->InsertFirstChild(contentGender);

    //5.为子节点增加属性
    //childNodeStu->SetAttribute("Name", "libai");

    root->InsertEndChild(childNodeCom);//childNodeStu是root的子节点
    root->InsertEndChild(childNodeDescription);//childNodeTea是root的子节点
    //childNodeDescription->InsertEndChild(childNodeTeaGender);//childNodeTeaGender是childNodeTea的子节点
    return doc.SaveFile("school.xml");
    //6.保存xml文件
}
