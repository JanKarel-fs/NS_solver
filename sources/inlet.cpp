#include "inlet.hpp"

Compressible inlet(const Compressible& wInside, const Vector2d& s, const Settings& setting) {
  const double& p0 = settings.p0;
  const double& rho0 = settings.rho0;
  const double& kappa = Compressible::kappa;

  double p = wInside.p();

  double rho = rho0 * pow(p/p0, 1./kappa);
  double Ma = std::sqrt(2./(kappa-1.) * (pow(p/p0, (1.-kappa)/kappa) - 1.));
  double a = std::sqrt(kappa * p / rho);

  double rhoU_magnitude = rho * Ma * a;

  double rhou = rhoU_magnitude * cos(setting.alpha);
  double rhov = rhoU_magnitude * sin(setting.alpha);

  double e = p / (kappa - 1.) + 0.5 * (rhou*rhou + rhov*rhov)/rho;

  return Compressible(rho, Vector2d(rhou, rhov), e);  
}
