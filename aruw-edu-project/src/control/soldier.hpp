#pragma once

#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/chassis_tank_drive_command.hpp"

namespace control
{
class Drivers;

class Robot
{
public:
    Robot(Drivers *drivers);

    void initSubsystemCommands(Drivers *drivers);

private:
    void initializeSubsystems();
    void registerSoldierSubsystems(Drivers *drivers);
    void setDefaultSoldierCommands(Drivers *drivers);
    void startSoldierCommands(Drivers *drivers);
    void registerSoldierIoMappings(Drivers *drivers);

    // Step 1: declare ChassisSubystem

    // Step 2: declare ChassisTankDriveCommand
};
}  // namespace control
