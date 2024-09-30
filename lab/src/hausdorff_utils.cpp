#include "hausdorff_utils.h"

double hausdorff_distance_cpp(Rcpp::NumericVector x,
                              Rcpp::NumericVector y,
                              unsigned int dimension)
{
  unsigned int numDimensions = dimension;
  unsigned int numPoints = x.size() / numDimensions;

  double dX = 0.0;
  double dY = 0.0;

  for (unsigned int i = 0;i < numPoints;++i)
  {
    double min_dist_x = std::numeric_limits<double>::infinity();
    double min_dist_y = std::numeric_limits<double>::infinity();

    for (unsigned int j = 0;j < numPoints;++j)
    {
      double dist_x = 0.0;
      double dist_y = 0.0;

      for (unsigned int k = 0;k < numDimensions;++k)
      {
        unsigned int index_i = k * numPoints + i;
        unsigned int index_j = k * numPoints + j;
        dist_x += std::pow(x[index_i] - y[index_j], 2);
        dist_y += std::pow(y[index_i] - x[index_j], 2);
      }
      min_dist_x = std::min(min_dist_x, dist_x);
      min_dist_y = std::min(min_dist_y, dist_y);
    }

    dX = std::max(dX, min_dist_x);
    dY = std::max(dY, min_dist_y);
  }

  return std::sqrt(std::max(dX, dY));
}

double hausdorff_distance_cpp(RcppParallel::RMatrix<double>::Row x,
                              RcppParallel::RMatrix<double>::Row y,
                              unsigned int dimension)
{
  unsigned int numDimensions = dimension;
  unsigned int numPoints = x.size() / numDimensions;

  double dX = 0.0;
  double dY = 0.0;

  for (unsigned int i = 0;i < numPoints;++i)
  {
    double min_dist_x = std::numeric_limits<double>::infinity();
    double min_dist_y = std::numeric_limits<double>::infinity();

    for (unsigned int j = 0;j < numPoints;++j)
    {
      double dist_x = 0.0;
      double dist_y = 0.0;

      for (unsigned int k = 0;k < numDimensions;++k)
      {
        unsigned index_i = k * numPoints + i;
        unsigned index_j = k * numPoints + j;
        dist_x += std::pow(x[index_i] - y[index_j], 2);
        dist_y += std::pow(y[index_i] - x[index_j], 2);
      }

      min_dist_x = std::min(min_dist_x, dist_x);
      min_dist_y = std::min(min_dist_y, dist_y);
    }

    dX = std::max(dX, min_dist_x);
    dY = std::max(dY, min_dist_y);
  }

  return std::sqrt(std::max(dX, dY));
}

Rcpp::NumericMatrix listToMatrix(Rcpp::List x)
{
  unsigned int nrows = x.size();
  unsigned int ncols = Rcpp::as<Rcpp::NumericVector>(x[0]).size();
  Rcpp::NumericMatrix out(nrows, ncols);
  Rcpp::NumericMatrix workMatrix;
  Rcpp::NumericVector workRow;

  for (unsigned int i = 0;i < nrows;++i)
  {
    workMatrix = Rcpp::as<Rcpp::NumericMatrix>(x[i]);
    workMatrix = Rcpp::transpose(workMatrix);
    workRow = Rcpp::as<Rcpp::NumericVector>(workMatrix);
    std::copy(workRow.begin(), workRow.end(), out.row(i).begin());
  }

  return out;
}
