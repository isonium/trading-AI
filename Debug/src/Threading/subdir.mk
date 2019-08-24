################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Threading/ThreadPool.cpp 

OBJS += \
./src/Threading/ThreadPool.o 

CPP_DEPS += \
./src/Threading/ThreadPool.d 


# Each subdirectory must supply rules for building sources it contributes
src/Threading/%.o: ../src/Threading/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -std=c++1y -D__DEBUG__=1 -D__MULTITHREADED__=1 -I/usr/include/boost_1_70_0 -I/usr/include/nlohmann -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lcrypto -lssl
	@echo 'Finished building: $<'
	@echo ' '


