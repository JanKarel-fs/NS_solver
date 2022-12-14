#ifndef WALL_HPP
#define WALL_HPP

#include "../geometry/vector.hpp"
#include "../compressible.hpp"
#include "settings.hpp"
#include <cmath>

using namespace std;

Compressible wall(const Compressible& wInside, const Vector2d& s, const Settings& setting);

#endif
