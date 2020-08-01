#pragma once

#include <Eigen/Core>
#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>
#include <vector>
#include <functional>

#include "macros.h"
#include "Helper.h"
#include "./threading/ctpl_stl.h"

namespace simulator {

class Constraints {
public:
  using Referrer = std::function<float& (int, int)>;
  using Func = std::function<float(const Eigen::MatrixXf&)>;
  using JacobianFunc = std::function<void(const Eigen::MatrixXf&, const Referrer&)>;

  struct Entry {
    Func f;
    JacobianFunc fD;
  };

  // Construct a constraint container with m control points.
  // To be called by Simulator only.
  Constraints(size_t m_, ctpl::thread_pool* thread_pool_) : m(m_), thread_pool(thread_pool_) { }

  // Adds constraint
  // f: constrain function of q
  // fD: d(f)/d(q(index)) for every index with non-zero value
  void addConstraint(Func f, JacobianFunc fD);

  // Gets Jacobian matrix of size c x (3 * m)
  // where c is the number of constraints
  // evaluated at q.
  Eigen::SparseMatrix<float> getJacobian(const Eigen::MatrixXf& q) const;

  // Evaluates the constraints at q
  // Returns the matrix of size c x 1
  Eigen::MatrixXf calculate(const Eigen::MatrixXf& q) const;

private:
  // number of control points
  size_t m;

  // thread pool
  ctpl::thread_pool* thread_pool;
  
  // list of constraints
  std::vector<Entry> constraints;

};

} // namespace simulator