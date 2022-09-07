/*
 * Copyright (c) 2020-2022 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of aruw-edu.
 *
 * aruw-edu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * aruw-edu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with aruw-edu.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "standard.hpp"

#include "tap/util_macros.hpp"

#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/chassis_tank_drive_command.hpp"

#include "drivers.hpp"

using tap::motor::MotorId;
using tap::can::CanBus;

namespace control
{
Robot::Robot(Drivers &drivers) : drivers(drivers)
// Step 3: construct ChassisSubsystem and ChassisTankDriveCommand
{
}

void Robot::initSubsystemCommands()
{
    initializeSubsystems();
    registerSoldierIoMappings();
    setDefaultSoldierCommands();
    startSoldierCommands();
    registerSoldierIoMappings();
}

void Robot::initializeSubsystems()
{
    // Step 4: initialize declared ChassisSubsystem
}

void Robot::registerSoldierSubsystems()
{
    // Step 5: register declared ChassisSubsystem
}

void Robot::setDefaultSoldierCommands()
{
    // Step 6: set ChassisTanKDriveCommand as default command for ChassisSubsystem
}

void Robot::startSoldierCommands() {}

void Robot::registerSoldierIoMappings() {}
}  // namespace control
