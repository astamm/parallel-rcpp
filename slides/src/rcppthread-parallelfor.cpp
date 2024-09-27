#include <Rcpp.h>

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppThread)]]
#include <RcppThread.h>

// [[Rcpp::export]]
std::vector<unsigned int> parallelfor_example(unsigned int n)
{
  // Index-based
  std::vector<unsigned int> x(n);

  auto task = [&x] (unsigned int i) {
    x[i] = i;
  };

  RcppThread::parallelFor(0, x.size(), task); // <1>

  return x;
}
