################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Parser/Parser.cpp 

OBJS += \
./src/Parser/Parser.o 

CPP_DEPS += \
./src/Parser/Parser.d 


# Each subdirectory must supply rules for building sources it contributes
src/Parser/%.o: ../src/Parser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__DEBUG__=0 -D__MULTITHREADED__=1 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


