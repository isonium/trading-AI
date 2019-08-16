################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AlpacaParser/AlpacaParser.cpp 

OBJS += \
./src/AlpacaParser/AlpacaParser.o 

CPP_DEPS += \
./src/AlpacaParser/AlpacaParser.d 


# Each subdirectory must supply rules for building sources it contributes
src/AlpacaParser/%.o: ../src/AlpacaParser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -std=c++0x -I/usr/include/boost_1_70_0 -I/usr/include/nlohmann -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lcrypto -lssl
	@echo 'Finished building: $<'
	@echo ' '


