
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt




.data 

    



 
;=========MACROS=================================  
   
   
 

 ; 1. print
 ; print x length 
  print macro string,length
     local entry
    mov SI,OFFSET string 
    mov cx,length   
    ENTRY:    
        mov al,[SI]
        mov ah,0eh ;
        int 10h 
        inc SI
    loop ENTRY     
  endm 
  
;================================== check

check macro p1 
    LOCAL DONOTHING,INCREMENT,END,here,there
     cmp [si],p1
    je doNothing  
     jne increment
     
      
     doNothing:
     jmp end
       
       
      
    increment:
    cmp [si],'X'
    je doNothing
     jne here
     here:
     cmp [si],'O'
     je doNothing
     jne doNothing
     
     jmp end
    
    end:
    endm 
;labels 


    
;end labels

  
; print table

print_table macro p1 ;== paramater
    LOCAL OUTER,LINE
                         
                       ; "      1 | 2 | 3 |    \n" 0ah,0dh => \n
                       ; "      4 5 6   "
    mov cx,tlength;
    MOV SI,OFFSET P1
    OUTER:
      MOV AL,[SI];
      mov ah,0eh
       int 10h
       INC SI 
          LOOP OUTER 
    mov cx,lineLength 
    mov si,offset newLine
    line:
    mov al , [si]
    mov ah,0eh;
    int 10h
    inc si
    loop line
         endm


;========new Macros=======================
; is the firstpalyer is the winner
 IsFirstTheWinner macro string 
      local outer,inner,outer2,outer3,inner2,inner3,outer4,inner4,end
      mov si,offset string 
      add si,10;
      mov bx,3
      mov cx,bx
    ;rows
    outer:
    mov dl,-1          
    mov cx,3         ; X X X  
                     ; 3 X 5
                     ; 6 7 8
    inner:
    AND dl,[si]
    add si,4
    loop inner
     cmp dl,"X"
     je win1
     ;jne continue  
     mov cx,bx
     dec bx
     add si,34
  loop outer 
  
  
  ;columns
  mov si,offset string
  add si,10;
      mov bx,3
      mov cx,bx
  outer2:
    mov dl,-1
    mov cx,3   
    inner2:
    AND dl,[si]
    add si,46
    loop inner2
     cmp dl,"X"
     je win1
     ;jne continue  
     mov cx,bx
     dec bx 
     add si,-138
     add si,4
  loop outer2  
  

  ;diagonals
   ;mov di ,offset values
  
   mov si,offset string
   add si,10
      mov bx,2
      mov cx,bx
  outer3:
    mov dl,-1
    mov cx,3   
    inner3:
    AND dl,[si]
    ADD SI , 50
     loop inner3
     cmp dl,"X"
     je win1
     ;jne continue         ; "            1 2 3"  
     mov cx,bx
     dec bx 
     mov si,offset string
     add si,18
  loop outer3
  
  
   mov si,offset string
   add si,10
      mov bx,2
      mov cx,bx
  outer4:
    mov dl,-1
    mov cx,3   
    inner4:
    AND dl,[si]
    ADD SI,42;
    loop inner4
     cmp dl,"X"
     je win1
     ;jne continue  
     mov cx,bx
     dec bx 
     mov si,offset string
     add si,18
     
  loop outer4
  
  
  jmp end   
    
  win1:
  print firstPlayerWins firstLength 
  ret
  
    
      
      
   end: 
   endm
;========================================================
; is the second is the winner   
   IsSecondTheWinner macro string
      local outer,inner,outer2,outer3,inner2,inner3,end
      mov si,offset string
      mov bx,3
      mov cx,bx
    
    mov si,offset string 
      add si,10;
      mov bx,3
      mov cx,bx
    ;rows
    outer:
    mov dl,-1
    mov cx,3   
    inner:
    AND dl,[si]
    add si,4
    loop inner
     cmp dl,"O"
     je win2
     ;jne continue  
     mov cx,bx
     dec bx
     add si,34
  loop outer 
  
  
  ;columns
  mov si,offset string
  add si,10;
      mov bx,3
      mov cx,bx
  outer2:
    mov dl,-1
    mov cx,3   
    inner2:
    AND dl,[si]
    add si,46
    loop inner2
     cmp dl,"O"
     je win2
     ;jne continue  
     mov cx,bx
     dec bx 
     add si,-138
     add si,4
  loop outer2  
  

  ;diagonals
   ;mov di ,offset values
  
   mov si,offset string
   add si,10
      mov bx,2
      mov cx,bx
  outer3:
    mov dl,-1
    mov cx,3   
    inner3:
    AND dl,[si]
    ADD SI , 50
     loop inner3
     cmp dl,"O"
     je win2
     ;jne continue  
     mov cx,bx
     dec bx 
     mov si,offset string
     add si,18
     
  loop outer3
  
  
   mov si,offset string
   add si,10
      mov bx,2
      mov cx,bx
  outer4:
    mov dl,-1
    mov cx,3   
    inner4:
    AND dl,[si]
    ADD SI,42;
    loop inner4
     cmp dl,"O"
     je win2
     ;jne continue  
     mov cx,bx
     dec bx 
     mov si,offset string
     add si,18
     
  loop outer4
  
  
  jmp end   
    
  win2:
  print secondPlayerWins secondLength 
  ret
 
      
      
   end: 
    endm
;============================================================== 
printnewLine macro 
      local line
      mov si,offset newLine
      mov cx,lineLength
      line:   
           mov al,[si]
           mov ah,0eh
           int 10h
           inc si
      
      loop line
      
      
      endm
;====================================================================
; change the table according to the 1st player move 
replaceFirst macro char
       local replace,exit 
      
      
      cmp [si],char
      je replace   
      jne exit
     
  replace:
    mov [si],"X"
    jmp exit  
    
    
    exit:    
    endm
;============================================ 
 firstchoice macro choice
        
     local edit,valid,OuterValid,WRNG,exit ; local label
     
     valid:
    mov cx,tlength;
    MOV SI,OFFSET table
    OuterValid:
      cmp choice , [si]
      je edit 
      inc si
    LOOP OuterValid 
   
    jmp WRNG 
     
     
     
     
     
     
     edit:
     
     mov [si],"X"
     print_table table
     
      ;LOCAL OUTER,XO,LINE
    
    
   ;mov cx,tlength
;    MOV SI,OFFSET table
;    OUTER:  
;    replaceFirst choice
;      MOV AL,[SI];
;       mov ah,0eh
;       int 10h
;       INC SI
;         LOOP OUTER
;     mov cx,lineLength 
;     mov si,offset newLine
;    line:
;    mov al ,[si]
;    mov ah,0eh;
;    int 10h
;    inc si
;    loop line
   jmp exit 
 WRNG: ; wrong choice INVALID
    print wrongChoice WL
    printnewLine
    mov ah,1
    int 21h
    mov choice,al 
    printnewLine
    jmp valid
        
      
         
        
   exit:     
    endm
;==================================================================
; change the table according to the 1st player move 
 replaceSecond macro char
       local replace,donothing,exit 
      cmp [si],char
      je replace 
      
      
      jne donothing 
     
    
    replace:
    mov [si],"O"
    
    jmp exit
    donothing:
    jmp exit
    
    exit:    
    endm
;====================================================== 
 secondchoice macro choice
     local edit,valid,OuterValid,WRNG ; local label
     
     valid:
    mov cx,tlength;
    MOV SI,OFFSET table
    OuterValid:
      cmp choice , [si]
      je edit 
      inc si
    LOOP OuterValid 
   
    jmp WRNG 
     local edit
   ; mov cx,tlength
;    mov si,offset table 
     edit:
      LOCAL OUTER,XO,LINE
    
      mov [si],"O"
       print_table table
   ;mov cx,tlength
;    MOV SI,OFFSET table
;    OUTER:  
;    replaceSecond choice
;      MOV AL,[SI];
;      
;      mov ah,0eh
;       int 10h
;       INC SI
;         LOOP OUTER
;     mov cx,lineLength 
;     mov si,offset newLine
;    line:
;    mov al , [si]
;    mov ah,0eh;
;    int 10h
;    inc si
;    loop line
    jmp exit
  WRNG: ; wrong choice INVALID
    print wrongChoice WL
    printnewLine
    mov ah,1
    int 21h
    mov choice,al 
    printnewLine
    jmp valid  
    
      
         
        
    exit:    
    endm