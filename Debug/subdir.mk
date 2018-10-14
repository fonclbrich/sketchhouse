################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../alignment.cc \
../delegatesketcher.cc \
../geometryobject.cc \
../geometrysketcher.cc \
../housesketcher.cc \
../output.cc \
../paintbox.cc \
../pathsketcher.cc \
../roomsketcher.cc \
../segments.cc \
../sketcher.cc \
../sketchhouse.cc \
../wallsketcher.cc \
../windowsketcher.cc 

CC_DEPS += \
./alignment.d \
./delegatesketcher.d \
./geometryobject.d \
./geometrysketcher.d \
./housesketcher.d \
./output.d \
./paintbox.d \
./pathsketcher.d \
./roomsketcher.d \
./segments.d \
./sketcher.d \
./sketchhouse.d \
./wallsketcher.d \
./windowsketcher.d 

OBJS += \
./alignment.o \
./delegatesketcher.o \
./geometryobject.o \
./geometrysketcher.o \
./housesketcher.o \
./output.o \
./paintbox.o \
./pathsketcher.o \
./roomsketcher.o \
./segments.o \
./sketcher.o \
./sketchhouse.o \
./wallsketcher.o \
./windowsketcher.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/libxml2 -I/usr/include/cairo -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


