#include "cartesian_velocity_position_controller/cartesian_velocity_position_controller.h"
#include <pluginlib/class_list_macros.h>
#include "kdl_conversions/kdl_msg.h"

namespace cartesian_velocity_position_controller {
    void Cartesian_Velocity_Position_Controller::testfun(){

    }
}

// Register controllers with the PLUGINLIB_EXPORT_CLASS macro to enable dynamic
// loading with the controller manager
PLUGINLIB_EXPORT_CLASS(cartesian_velocity_position_controller::Cartesian_Velocity_Position_Controller, controller_interface::ControllerBase)
