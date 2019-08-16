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
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


