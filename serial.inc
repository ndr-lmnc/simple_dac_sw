; Dependencie for serial uart communication

init_serial:
    ; timer 3 for boud generation with internal core clock?
    mov     t3con,#82h
    MOV     t3fd,#2Dh
    MOV     scon,#52h
    RET

send_byte:
    jnb  ti, send_byte ; Wait until the byte is sent
    clr  ti ; Clear the flag
    mov  sbuf, a ; Send the byte
    RET
