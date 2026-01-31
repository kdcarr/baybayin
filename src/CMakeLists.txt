find_package(cli11 REQUIRED)
include(utils)
executable(norm norm.cpp "include/utils.h" "CLI11::CLI11;baybayin-core")
executable(tl tl.cpp "include/utils.h" "CLI11::CLI11;baybayin-core")