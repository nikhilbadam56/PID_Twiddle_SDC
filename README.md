# PID Controller Project SDC
Self-Driving Car Engineer Nanodegree Program
---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Overview

“PID Controller SDC” , this project involves to code a PID system for controlling(atleast) the
control variable “steering angle” based on the input “Cross Track Error” which basically is
the amount of distance between the center of the lane and the centroid of the box model
of car in simulation.
Initial values of PID parameters are set manually by individually varying parameters, then
used twiddle optimization algorithm for about 5 iterations each with a step size of 300 to
optimize the manually obtained parameters.

## Goals

1. To code PID algorithms from scratch in CPP.
2. To code Twiddle algorithm.
3. To make a car in a simulation maneuver around the track using a PID controller.

## Brief

```
● “PID controller” stands for proportional , Integral,derivative controller. Proportional
part takes the cross track error and changes the control variable ,here steering
angle, proportional to the amount of cross track error. This is good for small value
of errors , but for large values of eros system tend to overshoot , this makes the
object , here car , go off the track or desired value it intended to achieve. Following
video shows the output of controller with only P parameter set , to value 0.05.
```
[![](http://img.youtube.com/vi/64YmirDHZJw/0.jpg)](https://youtu.be/64YmirDHZJw)

```
● When only the p-controller is set, the system oscillates vigorously about the
desired value i.e., center of the lane. In order to kill this behaviour and make
the response die out as we progress we use a Derivative part of the
controller. This works like a feedback , gives the system a memory about the
performance of the system in previous timestep and thereby controls
present behaviour. We approximate this derivative by a first order difference
equation with assumption of time gap 1 second. Following video shows the
output response of the system when both P parameter and D parameter are
set , and also I have set a very small value to the I parameter , this decreases
the steady state error , this accumulates overall previous error (integration)
and changes the output response.
P parameter : 0.
D parameter : 1.
I parameter : 0.
```
[![](http://img.youtube.com/vi/vDEouoN_UHI/0.jpg)](https://youtu.be/vDEouoN_UHI)
```
● Now we got a good set of PID parameter values , but in order to still refine
the output we could still refine the parameters i.e., optimizing the
parameters , for this kind of task we generally use optimization algorithms
like gradient descent , Twiddle algorithm , Stochastic Gradient descent etc.
For them to perform better we generally set a good initial value to the
parameters , this is done to achieve optimized values fastly that is with good
initialization we restrict search space. For this project I have a twiddle
algorithm for optimization tasks. I have run twiddle algorithm for 5 iterations
and obtained optimized PID parameters are
P parameter : 0.
D parameter : 2.
I Parameter : 0.
```
(NOTE: even though i have run the twiddle for 5 iteration , i have achieved above
values in 3 iterations , remaining iteration only made things oscillatory).


[![](http://img.youtube.com/vi/iYE36Rv70K8/0.jpg)](https://youtu.be/iYE36Rv70K8)
