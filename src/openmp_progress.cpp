#include <Rcpp.h>

// [[Rcpp::depends(BH)]]
#include <boost/math/special_functions/erf.hpp>

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>

// [[Rcpp::depends(RcppProgress)]]
#include <progress.hpp>
#include <progress_bar.hpp>

// [[Rcpp::export]]
Rcpp::NumericVector erf_omp(Rcpp::NumericVector x,
                            unsigned int ncores,
                            bool display_progress = false)
{
  unsigned int n = x.size();
  Rcpp::NumericVector out(n);
  Progress p(n, display_progress);

  RcppParallel::RVector<double> wo(out); // <1>
  RcppParallel::RVector<double> wx(x); // <2>

#ifdef _OPENMP
#pragma omp parallel for num_threads(ncores)
#endif
  for (unsigned int i = 0;i < n;++i)
  {
    if (!Progress::check_abort())
    {
      p.increment();
      wo[i] = boost::math::erf(wx[i]); // <3>
    }
  }

  return out;
}
