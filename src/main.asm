; Simple DAC Practice Enterprice Project source code
; Written by Alessandro Lo Monaco v1 on 2024-05-01
;
; Hardware: ADuC832
;
;

org     0000h
ljmp    main

; MAIN VARIABLES ------------------------------------------------------------ ;
;
CHANNELS    EQU    030h
BUTTONS     EQU    031h
BUTMASK     EQU    P0
LEDS        EQU    P2


; I2C VARIABLES ------------------------------------------------------------- ;
;
SLAVEADD   EQU    032h
OUTPUT     EQU    033h
BITCNT     EQU    034h

NOACK      BIT    035h       ; Some flags but strange Bit assotiation
ERR        BIT    036h

; MAIN PROGRAM -------------------------------------------------------------- ;

main:
        mov     sp, #7fh
;        mov     SLAVEADD,#60h   ; This slave address is shifted to the left by 1 bit for the WRITE operation

        lcall   init_clock   ; set the clock to 16.777216 MHz all next operations are based on this clock
        ;lcall   init_IIC     ; initialize IIC communication
        lcall   init_SPI     ; initialize SPI communication
        lcall   init_display ; initialize display
        lcall   init_serial  ; initialize serial communication to 9600 baud
        lcall   init_adc     ; initialize ADC
;        lcall   init_volume  ; initialize volume bars
loop:
        mov     CHANNELS,#7
        mov     BUTMASK,#10000000b
loop1:
        mov     a,CHANNELS   ; need loop for all 8 channels and send to serial
        lcall   read_adc     ; read ADC value of channel in ACC

        lcall   send_byte    ; send read value to serial
        mov     a,CHANNELS
        lcall   send_byte    ; send channel number to serial

        ;mov     a,BUTTONS    ; read button state
        ;anl     a,BUTMASK
        ;cjne    a,#0,loop1   ; if button is pressed, skip to next channel

;        mov     r0,#aah
;        lcall   set_volume

loop2:
        ljmp    loop

; INITIALIZATION SUBROUTINES -------------------------------------------------- ;

; _____________________________________________________________________________ ;
;                                                              Initialize Clock
; init_clock: initializes the PLL to 16.777216 MHz
init_clock:
        push    psw
        push    acc
        mov     pllcon, #00h
        pop     acc
        pop     psw

        ret

; _____________________________________________________________________________ ;
;                                                                Initialize ADC
init_adc:
        mov     adccon1,#10001100b      ; set ADC control register 1
                                        ; Enable ADC
                                        ; Conversion time 32 = 16,777216 MHz / 32 = 524288 Hz
                                        ; Acquisition time 1

        ret

; _____________________________________________________________________________ ;
;                                                        Initialize Volume Bars
;init_volume:
;        push    acc
;        push    psw

;        mov     a,SLAVEADD
;        rl      a
;        mov     SLAVEADD,a

;        lcall   init_tlc56116f

;        mov     a,SLAVEADD
;        rr      a
;        mov     SLAVEADD,a

;        inc     SLAVEADD
;        mov     a,SLAVEADD
;        cjne    a,#64h,init_volume   ; if slave address does not reach 0x64, loop

;        pop     psw
;        pop     acc

;        ret

; MAIN SUBROUTINES ------------------------------------------------------------ ;

; _____________________________________________________________________________ ;
;                                                                      read_adc
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

; _____________________________________________________________________________ ;
;                                                                  read_buttons
;read_buttons:
;        push    acc
;        push    psw

;        mov     a,p0                    ; read button state
;        mov     p2,a                    ; write button state back to leds
;                                        ; wait until button is unpressed
;        cjne    a,#0,read_button

;        cpl     a                       ; invert button state

;        pop     psw
;        pop     acc

;        ret

; _____________________________________________________________________________ ;
;                                                           set_volue_bar (IIC)
; set the volume bar to the nibble in r0 (0 to 16) to the SLAVEADD channel
set_volume:
        push    psw

        lcall   set_start_address

set_volume1:
        mov     r1,#00h     ; output byte
        mov     r2,#04h     ; 2bit counter

set_volume2:
        mov     a,r1
        orl     a,#01h
        rl      a
        rl      a
        mov     r1,a

        djnz    r2,set_volume2

        mov     a,r1
        lcall   send_byte
        mov     OUTPUT,r1
        lcall   send_byte_IIC

        djnz    r0,set_volume1

        pop     psw
        ret

; _____________________________________________________________________________ ;
;                                                              delay subroutine
delay:
        mov     r7, #255
delay1:
        mov     r6, #255
delay2:
        djnz    r6, delay2
        djnz    r7, delay1

        ret

; IMPORTED SUBROUTINES AND DECLARATIONS ---------------------------------------;

#include "dec.inc"
#include "serial.inc"
#include "i2c.inc"
#include "tlc59116.inc"
end
