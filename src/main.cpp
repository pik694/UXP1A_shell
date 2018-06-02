#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <fcntl.h>
#include <zconf.h>


int main(int argc, char** argv) {

    if (fork()) {
        int a;
        std::cin >> a;
        std::cout << "Parent: " << a << std::endl;
    }
    else {
        int a;
        std::cin >> a;
        std::cout << "child: "<< a << std::endl;
    }

    return 0;
}