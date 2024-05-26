; Simple DAC Practice Enterprice Project source code
; Written by Alessandro Lo Monaco v1 on 2024-05-01
;
; IC: TLC56116F
;
;

; INIT TLC56116F -------------------------------------------------------------- ;
;
init_tlc56116f:
    mov     OUTPUT,#10000000b       ; AUTO_INCREMENT_ALL_REGISTERS
    lcall   send_data_IIC

    mov     OUTPUT,#00h             ; no sub-addressing
    lcall   send_data_IIC

    mov     OUTPUT,#00h             ; dimming
    lcall   send_data_IIC

    mov     r0,#11h                 ; 0x11 = 17
init_tlc56116f2:
    mov     OUTPUT,#ffh             ; individual maximum brightness
    lcall   send_data_IIC

    djnz    r0,init_tlc56116f2

    mov     OUTPUT,#ffh             ; grppwm full brightness
    lcall   send_data_IIC

    mov     OUTPUT,#ffh             ; grpfreq disable blinking
    lcall   send_data_IIC

    mov     r0,#04h
init_tlc56116f3:
    mov     OUTPUT,#00h             ; LED off
    lcall   send_data_IIC

    djnz    r0,init_tlc56116f3

    ret

;
;
set_start_address:
    mov     OUTPUT,#94h             ; Auto-increment + Start address
    lcall   send_data_IIC

    ret


;
;
send_ledout:
    lcall   send_data_IIC

    ret
