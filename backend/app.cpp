
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>

int main() {
    // This header tells the browser to display the text instead of downloading a file
    std::cout << "HTTP/1.1 200 OK\r\n";
    std::cout << "Content-Type: text/html\r\n";
    std::cout << "Connection: close\r\n\r\n";
    
    // This will show the Container ID so you can see the load balancing happen
    std::cout << "<html><body><h1>Served by Backend ID: " << std::getenv("HOSTNAME") << "</h1></body></html>" << std::endl;
    return 0;
}
    
    // Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "ERROR: Failed to create socket" << std::endl;
        return 1;
    }
    
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Bind to port 8080
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "ERROR: Failed to bind to port 8080" << std::endl;
        return 1;
    }
    
    if (listen(server_fd, 10) < 0) {
        std::cerr << "ERROR: Failed to listen on port 8080" << std::endl;
        return 1;
    }
    
    std::cout << "Server listening on port 8080 (hostname: " << hostname << ")" << std::endl;
    
    // Accept connections in loop
    while(true) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) continue;
        
        // Simple HTTP response
        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/plain\r\n";
        response += "Connection: close\r\n\r\n";
        response += "Served by backend: " + std::string(hostname) + "\n";
        
        send(client_fd, response.c_str(), response.length(), 0);
        close(client_fd);
    }
    
    return 0;
}
