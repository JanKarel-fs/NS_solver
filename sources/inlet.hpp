#ifndef INLET_HPP
#define INLET_HPP

#include "../geometry/vector.hpp"
#include "../compressible.hpp"
#include "settings.hpp"
#include <cmath>

using namespace std;

Compressible inlet(const Compressible& wInside, const Vector2d& s, const Settings& setting);

#endif
