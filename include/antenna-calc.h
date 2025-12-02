#pragma once

class antenna_calc{

private:
    double  frequency_MHz;
    float   quarter_dipole_element_lenght;

public:
    antenna_calc(double _frequency_MHz);
    ~antenna_calc();

    float get_element_length(void){ return quarter_dipole_element_lenght; }
};
