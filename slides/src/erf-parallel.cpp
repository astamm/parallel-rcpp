//---------------------------------
#include <Rcpp.h>

// [[Rcpp::depends(BH)]]
#include <boost/math/special_functions/erf.hpp>

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>

struct ErfFunctor : public RcppParallel::Worker { // <1>
  // Threadsafe wrapper around input vector
  const RcppParallel::RVector<double> m_InputVector; // <2>

  // Threadsafe wrapper around output vector
  RcppParallel::RVector<double> m_OutputVector; // <3>

  // initialize with input and output vectors
  ErfFunctor(const Rcpp::NumericVector input, Rcpp::NumericVector output)
    : m_InputVector(input), m_OutputVector(output) {} // <4>

  // function call operator that work for the specified range (begin/end)
  void operator()(std::size_t begin, std::size_t end) { // <5>
    for (unsigned int i = begin;i < end;++i) {
      m_OutputVector[i] = boost::math::erf(m_InputVector[i]);
    }
  }
};

// [[Rcpp::export]]
Rcpp::NumericVector erf_parallel_impl(Rcpp::NumericVector x) { // <6>
  Rcpp::NumericVector y(x.size());

  ErfFunctor erfFunctor(x, y);
  RcppParallel::parallelFor(0, x.size(), erfFunctor);

  return y;
}
