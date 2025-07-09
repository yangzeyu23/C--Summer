#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <getopt.h>
#include "server.h"
#include "module.h"

void print_usage() {
    std::cout << "Usage: ./server_main --address <address> --port <port> [options]\n"
              << "Options:\n"
              << "  -a, --address <address>   Server address (default: localhost)\n"
              << "  -p, --port <port>         Server port (default: 8008)\n"
              << "  -h, --help                Show this help message\n"
              << "  -m, --modir <modir>       Service module directory\n"
              << "  -v, --verbose              Verbose output\n";
}

int main(int argc, char* argv[]) {
    const char* address = "localhost";
    uint16_t port = 8008;
    int opt;

    while ((opt = getopt(argc, argv, "a:h:m:p:v")) != -1) {
        switch (opt) {
            case 'a':
                address = optarg;
                break;
            case 'p':
                port = static_cast<uint16_t>(std::stoi(optarg));
                break;
            case 'h':
                print_usage();
                return 0;
            case 'm':
                // Handle module directory option
                break;
            case 'v':
                // Enable verbose output
                break;
            default:
                print_usage();
                return EXIT_FAILURE;
        }
    }

    // Start the server
    struct in_addr local_address;
    inet_aton(address, &local_address);
    server_run(local_address, port);

    return 0;
}