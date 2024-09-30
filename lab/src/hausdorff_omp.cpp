#include "hausdorff_utils.h"

// // [[Rcpp::plugins(openmp)]] // Uncomment on Windows and Linux

Rcpp::NumericVector dist_omp(Rcpp::NumericMatrix x,
                             unsigned int dimension = 1,
                             unsigned int ncores = 1)
{
  unsigned int N = x.nrow();
  unsigned int K = N * (N - 1) / 2;
  Rcpp::NumericVector out(K);
  RcppParallel::RMatrix<double> xSafe(x);
  RcppParallel::RVector<double> outSafe(out);

#ifdef _OPENMP
#pragma omp parallel for num_threads(ncores)
#endif
  for (unsigned int k = 0;k < K;++k)
  {
    unsigned int i = N - 2 - std::floor(std::sqrt(-8 * k + 4 * N * (N - 1) - 7) / 2.0 - 0.5);
    unsigned int j = k + i + 1 - N * (N - 1) / 2 + (N - i) * ((N - i) - 1) / 2;
    outSafe[k] = hausdorff_distance_cpp(xSafe.row(i), xSafe.row(j), dimension);
  }

  out.attr("Size") = N;
  out.attr("Labels") = Rcpp::seq(1, N);
  out.attr("Diag") = false;
  out.attr("Upper") = false;
  out.attr("method") = "hausdorff";
  out.attr("class") = "dist";
  return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector dist_omp(Rcpp::List x,
                             unsigned int dimension = 1,
                             unsigned int ncores = 1)
{
  Rcpp::NumericMatrix xMatrix = listToMatrix(x);
  return dist_omp(xMatrix, dimension, ncores);
}
