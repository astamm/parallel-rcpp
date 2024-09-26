//---------------------------------
#include <Rcpp.h>

// [[Rcpp::depends(BH)]]
#include <boost/math/special_functions/erf.hpp>

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>

// [[Rcpp::plugin(openmp)]] // Remove `//` on Windows and Linux

// [[Rcpp::export]]
Rcpp::NumericVector erf_omp(Rcpp::NumericVector x, unsigned int ncores)
{
  unsigned int n = x.size();
  Rcpp::NumericVector out(n);

  RcppParallel::RVector<double> wo(out); // <1>
  RcppParallel::RVector<double> wx(x); // <2>

#ifdef _OPENMP
#pragma omp parallel for num_threads(ncores) // <3>
#endif
  for (unsigned int i = 0;i < n;++i)
    wo[i] = boost::math::erf(wx[i]); // <4>

  return out;
}
