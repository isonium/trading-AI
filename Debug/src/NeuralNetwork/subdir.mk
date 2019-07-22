################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/NeuralNetwork/Connection.cpp \
../src/NeuralNetwork/NN.cpp \
../src/NeuralNetwork/Neuron.cpp \
../src/NeuralNetwork/Topology.cpp 

OBJS += \
./src/NeuralNetwork/Connection.o \
./src/NeuralNetwork/NN.o \
./src/NeuralNetwork/Neuron.o \
./src/NeuralNetwork/Topology.o 

CPP_DEPS += \
./src/NeuralNetwork/Connection.d \
./src/NeuralNetwork/NN.d \
./src/NeuralNetwork/Neuron.d \
./src/NeuralNetwork/Topology.d 


# Each subdirectory must supply rules for building sources it contributes
src/NeuralNetwork/%.o: ../src/NeuralNetwork/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -I/usr/include/boost_1_70_0 -I/usr/include/nlohmann -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lcrypto -lssl
	@echo 'Finished building: $<'
	@echo ' '


