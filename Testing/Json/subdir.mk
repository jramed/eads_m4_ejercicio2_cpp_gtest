################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Json/jsoncpp.cpp 

OBJS += \
./Json/jsoncpp.o 

CPP_DEPS += \
./Json/jsoncpp.d 


# Each subdirectory must supply rules for building sources it contributes
Json/%.o: ../Json/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=gnu++14 -D__GXX_EXPERIMENTAL_CXX0X__ -I"../AnalizarNoticias" -I"../Json" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


