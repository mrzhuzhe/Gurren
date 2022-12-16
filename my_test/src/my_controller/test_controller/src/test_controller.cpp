
#include <test_controller/test_controller.h>

#include <hardware_interface/hardware_interface.h>
#include <pluginlib/class_list_macros.h>
#include <ros/ros.h>


namespace test_controller {
    /** \brief Initialize the kinematic chain for kinematics-based computation.
    *
    */
    bool Test_Controller::init(hardware_interface::PositionJointInterface *robot, ros::NodeHandle &n) {
        ROS_INFO("Test_Controller init");
        return true;
    }

    /** \brief This is called from within the realtime thread just before the
    * first call to \ref update
    *
    * \param time The current time
    */
    void Test_Controller::starting(const ros::Time& time){
        ROS_INFO("Test_Controller starting");
    }

    /*!
    * \brief Issues commands to the joint. Should be called at regular intervals
    */
    void Test_Controller::update(const ros::Time& time, const ros::Duration& period) {

    }

    /********************************************/
    /**FUNCTIONS OF INSTANCES OF THE BASE CLASS**/
    /********************************************/

    /** \brief write the desired velocity command in the hardware interface input
    * for a VelocityJointInterface
    * \param period The duration of an update cycle
    */
    void Test_Controller::writeVelocityCommands(
                                        const ros::Duration& period) {

    }

    void Test_Controller::writePositionCommands(
                                        const ros::Duration& period)  {
        
    }

}   

// Register controllers with the PLUGINLIB_EXPORT_CLASS macro to enable dynamic
// loading with the controller manager
PLUGINLIB_EXPORT_CLASS(test_controller::Test_Controller,
                       controller_interface::ControllerBase)
