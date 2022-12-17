
#include <cartesian_controller/cartesian_controller.h>

#include <hardware_interface/hardware_interface.h>
#include <pluginlib/class_list_macros.h>
#include <ros/ros.h>

#include "cartesian_controller/kdl_base.h"

namespace cartesian_controller {
    /** \brief Initialize the kinematic chain for kinematics-based computation.
    *
    */
    bool Cartesian_Controller::init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &node_handle) {
        ROS_INFO("Cartesian Controller init");
        
        // KDL
        kdl_base::KDL_Base::init(robot, node_handle);

        //  read param out side
        std::string name_space = node_handle.getNamespace();
        std::string test_value;
        if (!node_handle.getParam(name_space + "/test_value", test_value)) {
            ROS_ERROR("Cartesian Controller: Could not read parameter test_value");
            return false;
        } else {
            ROS_INFO_STREAM("test_value: " << test_value);
        }
        return true;
    }

    /** \brief This is called from within the realtime thread just before the
    * first call to \ref update
    *
    * \param time The current time
    */
    void Cartesian_Controller::starting(const ros::Time& time){

        
        ROS_INFO("Cartesian Controller starting");
    }

    /*!
    * \brief Issues commands to the joint. Should be called at regular intervals
    */
    void Cartesian_Controller::update(const ros::Time& time, const ros::Duration& period) {
        
        
        //ROS_INFO_STREAM("LOOPRATE");
    }

    /********************************************/
    /**FUNCTIONS OF INSTANCES OF THE BASE CLASS**/
    /********************************************/

    /** \brief write the desired velocity command in the hardware interface input
    * for a VelocityJointInterface
    * \param period The duration of an update cycle
    */
    void Cartesian_Controller::writeVelocityCommands(
                                        const ros::Duration& period) {

    }

    void Cartesian_Controller::writePositionCommands(
                                        const ros::Duration& period)  {
        
    }

}   

// Register controllers with the PLUGINLIB_EXPORT_CLASS macro to enable dynamic
// loading with the controller manager
PLUGINLIB_EXPORT_CLASS(cartesian_controller::Cartesian_Controller,
                       controller_interface::ControllerBase)
