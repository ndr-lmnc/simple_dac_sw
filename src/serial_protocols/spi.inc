; Simple DAC Practice Enterprice Project source code
; Written by Alessandro Lo Monaco v1 on 2024-05-01
;
; SPI SUBROUTINES ----------------------------------------------------------- ;
;

; _____________________________________________________________________________ ;
;                                                                Initialize SPI
init_SPI:
        mov     spicon,#00000000b       ; set SPI control register
                                        ; SPI master mode
                                        ; SPI clock = 16,777216 MHz / 2 = 8,388608 MHz
                                        ; SPI clock polarity = 0
                                        ; SPI clock phase = 0
                                        ; SPI clock rate = 0

        ret
