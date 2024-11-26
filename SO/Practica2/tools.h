

#pragma once;

#include <iostream>
#include <string>
#include <fstream>
#include <expected>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string_view>
#include <errno.h>


void show_help();
std::expected<std::string_view, int> read_all(const std::string& path);
ErrorCode parse_args(int argc, char *argv[]);

