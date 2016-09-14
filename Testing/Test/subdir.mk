################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Test/Agrupador_test.cpp \
../Test/AnalizadorFileNameFormat_test.cpp \
../Test/Analizador_test.cpp \
../Test/Articulo_test.cpp \
../Test/EntidadNombrada_test.cpp \
../Test/LectorNoticias_test.cpp \
../Test/Noticia_test.cpp \
../Test/NoticiasTestingUtilities.cpp \
../Test/PalabrasReservadas_test.cpp \
../Test/PresentadorAgrupacionesJson_test.cpp \
../Test/PresentadorAgrupaciones_test.cpp \
../Test/Tuit_test.cpp \
../Test/Utilidades_test.cpp 

OBJS += \
./Test/Agrupador_test.o \
./Test/AnalizadorFileNameFormat_test.o \
./Test/Analizador_test.o \
./Test/Articulo_test.o \
./Test/EntidadNombrada_test.o \
./Test/LectorNoticias_test.o \
./Test/Noticia_test.o \
./Test/NoticiasTestingUtilities.o \
./Test/PalabrasReservadas_test.o \
./Test/PresentadorAgrupacionesJson_test.o \
./Test/PresentadorAgrupaciones_test.o \
./Test/Tuit_test.o \
./Test/Utilidades_test.o 

CPP_DEPS += \
./Test/Agrupador_test.d \
./Test/AnalizadorFileNameFormat_test.d \
./Test/Analizador_test.d \
./Test/Articulo_test.d \
./Test/EntidadNombrada_test.d \
./Test/LectorNoticias_test.d \
./Test/Noticia_test.d \
./Test/NoticiasTestingUtilities.d \
./Test/PalabrasReservadas_test.d \
./Test/PresentadorAgrupacionesJson_test.d \
./Test/PresentadorAgrupaciones_test.d \
./Test/Tuit_test.d \
./Test/Utilidades_test.d 


# Each subdirectory must supply rules for building sources it contributes
Test/%.o: ../Test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=gnu++14 -D__GXX_EXPERIMENTAL_CXX0X__ -I"../AnalizarNoticias" -I"../Json" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


