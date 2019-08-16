################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Trader/Simulation.cpp \
../src/Trader/Trader.cpp \
../src/Trader/Trader_test.cpp 

OBJS += \
./src/Trader/Simulation.o \
./src/Trader/Trader.o \
./src/Trader/Trader_test.o 

CPP_DEPS += \
./src/Trader/Simulation.d \
./src/Trader/Trader.d \
./src/Trader/Trader_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/Trader/%.o: ../src/Trader/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


