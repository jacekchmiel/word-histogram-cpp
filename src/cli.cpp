#include "cli.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;
using namespace std;

Args* Args::from_commandline(int ac, char *av[]){
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("file", po::value<string>(), "data file to process")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
    }

    Args* args = new Args();

    if (vm.count("file")) {
        args->file = vm["file"].as<string>();
    } else {
        cout << "Using default input file: " << args->file << endl;
    }

    return args;
}
