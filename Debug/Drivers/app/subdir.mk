################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/app/app.c 

OBJS += \
./Drivers/app/app.o 

C_DEPS += \
./Drivers/app/app.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/app/%.o Drivers/app/%.su Drivers/app/%.cyclo: ../Drivers/app/%.c Drivers/app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I"H:/grad project/cubeWorkSpace/Grad_project/Drivers/app" -I../Core/Inc -I"H:/grad project/cubeWorkSpace/Grad_project/Drivers/motorDriver" -I"H:/grad project/cubeWorkSpace/Grad_project/Drivers/ultraSonic" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-app

clean-Drivers-2f-app:
	-$(RM) ./Drivers/app/app.cyclo ./Drivers/app/app.d ./Drivers/app/app.o ./Drivers/app/app.su

.PHONY: clean-Drivers-2f-app

