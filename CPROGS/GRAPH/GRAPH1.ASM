
                DOSSEG
                .MODEL  LARGE
                
                .CODE
;
; Turbo C-callable function that set up VGA to bios mode passed
;  to it.
; 
;
; Function prototype:
;     extern void VGAm(int modeval);
;
; Input:
;     int modeval:              video mode for VGA card
                PUBLIC  _VGAm
_VGAm           PROC
                ARG     modeval:WORD
                push    bp
                mov     bp,sp
                mov     ax,modeval      ;mode to set up vga 
                mov     ah,0            ;set mode command byte
                int     10h             ;call the BIOS
                
                pop     bp              ; outta here.
                ret                     ;
_VGAm           ENDP

;
; Turbo C-callable function that clears a screen or 
;  block of memory to a particular value
; 
;
; Function prototype:
;     extern void clrs(unsigned int *screen,
;                      unsigned int val     );
;
; Input:
;       char far *screen:   far pointer to memory
;       unsigned int val    :   value to stuff into memory

SCREEN_WIDTH    EQU     320     ;screen width
SCREEN_DEPTH    EQU     200     ;screen depth

                PUBLIC  _clrs
_clrs           PROC
                ARG     screen:DWORD,val:WORD
                push    bp
                mov     bp,sp

                push    es              ;save em off to allay a C barf
                push    di

                les     di,screen       ;get passed address from C prog
                mov     ax,val          ;value to use in screen clear
                mov     cx,(SCREEN_WIDTH/2)*SCREEN_DEPTH
                                        ;count of pixels to clear (based on
                                        ; word moves... NOT BYTE MOVES!!

                rep     stosw           ;BLOW THE SOB ONTO THE SCREEN PRONTO

                pop     di              ; outta here.                
                pop     es              ;
                pop     bp              ;
                ret                     ;
_clrs           ENDP
;
; routine for setting the VGA palette
;
                PUBLIC  _SetPalette
_SetPalette     PROC    
                ARG     regs:DWORD
                push    bp
                mov     bp,sp

                les     dx,regs         ;point to c structure
                mov     ah,10h          ;BIOS function 10h
                mov     al,12h          ;set palette function
                mov     bx,0            ;start at register 0
                mov     cx,100h         ;the whole magilla
                int     10h             ;do it.

                pop     bp              ;outta here.
                ret
                ENDP



; nice little procedure for creating the current VGA palette as a 
; horizontal rainbow on the screen.  Of absolutely no use whatsoever!

                PUBLIC  _rbow
_rbow           PROC
                push    bp
                mov     bp,sp

                push    es              ;save em off to allay a C barf
                push    di

                mov     ax,0A000h       ;blow screen address into       
                mov     es,ax           ;es:di
                mov     di,0

                mov     cx,200          ;row count 

rbow1:          mov     bx,255          ;column/color count

rbow2:          mov     es:[bx+di],bl   ;blow color onto screen
                dec     bx              ; for 'column' counts
                jge     rbow2           ; until were finito w/ row
                
                add     di,320          ; next row
                dec     cx              ; until finito with all rows
                jne     rbow1

                pop     di              ; outta here.                
                pop     es              ;
                pop     bp              ;
                ret                     ;
_rbow           ENDP

                END 
