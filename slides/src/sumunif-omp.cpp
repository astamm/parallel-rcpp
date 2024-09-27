//---------------------------------
#include <Rcpp.h>
#include <sitmo.h>

// // [[Rcpp::plugins(openmp)]] // Uncomment on Windows and Linux

#ifdef _OPENMP
#include <omp.h> // <1>
#endif

// [[Rcpp::depends(sitmo)]]

// [[Rcpp::export]]
Rcpp::NumericVector sumunif_sitmo_omp(unsigned int n,
                                      unsigned int nstep,
                                      Rcpp::IntegerVector seeds) // <2>
{
  Rcpp::NumericVector out(n);

  unsigned int ncores = seeds.size(); // <3>

#ifdef _OPENMP
#pragma omp parallel num_threads(ncores) // <4>
{
#endif
  unsigned int seed = seeds[0]; // <5>

#ifdef _OPENMP
  seed = seeds[omp_get_thread_num()]; // <6>
#endif

  sitmo::prng eng(seed);
  double mx = sitmo::prng::max();
  double tmp = 0;

#ifdef _OPENMP
#pragma omp for // <7>
#endif
  for (unsigned int i = 0;i < n;++i)
  {
    tmp = 0.0;
    for (unsigned int k = 0;k < nstep;++k)
      tmp += eng() / mx;

    out[i] = tmp;
  }

#ifdef _OPENMP
} // <8>
#endif

return out;
}
