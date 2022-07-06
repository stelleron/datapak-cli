#include "datapak.hpp"
#include "logger.hpp"
#include <sys/stat.h>


int main(int argc, char** argv) {
    Logger::init();
    INFO("Hello World!");
}