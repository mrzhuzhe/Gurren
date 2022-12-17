#ifndef CARTESIAN_KDL_BASE_H
#define CARTESIAN_KDL_BASE_H

#include <urdf/model.h>
#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>

#include <ros/node_handle.h>
#include <ros/ros.h>

#include <kdl/tree.hpp>
#include <kdl/kdl.hpp>
#include <kdl/chain.hpp>
#include <kdl/chainfksolver.hpp>
#include <kdl/frames.hpp>
//this to compute the gravity vector
#include <kdl/chaindynparam.hpp> 
#include <kdl/chainjnttojacsolver.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/chainfksolvervel_recursive.hpp>
#include <kdl_parser/kdl_parser.hpp>

namespace kdl_base 
{
    class KDL_Base: public controller_interface::Controller<hardware_interface::PositionJointInterface>
    {
        public:
            KDL_Base() {}
            ~KDL_Base() {}

            bool init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &n);

        protected:
            ros::NodeHandle   nh_;
            KDL::Chain        kdl_chain_;
            KDL::JntArrayVel  joint_state_;
            KDL::JntArray     joint_effort_;

            struct limits_
            {
                KDL::JntArray min;
                KDL::JntArray max;
                KDL::JntArray center;
            } joint_limits_;

            std::vector<hardware_interface::JointHandle> joint_handles_;
    };


    bool KDL_Base::init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &n)
    {
        ROS_INFO("---------------KDL_BASE Init--------------");
        return true;
    }

}   

#endif