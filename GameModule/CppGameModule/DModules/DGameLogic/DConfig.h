#pragma once

#include <json/json.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "dl_pch.h"
#include "../DModules/DGenericLib/Singleton.h"

class DConfig : public DGeneric::Singleton<DConfig>
{
public:
    DGeneric::String cdn_ip;
    int server_port;
    DGeneric::String server_ip;
public:
    DConfig() {}
public:
    bool Load(DGeneric::String path) {
        // Sample JSON data
        std::string jsonData;
        std::ifstream inputFile;
        std::string filename, line;

        filename = path;

        inputFile.open(filename);

        if (!inputFile.is_open()) {
            std::cout << "Error opening file: " << filename << std::endl;
            return false;
        }

        std::cout << "Contents of the file:\n";
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
            jsonData.append(line);
        }

        inputFile.close();


        //..

        // Parsing JSON data
        Json::Value root;
        Json::CharReaderBuilder reader;
        Json::String errs;

        // Create a Json::StringStream from the jsonData
        std::istringstream jsonStream(jsonData);

        bool parsingSuccessful = Json::parseFromStream(reader, jsonStream, &root, &errs);

        if (!parsingSuccessful) {
            std::cout << "Failed to parse JSON: " << errs << std::endl;
            return false;
        }

        // Accessing JSON data
        cdn_ip = root["cdn_ip"].asString();
        server_ip = root["server_ip"].asString();
        server_port = root["server_port"].asInt();

        std::cout << "cdn_ip: " << cdn_ip << std::endl;
        std::cout << "server_ip: " << server_ip << std::endl;
        std::cout << "server_port: " << server_port << std::endl;

        return true;
    }
};

