## OpenVNA

This repository contains a simple example for interfacing with a single Akela
VNA from C++.

Qt thread management primitives are used for both managing a running 
acquisition, and inter-thread communications, exploiting the built-in thread
safety of default Qt signals and slots.

Some additional synchonization is managed with explicit locking (primarily 
starting and stopping) the actual acquisition of sweeps.

Dependencies:
 - Qt5
 - Qwt >= 6.1 (graphing library)

The build process uses `qmake`. Currently, we use the Qt Creator IDE for 
managing `qmake`, promarily because it's extremely simple. 

OpenVNA has been tested successfully on both windows and linux.
