#include "nlohmann/json.hpp"
#include <filesystem>
#include <iostream>
#include "directory.h"
#include "../log.h"

using json = nlohmann::json;
using namespace std::filesystem;

std::shared_ptr<directory> directory_parse_from_request(http::web_request& req) {
    std::shared_ptr<directory> result = std::make_shared<directory>();

    auto body = req.body();
    try {
        json j = json::parse(body);

        auto dirs = j["dirs"];
        for (const auto& d : dirs) {
            result->dirs.push_back(d);
            break; //TODO NOT support multi dir request now
        }
    }
    catch (const std::exception& e)
    {
        return nullptr;
    }

    return result;
}

std::shared_ptr<std::map<std::string, std::vector<DirectoryContent>>> directory_get_content(std::string& webroot, std::shared_ptr<directory> dirs) {
    if (!dirs)
        return nullptr;

    auto result = std::make_shared<std::map<std::string, std::vector<DirectoryContent>>>();
    try {
        std::filesystem::path p1(webroot);
        for (const auto& d : dirs->dirs) {
            std::vector<DirectoryContent> contents;

            std::filesystem::path p2(d);
            std::filesystem::path full_path = p1 / p2;

            directory_entry entry(full_path);		//文件入口
            if (entry.status().type() == file_type::directory)	//这里用了C++11的强枚举类型
                std::cout << "该路径是一个目录" << std::endl;

            directory_iterator list(full_path);	        //文件入口容器
            for (auto& it:list) {
                //std::filesystem::path uri= p2 / it.path().filename().string();
                DirectoryContent dc = {it.is_directory(), it.path().filename().string(), 0};
                contents.emplace_back(dc);
            }

            result->insert(std::pair<std::string, std::vector<DirectoryContent>>(d, contents));

        }
    }
    catch (const std::exception& e)
    {
        LOGE("exception: %s", e.what());
        return nullptr;
    }


    return result;
}

std::string directory_generate_response(std::shared_ptr<std::map<std::string, std::vector<DirectoryContent>>> dirs) {
    if (!dirs)
        return "";

    json j;
    for (const auto& item : *dirs) {
        j["data"]["directory_name"] = item.first;
        for (const auto& u : item.second) {
            j["data"]["items"].push_back({{"uri", u.uri},
                                          {"isDir", u.isDir}});
        }
    }

    return to_string(j);
}

void set_cors(http::web_request& req, http::web_response& rep) {
    rep.set("Access-Control-Allow-Headers", "Content-Type");
    rep.set("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    rep.set("Access-Control-Max-Age", "3600");
    rep.set("Access-Control-Allow-Origin", "*");
}