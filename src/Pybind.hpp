#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <cstdint>

#include "xqboard.hpp"
#include "utils.hpp"

void registerPy(pybind11::module &m);
