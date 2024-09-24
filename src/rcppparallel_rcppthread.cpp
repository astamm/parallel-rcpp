#include <Rcpp.h>

// [[Rcpp::depends(BH)]]
#include <boost/math/special_functions/erf.hpp>

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>

// [[Rcpp::plugins(cpp14)]]
// [[Rcpp::depends(RcppThread)]]
#include <RcppThread.h>

struct ErfFunctor : public RcppParallel::Worker { // <1>
  // Threadsafe wrapper around input vector
  const RcppParallel::RVector<double> m_InputVector; // <2>

  // Threadsafe wrapper around output vector
  RcppParallel::RVector<double> m_OutputVector; // <3>

  RcppThread::ProgressBar *m_ProgressBar;

  // initialize with input and output vectors
  ErfFunctor(const Rcpp::NumericVector input,
             Rcpp::NumericVector output,
             RcppThread::ProgressBar *pb = NULL)
    : m_InputVector(input), m_OutputVector(output), m_ProgressBar(pb) {} // <4>

  // function call operator that work for the specified range (begin/end)
  void operator()(std::size_t begin, std::size_t end) { // <5>
    for (unsigned int i = begin;i < end;++i) {
      RcppThread::checkUserInterrupt();
      if (m_ProgressBar != NULL)
        m_ProgressBar++;
      m_OutputVector[i] = boost::math::erf(m_InputVector[i]);
    }
  }
};

// [[Rcpp::export]]
Rcpp::NumericVector erf_parallel(Rcpp::NumericVector x,
                                 bool display_progress = false) { // <6>
  unsigned int n = x.size();
  Rcpp::NumericVector y(n);
  RcppThread::ProgressBar pb(n, 1);
  ErfFunctor erfFunctor(x, y, &pb);
  RcppParallel::parallelFor(0, n, erfFunctor);
  return y;
}
