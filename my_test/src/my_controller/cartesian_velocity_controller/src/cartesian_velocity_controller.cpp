
#include <cartesian_velocity_controller/cartesian_velocity_controller.h>
#include <pluginlib/class_list_macros.h>
#include "kdl_conversions/kdl_msg.h"

#include "cartesian_velocity_controller/kdl_base.h"


namespace cartesian_velocity_controller {
    /** \brief Initialize the kinematic chain for kinematics-based computation.
    *
    */
    bool Cartesian_Velocity_Controller::init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &node_handle) {
        ROS_INFO("Cartesian_Velocity_Controller init");
        
        //  read param out side
        std::string name_space = node_handle.getNamespace();
        std::string test_value;
        if (!node_handle.getParam(name_space + "/test_value", test_value)) {
            ROS_ERROR("Cartesian_Velocity_Controller: Could not read parameter test_value");
            return false;
        } else {
            ROS_INFO_STREAM("test_value: " << test_value);
        }

        ros::NodeHandle &n = node_handle;
        // KDL
        kdl_base::KDL_Base::init(robot, n);

        ik_vel_solver_.reset(new KDL::ChainIkSolverVel_pinv_givens(this->kdl_chain_));
        fk_vel_solver_.reset(new KDL::ChainFkSolverVel_recursive(this->kdl_chain_));
        fk_pos_solver_.reset(new KDL::ChainFkSolverPos_recursive(this->kdl_chain_));

        // get publishing period
        if (!n.getParam("publish_rate", publish_rate_)){
            ROS_ERROR("Parameter 'publish_rate' not set");
            return false;
        }
        realtime_pub_.reset(new realtime_tools::RealtimePublisher
            <cartesian_state_msgs::PoseTwist>(n, "ee_state", 4));


        // Topics
        sub_command_ = n.subscribe("command_cart_vel", 5,
            &Cartesian_Velocity_Controller::command_cart_vel, this,
            ros::TransportHints().reliable().tcpNoDelay());

        // Variable init
        this->joint_state_.resize(this->kdl_chain_.getNrOfJoints());
        //this->joint_effort_.resize(this->kdl_chain_.getNrOfJoints());
        Jnt_Vel_Cmd_.resize(this->kdl_chain_.getNrOfJoints());
        End_Vel_Cmd_ = KDL::Twist::Zero();
        End_Pos_.p.Zero();
        End_Pos_.M.Identity();
        End_Vel_.p.Zero();
        End_Vel_.M.Identity();

        return true;
    }

    /** \brief This is called from within the realtime thread just before the
    * first call to \ref update
    *
    * \param time The current time
    */
    void Cartesian_Velocity_Controller::starting(const ros::Time& time){

        
        ROS_INFO("Cartesian_Velocity_Controller starting");
        for(std::size_t i=0; i < this->joint_handles_.size(); i++) {
            Jnt_Vel_Cmd_(i) = 0.0;
            this->joint_state_.q(i)     = 0.0;
            this->joint_state_.qdot(i)  = 0.0;
        }
        End_Vel_Cmd_ = KDL::Twist::Zero();
        last_publish_time_ = time;
    }

    /*!
    * \brief Issues commands to the joint. Should be called at regular intervals
    */
    void Cartesian_Velocity_Controller::update(const ros::Time& time, const ros::Duration& period) {
        
        // Get joint positions
        for(std::size_t i=0; i < this->joint_handles_.size(); i++)
        {
            if(fabs(this->joint_handles_[i].getPosition()-(this->joint_state_.q(i) + Jnt_Vel_Cmd_(i)*period.toSec()))<0.0000001 
            || Jnt_Vel_Cmd_(i)!=0
            )  //  joint will keep running without 
            {
            this->joint_state_.q(i)         = this->joint_handles_[i].getPosition();
            this->joint_state_.qdot(i)      = this->joint_handles_[i].getVelocity();
            }
        }
       
        // Compute inverse kinematics velocity solver
        //  http://docs.ros.org/en/hydro/api/orocos_kdl/html/classKDL_1_1ChainIkSolverVel.html
        ik_vel_solver_->CartToJnt(this->joint_state_.q, End_Vel_Cmd_, Jnt_Vel_Cmd_);

        

        writeVelocityCommands(period);

        // Forward kinematics
        fk_vel_solver_->JntToCart(this->joint_state_, End_Vel_);
        fk_pos_solver_->JntToCart(this->joint_state_.q, End_Pos_);

        // Limit rate of publishing
        if (publish_rate_ > 0.0 && last_publish_time_
            + ros::Duration(1.0/publish_rate_) < time) {

            // try to publish
            if (realtime_pub_->trylock()) {
            last_publish_time_ = last_publish_time_
                                + ros::Duration(1.0/publish_rate_);
            // populate message
            realtime_pub_->msg_.header.stamp = time;
            tf::poseKDLToMsg(End_Pos_, realtime_pub_->msg_.pose);
            tf::twistKDLToMsg(End_Vel_.GetTwist(), realtime_pub_->msg_.twist);

            //  http://docs.ros.org/en/indigo/api/orocos_kdl/html/classKDL_1_1Frame.html
            //ROS_INFO("End_Pos_ %f %f %f", End_Pos_.p(0), End_Pos_.p(1), End_Pos_.p(2));
            
            realtime_pub_->unlockAndPublish();
            }
        }
        //ROS_INFO_STREAM("LOOPRATE");
    }

    /*!
    * \brief Subscriber's callback: copies twist commands
    */
    void Cartesian_Velocity_Controller::command_cart_vel(const geometry_msgs::TwistConstPtr &msg) {
        
        End_Vel_Cmd_.vel(0) = msg->linear.x;
        End_Vel_Cmd_.vel(1) = msg->linear.y;
        End_Vel_Cmd_.vel(2) = msg->linear.z;
        End_Vel_Cmd_.rot(0) = msg->angular.x;
        End_Vel_Cmd_.rot(1) = msg->angular.y;
        End_Vel_Cmd_.rot(2) = msg->angular.z;
    }

    /********************************************/
    /**FUNCTIONS OF INSTANCES OF THE BASE CLASS**/
    /********************************************/

    /** \brief write the desired velocity command in the hardware interface input
    * for a PositionJointInterface
    * \param period The duration of an update cycle
    */
    void Cartesian_Velocity_Controller::writeVelocityCommands(
                                        const ros::Duration& period) {
                                            

        for(std::size_t i=0; i < this->joint_handles_.size(); i++) {                   
            this->joint_handles_[i].setCommand(this->joint_state_.q(i) + Jnt_Vel_Cmd_(i)*period.toSec());
        }
    }

}   

// Register controllers with the PLUGINLIB_EXPORT_CLASS macro to enable dynamic
// loading with the controller manager
PLUGINLIB_EXPORT_CLASS(cartesian_velocity_controller::Cartesian_Velocity_Controller,
                       controller_interface::ControllerBase)
