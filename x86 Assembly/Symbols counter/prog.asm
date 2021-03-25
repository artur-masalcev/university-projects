;;;Artur Masalcev
;;;LT: Parasyti programa, kuri skaiciuoja kiek simboliu yra ivestoje teksto eiluteje
;;;EN: Make a program, that countes amount of each type of symbols in the given string
;;;	   NOTICE: comments are writen in the Lithuanian language

.model small

.stack 100h

.code

    MAIN:
      
        JMP READ_FIRST_PARAM      
    READ_FIRST_PARAM_END:
    
        CALL IGNORE_SPACES
        
        MOV si, OFFSET param_2
               
    
    READ_SECOND_PARAM:
        CMP es:[bx], ' '         ;Jeigu pamatem tarpa - baigti skaityti
        JE  READ_SECOND_PARAM_END
        
        CMP es:[bx], 13          ;Jeigu pamatem eilutes pabaiga - baigti skaityti
        JE  READ_SECOND_PARAM_END
        
        CMP es:[bx], ax          ;Jeigu parametru eiluteje nera simboliu - baigti skaityti
        JE  READ_SECOND_PARAM_END
        
        MOV dh, es:[bx]
        MOV [si], dh
        
        INC si
        INC bx
        
        JMP READ_SECOND_PARAM
    READ_SECOND_PARAM_END:          
       
        ;-------------------------;
        ;Skaitymo failo atidarymas;
        ;-------------------------;
        
        MOV ax, 3d00h           ;Atidaryti faila skaitymui
	    MOV dx, offset param_1  ;Failo pavadinimas
	    INT 21h
	    
	    JC PRINT_READ_ERROR ;Jeigu failas neatidarytas - isvesti klaidos pranesima
	    MOV descriptor, ax  ;Issaugoti ax reiskme, kadangi jis dar bus naudojamas rezultato failo ikurimui
	    
	    
	    ;----------------------;
        ;Pagrindinis algoritmas;
        ;----------------------;
        
        
    READ_CYCLE:
        MOV bx, descriptor        ;Skaitymo opercaijai reikalinga, kad deskriptoriaus reiksme butu bx registre
        MOV ah, 3fh               ;Skaitymo is failo funkcija 
        MOV cx,100h               ;Kiek baitu yra skaitymo buferyje
        MOV dx, OFFSET input_buff ;Skaitymo bufero adresas
        INT 21h                   ;Skaityti faila
        JC PRINT_READ_ERROR       ;Jeigu Carry flag = 0, isvesti klaidos pranesima
        
        OR ax,ax          ;Jeigu ax = 0, tai reiskia, kad perskaitytas visias failas
        JZ READ_CYCLE_END ;Tokiu atveju, persokti i skaitymo ciklo pabaiga
        
        MOV cx, 0  
        MOV cx, ax ;CX = AX, kad realizuoti cikla
        
        MOV si, 0
        MOV bx, 0
        
        READ_BY_BYTE:
        
        MOV bl, input_buff[si] ;Issaugome i bx registra ascii simbolo reiksme
        INC table[bx]          ;Sita reiksme atitiks jos vietai rezultato lenteleje
        
        INC si
        
        LOOP READ_BY_BYTE 
        
        JMP READ_CYCLE
    READ_CYCLE_END:    
       
        ;---------------------------------------------------------------------;
        ;Uzdaromas skaitymo failas ir atidaromas/sukuriamas irasynejimo failas;
        ;---------------------------------------------------------------------;
        
        MOV ah, 3Eh          ;Uzdaryti skaitymo faila
	    MOV bx, offset descriptor
	    INT 21h
	    
	    MOV ah, 3dh             ;Atidaryti faila
	    MOV al, 1               ;Rasymui
	    MOV dx, offset param_2  ;Failo pavadinimas
	    INT 21h
	    
	    JNC OUTPUT               ;Jeigu failas neatidarytas - pabandyti ji sukurti
	    
	    MOV ah, 3ch              ;Sukurti faila
	    MOV cx, 0                ;Be papildomu nustatymu
	    MOV dx, offset param_2   ;Failo pavadinimas
	    INT 21h                
	    
	    MOV ah, 3dh             ;Vel atidaryti faila
	    MOV al, 1               ;Rasymui
	    MOV dx, offset param_2  ;Failo pavadinimas
	    INT 21h
	    
	    JC PRINT_OUTPUT_ERROR
	   
	    ;---------;
        ;Isvedimas;
        ;---------; 
	   
	OUTPUT:
	    MOV descriptor, ax   ;Issaugoti deskriptoriu
	    MOV cx, 127          ;(128 - 1) = 127 -> rezultato lenteles dydis atimti vienieta, nes ciklas pradedamas nuo 1(NULL dokumente greiciausiai nebus)
	    
	    MOV si, 0 ;pozicija rezultato lenteleje
	    MOV di, 0 ;pozicija isvedimo buferyje
	    
    OUTPUT_CYCLE:
	    INC si              
	    CMP table[si], 0h    ;Jeigu ascii simboliui atitinkamas langelis rezultato masyve tuscias
	    JE SKIP_OUTPUT_CYCLE ;Praleisti si ciklo zingsni
	    
        ;Desimtainio skaiciaus isvedimas;  
	    MOV ax, si     ;Kad galima butu isvesti 2 sesiuoliktanius skaitmenus, juos reikia suskirstiti i AH ir AL registrus           
	    MOV bx, 0010h
	    DIV bl
	    
	    CMP al, 9               ;Jeigu tai yra raide (A-F)
	    JA al_GREATER_THAN_NINE ;Isvesti raide
	    
	    ADD al, 30h             ;Jeigu tai yra skaicius(0-9), prideti 30h (Zr. ASCII lentele)
	    JMP SECOND_DIGIT        ;Persokti prie antro skaiciaus
	    
    al_GREATER_THAN_NINE:
	    ADD al, 55              ;Jeigu norima isvesti raide reikia prideti 55(Skaiciavimas atlikti vel pagal ASCII lentele)
	               
    SECOND_DIGIT:                 ;Viskas tas pats, bet su antru skaitmenu
	    CMP ah, 9
	    JA ah_GREATER_THAN_NINE
	    
	    ADD ah, 30h
	    JMP PRINT_SYMBOL
	    
    ah_GREATER_THAN_NINE:
	    ADD ah, 55
	    
	    ;Simbolio reiksmes ascii formatu isvedimas
    PRINT_SYMBOL:
	    MOV output_buff[di], al   ;Priskiriame gautusias reiksmes buferiui
	    INC di
	    
	    MOV output_buff[di], ah
	    INC di
	    
	    MOV output_buff[di], ' '  ;Spausdinome sklaustus, tarpus ir ASCII reiskme
	    INC di
	    MOV output_buff[di], '(' 
	    INC di                       
	    
	    MOV output_buff[di], ' '  ;Kolkas uzrasysim tarpa vietoj ASCII reiksmes
	    CMP si, 32                ;Jeigu sio simbolio nera prasmes spausdinti(pvz NEW LINE)
	    JB  UNABLE_TO_PRINT_ASCII ;Palikti tarpa
	    MOV ax, si
	    MOV output_buff[di], al ;Zinodamas, kad ax <= 00FF, isvedziu iskarto al
    UNABLE_TO_PRINT_ASCII:
	    
	    INC di
	    MOV output_buff[di], ')'
	    INC di
	    MOV output_buff[di], ':'
	    INC di
	    MOV output_buff[di], ' '
	    
	    ;Simbolio reiksmes rezultato lenteleje isvedimas(t.y. kiek kartu buvo sitas simbolis salygos faile)
	    ;Isvedimas desimtainiu formatu
	    CMP table[si], 99 ;Jiegu skaicius trizenklis
	    
	    JA THREE_DIGIT
	    
	    CMP table[si], 9  ;Jeigu skacius dvizenklis
	    
	    JA TWO_DIGIT
	                      ;Jeigu skaicius vienazenklis
    ONE_DIGIT:
	    INC di
	    MOV ah, table[si]
	    ADD ah, 30h
	    MOV output_buff[di], ah
	    INC di
	    
	    JMP PRINT
	    
    TWO_DIGIT:
	    INC di
	    MOV ax, 0
	    MOV al, table[si]
	    MOV bx, 000Ah
	    DIV bl
	    
	    ADD al, 30h
	    MOV output_buff[di], al
	    INC di
	    ADD ah, 30h
	    MOV output_buff[di], ah
	    INC di
	    
	    JMP PRINT
	    
    THREE_DIGIT:
	    ADD di, 3
	    
	    MOV ax, 0
	    MOV al, table[si]
	    MOV bx, 000Ah
	    DIV bl
	    
	    ADD ah, 30h
	    MOV output_buff[di], ah
	    
	    MOV ah, 0
	    
	    DIV bl
	    
	    DEC di
	    
	    ADD ah, 30h
	    MOV output_buff[di], ah
	    
	    DEC di
	    
	    ADD al, 30h
	    MOV output_buff[di], al
	    
	    ADD di, 3	    	    
	    
	    ;Rasymo buferio irrasymas i faila
	    PRINT:
	    
	    MOV output_buff[di], 13 ;Prirasoma nauja eilute
	    INC di
	    MOV output_buff[di], 10
	    
	    push cx                 ;Issaugome cx, jis reikalingas ciklui
	    
	    MOV ax, 4000h           ;Rasymas i faila
	    MOV bx, descriptor      ;Failo deskriptorius
	    
	    INC di                  ;Kadangi 13 - maksimali rasymo buferio reiksme, nebutinai visada reikes isvesti 13 simboliu
	    MOV cx, di              ;Jeigu skaicius dvizenklis pakankama 12 simboliu, jeigu vienazenklis - 11 simboliu
	    
	    MOV dx, offset output_buff
	    INT 21h
	    
	    JC PRINT_OUTPUT_ERROR   ;Jeigu rasymo metu ivyko klaida, ispausdinti pranesima ir baigti darba
	    
	    pop cx
	
	    MOV di, 0
	SKIP_OUTPUT_CYCLE:
	LOOP OUTPUT_CYCLE:      
    
    ;pabaiga
    EXIT:
        MOV ah, 4Ch
        MOV al, 0
        INT 21h
    
    ;---Proceduros---
    
    IGNORE_SPACES PROC
        CMP es:[bx], ' '      ;Jeigu simbolis nera tarpas
        JNE IGNORE_SPACES_END ;Sugrizti atgal
    
    IGNORE_SPACES_LOOP:       
        INC BX
        CMP es:[bx], ' '      ;Kol parametru teksto eilutes simbolis yra tarpas
        JE IGNORE_SPACES_LOOP ;Testi juos ignoruoti
        
    IGNORE_SPACES_END:
    RET
    
    ENDP
    
    PRINT_READ_ERROR:
        MOV ah, 9
        MOV dx, offset read_error_message 
        INT 21h
        JMP PRINT_HELP_MESSAGE
       
    PRINT_OUTPUT_ERROR:
        MOV ah, 9
        MOV dx, offset output_error_message 
        INT 21h
        JMP PRINT_HELP_MESSAGE 
        
    PRINT_HELP_MESSAGE:
        MOV ah, 9
        MOV dx, offset help_message 
        INT 21h
        JMP EXIT
    
    END