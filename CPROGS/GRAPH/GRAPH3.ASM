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
                ARG     sprite_addr:DWORD,savebuf:DWORD,screenb:DWORD,lines:WORD,sprite_width:WORD
                ; caller return [bp+0] - [bp+5] ;offset+seg return addr + pushed bp
                ; sprite_addr  : (offset) [bp+6]
                ; sprite_addr  : (segmnt) [bp+8]
                ; savebuf      : (offset) [bp+10]
                ; savebuf      : (segmnt) [bp+12]
                ; screenb      : (offset) [bp+14]
                ; screenb      : (segmmt) [bp+16]
                ; lines        : (offset) [bp+18]
                ; sprite_width : (offset) [bp+20]
                      
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
slamx1:         mov     cx,sprite_width         ;width in bytes
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

slam2:          mov     cx,sprite_width

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

JOYPORT         EQU     0201H           ;Joystick port

                  PUBLIC  _joy_button_read
_joy_button_read  PROC    FAR
                ARG     bitmask:WORD

                push    bp
                mov     bp,sp

                mov     dx,JOYPORT      
                mov     ah,0
                out     dx,al           ; ask for port...
                in      al,dx           ; get data from it.
                not     al              ; invert it due to joystick nonsense
                mov     bx,bitmask      ; mask out proper button
                and     al,bl           

                pop     bp              ; later.
                ret                     ;
_joy_button_read  ENDP

READ_JOY        EQU     84H
READ_JOYAXIS    EQU     1

;***********************************************
;below is not thoroughly tested and in transition... unusable!
;***********************************************

;                PUBLIC  _joy_axis_read
;_joy_axis_read  PROC    FAR
;                ARG     j1x,j1y,j2x,j2y:WORD
                ; before push of bx (or after pop)....
                ; caller return [bp+0] - [bp+5] ;offset+seg return addr + pushed bp
                ; j1x          : (offset) [bp+6]
                ; j1y          : (offset) [bp+8]
                ; j2x          : (offset) [bp+10]
                ; j2y          : (offset) [bp+12]

                ; after push of bx....
                ; caller return [bp+2] - [bp+7] ;offset+seg return addr + pushed bp
                ; j1x          : (offset) [bp+8]
                ; j1y          : (offset) [bp+10]
                ; j2x          : (offset) [bp+12]
                ; j2y          : (offset) [bp+14]

;                push    bp
;                mov     bp,sp
;
;                mov     ah,READ_JOY
;                mov     dx,READ_JOYAXIS
;                int     15H
;                push    bx
;                mov     bx,[bp+8]       ;get j1x addr.
;                mov     [bx],ax         ;mov j1x val to it
;                mov     bx,[bp+12]      ;get j2x addr
;                mov     [bx],cx         ;mov j2x val to it
;                mov     bx,[bp+14]      ; get j2y addr
;                mov     [bx],dx         ; mov j2y val to it
;                pop     ax              ; restore j1y val
;                mov     bx,[bp+8]       ; get j1y addr
;                mov     [bx],ax         ; move j1y val to it


;                cli                     ;don't interrupt us please...
;
;                mov     dx,JOYPORT      
;                mov     ah,byte ptr bitmask     ; for testing bit.
;                mov     al,0                    ; clear initially
;                mov     cx,0                    ; loop up to 64k
;
;                out     dx,al
;jx_notyet:      in      al,dx
;                test    al,ah
;                loopne  jx_notyet
;
;                sti                     ;ok ok...
;                mov     ax,0
;                sub     ax,cx           ; two's complement?
;                pop     bp
;                ret                     ;
;_joy_axis_read  ENDP


;
;       initialize mouse
;
                PUBLIC  _initmouse
_initmouse      PROC    FAR
                mov     ax,0
                int     33h
                ret                     ;
_initmouse      ENDP

;
;       show mouse pointer
;

                PUBLIC  _disppointer
_disppointer    PROC    FAR
                mov     ax,1
                int     33h
                ret                     ;
_disppointer    ENDP

;
;       hide mouse pointer
;
                PUBLIC  _rempointer
_rempointer     PROC    FAR
                mov     ax,2
                int     33h
                ret                     ;
_rempointer     ENDP
;
;       get mouse buttons
;
                PUBLIC  _readbutton
_readbutton     PROC    FAR
                mov     ax,3
                int     33h
                mov     ax,bx
                ret                     ;
_readbutton     ENDP
;
;        get relative position of mouse (in mickey's)
;
                PUBLIC  _relpos
_relpos         PROC    FAR
                ARG     x:DWORD,y:DWORD
                push    bp
                mov     bp,sp

                mov     ax,0Bh
                int     33h     
                les     bx,x
                mov     es:[bx],cx
                les     bx,y
                mov     es:[bx],dx

                pop     bp
                ret                     ;
_relpos         ENDP
                PUBLIC  _relpos

KEY_INTERRUPT   EQU     016h
KEY_SHIFT       EQU     12h
KEY_READY       EQU     1
KEY_GET         EQU     0

                PUBLIC  _keyRead
_keyRead        PROC    FAR
                push    bp
                mov     bp,sp

                mov     ah,KEY_READY
                int     KEY_INTERRUPT     
                jz      _keyRead_nothing
                mov     ah,KEY_GET
                int     KEY_INTERRUPT     
                jmp     _keyRead_exit
_keyRead_nothing:
                xor     ax,ax           ; clear it...
                        
_keyRead_exit:
                pop     bp
                ret                     ;
_keyRead        ENDP

                PUBLIC  _keyShiftStat
_keyShiftStat   PROC    FAR
                push    bp
                mov     bp,sp

                mov     ah,KEY_SHIFT
                int     KEY_INTERRUPT     
                        
                pop     bp
                ret                     ;
_keyShiftStat   ENDP



x_unit          DW      1
y_unit          DW      1
scr_offset      DW      1
ydiff           DW      1
xdiff           DW      1
error_term      DW      1
length          DW      1
i               DW      1

                PUBLIC  _linedraw_asm
_linedraw_asm   PROC    FAR
                ARG     x1:WORD,y1:WORD,x2:WORD,y2:WORD,color:WORD,screen:DWORD

                push    bp
                mov     bp,sp
                push    es              ;save em off to allay a C barf
                push    di
                push    ax
                push    bx
                push    cx
                push    dx
                les     di,screen       ;get passed address from C prog

                xor     ax,ax
                mov     error_term,ax

                mov     bx,320          ;int offset = y1 * 320 + x1
                mov     ax,y1           
                mul     bx
                add     ax,x1           ;add em..
                mov     scr_offset,ax

                mov     y_unit,320

                mov     ax,y2
                sub     ax,y1           ;y2 - y1
                jc      ld2             ;go to negative result
                                        ; else.. positive...
                mov     ydiff,ax
                jmp     ld3
ld2:                                    ; negative result logic
                neg     ax
                mov     ydiff,ax
                neg     y_unit
ld3:
                mov     x_unit,1
        
                mov     ax,x2
                sub     ax,x1           ;x2 - x1
                jc      ld4             ;go to negative result
                                        ; else.. positive...
                mov     xdiff,ax
                jmp     ld5
ld4:                                    ; negative result logic
                neg     ax
                mov     xdiff,ax
                neg     x_unit
ld5:
                mov     ax,xdiff
                cmp     ax,ydiff        ;xdiff - ydiff
                jc      ld6             ;xdiff < ydiff!
                                        ; must be xdiff > ydiff...
                mov     bx,scr_offset   ; 
                mov     cx,color        ;
                mov     dx,xdiff        ;length = xdiff + 1  (dx)
                inc     dx
                xor     ax,ax           ;error_term
xdg_loop:
                mov     es:[bx + di],cl ;screen[scr_offset] = color
                add     bx,x_unit       ; scr_offset += x_unit
                add     ax,ydiff        
                cmp     ax,xdiff        ; error_term >= xdiff ?
                jl      xdg_loop2       ; take if no.
                sub     ax,xdiff        ; yup... error_term -= xdiff
                add     bx,y_unit       ; scr_offset += y_unit
xdg_loop2:
                dec     dx
                jnz     xdg_loop
                jmp     bresh_out

ld6: 
                mov     bx,scr_offset
                mov     cx,color        ;
                mov     dx,ydiff        ;length = ydiff + 1  (dx)
                inc     dx
                xor     ax,ax           ;error_term
xdg_loop4:
                mov     es:[bx + di],cl ;screen[scr_offset] = color
                add     bx,y_unit       ; scr_offset += y_unit
                add     ax,xdiff        
                cmp     ax,ydiff        ; error_term >= ydiff ?
                jl      xdg_loop3       ; take if no.
                sub     ax,ydiff        ; yup... error_term -= ydiff
                add     bx,x_unit       ; scr_offset += x_unit
xdg_loop3:             
                dec     dx
                jnz     xdg_loop4

bresh_out:
                pop     dx
                pop     cx
                pop     bx
                pop     ax
                pop     di
                pop     es
                pop     bp
                ret                     
_linedraw_asm   ENDP

                END

