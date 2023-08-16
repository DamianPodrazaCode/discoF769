################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/stm32f7xx_it.c \
../src/syscalls.c \
../src/system_stm32f7xx.c 

OBJS += \
./src/main.o \
./src/stm32f7xx_it.o \
./src/syscalls.o \
./src/system_stm32f7xx.o 

C_DEPS += \
./src/main.d \
./src/stm32f7xx_it.d \
./src/syscalls.d \
./src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o src/%.su src/%.cyclo: ../src/%.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F769NIHx -DSTM32F769I_DISC1 -DDEBUG -DSTM32F769xx -DUSE_HAL_DRIVER -c -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/ampire480272" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/n25q512a" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/s5k5cag" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/mfxstm32l152" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/CMSIS/device" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/n25q128a" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/ts3510" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/st7735" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/rk043fn48h" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/HAL_Driver/Inc/Legacy" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/ov9655" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/otm8009a" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/Common" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/HAL_Driver/Inc" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/stmpe811" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/wm8994" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Fonts" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/ft5336" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/inc" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/ft6x06" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/exc7200" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/st7789h2" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Log" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/adv7533" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/ampire640480" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/STM32F769I-Discovery" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/CMSIS/core" -I"D:/__GitHub/discoF769/STM32CubeIDE/115_SDRAM/Utilities/Components/mx25l512" -O0 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src

clean-src:
	-$(RM) ./src/main.cyclo ./src/main.d ./src/main.o ./src/main.su ./src/stm32f7xx_it.cyclo ./src/stm32f7xx_it.d ./src/stm32f7xx_it.o ./src/stm32f7xx_it.su ./src/syscalls.cyclo ./src/syscalls.d ./src/syscalls.o ./src/syscalls.su ./src/system_stm32f7xx.cyclo ./src/system_stm32f7xx.d ./src/system_stm32f7xx.o ./src/system_stm32f7xx.su

.PHONY: clean-src

