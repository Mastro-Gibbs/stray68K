#include "help.hpp"

#include <Wt/Http/Response.h>
#include <Wt/Utils.h>

#include <fstream>

HelpSection::HelpSection()
{

}


HelpSection::~HelpSection()
{
    beingDeleted();
}


void HelpSection::handleRequest(const Wt::Http::Request &request,
                             Wt::Http::Response &response)
{
    response.setMimeType("text/html");

    std::ifstream inputFile("template/xmls/help.xml");

    if (inputFile.is_open()) 
    {
        std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

        response.out() << fileContent;
        inputFile.close();
    }

    
}