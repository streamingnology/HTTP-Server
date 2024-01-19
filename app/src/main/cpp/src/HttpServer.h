#pragma once
#include <string>
#include <cstdint>
#include "asio2/asio2.hpp"
#include <memory>

class HttpServer {
public:
    explicit HttpServer() {}
    ~HttpServer();

    HttpServer(const HttpServer&) = delete;
    HttpServer(HttpServer&&) = delete;
    HttpServer& operator=(const HttpServer&) = delete;
    HttpServer& operator=(HttpServer&&) = delete;

    int open(std::string root, std::uint16_t port);

    int start();

    int stop();

private:
    void set_cors(http::web_request& req, http::web_response& rep);

private:
    bool running_ {false};
    std::string root_ {"/sdcard/"};
    std::uint16_t port_ {8989};
    std::shared_ptr<asio2::http_server> http_server_ {nullptr};
};

