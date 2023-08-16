################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f769xx.s 

OBJS += \
./startup/startup_stm32f769xx.o 

S_DEPS += \
./startup/startup_stm32f769xx.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/ampire480272" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/n25q512a" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/s5k5cag" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/mfxstm32l152" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/CMSIS/device" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/n25q128a" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/ts3510" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/st7735" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/rk043fn48h" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/HAL_Driver/Inc/Legacy" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/ov9655" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/otm8009a" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/Common" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/HAL_Driver/Inc" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/stmpe811" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/wm8994" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Fonts" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/ft5336" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/inc" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/ft6x06" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/exc7200" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/st7789h2" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Log" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/adv7533" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/ampire640480" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/STM32F769I-Discovery" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/CMSIS/core" -I"D:/__GitHub/discoF769/STM32CubeIDE/111_template/Utilities/Components/mx25l512" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_stm32f769xx.d ./startup/startup_stm32f769xx.o

.PHONY: clean-startup

