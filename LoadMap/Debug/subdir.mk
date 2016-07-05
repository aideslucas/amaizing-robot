################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AStarAlgorithm.cpp \
../Cell.cpp \
../ConfigurationManager.cpp \
../Graph.cpp \
../LocalizationManager.cpp \
../Lucatron.cpp \
../Main.cpp \
../Map.cpp \
../Particle.cpp \
../Position.cpp \
../Waypoint.cpp \
../WaypointManager.cpp \
../lodepng.cpp 

OBJS += \
./AStarAlgorithm.o \
./Cell.o \
./ConfigurationManager.o \
./Graph.o \
./LocalizationManager.o \
./Lucatron.o \
./Main.o \
./Map.o \
./Particle.o \
./Position.o \
./Waypoint.o \
./WaypointManager.o \
./lodepng.o 

CPP_DEPS += \
./AStarAlgorithm.d \
./Cell.d \
./ConfigurationManager.d \
./Graph.d \
./LocalizationManager.d \
./Lucatron.d \
./Main.d \
./Map.d \
./Particle.d \
./Position.d \
./Waypoint.d \
./WaypointManager.d \
./lodepng.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


