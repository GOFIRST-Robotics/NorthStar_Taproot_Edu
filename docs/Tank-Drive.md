## Hardware

The chassis is a fundamental subsystem for all RoboMaster robots. Our 2022
standard chassis consists of the following hardware:

* Main microcontroller. The
  [microcontroller](https://en.wikipedia.org/wiki/Microcontroller) used on the
  standard is the [RoboMaster type A Board](). The microcontroller has
  peripherals to interact with all other hardware subsystems including the
  chassis subsystem. 
* Four motor controllers ([RoboMaster C620 motor controllers]()). The motor
  controllers are wired to the microcontroller so the main microcontroller can
  send commands to the microcontroller using a protol called [CAN])().
  Furthermore, the motor controllers send motor information to the main
  microcontroller. This information includes information about the velocity of
  the motor and the rotational position.
* Four motors ([RoboMaster M3508 motors]()). Each motor is connected to the
  motor controller. The motor takes commands from the motor controller and sends
  information back to the motor controller. Each motor is connected to a
  [mecanum wheel]().

## Tank Drive

Your goal is to write a program that will allow you to control a robot with
**"tank drive,** a simple but common drive system. “Tank drive” is when you have
a robot you move with 2 joysticks, where the y-axis (vertical) of each joystick
controls the left and right side of the robot’s drive motors respectively. This
is how big military tanks work (hence the name).

## Code Architecture

The robot we develop is complicated, so we attempt to keep our work sane by
using an architecture that we have developed previously that does some of the
tedious and more challenging operations for us. This curriculum focuses only on
learning the basics of using **subsystems** and **commands** (our high level
control architecture), as well as the **operator interface**, which interprets
remote and computer input and allows a user to control the robot. There is a lot
more that goes into controlling the robot that we will glaze over in this
tutorial.

Much of the subsystem and command framework developed previously was at a high
level based on FIRST programming. There is a good explanation of how subsystems
and commands work
[here](https://docs.wpilib.org/en/latest/docs/software/commandbased/what-is-command-based.html).
On this page, you should read the following sections:
- What Is "Command-Based" Programming?
- Subsystems and Commands
- How Commands Are Run

In addition, I recommend looking at the following pages:
- [Subsystems](https://docs.wpilib.org/en/latest/docs/software/commandbased/subsystems.html)
- [Commands](https://docs.wpilib.org/en/latest/docs/software/commandbased/commands.html)
- [The Command
  Scheduler](https://docs.wpilib.org/en/latest/docs/software/commandbased/command-scheduler.html)

Note though that while our code is not designed exactly like what is found in
FIRST, the ideas are similar. Our implementation of command groups, for example,
is very different. Our implementation is not close to perfect, but hopefully you
will be able to improve it some time in the future!

## Installing the Development Environment

Before starting this tutorial, you must install the development environment.
Please refer to the README's "Getting started with this repo" section to set up
aruw-edu.

Once you have installed aruw-edu, create a git branch on the repository with
some reasonable name. This is where you will be developing software for this
tutorial.

Reference [this Git
tutorial](https://gitlab.com/aruw/controls/taproot/-/wikis/Git-Tutorial) for
information about cloning, creating, and checking out a new branch if you are
unfamiliar with using Git.

## Notes Before Beginning

- As you start working through this tutorial, **build your code often**. This
  will help tremendously because it allows you to easily identify where errors
  are coming from. Unlike some IDEs, VSCode Intellisense is not always accurate
  and will sometimes not identify errors (especially more complex, annoying
  ones). So, please, please build often. To build, refer to the section in the
  README called "Building code and programming the RoboMaster Development
  Board."

- The library that you will be using to develop your chassis tank drive software
  is called
  [taproot](https://gitlab.com/aruw/controls/taproot/-/wikis/definitions#taproot).
  Please look over the section called ["Code Generated in User
  Projects"](https://gitlab.com/aruw/controls/taproot/-/wikis/Code-Generation-in-User-Projects)
  in the taproot wiki. In aruw-edu, taproot is included as a submodule at the
  top level of the repository. Generated taproot software that you will be
  interacting with is located in `./aruw-edu/aruw-edu-project/taproot`.

- If you are stuck on some part of the curriculum, please reach out for help.
  Solutions are available; however, these should not be referenced unless
  absolutely necessary. Doing so defeats the purpose of the curriculum.

## Overview

During this project, you will be developing software in `./aruw-edu/src`. This
wiki will guide you through finishing a variety of incomplete subsystems and
commands. Next is a description of each section you will be developing.

- **`ControlOperatorInterface`**: Access inputs provided by a user from the
  [remote](https://gitlab.com/aruw/controls/taproot/-/wikis/definitions#remote).
  Provides an abstraction layer between remote input and user control used in
  commands. For example, translates "move the left stick up and right stick
  down" to "I want to turn left".

- **`ChassisSubsystem`**: Interprets chassis movement commands sent by a command
  that is running and sends motor control commands to the motors.

- **`ChassisDriveCommand`**: Translates user input ("I want to turn left") into
  instructions that the `ChassisSubsystem` can understand.

- **`Soldier`**: Where instances of the `ChassisSubsystem`,
  `ChassisDriveCommand`, and other control-related object instances are
  instantiated.

## `ControlOperatorInterface`

Next you will be adding a couple of functions to the `ControlOperatorInterface`
object in `control_operator_interface.hpp` and `control_operator_interface.cpp`.
In these files, you will find sections labeled `// STEP <n>`. Hints
corresponding to these sections are listed below to help you along.

You will be adding the `getChassisTankLeftInput` and `getChassisTankRightInput`
functions to the operator interface.

### Step 1: Declare Functions

**The functions should have 0 function parameters and returnr a `float`.**

In general, functions are declared in headers (`.hpp` files) and defined in
source files (`.cpp` files). The operator interface is no exception (for
reference refer to [this Stack Overflow
post](https://stackoverflow.com/questions/25274312/is-it-a-good-practice-to-define-c-functions-inside-header-files)).

The functions should be declared as public members of the
`ControlOperatorInterface` class. The function should return a value between
`[-1 ,1]`.

For example, in the example class below, the function `greatFunction` has been
declared as a public member.

```cpp
// example.hpp

class Example {
 public:
  void greatFunction();
};

-----------------------------
// example.cpp

void Example::greatFunction() {
  // Do great things
}
```

This is because `greatFunction` is declared in the example class within the
section with `public` at the top.

### Step 2: Define Functions

In the example above, `greatFunction` is defined in `example.cpp`. In general,
the formula for defining a function for a class outside of the class involves
adding `<class name>::` in front of the function name.

Once you have defined the functions, you have to actually write logic in the
functions.

Refer to [`generated
documentation`](https://aruw.gitlab.io/controls/taproot/api/classtap_1_1communication_1_1serial_1_1_remote.html)
for API documentation. These function should call the remote's `getSwitch`
functions. The left left vertical switch should be used to get user input for
the left tank drive function and the right vertical switch for the right tank
drive function.

## `ChassisSubsystem`

You will be finishing the `ChassisSubsystem` class first in
`chassis_subsystem.hpp` and `chassis_subsystem.cpp`.

Again, follow the steps in the files.

### Step 1: Create ChassisSubsystem Constructor

If you are unfamiliar with C++ class structure, read [this page on C++
classes](https://cplusplus.com/doc/tutorial/classes/). Much of our logic is
encapsulated into classes. Each subsystem and command is encapsulated in a
class. A class constructor is needed to initialize various objects that are
declared in the class. In the case of the `ChassisSubsystem`, the private
variables in the `ChassisSubsystem` are shown below.

```cpp
    /// @brief Motor ID to index into the velocityPid and motors object.
    enum class MotorId : uint8_t
    {
        LF = 0,
        LB,
        RF,
        RB,
        NUM_MOTORS,
    };

    /// Desired wheel output for each motor 
    std::array<float, static_cast<uint8_t>(MotorId::NUM_MOTORS)> desiredOutput;

    /// PID controllers. Input desired wheel velocity, output desired motor current.
    std::array<modm::Pid<float>, static_cast<uint8_t>(MotorId::NUM_MOTORS)> pidControllers;

#if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
public:
    /// Replace motors with mocks during testing.
    std::array<tap::mock::DjiMotorMock, static_cast<uint8_t>(MotorId::NUM_MOTORS)> motors;
#else
    /// Motors.
    tap::motor::DjiMotor motors[static_cast<uint8_t>(MotorId::NUM_MOTORS)];
#endif
```

The `pidControllers` and `motors` arrays must be constructed in the
`ChassisSubsystem`'s constructor. In addition, any other objects that you
declare in the `ChassisSubsystem` must be constructed as well. Refer to the
section on [member initialization in
constructors](https://cplusplus.com/doc/tutorial/classes/) in the C++ classes
tutorial.

#### Member Initialization of Arrays in Classes

Once you understand member initialization of objects in classes, you must learn
specifically how to initialize an array (`std::array`). See the example below:

```cpp
// foo.h

class Foo {
 public:
  Foo();

 private:
  std::array<int, 4> a;
};

------------------------------
// foo.cpp

Foo::Foo() : a{0, 1, 2, 3} {}
```

Here `Foo` constructs the array `a` with `int` elements 0, 1, 2, and 3.

### Step 2: `initialize` Function

This function should call each of the `DjiMotor`'s `initialize` function.

### Step 3: `setVelocityTankDrive` Function

As the name and function comments suggests, this function takes in left and
right chassis speed in m/s. The post condition of this function is that the
array `desiredOutput` array should store desired wheel speed (in rotations per
second). For example, given the left side speed is 1 m/s and the right side
speed is 0 m/s, the desired wheelspeed of the two left motors should be positive
and converted from linear speed to rotational speed, and the two right wheels
should have a desired wheelspeed of 0. Note the desired wheel speed should be
limited by `setVelocityTankDrive` to `[-MAX_WHEELSPEED_RPM,
MAX_WHEELSPEED_RPM]`. Look up how to convert m/s to RPM as required. Note that
the motors are geared approximately 19:1, so any conversion should should
include a multiplication by by 19.

### Step 4: `refresh` Function

The `refresh` function is called repeatedly at some specified frequency. In
`aruw-mcb`, this rate is 500 Hz. This function should do the following:

- Call each PID's `update` function. This function expects an input. The input
  should be the difference between the desired RPM and the motor's actual RPM. 
- Call each motor's `setDesiredOutput` function, passing to this function the
  PID's `getValue` function.

## `ChassisDriveCommand`

Next you will be finishing the `ChassisDriveCommand` object in
`chassis_drive_command.hpp` and `chassis_drive_command.cpp`. Again, complete all
the steps in both files.

### Step 1: Constructor

The constructor of this object should store the passed in `chassis` in the
private member function called `chassis`. Same goes for the
`ControlOperatorInterface`. Also, you should call the `Command`'s
`addSubsystemRequirement`. This is a required step for the `Command` to function
properly.

### Step 2: `execute` Function

This function should set the chassis's desired speed to values reported by the
`ControlOperatorInterface`. Use the operator interface's
`getChassisTankLeftInput` and `getChassisTankRightInput` functions. These
functions return values between `[-1, 1]`, so convert this input to
`[-MAX_CHASSIS_SPEED_MPS, MAX_CHASSIS_SPEED_MPS]` before passing to the
`ChassisSubsystem`'s `setVelocityTankDrive` function.

### Step 3: `end` Function

This function should set the chassis's desired speed to all 0s.

## `Soldier`

