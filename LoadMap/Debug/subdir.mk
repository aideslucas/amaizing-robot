################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AStarAlgorithm.cpp \
../Actions.cpp \
../Cell.cpp \
../ConfigurationManager.cpp \
../FindWayPoint.cpp \
../Graph.cpp \
../Lucatron.cpp \
../Main.cpp \
../Map.cpp \
../Move.cpp \
../Particle.cpp \
../ParticleFilter.cpp \
../Path.cpp \
../PathPlanner.cpp \
../Robot.cpp \
../WalkPath.cpp \
../Waypoint.cpp \
../WaypointManager.cpp \
../lodepng.cpp 

OBJS += \
./AStarAlgorithm.o \
./Actions.o \
./Cell.o \
./ConfigurationManager.o \
./FindWayPoint.o \
./Graph.o \
./Lucatron.o \
./Main.o \
./Map.o \
./Move.o \
./Particle.o \
./ParticleFilter.o \
./Path.o \
./PathPlanner.o \
./Robot.o \
./WalkPath.o \
./Waypoint.o \
./WaypointManager.o \
./lodepng.o 

CPP_DEPS += \
./AStarAlgorithm.d \
./Actions.d \
./Cell.d \
./ConfigurationManager.d \
./FindWayPoint.d \
./Graph.d \
./Lucatron.d \
./Main.d \
./Map.d \
./Move.d \
./Particle.d \
./ParticleFilter.d \
./Path.d \
./PathPlanner.d \
./Robot.d \
./WalkPath.d \
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


