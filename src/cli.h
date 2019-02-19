#pragma once

#include <iostream>

using namespace::std;

struct Args {
    std::string file = "input";

    /// Returns nullptr if args were not created during parsing command line
    /// (e.g. in case of `help`). Could have safer interface here (e.g. Option).
    static Args* from_commandline(int ac, char* av[]);
};

