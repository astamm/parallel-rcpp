#include <Rcpp.h>

// [[Rcpp::plugins(cpp11)]] // <1>
// [[Rcpp::depends(RcppThread)]] // <2>
#include <RcppThread.h> // <3>

// [[Rcpp::export]]
void pyjamaParty()
{
  auto job = [] (int id) { // <4>
    std::this_thread::sleep_for(std::chrono::seconds(1));
    RcppThread::Rcout << id << " slept for one second" << std::endl;
    RcppThread::checkUserInterrupt();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    RcppThread::Rcout << id << " slept for another second" << std::endl;
  };
  RcppThread::Thread t1(job, 1); // <5>
  RcppThread::Thread t2(job, 2);
  t1.join(); // <6>
  t2.join();
}
