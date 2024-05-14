; Simple DAC Practice Enterprice Project source code
; Written by Alessandro Lo Monaco v1 on 2024-05-01

org 0000h
ljmp main

main:   mov   sp, #7fh
        lcall init_clock
        lcall init_serial
        lcall init_adc
loop:   mov   p2,#11111110b
        mov   a,#0         ; need loop for all 8 channels and send to serial
        lcall read_adc
        ;lcall send_byte
        lcall delay
        mov   p2,#11111111b
        lcall delay
        ljmp loop

; INITIALIZATION FUNCTIONS ---------------------------------------------------;

; temporary init function for clock
init_clock:
        push psw
        push acc
        mov pllcon, #00h
        pop acc
        pop psw

        ret

init_adc:
        mov   adccon1,#11001100b

        ret

; MAIN FUNCTIONS ------------------------------------------------------------;

; read_adc: reads the ADC value from the ADC and returns it in the accumulator
; ACC as 0-7 channel selection parameter
; return value: 8-bit ADC value in ACC
read_adc:       mov   adccon2,acc
read_adc1:      setb  sconv
read_adc2:      jb    sconv,read_adc2
                mov   a,adcdatah
                anl   a,#0fh
                mov   b,a
                mov   a,adcdatal
                anl   a,#f0h
                orl   a,b
                swap  a

                ret

delay:
    MOV R7, #255
delay1:
    MOV R6, #255
delay2:
    DJNZ R6, delay2
    DJNZ R7, delay1
    RET

; IMPORTED FUNCTIONS AND DECLARATIONS ---------------------------------------;

#include "serial.inc"
#include "dec.inc"
end
