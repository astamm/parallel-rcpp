//---------------------------------
#include <Rcpp.h>
#include <sitmo.h> // <1>

// [[Rcpp::depends(sitmo)]] // <2>

// [[Rcpp::export]]
Rcpp::NumericVector sumunif_sitmo(unsigned int n,
                                  unsigned int nstep,
                                  unsigned int seed)
{
  Rcpp::NumericVector out(n);
  sitmo::prng eng(seed); // <3>
  double mx = sitmo::prng::max(); // <4>
  double tmp = 0;

  for (unsigned int i = 0;i < n;++i)
  {
    tmp = 0.0;
    for (unsigned int k = 0;k < nstep;++k)
      tmp += eng() / mx; // <5>

    out[i] = tmp;
  }

  return out;
}
