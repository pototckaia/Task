#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <set>


//Необходимо вывести на экран информацию о каждом url в формате
//Protocol: по умолчанию "http"
// Host: по умолчанию "localhost"
// Port: по умолчанию "80"
// Page: по умолчанию "/"


// <url> ::= [<protocol> "://"] [<hostname>[":" <port>]] ["/" <path>]

//<protocol> ::= <alpha> *[<alpha> | <digit> | "+" | "." | "-"]
// <hostname> ::=  *[ <domain> "." ] <top> [ "." ]
// <domain> ::=  <alphanum>
//               | <alphanum> *[ <alphanum> | "-" ] <alphanum>
//<top> ::=  <alpha> | <alpha> *[ <alphanum> | "-" ] <alphanum>
//<port> ::= <digits>

bool isdigits(const std::string &s) {
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

struct Url {
    std::string protocol, hostName, port, path, href;
};

void printUrl(Url &url) {
    std::cout
            << "String: " << url.href << std::endl
            << "Protocol: " << url.protocol << std::endl
            << "Host: " << url.hostName << std::endl
            << "Port: " << url.port << std::endl
            << "Path: " << url.path << std::endl
            << std::endl;
}

void printUrlStructure(std::string &s) {
    Url url;
    url.protocol = "http";
    url.hostName = "localhost";
    url.port = "80";
    url.path = "/";
    url.href = s;

    if (s.empty()) {
        printUrl(url);
        return;
    }

    std::size_t startOfStr = 0;
    auto delProtocolHost = s.find("://", startOfStr);
    if (!delProtocolHost) {
        throw std::logic_error("Error: :// in start url");
    }

    if (delProtocolHost != std::string::npos) {
        url.protocol = s.substr(startOfStr, delProtocolHost);
        startOfStr = delProtocolHost + 3;
    }

    auto delHostPath = s.find('/', startOfStr);
    if (delHostPath == std::string::npos) {
        delHostPath = s.size();
    }

    if (s.size() - delHostPath > 1) { // path size
        url.path = s.substr(delHostPath + 1);
    }

    auto host = s.substr(startOfStr, delHostPath - startOfStr);
    if (!host.empty()) {
        auto delHostNamePort = host.find(':');
        if (delHostNamePort != std::string::npos) {
            auto port = host.substr(delHostNamePort + 1);
            if (port.empty() || !isdigits(port)) {
                throw std::logic_error("Port isn't number: " + port);
            }
            url.port = port;
            url.hostName = host.substr(0, delHostNamePort);
        } else {
            url.hostName = host;
        }
    }


    printUrl(url);

}


int main(int argc, char **argv) {
    std::vector<std::string> urls = {
            "http://mytona.com/index.html",
            "https://mytona.com:8080/",
            "mytona.com",
            "https://example.com:8080",
            "ws://travel.travel:80/bar",
            "https://localhost/a/b/c/d/e/f/g/j/1/d/4/",
            "127.0.0.1:3340",
            "/",
            "/@3rd-Eden",
            "xn--n3h.com:844/fav.ico",
            "sub.sub.sub.domain.nl//foo.bar/foo",
            "/bar",
            "test.test.test:8333",
            "file:///home/cheri/Рабочий%20стол/url.html"};

    for (auto &e: urls) {
        try {
            printUrlStructure(e);
        } catch (std::logic_error &e) {
            std::cout << e.what() << std::endl;
        }
    }

}