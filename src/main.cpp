#include <iostream>
#include <unistd.h>
#include "eigen3/Eigen/Core"
 

using Eigen::MatrixXd;
using Eigen::MatrixXf;
using Eigen::Vector2cf;

int main()

{
  Vector2cf m = Vector2cf();
  std::cout << m << std::endl;
  MatrixXf a = MatrixXf::Random(10,10);
  std::cout << a << std::endl;
}
