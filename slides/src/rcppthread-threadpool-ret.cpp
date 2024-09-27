#include <Rcpp.h>

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppThread)]]
#include <RcppThread.h>

// [[Rcpp::export]]
std::vector<unsigned int> rcpp_thread_example2(unsigned int n,
                                               unsigned int ncores)
{
  RcppThread::ThreadPool pool(ncores);

  std::vector<unsigned int> x(n); // <1>
  for (unsigned int i = 0;i < n;++i)
    x[i] = i + 1;

  auto task = [&x] (unsigned int i) { // <2>
    return x[i] * x[i];
  };

  std::vector<std::future<unsigned int>> futures(n); // <3>
  for (unsigned int i = 0;i < n;++i)
    futures[i] = pool.pushReturn(task, i);

  std::vector<unsigned int> results(n); // <4>
  for (unsigned int i = 0;i < n;++i)
    results[i] = futures[i].get();

  pool.join(); // <5>

  return results;
}
