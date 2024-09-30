#pragma once
#include <Rcpp.h>

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>

// [[Rcpp::export]]
double hausdorff_distance_cpp(
    Rcpp::NumericVector x,
    Rcpp::NumericVector y,
    unsigned int dimension = 1
);

double hausdorff_distance_cpp(
    RcppParallel::RMatrix<double>::Row x,
    RcppParallel::RMatrix<double>::Row y,
    unsigned int dimension = 1
);

Rcpp::NumericMatrix listToMatrix(Rcpp::List x);
