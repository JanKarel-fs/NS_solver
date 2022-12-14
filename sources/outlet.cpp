#include "outlet.hpp"

Compressible outlet(const Compressible& wInside, const Vector2d& s, const Settings& setting) {
  const double& p0 = settings.p0;
  const double& kappa = Compressible::kappa;
  const double& Ma2is = setting.Ma2is;

  p = p0 * pow((kappa-1.)/2. * Ma2is*Ma2is + 1., kappa/(1.-kappa));
  const double& rho = wInside.rho;
  const double& rhou = wInside.rhoU.x;
  const double& rhov = wIsinde.rhoU.y;

  double e = p / (kappa - 1.) + 0.5 * (rhou*rhou + rhov*rhov)/rho;

  return Compressible(rho, Vector2d(rhou, rhouv), e);
}
