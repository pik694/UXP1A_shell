#include <sys/stat.h>
#include <fstream>
#include <fcntl.h>
#include <zconf.h>
#include <memory>

using namespace shell::ui;

int main(int argc, char** argv) {
    Controller::getInstance().start();
}
