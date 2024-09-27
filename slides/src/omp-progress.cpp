//---------------------------------
#include <Rcpp.h>

// // [[Rcpp::plugins(openmp)]] // Uncomment on Windows and Linux

// [[Rcpp::depends(BH)]]
#include <boost/math/special_functions/erf.hpp>

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>

// [[Rcpp::depends(RcppProgress)]] // <1>
#include <progress.hpp> // <2>
#include <progress_bar.hpp>

// [[Rcpp::export]]
Rcpp::NumericVector erf_omp_progress(Rcpp::NumericVector x,
                                     unsigned int ncores,
                                     bool display_progress = false) // <3>
{
  unsigned int n = x.size();
  Rcpp::NumericVector out(n);
  Progress p(n, display_progress); // <4>

  RcppParallel::RVector<double> wo(out);
  RcppParallel::RVector<double> wx(x);

#ifdef _OPENMP
#pragma omp parallel for num_threads(ncores)
#endif
  for (unsigned int i = 0;i < n;++i)
  {
    if (!Progress::check_abort()) // <5>
    {
      p.increment(); // <6>
      wo[i] = boost::math::erf(wx[i]);
    }
  }

  return out;
}
