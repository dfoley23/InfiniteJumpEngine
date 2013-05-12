################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Camera.cpp \
../Entity.cpp \
../GLDataObject.cpp \
../Game.cpp \
../KinematicComponent.cpp \
../Level.cpp \
../Mesh.cpp \
../ResManager.cpp \
../Shader.cpp \
../Tile.cpp \
../TileSet.cpp \
../main.Dennis.cpp \
../main.Kevin.cpp \
../main.cpp 

C_SRCS += \
../glew.c 

OBJS += \
./Camera.o \
./Entity.o \
./GLDataObject.o \
./Game.o \
./KinematicComponent.o \
./Level.o \
./Mesh.o \
./ResManager.o \
./Shader.o \
./Tile.o \
./TileSet.o \
./glew.o \
./main.Dennis.o \
./main.Kevin.o \
./main.o 

C_DEPS += \
./glew.d 

CPP_DEPS += \
./Camera.d \
./Entity.d \
./GLDataObject.d \
./Game.d \
./KinematicComponent.d \
./Level.d \
./Mesh.d \
./ResManager.d \
./Shader.d \
./Tile.d \
./TileSet.d \
./main.Dennis.d \
./main.Kevin.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Users\Kevin Cameron\workspace\InfiniteJumpEngine\InfiniteJumpEngine\InfiniteJumpEngine\include" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"C:\Users\Kevin Cameron\workspace\InfiniteJumpEngine\InfiniteJumpEngine\InfiniteJumpEngine\include" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


