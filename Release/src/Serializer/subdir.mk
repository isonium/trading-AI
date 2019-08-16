################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Serializer/Serializable.cpp \
../src/Serializer/Serializer.cpp 

OBJS += \
./src/Serializer/Serializable.o \
./src/Serializer/Serializer.o 

CPP_DEPS += \
./src/Serializer/Serializable.d \
./src/Serializer/Serializer.d 


# Each subdirectory must supply rules for building sources it contributes
src/Serializer/%.o: ../src/Serializer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


