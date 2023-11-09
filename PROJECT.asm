
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h
  
.data  
  
  wrongChoice DB "wrong choice, try again",0
  WL = ($-wrongChoice)
  firstPlayerWins DB "FIRST PLAYER WINS!",0; 
  firstLength = ($-firstPlayerWins)
  secondPlayerWins DB "SECOND PLAYER WINS!",0;
  secondLength = ($-secondPlayerWins) 
  Tie DB "NO ONE WINS!",0
  tieLength = ($-Tie)  
  WELCOME DB "welcome to TIC TAC TOE game...press any key to continue",0AH,0DH;
  welLength = ($-WELCOME)
  table DB "          1 | 2 | 3 |",0ah,0dh
        DB "          -----------",0ah,0dh
        DB "          4 | 5 | 6 |",0ah,0dh 
        DB "          -----------",0ah,0dh
        DB "          7 | 8 | 9 |",0ah,0dh
        DB "          -----------",0ah,0dh
  TLENGTH = ($-table)  
  newLine db 0ah,0dh
  lineLength = ($-newLine)
  firstPlayerMove DB "First Player Move: ",0;
  FPM = ($-firstPlayerMove) 
  secondPlayerMove DB "Second Player Move: ",0;
  SPM = ($-secondPlayerMove) 
  
 include functions.inc 
 
 
 
.code





jmp MAIN  
 
  

  
 

 
 
MAIN PROC
   
   print WELCOME,welLength

   mov ah,1 ;press any key
   int 21h  ; to continue
   printnewLine
   printnewLine
   print_table table ; draw table
   
    
    
    mov dh,5
    mov cx,0
    mov cl,dh  ; intialize counter to 5
   
    prog:
     print firstPlayerMove FPM; print first player move
     MOV AH,1; get input from first player
     INT 21H; 
     mov dl,al;
     printnewLine   
     firstchoice dl; replace choice of the player with "X"
     IsFirstTheWinner table ; check if the first wins 
     
     mov cx,0
     mov cl,dh
     CMP cx,1 ;check if it is the last cell
     je finish
     print secondPlayerMove SPM
     MOV AH,1;get input from second player
     INT 21H;
     mov dl,al;  
     printnewLine   
     secondchoice dl ; replace choice of the second player with "O"
     printnewLine
     IsSecondTheWinner table ; check if the second wins
        mov cx,0
        mov cl,dh   ; reset value of cx
        dec dh
         loop prog
     
   finish:
   print Tie tieLength  ; no one wins

 ret
 
 
 
endp
end main