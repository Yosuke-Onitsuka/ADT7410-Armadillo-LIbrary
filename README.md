# ADT7410-Armadillo-Library

## Overview
This is an Armadillo library for using ADT7410 temperature sensor.  

## Usage
For using this library, prease inheritance it and QObject library like Qsennsser.cpp and QSensser.h.

## Commands

#### `bool begin(void)`
Starts initialization settings.  
Returns `true`, if initialization settings with any ploblem.

#### `uint16_t getTmp(void)`
Returns value of quotized temperature.  
It is **not value Celsius or Fahrenheit**, only electric value.

#### `double calculateTmp(uint16_t)`
Prease throw the value got with `getTmp()` as argument.  
Returns `double` type value. It means Celsius tempelature.

#### `void setResolution(adt7410Resolution_t resolution)`
ADT7410 has two resolutions.  
To set resolution 13, write `ADT7410_RESOLUTION_13` as argument.  
To set resolution 16, write `ADT7410_RESOLUTION_16` as argument.

#### `void setMode(adt7410Mode_t mode)`
ADT7410 has 4 modes.  
To set NORMAL mode, write `ADT7410_NORMAL_MODE` as argument.  
To set ONE SHOT mode, write `ADT7410_ONE_SHOT_MODE` as argument.  
To set ONE SPS mode, write `ADT7410_ONE_SPS_MODE` as argument.  
To set SHUTDOWN mode, write `ADT7410_SHUTDOWN_MODE` as argument.  
