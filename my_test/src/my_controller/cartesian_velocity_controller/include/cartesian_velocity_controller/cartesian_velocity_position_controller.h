#ifndef CARTESIAN_VELOCITY_POSITION_CONTROLLER_H
#define CARTESIAN_VELOCITY_POSITION_CONTROLLER_H

#include "kdl_base.h"
#include "cartesian_velocity_controller.h"

namespace cartesian_velocity_position_controller {
    class Cartesian_Velocity_Position_Controller: public cartesian_velocity_controller::Cartesian_Velocity_Controller {
        public:
            Cartesian_Velocity_Position_Controller() {}
            ~Cartesian_Velocity_Position_Controller() {}
    };
}

#endif