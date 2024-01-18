#include "HttpServer.h"
#include "nlohmann/json.hpp"
#include "actions/directory.h"
#include "resources/res.h"
#include "base64.h"

HttpServer::~HttpServer() {
    stop();
}

int HttpServer::open(std::string root, std::uint16_t port) {
    if (running_ || http_server_)
        return 0;

    this->root_ = root;
    this->port_ = port;

    http_server_ = std::make_shared<asio2::http_server>();

    if (!http_server_)
        return -1;

    http_server_->set_root_directory(this->root_);

    return 0;
}

int HttpServer::start() {
    if (running_ && http_server_)
        return 0;

    if (!http_server_)
        return -1;

    http_server_->bind<http::verb::get, http::verb::post>("/@!/api/v10/directory", [this](http::web_request& req, http::web_response& rep)
    {
        set_cors(req, rep);
        auto directory = directory_parse_from_request(req);
        if (!directory || directory->dirs.empty()) {
            rep.fill_page(bho::beast::http::status::bad_request);
        }

        auto content = directory_get_content(root_, directory);

        auto response = directory_generate_response(content);

        rep.fill_json(response);
    });

    http_server_->bind<http::verb::delete_>("/@!/api/v10/directory", [](http::web_request& req, http::web_response& rep)
    {
        asio2::ignore_unused(req, rep);
        set_cors(req, rep);
        rep.fill_html(http::status::not_implemented);
    });

    http_server_->bind<http::verb::delete_>("/@!/api/v10/file", [](http::web_request& req, http::web_response& rep)
    {
        asio2::ignore_unused(req, rep);
        set_cors(req, rep);
        rep.fill_html(http::status::not_implemented);
    });

    http_server_->bind<http::verb::get>("/@!/webroot/*", [](http::web_request& req, http::web_response& rep)
    {
        asio2::ignore_unused(req, rep);
        set_cors(req, rep);
        rep.fill_html(http::status::not_implemented);
    });

    http_server_->bind<http::verb::get>("/", [](http::web_request& req, http::web_response& rep)
    {
        asio2::ignore_unused(req, rep);
        set_cors(req, rep);

        rep.fill_html(index_html);
    });
    http_server_->bind<http::verb::get>("/@!/assets/index.js", [](http::web_request& req, http::web_response& rep)
    {
        asio2::ignore_unused(req, rep);
        set_cors(req, rep);

        std::string js_data = base64_decode(index_js, true);

        rep.fill_html(js_data, http::status::ok, "application/javascript");
    });
    http_server_->bind<http::verb::get>("/@!/assets/index.css", [](http::web_request& req, http::web_response& rep)
    {
        asio2::ignore_unused(req, rep);
        set_cors(req, rep);

        rep.fill_html(index_css, http::status::ok, "text/css; charset=UTF-8");
    });
    http_server_->bind<http::verb::get>("/@!/storage.svg", [](http::web_request& req, http::web_response& rep)
    {
        asio2::ignore_unused(req, rep);
        set_cors(req, rep);

        rep.fill_html(svg_file);
    });

    http_server_->bind<http::verb::options>("*", [](http::web_request& req, http::web_response& rep)
    {
        asio2::ignore_unused(req, rep);
        set_cors(req, rep);
    });

    // If no method is specified, GET and POST are both enabled by default.
    http_server_->bind("*", [](http::web_request& req, http::web_response& rep)
    {
        rep.fill_file(http::url_decode(req.target()));
        rep.chunked(true);
    });

    http_server_->bind_not_found([](http::web_request& req, http::web_response& rep)
                          {
                              asio2::ignore_unused(req);

                              rep.fill_page(http::status::not_found);
                          });

    std::string ipv4_listen_host = "0.0.0.0";
    http_server_->start(ipv4_listen_host, port_);

    running_ = true;

    return 0;
}

int HttpServer::stop() {
    if (http_server_) {
        http_server_->stop();
        http_server_ = nullptr;
    }
    running_ = false;
    return 0;
}
