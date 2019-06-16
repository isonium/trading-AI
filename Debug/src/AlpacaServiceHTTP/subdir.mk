################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AlpacaServiceHTTP/AlpacaServiceHTTP.cpp \
../src/AlpacaServiceHTTP/AlpacaServiceHTTP_test.cpp 

OBJS += \
./src/AlpacaServiceHTTP/AlpacaServiceHTTP.o \
./src/AlpacaServiceHTTP/AlpacaServiceHTTP_test.o 

CPP_DEPS += \
./src/AlpacaServiceHTTP/AlpacaServiceHTTP.d \
./src/AlpacaServiceHTTP/AlpacaServiceHTTP_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/AlpacaServiceHTTP/%.o: ../src/AlpacaServiceHTTP/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -I/usr/include/boost_1_70_0 -I/usr/include/nlohmann -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lcrypto -lssl
	@echo 'Finished building: $<'
	@echo ' '


