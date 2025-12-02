#include "antenna-calc.h"



antenna_calc::antenna_calc(double _frequency_MHz)
{
    frequency_MHz = _frequency_MHz;
    quarter_dipole_element_lenght = (299.792458 / frequency_MHz) / 4.0;
}



antenna_calc::~antenna_calc()
{
}
