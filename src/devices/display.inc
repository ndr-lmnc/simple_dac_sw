; Simple DAC Practice Enterprice Project source code
; Written by Alessandro Lo Monaco v1 on 2024-05-01
;
; HW: EA OLEDS102-6LGA
; 
; Datasheet:
; https://www.lcd-module.com/fileadmin/eng/pdf/grafik/oleds102-6e.pdf
;
; Display Subroutines ------------------------------------------------------- ;
;

; ___________________________________________________________________________ ;
;                                                          Initialize Display
init_display:
    push   acc

    clr    reset

    lcall  delay

    setb   reset

    mov    a,#40h                   ; Set display start line
    lcall  write_control_register

    mov    a,#A0h                   ; Bottom view no segment remap
    lcall  write_control_register

    mov    a,#C0h                   ; Bottom view COM scan direction normal
    lcall  write_control_register

    mov    a,#2Eh                   ; StartColumnAddress
    lcall  write_control_register

    mov    a,#8Dh                   ; Switch charge pump (9V)
    lcall  write_control_register
    mov    a,#95h
    lcall  write_control_register

    mov    a,#20h                   ; Set memory addressing mode
    lcall  write_control_register
    mov    a,#02h
    lcall  write_control_register

    mov    a,#81h                   ; Set brightness
    lcall  write_control_register
    mov    a,#FFh
    lcall  write_control_register

    mov    a,#D5h                   ; Set display clock divide
    lcall  write_control_register
    mov    a,#40h
    lcall  write_control_register

    mov    a,#D9h                   ; Set pre-charge period
    lcall  write_control_register
    mov    a,#F1h
    lcall  write_control_register

    mov    a,#ADh                   ; Set internal reference
    lcall  write_control_register
    mov    a,#30h
    lcall  write_control_register

    mov    a,#21h                   ; Set column address
    lcall  write_control_register
    mov    a,#0Dh
    lcall  write_control_register
    mov    a,#72h
    lcall  write_control_register

    mov    a,#22h                   ; Set page address
    lcall  write_control_register
    mov    a,#00h
    lcall  write_control_register
    mov    a,#3Fh
    lcall  write_control_register

    mov    a,#AFh                   ; Display on
    lcall  write_control_register

    pop    acc

    ret

; ___________________________________________________________________________ ;
;                                                           Display Clear RAM
clear_display:
    push   acc
    push   b
    push   00h

    mov    r0,#6                        ; 7 pages
clear_display_page_loop:
    mov    b,#255                       ; 101 columns

clear_display_loop:
    mov    a,#00h                       ; Clear data
    lcall  write_data_register

    djnz   b,clear_display_loop         ; Loop for all columns
    ;djnz   r0,clear_display_page_loop   ; Loop for all pages

    pop    00h
    pop    b
    pop    acc

    ret

; ___________________________________________________________________________ ;
;                                                    Write Display Data Byte
write_display_data:
    mov    a,#FFh
    lcall  write_data_register

    ret
