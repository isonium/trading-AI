################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Stock/Portfolio.cpp 

OBJS += \
./src/Stock/Portfolio.o 

CPP_DEPS += \
./src/Stock/Portfolio.d 


# Each subdirectory must supply rules for building sources it contributes
src/Stock/%.o: ../src/Stock/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -std=c++1y -D__DEBUG__=1 -D__MULTITHREADED__=1 -I/usr/include/boost_1_70_0 -I/usr/include/nlohmann -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lcrypto -lssl
	@echo 'Finished building: $<'
	@echo ' '


