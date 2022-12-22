#ifndef CARTESIAN_VELOCITY_POSITION_CONTROLLER_H
#define CARTESIAN_VELOCITY_POSITION_CONTROLLER_H

#include <ros/node_handle.h>
#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>

#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <cartesian_state_msgs/PoseTwist.h>
#include <kdl/chainiksolvervel_pinv.hpp>
#include <kdl/chainiksolvervel_pinv_givens.hpp>
#include <kdl/chainiksolverpos_lma.hpp>
#include <kdl/chainfksolvervel_recursive.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <realtime_tools/realtime_publisher.h>
#include "kdl_base.h"

namespace cartesian_velocity_position_controller {
    //class Cartesian_Velocity_Position_Controller: public cartesian_velocity_controller::Cartesian_Velocity_Controller {
    class Cartesian_Velocity_Position_Controller: public kdl_base::KDL_Base {
        public:
            Cartesian_Velocity_Position_Controller() {}
            ~Cartesian_Velocity_Position_Controller() {}
            void testfun(void);
            
            /** \brief The init function is called to initialize the controller from a
            * non-realtime thread with a pointer to the hardware interface, itself,
            * instead of a pointer to a RobotHW.
            *s
            * \param robot The specific hardware interface used by this controller.
            *
            * \param n A NodeHandle in the namespace from which the controller
            * should read its configuration, and where it should set up its ROS
            * interface.
            *
            * \returns True if initialization was successful and the controller
            * is ready to be started.
            */
            bool init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &n);

            /** \brief This is called from within the realtime thread just before the
            * first call to \ref update
            *
            * \param time The current time
            */
            void starting(const ros::Time& time);

            /*!
            * \brief Issues commands to the joint. Called at regular intervals
            */
            void update(const ros::Time& time, const ros::Duration& period);

            /*!
            * \brief Subscriber's callback function
            */
            void command_cart_vel(const geometry_msgs::TwistConstPtr &msg);

            void command_cart_pos(const geometry_msgs::PoseConstPtr &msg);
        private:
            /** \brief Write current commands to the hardware interface
            */
            void writeVelocityCommands(const ros::Duration& period);
                    
        protected:
            ros::Subscriber                 sub_command_; // Interface to external commands

            ros::Time                       last_publish_time_;
            double                          publish_rate_;

            KDL::Rotation                   End_Pos_Rotation;
            KDL::Vector                     End_Pos_Vector;
            KDL::Frame                      End_Pos_Cmd_;      // Desired end-effector position

            KDL::JntArray                   Jnt_Vel_Cmd_;      // Desired joint velocity
            KDL::Twist                      End_Vel_Cmd_;      // Desired end-effector velocity
            KDL::FrameVel                   End_Vel_;
            KDL::Frame                      End_Pos_;
            cartesian_state_msgs::PoseTwist msg_state_;


            boost::shared_ptr<KDL::ChainFkSolverVel> fk_vel_solver_;
            boost::shared_ptr<KDL::ChainFkSolverPos> fk_pos_solver_;
            boost::shared_ptr<KDL::ChainIkSolverVel> ik_vel_solver_;

            boost::shared_ptr<realtime_tools::RealtimePublisher<
                cartesian_state_msgs::PoseTwist> > realtime_pub_;
            //  Quaterniond desired_pose_orientation_;
            //  Quaterniond arm_orientation_;

    };
}

#endif