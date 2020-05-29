# Motor control libraries
See [`src/main.cpp`](src/main.cpp) for usage examples. To install,
copy [`include/motor.hpp`](include/motor.hpp) and
[`src/motor.cpp`](src/motor.cpp) to the project.

## API Reference
### class Motor::**DCMotor**
Class for controlling a DC Motor attached to an H-bridge via
PWM. Speed and direction of the motor are controlled
independently. The output is always updated immediately.

#### Constructors
##### `DCMotor`(PinName forwardPin, PinName reversePin)
- **forwardPin**: PWM-capable pin that turns the motor forward.
- **reversePin**: PWM-capable pin that turns the motor in reverse.

On initialization, DC motors are at speed 0 and stopped. The two pins
are set to output mode and PWM is started immediately.

#### Public member functions
##### double `getSpeed`()
Return the speed of the motor as a percentage of full speed, where 0
represents stopped and 100 is full speed. To get the current PWM
level, use Motor::DCMotor::getPWMOutput()

##### Motor::Direction `getDirection`()
Return the current direction of the motor. Note that if the speed is
low enough, the motor may not turn even if the direction is not stopped.

##### void `forward`()
##### void `reverse`()
##### void `stop`()
Set the motor direction to forward, reverse, or stop, respectively.

##### void `switchDirection`()
Reverse the direction of the motor from forward to reverse or vice
versa. If the motor is stopped, nothing changes.

##### void `setSpeed`(double speed)
- **speed**: a percentage from 0 to 100

Set the speed as a percentage of full speed. If the new speed
is outside the range 0-100, nothing happens.

##### void `setDirection`(Motor::Direction dir)
- **dir**: the new direction

Set the direction of the motor. Use Motor::Direction::Stop to stop
the motor.

##### void `setSpeedAndDirection`(double speed, Motor::Direction dir)
- **speed**: a percentage from 0 to 100
- **dir**: the new direction

Set both the speed and direction in one function call. If the speed
is outside the range 0-100, the speed is unchanged but the direction
will still be set.

##### unsigned int `getPWMOutput`()
Get the current PWM duty cycle.

##### void `setPWMOutput`(unsigned int dutyCycle)
- **dutyCycle**: the new duty cycle value, 0-1024

Set the current PWM duty cycle. If the new duty cycle is outside the
valid range, nothing will happen.

### enum class Motor::Direction
Value | Meaning
------|--------
Forward | The motor turns forward
Reverse | The motor turns in the reverse direction
Stop | The motor is stopped
