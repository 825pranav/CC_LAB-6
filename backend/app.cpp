#include <iostream>
#include <cstdlib>

int main() {
    // We keep it simple because the Dockerfile handles the HTTP headers and ports
    // This identifies the container ID for your load balancing screenshots
    std::cout << "Served by backend: " << std::getenv("HOSTNAME") << std::endl;
    return 0;
}
