################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/NeuralNetwork/Connection.cpp \
../src/NeuralNetwork/Mutation.cpp \
../src/NeuralNetwork/NN.cpp \
../src/NeuralNetwork/NeuralNetwork.cpp \
../src/NeuralNetwork/Neuron.cpp \
../src/NeuralNetwork/Phenotype.cpp \
../src/NeuralNetwork/Species.cpp \
../src/NeuralNetwork/Topology.cpp 

OBJS += \
./src/NeuralNetwork/Connection.o \
./src/NeuralNetwork/Mutation.o \
./src/NeuralNetwork/NN.o \
./src/NeuralNetwork/NeuralNetwork.o \
./src/NeuralNetwork/Neuron.o \
./src/NeuralNetwork/Phenotype.o \
./src/NeuralNetwork/Species.o \
./src/NeuralNetwork/Topology.o 

CPP_DEPS += \
./src/NeuralNetwork/Connection.d \
./src/NeuralNetwork/Mutation.d \
./src/NeuralNetwork/NN.d \
./src/NeuralNetwork/NeuralNetwork.d \
./src/NeuralNetwork/Neuron.d \
./src/NeuralNetwork/Phenotype.d \
./src/NeuralNetwork/Species.d \
./src/NeuralNetwork/Topology.d 


# Each subdirectory must supply rules for building sources it contributes
src/NeuralNetwork/%.o: ../src/NeuralNetwork/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -std=c++1y -D__DEBUG__=1 -D__MULTITHREADED__=1 -I/usr/include/boost_1_70_0 -I/usr/include/nlohmann -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lcrypto -lssl
	@echo 'Finished building: $<'
	@echo ' '


