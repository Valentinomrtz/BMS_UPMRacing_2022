#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BMS_DESCARGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BMS_DESCARGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=app/dev/lib/uart.c app/dev/lib/gpio.c app/dev/lib/timer.c app/dev/lib/spi.c app/dev/lib/adc.c app/dev/lib/flash.c app/dev/lib/can.c app/dev/serial.c app/dev/leds.c app/dev/time.c app/dev/ltc.c app/dev/analog.c app/dev/control.c app/dev/memory.c app/dev/canlib.c app/init.c app/interrupts.c app/slave_comm.c app/input_comm.c app/mode_control.c app/hv_control.c app/error_verification.c app/relay_control.c app/cooling_control.c app/output_comm.c app/balance_control.c app/state_estimation.c app/charge_control.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/app/dev/lib/uart.o ${OBJECTDIR}/app/dev/lib/gpio.o ${OBJECTDIR}/app/dev/lib/timer.o ${OBJECTDIR}/app/dev/lib/spi.o ${OBJECTDIR}/app/dev/lib/adc.o ${OBJECTDIR}/app/dev/lib/flash.o ${OBJECTDIR}/app/dev/lib/can.o ${OBJECTDIR}/app/dev/serial.o ${OBJECTDIR}/app/dev/leds.o ${OBJECTDIR}/app/dev/time.o ${OBJECTDIR}/app/dev/ltc.o ${OBJECTDIR}/app/dev/analog.o ${OBJECTDIR}/app/dev/control.o ${OBJECTDIR}/app/dev/memory.o ${OBJECTDIR}/app/dev/canlib.o ${OBJECTDIR}/app/init.o ${OBJECTDIR}/app/interrupts.o ${OBJECTDIR}/app/slave_comm.o ${OBJECTDIR}/app/input_comm.o ${OBJECTDIR}/app/mode_control.o ${OBJECTDIR}/app/hv_control.o ${OBJECTDIR}/app/error_verification.o ${OBJECTDIR}/app/relay_control.o ${OBJECTDIR}/app/cooling_control.o ${OBJECTDIR}/app/output_comm.o ${OBJECTDIR}/app/balance_control.o ${OBJECTDIR}/app/state_estimation.o ${OBJECTDIR}/app/charge_control.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/app/dev/lib/uart.o.d ${OBJECTDIR}/app/dev/lib/gpio.o.d ${OBJECTDIR}/app/dev/lib/timer.o.d ${OBJECTDIR}/app/dev/lib/spi.o.d ${OBJECTDIR}/app/dev/lib/adc.o.d ${OBJECTDIR}/app/dev/lib/flash.o.d ${OBJECTDIR}/app/dev/lib/can.o.d ${OBJECTDIR}/app/dev/serial.o.d ${OBJECTDIR}/app/dev/leds.o.d ${OBJECTDIR}/app/dev/time.o.d ${OBJECTDIR}/app/dev/ltc.o.d ${OBJECTDIR}/app/dev/analog.o.d ${OBJECTDIR}/app/dev/control.o.d ${OBJECTDIR}/app/dev/memory.o.d ${OBJECTDIR}/app/dev/canlib.o.d ${OBJECTDIR}/app/init.o.d ${OBJECTDIR}/app/interrupts.o.d ${OBJECTDIR}/app/slave_comm.o.d ${OBJECTDIR}/app/input_comm.o.d ${OBJECTDIR}/app/mode_control.o.d ${OBJECTDIR}/app/hv_control.o.d ${OBJECTDIR}/app/error_verification.o.d ${OBJECTDIR}/app/relay_control.o.d ${OBJECTDIR}/app/cooling_control.o.d ${OBJECTDIR}/app/output_comm.o.d ${OBJECTDIR}/app/balance_control.o.d ${OBJECTDIR}/app/state_estimation.o.d ${OBJECTDIR}/app/charge_control.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/app/dev/lib/uart.o ${OBJECTDIR}/app/dev/lib/gpio.o ${OBJECTDIR}/app/dev/lib/timer.o ${OBJECTDIR}/app/dev/lib/spi.o ${OBJECTDIR}/app/dev/lib/adc.o ${OBJECTDIR}/app/dev/lib/flash.o ${OBJECTDIR}/app/dev/lib/can.o ${OBJECTDIR}/app/dev/serial.o ${OBJECTDIR}/app/dev/leds.o ${OBJECTDIR}/app/dev/time.o ${OBJECTDIR}/app/dev/ltc.o ${OBJECTDIR}/app/dev/analog.o ${OBJECTDIR}/app/dev/control.o ${OBJECTDIR}/app/dev/memory.o ${OBJECTDIR}/app/dev/canlib.o ${OBJECTDIR}/app/init.o ${OBJECTDIR}/app/interrupts.o ${OBJECTDIR}/app/slave_comm.o ${OBJECTDIR}/app/input_comm.o ${OBJECTDIR}/app/mode_control.o ${OBJECTDIR}/app/hv_control.o ${OBJECTDIR}/app/error_verification.o ${OBJECTDIR}/app/relay_control.o ${OBJECTDIR}/app/cooling_control.o ${OBJECTDIR}/app/output_comm.o ${OBJECTDIR}/app/balance_control.o ${OBJECTDIR}/app/state_estimation.o ${OBJECTDIR}/app/charge_control.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=app/dev/lib/uart.c app/dev/lib/gpio.c app/dev/lib/timer.c app/dev/lib/spi.c app/dev/lib/adc.c app/dev/lib/flash.c app/dev/lib/can.c app/dev/serial.c app/dev/leds.c app/dev/time.c app/dev/ltc.c app/dev/analog.c app/dev/control.c app/dev/memory.c app/dev/canlib.c app/init.c app/interrupts.c app/slave_comm.c app/input_comm.c app/mode_control.c app/hv_control.c app/error_verification.c app/relay_control.c app/cooling_control.c app/output_comm.c app/balance_control.c app/state_estimation.c app/charge_control.c main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/BMS_DESCARGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/app/dev/lib/uart.o: app/dev/lib/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/uart.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/uart.o.d" -o ${OBJECTDIR}/app/dev/lib/uart.o app/dev/lib/uart.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/gpio.o: app/dev/lib/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/gpio.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/gpio.o.d" -o ${OBJECTDIR}/app/dev/lib/gpio.o app/dev/lib/gpio.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/timer.o: app/dev/lib/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/timer.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/timer.o.d" -o ${OBJECTDIR}/app/dev/lib/timer.o app/dev/lib/timer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/spi.o: app/dev/lib/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/spi.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/spi.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/spi.o.d" -o ${OBJECTDIR}/app/dev/lib/spi.o app/dev/lib/spi.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/adc.o: app/dev/lib/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/adc.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/adc.o.d" -o ${OBJECTDIR}/app/dev/lib/adc.o app/dev/lib/adc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/flash.o: app/dev/lib/flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/flash.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/flash.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/flash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/flash.o.d" -o ${OBJECTDIR}/app/dev/lib/flash.o app/dev/lib/flash.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/can.o: app/dev/lib/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/can.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/can.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/can.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/can.o.d" -o ${OBJECTDIR}/app/dev/lib/can.o app/dev/lib/can.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/serial.o: app/dev/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/serial.o.d 
	@${RM} ${OBJECTDIR}/app/dev/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/serial.o.d" -o ${OBJECTDIR}/app/dev/serial.o app/dev/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/leds.o: app/dev/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/leds.o.d 
	@${RM} ${OBJECTDIR}/app/dev/leds.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/leds.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/leds.o.d" -o ${OBJECTDIR}/app/dev/leds.o app/dev/leds.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/time.o: app/dev/time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/time.o.d 
	@${RM} ${OBJECTDIR}/app/dev/time.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/time.o.d" -o ${OBJECTDIR}/app/dev/time.o app/dev/time.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/ltc.o: app/dev/ltc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/ltc.o.d 
	@${RM} ${OBJECTDIR}/app/dev/ltc.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/ltc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/ltc.o.d" -o ${OBJECTDIR}/app/dev/ltc.o app/dev/ltc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/analog.o: app/dev/analog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/analog.o.d 
	@${RM} ${OBJECTDIR}/app/dev/analog.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/analog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/analog.o.d" -o ${OBJECTDIR}/app/dev/analog.o app/dev/analog.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/control.o: app/dev/control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/control.o.d 
	@${RM} ${OBJECTDIR}/app/dev/control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/control.o.d" -o ${OBJECTDIR}/app/dev/control.o app/dev/control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/memory.o: app/dev/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/memory.o.d 
	@${RM} ${OBJECTDIR}/app/dev/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/memory.o.d" -o ${OBJECTDIR}/app/dev/memory.o app/dev/memory.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/canlib.o: app/dev/canlib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/canlib.o.d 
	@${RM} ${OBJECTDIR}/app/dev/canlib.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/canlib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/canlib.o.d" -o ${OBJECTDIR}/app/dev/canlib.o app/dev/canlib.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/init.o: app/init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/init.o.d 
	@${RM} ${OBJECTDIR}/app/init.o 
	@${FIXDEPS} "${OBJECTDIR}/app/init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/init.o.d" -o ${OBJECTDIR}/app/init.o app/init.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/interrupts.o: app/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/interrupts.o.d 
	@${RM} ${OBJECTDIR}/app/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/app/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/interrupts.o.d" -o ${OBJECTDIR}/app/interrupts.o app/interrupts.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/slave_comm.o: app/slave_comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/slave_comm.o.d 
	@${RM} ${OBJECTDIR}/app/slave_comm.o 
	@${FIXDEPS} "${OBJECTDIR}/app/slave_comm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/slave_comm.o.d" -o ${OBJECTDIR}/app/slave_comm.o app/slave_comm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/input_comm.o: app/input_comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/input_comm.o.d 
	@${RM} ${OBJECTDIR}/app/input_comm.o 
	@${FIXDEPS} "${OBJECTDIR}/app/input_comm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/input_comm.o.d" -o ${OBJECTDIR}/app/input_comm.o app/input_comm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/mode_control.o: app/mode_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/mode_control.o.d 
	@${RM} ${OBJECTDIR}/app/mode_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/mode_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/mode_control.o.d" -o ${OBJECTDIR}/app/mode_control.o app/mode_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/hv_control.o: app/hv_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/hv_control.o.d 
	@${RM} ${OBJECTDIR}/app/hv_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/hv_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/hv_control.o.d" -o ${OBJECTDIR}/app/hv_control.o app/hv_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/error_verification.o: app/error_verification.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/error_verification.o.d 
	@${RM} ${OBJECTDIR}/app/error_verification.o 
	@${FIXDEPS} "${OBJECTDIR}/app/error_verification.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/error_verification.o.d" -o ${OBJECTDIR}/app/error_verification.o app/error_verification.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/relay_control.o: app/relay_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/relay_control.o.d 
	@${RM} ${OBJECTDIR}/app/relay_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/relay_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/relay_control.o.d" -o ${OBJECTDIR}/app/relay_control.o app/relay_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/cooling_control.o: app/cooling_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/cooling_control.o.d 
	@${RM} ${OBJECTDIR}/app/cooling_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/cooling_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/cooling_control.o.d" -o ${OBJECTDIR}/app/cooling_control.o app/cooling_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/output_comm.o: app/output_comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/output_comm.o.d 
	@${RM} ${OBJECTDIR}/app/output_comm.o 
	@${FIXDEPS} "${OBJECTDIR}/app/output_comm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/output_comm.o.d" -o ${OBJECTDIR}/app/output_comm.o app/output_comm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/balance_control.o: app/balance_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/balance_control.o.d 
	@${RM} ${OBJECTDIR}/app/balance_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/balance_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/balance_control.o.d" -o ${OBJECTDIR}/app/balance_control.o app/balance_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/state_estimation.o: app/state_estimation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/state_estimation.o.d 
	@${RM} ${OBJECTDIR}/app/state_estimation.o 
	@${FIXDEPS} "${OBJECTDIR}/app/state_estimation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/state_estimation.o.d" -o ${OBJECTDIR}/app/state_estimation.o app/state_estimation.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/charge_control.o: app/charge_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/charge_control.o.d 
	@${RM} ${OBJECTDIR}/app/charge_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/charge_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/charge_control.o.d" -o ${OBJECTDIR}/app/charge_control.o app/charge_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
else
${OBJECTDIR}/app/dev/lib/uart.o: app/dev/lib/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/uart.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/uart.o.d" -o ${OBJECTDIR}/app/dev/lib/uart.o app/dev/lib/uart.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/gpio.o: app/dev/lib/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/gpio.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/gpio.o.d" -o ${OBJECTDIR}/app/dev/lib/gpio.o app/dev/lib/gpio.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/timer.o: app/dev/lib/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/timer.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/timer.o.d" -o ${OBJECTDIR}/app/dev/lib/timer.o app/dev/lib/timer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/spi.o: app/dev/lib/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/spi.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/spi.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/spi.o.d" -o ${OBJECTDIR}/app/dev/lib/spi.o app/dev/lib/spi.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/adc.o: app/dev/lib/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/adc.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/adc.o.d" -o ${OBJECTDIR}/app/dev/lib/adc.o app/dev/lib/adc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/flash.o: app/dev/lib/flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/flash.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/flash.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/flash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/flash.o.d" -o ${OBJECTDIR}/app/dev/lib/flash.o app/dev/lib/flash.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/lib/can.o: app/dev/lib/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev/lib" 
	@${RM} ${OBJECTDIR}/app/dev/lib/can.o.d 
	@${RM} ${OBJECTDIR}/app/dev/lib/can.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/lib/can.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/lib/can.o.d" -o ${OBJECTDIR}/app/dev/lib/can.o app/dev/lib/can.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/serial.o: app/dev/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/serial.o.d 
	@${RM} ${OBJECTDIR}/app/dev/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/serial.o.d" -o ${OBJECTDIR}/app/dev/serial.o app/dev/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/leds.o: app/dev/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/leds.o.d 
	@${RM} ${OBJECTDIR}/app/dev/leds.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/leds.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/leds.o.d" -o ${OBJECTDIR}/app/dev/leds.o app/dev/leds.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/time.o: app/dev/time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/time.o.d 
	@${RM} ${OBJECTDIR}/app/dev/time.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/time.o.d" -o ${OBJECTDIR}/app/dev/time.o app/dev/time.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/ltc.o: app/dev/ltc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/ltc.o.d 
	@${RM} ${OBJECTDIR}/app/dev/ltc.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/ltc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/ltc.o.d" -o ${OBJECTDIR}/app/dev/ltc.o app/dev/ltc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/analog.o: app/dev/analog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/analog.o.d 
	@${RM} ${OBJECTDIR}/app/dev/analog.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/analog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/analog.o.d" -o ${OBJECTDIR}/app/dev/analog.o app/dev/analog.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/control.o: app/dev/control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/control.o.d 
	@${RM} ${OBJECTDIR}/app/dev/control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/control.o.d" -o ${OBJECTDIR}/app/dev/control.o app/dev/control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/memory.o: app/dev/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/memory.o.d 
	@${RM} ${OBJECTDIR}/app/dev/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/memory.o.d" -o ${OBJECTDIR}/app/dev/memory.o app/dev/memory.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/dev/canlib.o: app/dev/canlib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app/dev" 
	@${RM} ${OBJECTDIR}/app/dev/canlib.o.d 
	@${RM} ${OBJECTDIR}/app/dev/canlib.o 
	@${FIXDEPS} "${OBJECTDIR}/app/dev/canlib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/dev/canlib.o.d" -o ${OBJECTDIR}/app/dev/canlib.o app/dev/canlib.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/init.o: app/init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/init.o.d 
	@${RM} ${OBJECTDIR}/app/init.o 
	@${FIXDEPS} "${OBJECTDIR}/app/init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/init.o.d" -o ${OBJECTDIR}/app/init.o app/init.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/interrupts.o: app/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/interrupts.o.d 
	@${RM} ${OBJECTDIR}/app/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/app/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/interrupts.o.d" -o ${OBJECTDIR}/app/interrupts.o app/interrupts.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/slave_comm.o: app/slave_comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/slave_comm.o.d 
	@${RM} ${OBJECTDIR}/app/slave_comm.o 
	@${FIXDEPS} "${OBJECTDIR}/app/slave_comm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/slave_comm.o.d" -o ${OBJECTDIR}/app/slave_comm.o app/slave_comm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/input_comm.o: app/input_comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/input_comm.o.d 
	@${RM} ${OBJECTDIR}/app/input_comm.o 
	@${FIXDEPS} "${OBJECTDIR}/app/input_comm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/input_comm.o.d" -o ${OBJECTDIR}/app/input_comm.o app/input_comm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/mode_control.o: app/mode_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/mode_control.o.d 
	@${RM} ${OBJECTDIR}/app/mode_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/mode_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/mode_control.o.d" -o ${OBJECTDIR}/app/mode_control.o app/mode_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/hv_control.o: app/hv_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/hv_control.o.d 
	@${RM} ${OBJECTDIR}/app/hv_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/hv_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/hv_control.o.d" -o ${OBJECTDIR}/app/hv_control.o app/hv_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/error_verification.o: app/error_verification.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/error_verification.o.d 
	@${RM} ${OBJECTDIR}/app/error_verification.o 
	@${FIXDEPS} "${OBJECTDIR}/app/error_verification.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/error_verification.o.d" -o ${OBJECTDIR}/app/error_verification.o app/error_verification.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/relay_control.o: app/relay_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/relay_control.o.d 
	@${RM} ${OBJECTDIR}/app/relay_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/relay_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/relay_control.o.d" -o ${OBJECTDIR}/app/relay_control.o app/relay_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/cooling_control.o: app/cooling_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/cooling_control.o.d 
	@${RM} ${OBJECTDIR}/app/cooling_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/cooling_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/cooling_control.o.d" -o ${OBJECTDIR}/app/cooling_control.o app/cooling_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/output_comm.o: app/output_comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/output_comm.o.d 
	@${RM} ${OBJECTDIR}/app/output_comm.o 
	@${FIXDEPS} "${OBJECTDIR}/app/output_comm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/output_comm.o.d" -o ${OBJECTDIR}/app/output_comm.o app/output_comm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/balance_control.o: app/balance_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/balance_control.o.d 
	@${RM} ${OBJECTDIR}/app/balance_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/balance_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/balance_control.o.d" -o ${OBJECTDIR}/app/balance_control.o app/balance_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/state_estimation.o: app/state_estimation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/state_estimation.o.d 
	@${RM} ${OBJECTDIR}/app/state_estimation.o 
	@${FIXDEPS} "${OBJECTDIR}/app/state_estimation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/state_estimation.o.d" -o ${OBJECTDIR}/app/state_estimation.o app/state_estimation.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/app/charge_control.o: app/charge_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/charge_control.o.d 
	@${RM} ${OBJECTDIR}/app/charge_control.o 
	@${FIXDEPS} "${OBJECTDIR}/app/charge_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app/charge_control.o.d" -o ${OBJECTDIR}/app/charge_control.o app/charge_control.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -fgnu89-inline -mdfp=${DFP_DIR}  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/BMS_DESCARGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/BMS_DESCARGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  -fgnu89-inline $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=512,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp=${DFP_DIR}
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/BMS_DESCARGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/BMS_DESCARGA.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  -fgnu89-inline $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp=${DFP_DIR}
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/BMS_DESCARGA.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
