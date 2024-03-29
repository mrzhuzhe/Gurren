#ifndef TEST_CONTROLLER_H
#define TEST_CONTROLLER_H


#include <ros/node_handle.h>

#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>

namespace test_controller {
    class Test_Controller: public controller_interface::Controller<hardware_interface::PositionJointInterface>{
        public:
            Test_Controller() {}
            ~Test_Controller() {}

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
        private:
            /** \brief Write current commands to the hardware interface
            */
            void writeVelocityCommands(const ros::Duration& period);
            void writePositionCommands(const ros::Duration& period);

        protected:
            std::vector<hardware_interface::JointHandle> joint_handles_;
            int _joint_len_ = 6;
            std::string _links[6] = { "shoulder_pan_joint",
                    "shoulder_lift_joint",
                    "elbow_joint",
                    "wrist_1_joint",
                    "wrist_2_joint",
                    "wrist_3_joint" };

    };
}

#endif