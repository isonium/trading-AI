################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AlpacaServiceWS/AlpacaServiceWS.cpp \
../src/AlpacaServiceWS/AlpacaServiceWS_test.cpp 

OBJS += \
./src/AlpacaServiceWS/AlpacaServiceWS.o \
./src/AlpacaServiceWS/AlpacaServiceWS_test.o 

CPP_DEPS += \
./src/AlpacaServiceWS/AlpacaServiceWS.d \
./src/AlpacaServiceWS/AlpacaServiceWS_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/AlpacaServiceWS/%.o: ../src/AlpacaServiceWS/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


