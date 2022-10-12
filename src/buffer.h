#include <iostream>
#include <map>
#include <Eigen/Core>

class Odom_Data
{
    public:
    Odom_Data(){};
    
    private:
    std::map<double, Eigen::VectorXd> OdomBuf_;
};

