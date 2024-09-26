//---------------------------------
#include <Rcpp.h>

// [[Rcpp::depends(BH)]] // <1>
#include <boost/math/special_functions/erf.hpp> // <2>

// [[Rcpp::export]]
Rcpp::NumericVector erf_cpp(Rcpp::NumericVector x) {
  Rcpp::NumericVector y(x.size());

  for (int i = 0; i < x.size(); i++) {
    y[i] = boost::math::erf(x[i]); // <3>
  }

  return y;
}
