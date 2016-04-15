################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Graph.cpp \
../Main.cpp \
../Map.cpp \
../Node.cpp \
../lodepng.cpp 

OBJS += \
./Graph.o \
./Main.o \
./Map.o \
./Node.o \
./lodepng.o 

CPP_DEPS += \
./Graph.d \
./Main.d \
./Map.d \
./Node.d \
./lodepng.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


