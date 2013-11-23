                dosseg
                .486
                .MODEL  USE16 LARGE           ;all call returns are 4 bytes!!!
                                              ; USE16 -> 16 bit segment regs !!!!!!
                                              ;      this is EXTREMELY IMPORTANT!
                
                .CODE
;
; Borland C++-callable function that set up VGA to bios mode passed
;  to it.
; 
;
; Function prototype:
;     extern void VGAm(int modeval);
;
; Input:
;     int modeval:              video mode for VGA card
                PUBLIC  _VGAm
_VGAm           PROC    FAR
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
_clrs           PROC    FAR
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
_SetPalette     PROC    FAR
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
_rbow           PROC    FAR
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


                PUBLIC  _slam_sprite
_slam_sprite    PROC    FAR
                ARG     sprite_addr:DWORD,savebuf:DWORD,screenb:DWORD,lines:WORD,width:WORD
                ; caller return [bp+0] - [bp+5] ;offset+seg return addr + pushed bp
                ; sprite_addr: (offset) [bp+6]
                ; sprite_addr: (segmnt) [bp+8]
                ; savebuf    : (offset) [bp+10]
                ; savebuf    : (segmnt) [bp+12]
                ; screenb    : (offset) [bp+14]
                ; screenb    : (segmmt) [bp+16]
                ; lines      : (offset) [bp+18]
                ; width      : (offset) [bp+20]
                      
                push    bp
                mov     bp,sp

                push    es              ;save em off to allay a C barf
                push    di
                push    ds
                push    si
                push    bx
                push    cx

                cld                             ; fwd pls
                les     di,savebuf              ;save off background @ savebuf
                lds     si,screenb              ; from our temporary screen buffer...
                mov     bx,lines                ; number of scan lines
                push    si
slamx1:         mov     cx,width                ;width in bytes
                shr     cx,1                    ;odd number of bytes?
                jnc     slamx1b
                movsb                           ;yup.. move a byte
slamx1b:        shr     cx,1                    ;odd number of words?
                jnc     slamx2                  
                movsw                           ;yup.. move a word
slamx2:         rep     movsd                   ;move double words...
                pop     si
                dec     bx                      ;next scan line until end.
                je      slam1
                add     si,320
                push    si
                jmp     slamx1
                
slam1:          lds     si,sprite_addr          ;move sprite..
                les     di,screenb              ;   to screen buffer
                mov     bx,lines                ;size in scan lines

                push    di

slam2:          mov     cx,width

slam3:          mov     al,ds:[si]              ;get sprite pixel
                cmp     al,0                    ;transparent?
                jz      slam4                   ;yup
                mov     es:[di],al              ;nope.        
slam4:          inc     si              
                inc     di
                dec     cx
                jne     slam3
                
                pop     di
                dec     bx
                je      slamexit
                add     di,320
                push    di
                jmp     slam2     

slamexit:       pop     cx              ;outta here!
                pop     bx
                pop     si
                pop     ds
                pop     di
                pop     es      
                pop     bp
                ret                     ;
_slam_sprite    ENDP

                PUBLIC  _zap_sprite
_zap_sprite     PROC    FAR
                ARG     zs_saved_background:DWORD,zs_screenb:DWORD,zs_lines:WORD,zs_width:WORD

                push    bp
                mov     bp,sp

                push    es              ;save em off to allay a C barf
                push    di
                push    ds
                push    si
                push    bx
                push    cx

                cld                             ; fwd pls
                les     di,zs_screenb
                lds     si,zs_saved_background
                mov     bx,zs_lines
                push    di
zapx1:          mov     cx,zs_width
                shr     cx,1
                jnc     zapx2
                movsb
zapx2:          shr     cx,1
                jnc     zapx3
                movsw
zapx3:          rep     movsd
                pop     di
                dec     bx
                je      zapexit
                add     di,320
                push    di
                jmp     zapx1

zapexit:        pop     cx              ;outta here!
                pop     bx
                pop     si
                pop     ds
                pop     di
                pop     es      
                pop     bp
                ret                     ;
_zap_sprite     ENDP


                PUBLIC  _scrn_updt
_scrn_updt      PROC    FAR
                ARG     l_screenbuf:DWORD,l_screen:DWORD,bytes_to_move:WORD

                push    bp
                mov     bp,sp

                push    es              ;save em off to allay a C barf
                push    di
                push    ds
                push    si
                push    cx

                
                lds     si,l_screenbuf          
;;;                mov     ds,[bp+8]               ;from
;;;                mov     si,[bp+6]
                les     di,l_screen             ;to
                mov     cx,bytes_to_move        ;amount
                cld                             ; fwd pls
                shr     cx,1
                jnc     su2
                movsb   
su2:            shr     cx,1
                jnc     su3
                movsw
su3:            rep     movsd

suexit:         pop     cx              ;outta here!
                pop     si
                pop     ds
                pop     di
                pop     es      
                pop     bp
                ret                     ;
_scrn_updt      ENDP


                END

