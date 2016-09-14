################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AnalizarNoticias/Agrupador.cpp \
../AnalizarNoticias/Analizador.cpp \
../AnalizarNoticias/Articulo.cpp \
../AnalizarNoticias/EntidadNombrada.cpp \
../AnalizarNoticias/LectorNoticias.cpp \
../AnalizarNoticias/Noticia.cpp \
../AnalizarNoticias/PalabrasReservadas.cpp \
../AnalizarNoticias/PresentadorAgrupacionesJson.cpp \
../AnalizarNoticias/PresentadorAgrupacionesTxt.cpp \
../AnalizarNoticias/PresentadorNoticiasJson.cpp \
../AnalizarNoticias/Tuit.cpp \
../AnalizarNoticias/Utilidades.cpp 

OBJS += \
./AnalizarNoticias/Agrupador.o \
./AnalizarNoticias/Analizador.o \
./AnalizarNoticias/Articulo.o \
./AnalizarNoticias/EntidadNombrada.o \
./AnalizarNoticias/LectorNoticias.o \
./AnalizarNoticias/Noticia.o \
./AnalizarNoticias/PalabrasReservadas.o \
./AnalizarNoticias/PresentadorAgrupacionesJson.o \
./AnalizarNoticias/PresentadorAgrupacionesTxt.o \
./AnalizarNoticias/PresentadorNoticiasJson.o \
./AnalizarNoticias/Tuit.o \
./AnalizarNoticias/Utilidades.o 

CPP_DEPS += \
./AnalizarNoticias/Agrupador.d \
./AnalizarNoticias/Analizador.d \
./AnalizarNoticias/Articulo.d \
./AnalizarNoticias/EntidadNombrada.d \
./AnalizarNoticias/LectorNoticias.d \
./AnalizarNoticias/Noticia.d \
./AnalizarNoticias/PalabrasReservadas.d \
./AnalizarNoticias/PresentadorAgrupacionesJson.d \
./AnalizarNoticias/PresentadorAgrupacionesTxt.d \
./AnalizarNoticias/PresentadorNoticiasJson.d \
./AnalizarNoticias/Tuit.d \
./AnalizarNoticias/Utilidades.d 


# Each subdirectory must supply rules for building sources it contributes
AnalizarNoticias/%.o: ../AnalizarNoticias/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=gnu++14 -D__GXX_EXPERIMENTAL_CXX0X__ -I"../AnalizarNoticias" -I"../Json" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


