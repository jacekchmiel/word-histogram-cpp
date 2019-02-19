#include "cli.h"
#include "WordStore.h"

#include <iostream>
#include <fstream>

int main(int ac, char* av[]) {
    auto args = Args::from_commandline(ac, av);
    if(args) {
        std::ifstream s;
        s.open(args->file);
        WordStore store;
        store.consume_stream(s);
        store.print_summary(10);
    }

}
