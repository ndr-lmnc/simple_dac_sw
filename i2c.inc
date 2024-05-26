; Simple DAC Practice Enterprice Project source code
; Written by Alessandro Lo Monaco v1 on 2024-05-01
;
; Based on analog devices application note uC001
; https://www.analog.com/media/en/technical-documentation/application-notes/uC001_-_MicroConverter_I2C_Compatible_Interface.pdf
;
; I2C SUBROUTINES ----------------------------------------------------------- ;
;

; 0xC0 = 0b11000000 up to 0xC6 = 0b11000110 excluding the last bit
; to allow this using a counter for 4 bits is better to use the address
; 0x60 = 0b01100000 up to 0x63 = 0b01100011 allowing to use the lr ACC
; before sending the IIC address to the TLC59116F

; ___________________________________________________________________________ ;
;                                                         init I2C subroutine
init_IIC:
    mov    I2CCON,#A8h      ; set master mode
    mov    OUTPUT,#0
    clr    NOACK
    clr    ERR

    ret

; ___________________________________________________________________________ ;
;
send_data_IIC:
    lcall   start_bit         ; acquire bus and send slave address

    mov     a,SLAVEADD       ; send slave address
    lcall   send_byte_IIC    ; sets NOACK if NACK received

    jb      NOACK,send_data_IIC_stop ; if NACK received, send stop

    mov     A,OUTPUT         ; send data
    lcall   send_byte_IIC

send_data_IIC_stop:
    lcall   stop_bit
    jnb     NOACK,send_data_IIC_ret ; if NACK not recived, return with NOERR
    setb    ERR

send_data_IIC_ret:
    ret


; ___________________________________________________________________________
;
send_byte_IIC:
    mov     BITCNT,#8
    setb    MDE       ; enable SDATA pin as output
    clr     MCO       ; make sure clock is low
send_bit:
    rlc     A         ; get next bit
    mov     MDO,C     ; set O/P on SDATA
    setb    MCO       ; set clock for bit
    clr     MCO       ; clear clock for next bit

    djnz    BITCNT,send_bit ; loop for all bits

    clr     MDE       ; disable SDATA pin as output
    setb    MCO       ; set clock for ACK
    jnb     MDI, next
    setb    NOACK     ; set NOACK if NACK received
next:
    clr     MCO       ; clear clock
    ret


; ___________________________________________________________________________
start_bit:
    setb   MDE      ; enable SDATA pin as output
    clr    NOACK
    clr    MDO      ; set O/P on SDATA
    clr    MCO      ; start bit

    ret

; ___________________________________________________________________________
stop_bit:
    setb   MDE      ; enable SDATA pin as output
    clr    MDO      ; get SDATA ready for stop
    setb   MCO      ; set clock for stop
    setb   MDO      ; this is the stop bit

    ret
