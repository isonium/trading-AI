################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Train/subdir.mk
-include src/Trader/subdir.mk
-include src/Stock/subdir.mk
-include src/Simulation/subdir.mk
-include src/NeuralNetwork/subdir.mk
-include src/AlpacaServiceWS/subdir.mk
-include src/AlpacaServiceHTTP/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: trading

# Tool invocations
trading: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: NVCC linker'
	/usr/local/cuda/bin/nvcc -lssl -lcrypto --cudart=static -L/usr/include/boost_1_70_0/stage/lib -ccbin g++ -gencode arch=compute_30,code=sm_30 -gencode arch=compute_30,code=compute_30 -o "trading" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS) trading
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
