#include <iostream>
#include <map>
#include <Eigen/Core>

class Odom_Data
{
    public:
    Odom_Data()
    {
        std::cout<<"odom_data construct"<<std::endl;
    }
    private:
    std::map<double, Eigen::VectorXd> OdomBuf_;
};

