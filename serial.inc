; Dependencie for serial uart communication

init_serial:
    ; Set up the timer 1 as a baud rate generator
    mov  tmod, #20h ; Timer 1, mode 2, 8-bit auto reload
    mov  th1, #fdh ; 9600 baud rate for 16.777216 MHz
    setb tr1 ; Start timer 1
    setb sm0 ; Serial mode 1, 8-bit UART, variable baud rate
    clr  sm1
    setb ren ; Enable serial reception
    RET

send_byte:
    jnb  ti, send_byte ; Wait until the byte is sent
    clr  ti ; Clear the flag
    mov  sbuf, a ; Send the byte
    RET