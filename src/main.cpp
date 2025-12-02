#include <iostream>
#include <getopt.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "antenna-calc.h"

static void print_usage(const char* prog) {
    std::cout << "Usage: " << prog << " [options]\n"
              << "  -h, --help            Show this help message\n"
              << "  -v, --verbose         Verbose output\n"
              << "  -o, --output FILE     Write output to FILE (default stdout)\n"
              << "  -f, --freq FREQUENCY  Frequency in MHz (default 403.7)\n";
}

int main(int argc, char** argv)
{
    const char* short_opts = "hvo:f:"; // note: 'f' takes an argument
    static struct option long_opts[] = {
        {"help",    no_argument,       nullptr, 'h'},
        {"verbose", no_argument,       nullptr, 'v'},
        {"output",  required_argument, nullptr, 'o'},
        {"freq",    required_argument, nullptr, 'f'},
        {nullptr, 0, nullptr, 0}
    };

    bool verbose = false;
    std::string output_path;
    double frequency_mhz = 403.7; // default

    int opt;
    int opt_index = 0;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, &opt_index)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;
            case 'v':
                verbose = true;
                break;
            case 'o':
                output_path = optarg;
                break;
            case 'f': {
                std::istringstream iss(optarg);
                if (!(iss >> frequency_mhz)) {
                    std::cerr << "Invalid frequency: " << optarg << "\n";
                    return 1;
                }
                break;
            }
            case '?': // unknown option
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    // Any remaining positional argument could be used as an input file
    std::string input_positional;
    if (optind < argc) {
        input_positional = argv[optind];
        if (verbose) std::cout << "Positional argument: " << input_positional << "\n";
    }

    antenna_calc antenna(frequency_mhz);
    double element_length_m = antenna.get_element_length();

    std::ostringstream out;
    out << "Antenna calculation:\n";
    out << "  Frequency (MHz): " << frequency_mhz << "\n";
    if (!input_positional.empty()) out << "  Input: " << input_positional << "\n";
    out << "  Di-pole element length: " << (element_length_m * 100.0) << " cm\n";

    if (verbose) {
        out << "  (verbose) internal element length meters: " << element_length_m << "\n";
    }

    if (!output_path.empty()) {
        std::ofstream ofs(output_path);
        if (!ofs) {
            std::cerr << "Failed to open output file: " << output_path << "\n";
            return 1;
        }
        ofs << out.str();
        if (verbose) std::cout << "Wrote output to " << output_path << "\n";
    } else {
        std::cout << out.str();
    }

    return 0;
}
