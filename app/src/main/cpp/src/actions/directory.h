#pragma once

#include <vector>
#include <memory>
#include "asio2/asio2.hpp"

struct directory {
    std::vector<std::string> dirs;
};

struct DirectoryContent {
    bool isDir;
    std::string uri;
    std::uint64_t timestamp;
};

std::shared_ptr<directory> directory_parse_from_request(http::web_request& req);

std::shared_ptr<std::map<std::string, std::vector<DirectoryContent>>> directory_get_content(std::string& webroot, std::shared_ptr<directory>);

std::string directory_generate_response(std::shared_ptr<std::map<std::string, std::vector<DirectoryContent>>>);
