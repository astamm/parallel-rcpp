//---------------------------------
#include <Rcpp.h>

// [[Rcpp::depends(RcppParallel)]] // <1>
#include <RcppParallel.h> // <2>

// [[Rcpp::export]]
Rcpp::IntegerVector transformVector(Rcpp::IntegerVector x) {
  RcppParallel::RVector<int> input(x); // <3>
  Rcpp::IntegerVector y(x.size()); // <4>
  RcppParallel::RVector<int> output(y); // <5>

  // <6>

  return y; // <7>
}
