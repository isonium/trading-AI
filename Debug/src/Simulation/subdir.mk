################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Simulation/Simulation.cpp \
../src/Simulation/Simulation_test.cpp 

OBJS += \
./src/Simulation/Simulation.o \
./src/Simulation/Simulation_test.o 

CPP_DEPS += \
./src/Simulation/Simulation.d \
./src/Simulation/Simulation_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/Simulation/%.o: ../src/Simulation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -I/usr/include/boost_1_70_0 -I/usr/include/nlohmann -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lcrypto -lssl
	@echo 'Finished building: $<'
	@echo ' '


