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
	@echo 'Invoking: GCC C++ Compiler'
	gcc -std=c++0x -I/usr/include/boost_1_70_0 -I/usr/include/nlohmann -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lcrypto -lssl
	@echo 'Finished building: $<'
	@echo ' '

