#include <Rcpp.h>

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppThread)]]
#include <RcppThread.h>

// [[Rcpp::export]]
std::vector<unsigned int> parallelforeach_example(unsigned int n)
{
  // Over elements of a vector
  std::vector<unsigned int> x(n);
  for (unsigned int i = 0;i < n;++i)
    x[i] = i;

  auto task = [] (unsigned int &xx) { // <1>
    xx *= 2;
  };

  RcppThread::parallelForEach(x, task); // <2>

  return x;
}
