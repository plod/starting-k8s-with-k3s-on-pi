#include <string>
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <pistache/endpoint.h>

using namespace Pistache;

struct HelloHandler:
       	public Http::Handler 
{
  HTTP_PROTOTYPE(HelloHandler)

  void onRequest(const Http::Request&, Http::ResponseWriter writer) override
  {
    std::cout << "Handling request\n";

    const std::string hostname = getHostname();
    auto stream = writer.send(Http::Code::Ok,
           std::string{"Hello, World! From C++ @"} + hostname);
  }

private:
  std::string getHostname() const
  {
    std::vector<char> char_hostname(HOST_NAME_MAX, '\0');

    if (0 != gethostname(char_hostname.data(), HOST_NAME_MAX)) {
        std::cerr << "Error: couldn't get hostname, error: " << errno << '\n';
        throw std::runtime_error("Error: can't get hostname");
    }
    //POSIX.1 says that if such
    //truncation occurs, then it is unspecified whether the returned buffer
    //includes a terminating null byte.
    char_hostname[HOST_NAME_MAX-1] = '\0';

    return std::string{char_hostname.data()};
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
