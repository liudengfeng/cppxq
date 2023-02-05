#include <pybind11/pybind11.h>

#include "Pybind.hpp"

PYBIND11_MODULE(xqcpp, m)
{
  registerPy(m);
}