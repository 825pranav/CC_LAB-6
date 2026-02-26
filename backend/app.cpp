#include <iostream>
#include <cstdlib>

int main() {
    // The Dockerfile handles the HTTP headers and the port.
    // This simply prints the container ID for your load balancing task.
    std::cout << "Served by backend: " << std::getenv("HOSTNAME") << std::endl;
    return 0;
}
