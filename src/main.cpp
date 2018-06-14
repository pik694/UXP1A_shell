#include <sys/stat.h>
#include <fstream>
#include <fcntl.h>
#include <zconf.h>
#include <memory>
#include <shell/ui/Controller.hpp>

int main(int argc, char** argv) {
    shell::ui::Controller::getInstance().start();
}
