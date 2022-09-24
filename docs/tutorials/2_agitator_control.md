# Agitator Control Tutorial

## Requirements

Pleas first complete the [Tank Drive Tutorial](1_tank_drive) and all of its required reading.

## Hardware

The agitator is an essential component of any launching mechanism. Hardware
components used are similar to the tank drive tutorial; however, the motor and
motor controller used is typically different (for the standard robot).

- Main microcontroller. See the [Tank Drive Tutorial](1_tank_drive)
- One motor controller. The wiring is identical to that described in the tank
  drive tutorial.
- One motor. The motor is connected to the motor controller identical to what is
  described in the tank drive tutorial. The motor is physically connected to an
  "agitator" (also described as an "indexer" or "stirrer").
- Remote control receiver and reomte. The receiver will be used in a simmilar
  fashion as the tank drive tutorial. During this tutorial, you will be
  connecting the remote to a computer, which you will used to receive mouse
  button click information.

## Agitator Control

Some agitator systems are more mechanically complex than others; however, all
agitators share the same purpose--to turn a container of unorganized projectiles
into a stream of projectiles that can then be fed into a launching mechanism. In
the case of ARUW's standard, the agitator is a turbine-like mechanism with 10
slots for balls to fall into. When spun, the projectiles are fed into a pair of
flywheels (rubber wheels that spin very fast) that launch projectiles out. This
design is typical of all RoboMaster standard robots.

A control system must be designed to control the rotation of the agitator. In
the simpliest case, an agitator system must rotate enough to launch one
projectile when a user commands (be that via a remote control or
keyboard/mouse). This is similar to FPS (point and click) games.

## Overview
