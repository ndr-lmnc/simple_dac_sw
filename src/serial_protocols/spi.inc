; Simple DAC Practice Enterprice Project source code
; Written by Alessandro Lo Monaco v1 on 2024-05-01
;
; SPI SUBROUTINES ----------------------------------------------------------- ;
;

; _____________________________________________________________________________ ;
;                                                                Initialize SPI
init_SPI:
        mov     spicon,#00110001b       

        ret

; _____________________________________________________________________________ ;
;                                                    Write SPI control register
write_control_register:
        clr     cs
        clr     dc
        mov     spidat,a
write_control_register1:
        jnb     ispi,write_control_register1
        clr     ispi
        setb    cs

        ret

; _____________________________________________________________________________ ;
;                                                       Write SPI data register
write_data_register:
        clr     cs
        setb    dc
        mov     spidat,a
write_data_register1:
        jnb     ispi,write_data_register1
        clr     ispi
        setb    cs

        ret
