# Tank Drive Tutorial

## Hardware

The chassis is a fundamental subsystem for many RoboMaster robots. Our 2022
standard chassis consists of the following hardware:

- Main microcontroller. The
  [microcontroller](https://en.wikipedia.org/wiki/Microcontroller) used on the
  standard is the [RoboMaster type A Board](). The microcontroller has
  peripherals to interact with all other hardware subsystems including the
  chassis subsystem. 
- Four motor controllers ([RoboMaster C620 motor controllers]()). The motor
  controllers are wired to the microcontroller so the main microcontroller can
  send commands to the motor controllers using a protocol called [CAN]().
  Furthermore, the motor controllers send motor information to the main
  microcontroller using the same protocol. This includes information about the
  measured velocity of the motor and the motor shaft's rotational position.
- Four motors ([RoboMaster M3508 motors]()). Each motor is connected to the
  motor controller. The motor takes commands from the motor controller and sends
  information back to the motor controller. Each motor is connected to a
  [mecanum wheel]().
- Remote control receiver. The [DR-16 receiver]() is used to wirelessly receive
  remote control information from a paired [remote]().

## Tank Drive

Your goal is to write a program that will allow you to control a robot with
**"tank drive",** a simple but common drive system. “Tank drive” is when you
control a robot with 2 joysticks, where the y-axis (vertical) of each joystick
controls the left and right side of the robot’s drive motors respectively. This
is how big military tanks work (hence the name).

For instance:
- Push both joysticks forward and the robot will move forward.
- Push both joysticks backward and the robot will move backward.
- Push left joystick forward and right joystick backward and robot will spin
  clockwise.

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

- This tutorial is not a comprehensive of C++ or the codebase. It is designed to
  guide your learning in a structured manner. As you go through this tutorial,
  it is expected that you work with others, ask leads questions about parts, and
  most importantly, search the internet for various questions that are not
  specific to the project.

- As you start working through this tutorial, **build your code often**. This
  will help tremendously because it allows you to easily identify where errors
  are coming from. Unlike some IDEs, VSCode Intellisense is not always accurate
  and will sometimes not identify errors (especially more complex, annoying
  ones). So, please, please build often. To build, refer to the section in the
  aruw-edu README called "Building code and programming the RoboMaster
  Development Board."

- The library that you will be using to develop your chassis tank drive software
  is called
  [taproot](https://gitlab.com/aruw/controls/taproot/-/wikis/definitions#taproot).
  Please look over the section called ["Code Generated in User
  Projects"](https://gitlab.com/aruw/controls/taproot/-/wikis/Code-Generation-in-User-Projects)
  in the taproot wiki. In aruw-edu, taproot is included as a git submodule at
  the top level of the repository. Generated taproot software that you will be
  interacting with is located in `./aruw-edu/aruw-edu-project/taproot`.

- If you are stuck on some part of this tutorial, please reach out for help.
  Solutions are available; however, these should not be referenced unless
  absolutely necessary. Doing so defeats the purpose of this tutorial.

- Various C++ tips that are not specific to our codebase will be in a note block.

## Overview

During this project, you will be developing software in
`./aruw-edu/aruw-edu-project/src`. This wiki will guide you through finishing a
variety of incomplete subsystems and commands. Next is a description of each
section you will be developing.

- **`ControlOperatorInterface`**: Accesses inputs provided by a user from the
  [remote](https://gitlab.com/aruw/controls/taproot/-/wikis/definitions#remote).
  Provides an abstraction layer between remote input and user control used in
  commands. For example, translates "move the left stick up and right stick
  down" to "I want to turn left".

- **`ChassisSubsystem`**: Interprets chassis movement commands sent by a command
  that is running and sends motor control commands to the motors.

- **`ChassisDriveCommand`**: Translates user input ("I want to turn left") into
  instructions that the `ChassisSubsystem` can understand.

- **`Robot`**: Where instances of the `ChassisSubsystem`, `ChassisDriveCommand`,
  and other control-related object instances are instantiated.

```{note}
**C++ Tip**: In C++, pointers, references, and variables are two very important
concepts that you must understand to successfully completet this tutorial.
Often, tutorials might state something like "pass variable X to function Y."
This statement in itself is ambiguous. In order to follow such an instruction,
you must be able to understand how you are passing variable X, be that as a
reference, pointer, or variable. If you do not have experience with C++
pointers, review [this
slideshow](https://courses.cs.washington.edu/courses/cse333/20sp/lectures/03-c-pointers.pdf).
If you do not have experience with C++ references, review [this slideshow](). It
is not expected that you are a master of pointers, references, and variables
before starting this tutorial, but it generally useful to have a base
understanding of how they work.

To test your understanding, answer the following questions:

  - Define `foo`, `bar`, and `baz` as pointers, references, or variables.
    ```{code-block}cpp
    void function()
    {
      int foo{42};
      int *bar = &foo;
      int &baz = foo;
    }
    ```
    <details>
    <summary>Answer</summary>
      <code>foo</code>: variable<br>
      <code>bar</code>: pointer<br>
      <code>baz</code>: reference
    </details>

  - In the function `f1` defined below, how would you call `f2`, `f3`, and `f4`
    respectively, passing the variable `foo` to these three functions?
    ```cpp
    void f2(int var)
    {
      // Print var and address of var
      std::cout << var << ", " << &var << std::endl;
    }

    void f3(int *var)
    {
      // Print var and address of var
      std::cout << var << ", " << &var << std::endl;
    }

    void f4(int &var)
    {
      // Print var and address of var
      std::cout << var << ", " << &var << std::endl;
    }

    void f1()
    {
      int foo{42};
      // Now call f2, f3, and f4, passing foo to each.
    }
    ```
    <details>
    <summary>Answer</summary>
    <code>f2(foo)</code>, <code>f3(&foo)</code>, <code>f4(foo)</code>
    </details>

    Bonus question, will `f2`, `f3` and `f4` print identical values when the
    functions above are called from `f1()`?

    <details>
    <summary>Answer</summary>
    No, <code>f2</code> will print a different result compared to <code>f3</code> and <code>f4</code>. While <code>var</code>
    is the same, the address of <code>var</code> is not in <code>f2</code>'s case since a copy of foo is
    being created for <code>f2</code> when you pass <code>foo</code> as a variable instead of a pointer
    or reference.
    </details>

    Bonus question 2, assume `f1()` has now been changed to the following:
    ```{code-block}cpp
    void f1()
    {
      int *foo = new int();
      // Now call f2, f3, and f4, passing foo to each
      delete foo;
    }
    ```
    How would you call `f2`, `f3`, and `f4` respectively, passing the variable
    `foo` to these three functions?

    <details>
    <summary>Answer</summary>
    <code>f2(*foo)</code>, <code>f3(foo)</code>, <code>f4(*foo)</code>
    </details>
```

## `ControlOperatorInterface`

First you will be adding a couple of functions to the `ControlOperatorInterface`
object in `control_operator_interface.hpp` and `control_operator_interface.cpp`.
In these files, you will find sections labeled `// STEP <n>`. Hints
corresponding to these sections are listed below to help you along.

```{note}
**C++ Tip**: In C++, we break apart separate logical units into classes similar
to Java. In the normal case, each C++ class will have an associated **header**
file (suffixed commonly by .hpp) and **source** file (suffixed commonly by
.cpp). Typical naming convention associates class and file names together. For
instance, a class named `ContiguousFloat` will be housed in corresponding source
and header files named `contiguous_float.cpp` and `contiguous_float.hpp`
respectively.
```

You will be adding the `getChassisTankLeftInput` and `getChassisTankRightInput`
functions to the operator interface.

### Step 1: Declare Functions

**The functions should have 0 function parameters and return a `float`.**

In general, functions are _declared_ in headers (`.hpp` files) and _defined_ in
source files (`.cpp` files). The operator interface is no exception (for
reference refer to [this Stack Overflow
post](https://stackoverflow.com/questions/25274312/is-it-a-good-practice-to-define-c-functions-inside-header-files)).

_**C++ Tip**: You can think of "declaring" a function as a way of documenting
the blueprint of a function for others to then use. The declaration will include
the name of the function, return value, and input parameters. The declaration
**will not** contain any of the actual logic. On the other hand, "defining" a
function can be thought of as the actual meat of the function that gives the
function meaning. An outside observer may use a declared function without
knowing the actual meat of the function as long as they know the declaration._

The functions should be declared as public members of the
`ControlOperatorInterface` class. The function should return a value between
`[-1 ,1]`.

For example, in the example class below, the function `greatFunction` has been
declared as a public member.

```cpp
// example.hpp

class Example {
 public:
  void greatFunction();  // Declaration
};

-----------------------------
// example.cpp

void Example::greatFunction() {  // Definition
  // Do great things
}
```

This is because `greatFunction` is declared in the example class within the
section with `public` at the top.

```{note}
**C++ Tip**: C++ classes contain `public`, `protected`, and `private` sections
of code. In general, a function that is in the public section means anyone can
call that function. A function that is in the protected section means any child
object can call that function, and function in the private section means only
the object can call that function.
```

Note: When declaring the functions, add the keyword `mockable` in front of the
declaration to aid with unit testability.

### Step 2: Define Functions

In the example above, `greatFunction` is defined in `example.cpp`. In general,
the formula for defining a function for a class outside of the class involves
adding `<class name>::` in front of the function name.

Once you have defined the functions, you have to actually write logic in the
functions.

Refer to the remote's [`generated
documentation`](https://aruw.gitlab.io/controls/taproot/api/classtap_1_1communication_1_1serial_1_1_remote.html)
to learn how to interact with the remote. The functions you define should call
the remote's `getSwitch` functions. The left left vertical switch should be used
to get user input for the left tank drive function and the right vertical switch
for the right tank drive function.

## `ChassisSubsystem`

Next, you will be finishing the `ChassisSubsystem` class in
`chassis_subsystem.hpp` and `chassis_subsystem.cpp`.

Again, follow the steps in the files.

### Step 1: Create ChassisSubsystem Constructor

If you are unfamiliar with C++ class structure, read [this page on C++
classes](https://cplusplus.com/doc/tutorial/classes/). Each subsystem and
command is encapsulated in a class. A class constructor is needed to initialize
various objects that are declared in the class. In the case of the
`ChassisSubsystem`, the private variables in the `ChassisSubsystem` are shown
below.

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

## `Robot`

Next, you will be finishing the `Robot` object in `standard.hpp` and
`standard.cpp`. The `Robot` object is a singleton, which means a single `Robot`
object is exected to be created. This object is created in `main.cpp`.

Again, follow the steps in the two files and refer to the documentation below to
help guide you through finishing the `Robot` object.

### Step 1: Declare `ChassisSubsystem`

Note that the subsystem is scoped inside the namespace `control`. Thus
`control::` will have to be appended on to the object name. For unit test
purposes, this object should be named `chassisSubsystem`.

```{note}
**C++ Tip:** Unlike in Java, declaring a variable of class or struct type
automatically instantiates that type -- there are no "null references" in C++,
and in fact, reference semantics as seen in Java are only applicable to C++
pointers. If you don't know how to instantiate objects in C++, look
[here](http://www.cplusplus.com/doc/tutorial/classes/).
```


### Step 2: Declare `ChassisTankDriveCommand`

This should be very similar to step 1. For unit test purposes, this object
should be named `chassisTankDriveCommand`.

### Step 3: Construct Subsystem and Command

Now that you have declared your subsystem and command in `standard.hpp`, you
must construct these objects in `standard.cpp`. Use your understanding of C++
member initialization to construct these the `ChassisSubsystem` and
`ChassisTankDriveCommand`.

### Step 4: Initialize Chassis

In the `initializeSubsystems()` function in `standard.cpp`, you must manually
initialize the `chassisSubsystem` object. Call `chassisSubsystem`'s `initialize`
function here.

### Step 5: Register Chassis

Any `Subsystem` you would like the command scheduler to manage must be
registered with it during runtime. The `Drivers` object that the `Standard` has
a reference to contains the main `CommandScheduler` that you should register the
`ChassisSubsystem` you created with. Refer to the `CommandScheduler`'s
[`registerSubsystem` function]().

### Step 6: Set Tank Drive Command as Default

We want the tank drive command you constructed to be a default command of the
chassis subsystem command you created. This way, the command scheduler will
execute the tank drive command whenever no other commands that have the chassis
subsystem as a dependency are running (so for now, all the time). To do so, the
`Subsystem` class (the `ChassisSubsystem` is a child of `Subsystem`) has a
function called `setDefaultCommand`. In the `setDefaultSoldierCommands`
subsystem, call this function, passing the `ChassisTankDriveCommand` you
declared previously.

## Run Tests

At this point, you should have completed all required software for the tank
drive tutorial. Before running the software you wrote on a robot, it is expected
that you code has unit tests associated with it. For this tutrial, uint tests
have been provided, so you do not have to write your own (see
`./aruw-edu-project/test/control`).

To compile and run tests for the chassis tank drive, run `scons run-tests`.

## Run Code on a Robot

It is now time to test and debug your code. Before you begin, **it is imperative
that you read the [debugging safety
information](https://gitlab.com/aruw/controls/taproot/-/wikis/Debugging-Safety-Information)
page**. I cannot stress this enough.

It is now time to run and debug your code. Reading the [debugging information
for using the the
ST-Link](https://gitlab.com/aruw/controls/taproot/-/wikis/Debugging-With-STLink)
and [debugging information for using the
J-Link](https://gitlab.com/aruw/controls/taproot/-/wikis/Debugging-With-JLink)
will give you a good base for debugging your code.

After reading these guides, test your code on the soldier. You should ask
another member for help getting the robot set up, though below is a list of some
things you should follow specific to this tutorial:

- You probably need a robot. Ask someone if you don't know where to find one.
- Before you begin, **prop the robot up on blocks**.
- Unplug power to everything but the chassis (again, ask another member for help
  so this is done correctly).
- Ensure the remote is connected to the robot's MCB.

After you are completed debugging, you should have functional tank drive
control. Following the same steps from above, **add, commit, and push your code
to the main repo** so it can be reviewed. Again, I recommend our [Git
tutorial](https://gitlab.com/aruw/controls/taproot/-/wikis/Git-Tutorial) if you
are having trouble.

Finally, find another member to review your code to ensure quality by opening up
a merge request.
