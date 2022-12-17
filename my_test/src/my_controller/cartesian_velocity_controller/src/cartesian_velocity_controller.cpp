
#include <cartesian_velocity_controller/cartesian_velocity_controller.h>

#include <hardware_interface/hardware_interface.h>
#include <pluginlib/class_list_macros.h>
#include <ros/ros.h>

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
        return true;
    }

    /** \brief This is called from within the realtime thread just before the
    * first call to \ref update
    *
    * \param time The current time
    */
    void Cartesian_Velocity_Controller::starting(const ros::Time& time){

        
        ROS_INFO("Cartesian_Velocity_Controller starting");
    }

    /*!
    * \brief Issues commands to the joint. Should be called at regular intervals
    */
    void Cartesian_Velocity_Controller::update(const ros::Time& time, const ros::Duration& period) {
        
        
        //ROS_INFO_STREAM("LOOPRATE");
    }

    /********************************************/
    /**FUNCTIONS OF INSTANCES OF THE BASE CLASS**/
    /********************************************/

    /** \brief write the desired velocity command in the hardware interface input
    * for a VelocityJointInterface
    * \param period The duration of an update cycle
    */
    void Cartesian_Velocity_Controller::writeVelocityCommands(
                                        const ros::Duration& period) {

    }

    void Cartesian_Velocity_Controller::writePositionCommands(
                                        const ros::Duration& period)  {
        
    }

}   

// Register controllers with the PLUGINLIB_EXPORT_CLASS macro to enable dynamic
// loading with the controller manager
PLUGINLIB_EXPORT_CLASS(cartesian_velocity_controller::Cartesian_Velocity_Controller,
                       controller_interface::ControllerBase)
