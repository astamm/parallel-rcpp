#include <Rcpp.h>

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppThread)]]
#include <RcppThread.h>

// [[Rcpp::export]]
std::vector<unsigned int> rcpp_thread_example1(unsigned int n,
                                               unsigned int ncores)
{
  RcppThread::ThreadPool pool(ncores); // <1>
  std::vector<unsigned int> x(n);
  auto task = [&x] (unsigned int i) { x[i] = i; }; // <2>
  for (unsigned int i = 0;i < x.size();++i)
    pool.push(task, i); // <3>
  pool.join(); // <4>
  return x;
}
