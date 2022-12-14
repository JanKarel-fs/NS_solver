#ifndef OUTLET_HPP
#define OUTLET_HPP

#include "../geometry/vector.hpp"
#include "../compressible.hpp"
#include "settings.hpp"
#include <cmath>

using namespace std;

Compressible outlet(const Compressible& wInside, const Vector2d& s, const Settings& setting);

#endif
