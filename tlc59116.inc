; Simple DAC Practice Enterprice Project source code
; Written by Alessandro Lo Monaco v1 on 2024-05-01
;
; IC: TLC59116F
;
; TLC59116F SUBROUTINES ----------------------------------------------------- ;

; ___________________________________________________________________________ ;
;                                             Set start address for TLC59116F
set_start_address:
    mov     OUTPUT,#94h             ; Auto-increment + Start address
    lcall   send_data_IIC

    ret
