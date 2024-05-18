; Simple DAC Practice Enterprice Project source code
; Written by Alessandro Lo Monaco v1 on 2024-05-01

org     0000h
ljmp    main

main:
        mov     sp, #7fh
        lcall   init_clock   ; set the clock to 16.777216 MHz all next operations are based on this clock
        ;lcall   init_I2C     ; initialize ports
        ;lcall   init_display ; initialize display
        lcall   init_serial  ; initialize serial communication to 9600 baud
        lcall   init_adc     ; initialize ADC
loop:
        mov     r0,#7
        mov     r1,#10000000b
loop1:
        mov     a,r0         ; need loop for all 8 channels and send to serial
        lcall   read_adc     ; read ADC value of channel in ACC

        lcall   send_byte    ; send read value to serial
        mov     a,r0
        lcall   send_byte    ; send channel number to serial

        mov     a,p0         ; read button state
        anl     a,r1
        cjne    a,#0,loop1   ; if button is pressed, skip to next channel

        lcall   delay        ; delay for a while

        dec     r0
        cjne    r0,#ffh,loop1
        ljmp    loop

; INITIALIZATION FUNCTIONS ---------------------------------------------------;

; temporary init function for clock
init_clock:
        push    psw
        push    acc
        mov     pllcon, #00h
        pop     acc
        pop     psw

        ret

init_adc:
        mov     adccon1,#10001100b

        ret

; MAIN FUNCTIONS ------------------------------------------------------------;

; read_adc: reads the ADC value from the ADC and returns it in the accumulator
; ACC as 0-7 channel selection parameter
; return value: 8-bit ADC value in ACC
read_adc:
        mov     adccon2,acc
read_adc1:
        setb    sconv
read_adc2:
        jb      sconv,read_adc2
        mov     a,adcdatah
        anl     a,#0fh
        mov     b,a
        mov     a,adcdatal
        anl     a,#f0h
        orl     a,b
        swap    a

        ret

read_buttons:
        push    acc
        push    psw

        mov     a,p0                    ; read button state
        mov     p2,a                    ; write button state back to leds
                                        ; wait until button is unpressed
        cjne    a,#0,read_button

        cpl     a                       ; invert button state

        pop     psw
        pop     acc

        ret

delay:
        mov     r7, #255
delay1:
        mov     r6, #255
delay2:
        djnz    r6, delay2
        djnz    r7, delay1

        ret

; IMPORTED FUNCTIONS AND DECLARATIONS ---------------------------------------;

#include "serial.inc"
#include "dec.inc"
#include "i2c.inc"
end
