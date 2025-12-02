#include <iostream>

#include "antenna-calc.h"



int main(int argc, char** argv)
{
    // Example usage of the antenna_calc class
    antenna_calc antenna(403.7); // Create an instance with 100 MHz frequency

    std::cout << "Di-pole elements length: " << antenna.get_element_length() * 100 << "cm" << std::endl;

    return 0;
}
