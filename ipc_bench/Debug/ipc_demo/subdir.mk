################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ipc_demo/follow.c \
../ipc_demo/ipc_bench.c \
../ipc_demo/lead.c 

OBJS += \
./ipc_demo/follow.o \
./ipc_demo/ipc_bench.o \
./ipc_demo/lead.o 

C_DEPS += \
./ipc_demo/follow.d \
./ipc_demo/ipc_bench.d \
./ipc_demo/lead.d 


# Each subdirectory must supply rules for building sources it contributes
ipc_demo/%.o: ../ipc_demo/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/ali/workspace/ipc_bench/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


