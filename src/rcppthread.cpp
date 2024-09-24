#include <Rcpp.h>


// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppThread)]]
#include <RcppThread.h>

// [[Rcpp::export]]
std::vector<unsigned int> rcpp_thread_example2() {
  RcppThread::ThreadPool pool(3);

  unsigned int n = 100;

  std::vector<unsigned int> x(n);
  for (unsigned int i = 0;i < n;++i)
    x[i] = i;

  auto task = [&x] (unsigned int i) {
    return x[i] * x[i];
  };

  std::vector<std::future<unsigned int>> futures(n);
  for (unsigned int i = 0;i < n;++i)
    futures[i] = pool.pushReturn(task, i);

  std::vector<unsigned int> results(100);
  for (unsigned int i = 0;i < n;++i)
    results[i] = futures[i].get();

  pool.join();

  return results;
}
