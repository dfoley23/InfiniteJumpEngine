################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../glm/core/dummy.cpp 

OBJS += \
./glm/core/dummy.o 

CPP_DEPS += \
./glm/core/dummy.d 


# Each subdirectory must supply rules for building sources it contributes
glm/core/%.o: ../glm/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/dennis/Documents/cmps164/InfiniteJumpEngine/InfiniteJumpEngine/InfiniteJumpEngine/include" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

