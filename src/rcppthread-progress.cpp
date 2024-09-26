#include <Rcpp.h>

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppThread)]]
#include <RcppThread.h>

// [[Rcpp::export]]
void pb_example()
{
  // 20 iterations in loop, update progress every 1 sec
  RcppThread::ProgressBar bar(20, 1); // <1>
  RcppThread::parallelFor(0, 20, [&] (int i) { // <2>
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ++bar;
  });
}
