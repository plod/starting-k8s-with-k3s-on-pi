#include <string>
#include <iostream>
#include <pistache/endpoint.h>
#include <unistd.h>
#include <limits.h>

using namespace Pistache;

struct HelloHandler:
       	public Http::Handler 
{
  HTTP_PROTOTYPE(HelloHandler)

  void onRequest(const Http::Request&, Http::ResponseWriter writer) override
  {
    char char_hostname[HOST_NAME_MAX];
    gethostname(char_hostname, HOST_NAME_MAX);
    std::string hostname(char_hostname);
    std::cout << "Handling request\n";
    writer.send(Http::Code::Ok, "Hello, World! From C++ @" +  hostname);
  }
};

int main(int argc, const char* argv[]) 
{
  ulong port = 8080;
  if (2 == argc) {
    if (0 == std::strcmp(argv[1], "--help")) {
      std::cout << "Usage:\n\t";
      std::cout << argv[0] << " [port]\n\n";
      exit(0);
    }
    else {
      port = std::stoul(argv[1]);
    }
  }

  std::cout << "Starting server at port " << port << '\n';
  Http::listenAndServe<HelloHandler>(Pistache::Address(Ipv4::any(), port));
}