################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Trader/LiveTrader.cpp \
../src/Trader/LiveTrading.cpp \
../src/Trader/Simulation.cpp \
../src/Trader/SimulationTrader.cpp \
../src/Trader/Trader.cpp \
../src/Trader/Trader_test.cpp 

OBJS += \
./src/Trader/LiveTrader.o \
./src/Trader/LiveTrading.o \
./src/Trader/Simulation.o \
./src/Trader/SimulationTrader.o \
./src/Trader/Trader.o \
./src/Trader/Trader_test.o 

CPP_DEPS += \
./src/Trader/LiveTrader.d \
./src/Trader/LiveTrading.d \
./src/Trader/Simulation.d \
./src/Trader/SimulationTrader.d \
./src/Trader/Trader.d \
./src/Trader/Trader_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/Trader/%.o: ../src/Trader/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -std=c++1y -D__DEBUG__=1 -D__MULTITHREADED__=1 -I/usr/include/boost_1_70_0 -I/usr/include/nlohmann -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lcrypto -lssl
	@echo 'Finished building: $<'
	@echo ' '


