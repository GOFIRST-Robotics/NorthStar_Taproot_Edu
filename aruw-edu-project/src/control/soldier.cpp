#include "soldier.hpp"

#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/chassis_tank_drive_command.hpp"
#include "tap/util_macros.hpp"

namespace control
{
void Robot::initSubsystemCommands(Drivers *drivers)
// Step 3: member initialization of ChassisSubsystem and ChassisTankDriveCommand.
{
    initializeSubsystems();
    registerSoldierIoMappings(drivers);
    setDefaultSoldierCommands(drivers);
    startSoldierCommands(drivers);
    registerSoldierIoMappings(drivers);
}

void Robot::initializeSubsystems()
{
    // Step 4: initialize declared ChassisSubsystem
}

void Robot::registerSoldierSubsystems(Drivers *drivers) {
    // Step 5: register declared ChassisSubsystem
}

void Robot::setDefaultSoldierCommands(Drivers *drivers)
{
    // Step 6: set ChassisTanKDriveCommand as default command for ChassisSubsystem
}

void Robot::startSoldierCommands(Drivers *drivers) {
    UNUSED(drivers);
}

void Robot::registerSoldierIoMappings(Drivers *drivers) {
    UNUSED(drivers);
}
}  // namespace control
