; Simple DAC Practice Enterprice Project source code
; Written by Alessandro Lo Monaco v1 on 2024-05-01
;
; ___________________________________________________________________________
;
;                                                      Serial UART subroutine

init_serial:
    ; timer 3 for boud generation with internal core clock of 16.777216Mhz
    ; DIV  = log(16777216 / 32 * 9600) / log(2) = 5.77 = 5 = 0x85
    ; T3FD = (2 * 16777216) / (2^5 * 9600) = 109.22 = 109 = 0x6D
    mov     t3con,#85h
    mov     t3fd,#6Dh
    mov     scon,#52h

    ret


; ___________________________________________________________________________
;
send_byte:
    jnb  ti, send_byte  ; Wait until the byte is sent
    clr  ti             ; Clear the flag
    mov  sbuf, a        ; Send the byte

    ret
