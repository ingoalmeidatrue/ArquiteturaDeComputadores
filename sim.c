#include <stdio.h>
#include "shell.h"
#include <string.h>
#include <math.h>
char convertidoBin[32];
int pos;
//conversor de hexadecimal para binario
void convertHexToBin(uint32_t x){
    //char bin[32];
    int i,j,k;
    int save = 0;
    int size = 0;
    char tam[50] = {'\0'};
    char hex[50];
    for(i = 0; i < 32;i++){
        convertidoBin[i] = 0;
    }
    sprintf(tam, "%x", mem_read_32(NEXT_STATE.PC));
    for(j = 0; j < 8;j++){
        if(tam[j] == '\0'){
            size++;
        }
    }
    for(int i=0;i<8;i++){
        hex[i] = '0';
    }
    for(int i=0;i<8;i++){
        if(i>size-1){
            hex[i] = tam[i-size];
        }
    }
    for(k = 0;k < 8;k++){
        int aux;
        aux = k*4;
        if(hex[k] == '0'){
            convertidoBin[aux] = '0';
            convertidoBin[aux + 1] = '0';
            convertidoBin[aux + 2] = '0';
            convertidoBin[aux + 3] = '0';
        }
        if(hex[k] == '1'){
            convertidoBin[aux] = '0';
            convertidoBin[aux + 1] = '0';
            convertidoBin[aux + 2] = '0';
            convertidoBin[aux + 3] = '1';
        }
        if(hex[k] == '2'){
            convertidoBin[aux] = '0';
            convertidoBin[aux + 1] = '0';
            convertidoBin[aux + 2] = '1';
            convertidoBin[aux + 3] = '0';
        }
        if(hex[k] == '3'){
            convertidoBin[aux] = '0';
            convertidoBin[aux + 1] = '0';
            convertidoBin[aux + 2] = '1';
            convertidoBin[aux + 3] = '1';
        }
        if(hex[k] == '4'){
            convertidoBin[aux] = '0';
            convertidoBin[aux + 1] = '1';
            convertidoBin[aux + 2] = '0';
            convertidoBin[aux + 3] = '0';
        }
        if(hex[k] == '5'){
            convertidoBin[aux] = '0';
            convertidoBin[aux + 1] = '1';
            convertidoBin[aux + 2] = '0';
            convertidoBin[aux + 3] = '1';
        }
        if(hex[k] == '6'){
            convertidoBin[aux] = '0';
            convertidoBin[aux + 1] = '1';
            convertidoBin[aux + 2] = '1';
            convertidoBin[aux + 3] = '0';
        }
        if(hex[k] == '7'){
            convertidoBin[aux] = '0';
            convertidoBin[aux + 1] = '1';
            convertidoBin[aux + 2] = '1';
            convertidoBin[aux + 3] = '1';
        }
        if(hex[k] == '8'){
            convertidoBin[aux] = '1';
            convertidoBin[aux + 1] = '0';
            convertidoBin[aux + 2] = '0';
            convertidoBin[aux + 3] = '0';
        }
        if(hex [k] == '9'){
            convertidoBin[aux] = '1';
            convertidoBin[aux + 1] = '0';
            convertidoBin[aux + 2] = '0';
            convertidoBin[aux + 3] = '1';
        }
        if(hex[k] == 'a'){
            convertidoBin[aux] = '1';
            convertidoBin[aux + 1] = '0';
            convertidoBin[aux + 2] = '1';
            convertidoBin[aux + 3] = '0';
        }
        if(hex[k] == 'b'){
            convertidoBin[aux] = '1';
            convertidoBin[aux + 1] = '0';
            convertidoBin[aux + 2] = '1';
            convertidoBin[aux + 3] = '1';
        }
        if(hex[k] == 'c'){
            convertidoBin[aux] = '1';
            convertidoBin[aux + 1] = '1';
            convertidoBin[aux + 2] = '0';
            convertidoBin[aux + 3] = '0';
        }
        if(hex[k] == 'd'){
            convertidoBin[aux] = '1';
            convertidoBin[aux + 1] = '1';
            convertidoBin[aux + 2] = '0';
            convertidoBin[aux + 3] = '1';
        }
        if(hex[k] == 'e'){
            convertidoBin[aux] = '1';
            convertidoBin[aux + 1] = '1';
            convertidoBin[aux + 2] = '1';
            convertidoBin[aux + 3] = '0';
        }
        if(hex[k] == 'f'){
            convertidoBin[aux] = '1';
            convertidoBin[aux + 1] = '1';
            convertidoBin[aux + 2] = '1';
            convertidoBin[aux + 3] = '1';
        }
    }
}
//converte de binario para inteiro sendo que esse inteiro e extritamente positivo
int GetIntFromBin(int x,int y){
    int i = 0;
    int j = 0;
    long result = 0;
    long save = 1;
    long aux = 0;
    int verf = 0;
    for(i = 0;i < x;i++){
        if(convertidoBin[pos] == '1'){
            verf = 1;
            int second = y-i;
            for(j = 0;j<second;j++){
                save *= 2;
            }
            aux += save;
            save = 1;
        }
        if(verf == 1){
            result = aux;
        }
        pos++;
    }
    return result;
}
//converte de binario para inteiro sendo que esse inteiro pode ser negativo
int getIntFromBinMaybeNegative(int x, int y){
    long decimal = 0;
    int posicao = 0;
    long contaBinMax = 1;
    int i,j;
    //maior valor possivel para o binario em questao
    for(j = 0;j<y;j++){
        contaBinMax *= 2;
    }
    posicao = contaBinMax;
    if(convertidoBin[pos] == '1'){
        for(i = 0;i<x;i++){
            if(convertidoBin[pos] == '1'){
                convertidoBin[pos] = '0';
            }
            else if(convertidoBin[pos] == '0'){
                convertidoBin[pos] = '1';
                decimal-=posicao;
            }
            posicao/=2;
            pos++;
        }
    }
    else if(convertidoBin[pos] == '0'){
    	decimal = GetIntFromBin(x,y);
    	return decimal;
    }
    //diminui 1 no decimal convertido
    decimal--;
    return decimal;
}
void process_instruction(){
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
    pos = 0;
    convertHexToBin(mem_read_32(CURRENT_STATE.PC));
    char aux[50];
    sprintf(aux,"%x",mem_read_32(CURRENT_STATE.PC));	
    //syscall
    if(GetIntFromBin(32,31) == 12) {
        if(NEXT_STATE.REGS[2] == 10) {
        	NEXT_STATE.PC += 4;
            RUN_BIT = 0;
            return;
        }
       	NEXT_STATE.PC += 4;
    }
    pos = 0;
    int opcode = GetIntFromBin(6,5);
    //R - TYPE
    if(opcode == 0){
    	//coletando todas as informocoes necessarias para as intrucoes do tipo R
        int immediate;
        int rs = GetIntFromBin(5,4);
        int rt = GetIntFromBin(5,4);
        int rd = GetIntFromBin(5,4);
        int shamt = GetIntFromBin(5,4);
        int funct = GetIntFromBin(6,5);
        //add
        if(funct == 32){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC += 4;
        }
        //addu
        if(funct == 33){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
        	NEXT_STATE.PC += 4;
        }
        //mult //refazer
	      else if(funct == 24){
	        long auxiliar1 = CURRENT_STATE.REGS[rs];
	        long auxiliar2 = CURRENT_STATE.REGS[rt];
	        long auxiliar = auxiliar1 * auxiliar2;
	        char  paus[64] = {'\0'};
	        char ce[50];
	        int size = 0;
	        int b = -1;
	        int contador = 0;
	        //transformando para binario
	        while(auxiliar > 0){
	          long conta = auxiliar % 2;
	          b++;
	          sprintf(ce,"%li",conta);
	          paus[b] = ce[0];
	          auxiliar = auxiliar/2;
	          size++;
	        }
	        int c;
	        char certo[size];
	        int auxpos = 0;
	        //colocando binario da forma certa
	        for(c = size-1;c>=0;c--){
	          certo[auxpos] = paus[c];
	          auxpos++;
	        }
	        //caso em que o binario e 0
	        if(size == 0){
	        	NEXT_STATE.LO = 0;
	        }	
	        //caso em que o binario e <= 32
	        else if(size <= 32){
	        	int h,i;
	        	long contaMaxValor = 1;
	        	//maior valor na ultima casa do binario
	        	for(h = 0;h<size-1;h++){
	        		contaMaxValor *=2;
	        	}
	        	long intFromBin = 0;
	        	int add;
	        	//soma no numero que sera colocado em lo cada vez que o numero na posicao H for 1
	        	for(h = 0;h<size;h++){
	        		if(certo[h] == '1'){
	        			add = contaMaxValor;
	        			intFromBin += add;
	        		}
	        		else if(certo[h] == '0'){
	        			intFromBin +=0;	
	        		}
	        		contaMaxValor /= 2; 
	        	}
	        NEXT_STATE.LO = intFromBin;		
	        }
	        //caso em que o binario e >32
	        else if(size > 32){
	        	int h,i;
	        	long contaMaxValor = 1;
	        	long contaMaxValor2 = 1;
	        	//maior valor para o numero que entrara em LO
	        	for(h = 0;h<size-1;h++){
	        		contaMaxValor2 *=2;
	        	}
	        	long intFromBinHI = 0;
	        	long intFromBinLO = 0;
	        	int cont = size - 32;
	        	//maior valor para o numero que entrara em HI
	        	for(h = 0;h<cont-1;h++){
	        		contaMaxValor *=2;
	        	}
	        	long add1,add2;
	        	for(h = 0;h<size;h++){
	        		//if para incrementar o numero que sera colocado em HI
	        		if(certo[h] == '1' && cont > 0){
	        			add1 = contaMaxValor;
		        		intFromBinHI += add1;
	        			cont--;
	        			contaMaxValor /= 2;
	        		}
	        		else if(certo[h] == '0' && cont > 0){
	        			intFromBinHI += 0;	
	        			cont--;
	        			contaMaxValor /= 2;
	        		}
	        		//if para incrementar o numero que sera colocado em LO
	        		else if(certo[h] == '1'){
	        			add2 = contaMaxValor2;	
	        			intFromBinLO += add2;
	        		}
	        		else if(certo[h] == '0'){
	        			intFromBinLO += 0;
	        		}
	        		contaMaxValor2 /= 2; 
	        	}
	        NEXT_STATE.LO = intFromBinLO;
	        NEXT_STATE.HI = intFromBinHI;
 	        }
	        NEXT_STATE.PC += 4;
	      }
        //multu //TODOS OS COMENTARIOS DA FUNCAO DE CIMA SAO IGUAIS A ESSA A BAIXO
        else if(funct == 25){
            long auxiliar1 = CURRENT_STATE.REGS[rs];
	        long auxiliar2 = CURRENT_STATE.REGS[rt];
	        long auxiliar = auxiliar1 * auxiliar2;
	        char  paus[64] = {'\0'};
	        char ce[50];
	        int size = 0;
	        int b = -1;
	        int contador = 0;
	        while(auxiliar > 0){
	          long conta = auxiliar % 2;
	          b++;
	          sprintf(ce,"%li",conta);
	          paus[b] = ce[0];
	          auxiliar = auxiliar/2;
	          size++;
	        }
	        int c;
	        char certo[size];
	        int auxpos = 0;
	        for(c = size-1;c>=0;c--){
	          certo[auxpos] = paus[c];
	          auxpos++;
	        }
	        if(size == 0){
	        	NEXT_STATE.LO = 0;
	        }	
	        else if(size <= 32){
	        	int h,i;
	        	long contaMaxValor = 1;
	        	for(h = 0;h<size-1;h++){
	        		contaMaxValor *=2;
	        	}
	        	long intFromBin = 0;
	        	int add;
	        	for(h = 0;h<size;h++){
	        		if(certo[h] == '1'){
	        			add = contaMaxValor;
	        			intFromBin += add;
	        		}
	        		else if(certo[h] == '0'){
	        			intFromBin +=0;	
	        		}
	        		contaMaxValor /= 2; 
	        	}
	        NEXT_STATE.LO = intFromBin;		
	        }
	        else if(size > 32){
	        	int h,i;
	        	long contaMaxValor = 1;
	        	long contaMaxValor2 = 1;
	        	for(h = 0;h<size-1;h++){
	        		contaMaxValor2 *=2;
	        	}
	        	long intFromBinHI = 0;
	        	long intFromBinLO = 0;
	        	int cont = size - 32;
	        	for(h = 0;h<cont-1;h++){
	        		contaMaxValor *=2;
	        	}
	        	long add1,add2;
	        	for(h = 0;h<size;h++){
	        		if(certo[h] == '1' && cont > 0){
	        			add1 = contaMaxValor;
		        		intFromBinHI += add1;
	        			cont--;
	        			contaMaxValor /= 2;
	        		}
	        		else if(certo[h] == '0' && cont > 0){
	        			intFromBinHI += 0;	
	        			cont--;
	        			contaMaxValor /= 2;
	        		}
	        		else if(certo[h] == '1'){
	        			add2 = contaMaxValor2;	
	        			intFromBinLO += add2;
	        		}
	        		else if(certo[h] == '0'){
	        			intFromBinLO += 0;
	        		}
	        		contaMaxValor2 /= 2; 
	        	}
	        NEXT_STATE.LO = intFromBinLO;
	        NEXT_STATE.HI = intFromBinHI;

 	        }
	        NEXT_STATE.PC += 4;
        }
        //sub
        else if(funct == 34){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
        	NEXT_STATE.PC += 4;
        }
        //subu
        else if(funct == 35){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
        	NEXT_STATE.PC += 4;
        }
        //divjogar
        else if(funct == 26){
            NEXT_STATE.LO = CURRENT_STATE.REGS[rs]/CURRENT_STATE.REGS[rt];
            NEXT_STATE.HI = CURRENT_STATE.REGS[rs]%CURRENT_STATE.REGS[rt];
        	NEXT_STATE.PC += 4;
        }
        //divu
        else if(funct == 27){
            NEXT_STATE.LO = CURRENT_STATE.REGS[rs]/CURRENT_STATE.REGS[rt];
            NEXT_STATE.HI = CURRENT_STATE.REGS[rs]%CURRENT_STATE.REGS[rt];
        	NEXT_STATE.PC += 4;
        }
        //MFHI //CURRENT STATE OU NEXT STATE [RD]
        else if(funct == 16){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;
        	NEXT_STATE.PC += 4;
        }
        //MFLO
        else if(funct == 18){
            NEXT_STATE.REGS[rd] == CURRENT_STATE.LO;
        	NEXT_STATE.PC += 4;
        }
        //MTHI
        else if(funct == 17){
            NEXT_STATE.HI = CURRENT_STATE.REGS[rs];
        	NEXT_STATE.PC += 4;
        }
        //MTLO
        else if(funct == 19){
            NEXT_STATE.LO = CURRENT_STATE.REGS[rs];
        	NEXT_STATE.PC += 4;
        }
        //and
        else if(funct == 36){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
        	NEXT_STATE.PC += 4;
        }
        //or
        else if(funct == 37){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];
        	NEXT_STATE.PC += 4;
        }
        //xor
        else if(funct == 38){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] ^ CURRENT_STATE.REGS[rt];
        	NEXT_STATE.PC += 4;
        }
        //nor
        else if(funct == 39){
            NEXT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);
        	NEXT_STATE.PC += 4;
        }
        //sll
        else if(funct == 0){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shamt;
        	NEXT_STATE.PC += 4;
        }
        //srl
        else if(funct == 2){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt;
        	NEXT_STATE.PC += 4;
        }
        //jr
        else if(funct == 8){
            NEXT_STATE.PC = CURRENT_STATE.REGS[31];
        }
        //jalr
        else if(funct == 9){
            //conferiando se rd != 0 para entrar no caso em que atualiza o valor do proprio
            if(rd != 0){
                CURRENT_STATE.REGS[rd] = CURRENT_STATE.PC + 4;
                NEXT_STATE.PC = rs;
            }
            else{
                CURRENT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
                NEXT_STATE.PC = rs;
            }
        	NEXT_STATE.PC += 4;
        }
        //sllv
        else if(funct == 4){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << CURRENT_STATE.REGS[rs];
        	NEXT_STATE.PC += 4;
        }
        //sra //MUDAR??
        else if(funct == 3){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt;
       		NEXT_STATE.PC += 4;
        }
        //srlv
        else if(funct == 6){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> rs;
        	NEXT_STATE.PC += 4;
        }
        //srav
        else if(funct == 7){
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> rs;
        	NEXT_STATE.PC += 4;
        }
         //sltu
        else if(funct == 43){
            if(CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt]){
                NEXT_STATE.REGS[rd] = 1;
            }
            else{
                NEXT_STATE.REGS[rd] = 0;
            }
        	NEXT_STATE.PC += 4;
        }
        //slt
        else if(funct == 42){
            if(CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt]){
                NEXT_STATE.REGS[rd] = 1;
            }
            else{
                NEXT_STATE.REGS[rd] = 0;
            }
        	NEXT_STATE.PC += 4;
        }
    }
    //J - TYPE
    else if(opcode == 2 || opcode == 3){
        int address = getIntFromBinMaybeNegative(26,25);
        //j
        if(opcode == 2){
            address = address * 4;	
            NEXT_STATE.PC =  address;
        }
        //jal
        else if(opcode == 3){
            address = address * 4;
            NEXT_STATE.REGS[31] = CURRENT_STATE.PC +4;
            NEXT_STATE.PC =  address;
        }
    }
    //I - TYPE
    else if(opcode != 0 && opcode != 2 && opcode != 3){
    	//coletando todas as informocoes necessarias para as intrucoes do tipo I
        int immediate;
        int rs = GetIntFromBin(5,4);
        int rt = GetIntFromBin(5,4);
        int compare = CURRENT_STATE.REGS[rs];
        //beq
        if(opcode == 4){
            if(CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]){
                immediate = getIntFromBinMaybeNegative(16,15);
                NEXT_STATE.PC += (immediate*4)+4;
            }
            else{
            	NEXT_STATE.PC += 4;
            }
        }
        //bne
        else if(opcode == 5){
            if(CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]){
                immediate = getIntFromBinMaybeNegative(16,15);
                NEXT_STATE.PC += (immediate*4)+4;
            }
            else{
            	NEXT_STATE.PC += 4;
            }
        }
        //bgez
        else if(opcode == 1 && rt == 1){
            immediate = getIntFromBinMaybeNegative(16,15);
            if(compare >= 0){
                NEXT_STATE.PC += (immediate)*4+4;
            }
            else{
            	NEXT_STATE.PC += 4;
            }
        }
        //bgezal
        else if(opcode == 1 && rt == 17){
            immediate = getIntFromBinMaybeNegative(16,15);
            if(compare >= 0){
                NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
                NEXT_STATE.PC += (immediate)*4+4;
            }
            else{
            	NEXT_STATE.PC += 4;
            }
        }
        //bgtz
        else if(opcode == 7 && rt == 0){
            immediate = getIntFromBinMaybeNegative(16,15);
            if(compare > 0){
                NEXT_STATE.PC += (immediate)*4+4;
            }
            else{
            	NEXT_STATE.PC += 4;
            }
        }
        //bltz
        else if(opcode == 1 && rt == 0){
            immediate = getIntFromBinMaybeNegative(16,15);
            if(compare < 0){
                NEXT_STATE.PC += (immediate)*4+4;
            }
            else{
            	NEXT_STATE.PC += 4;
            }
        }
        //bltzal
        else if(opcode == 1 && rt == 16){
            immediate = getIntFromBinMaybeNegative(16,15);
            if(compare < 0){
            	NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
                NEXT_STATE.PC += (immediate)*4+4;
            }
            else{
            	NEXT_STATE.PC += 4;
            }
        }
        //blez
        else if(opcode == 6 && rt == 0){
            immediate = getIntFromBinMaybeNegative(16,15);
            if(compare <= 0){
                NEXT_STATE.PC += (immediate)*4+4;
            }
            else{
            	NEXT_STATE.PC += 4;
            }
        }
        //addiu
        else if(opcode == 9){
            immediate = getIntFromBinMaybeNegative(16,15);
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + immediate;
        	NEXT_STATE.PC += 4; 
        }
        //addi
        else if(opcode == 8){
            immediate = getIntFromBinMaybeNegative(16,15);
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + immediate;
        	NEXT_STATE.PC += 4;
        }
        //slti
        else if(opcode == 10){
            immediate = getIntFromBinMaybeNegative(16,15);
            if(CURRENT_STATE.REGS[rs] < immediate){
                NEXT_STATE.REGS[rt] = 1;
            }
            else{
                NEXT_STATE.REGS[rt] = 0;
            }
            NEXT_STATE.PC += 4;
        }
        //sltiu
        else if(opcode == 11){
            immediate = GetIntFromBin(16,15);
            if(CURRENT_STATE.REGS[rs] < immediate){
                NEXT_STATE.REGS[rt] = 1;
            }
            else{
                NEXT_STATE.REGS[rt] = 0;
            }
            NEXT_STATE.PC += 4;
        }
        //andi
        else if(opcode == 12){
            immediate = GetIntFromBin(16,15);
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] & immediate;
        	NEXT_STATE.PC += 4;
        }
        //ori
        else if(opcode == 13){
            immediate = GetIntFromBin(16,15);
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | immediate;
        	NEXT_STATE.PC += 4;	
	     }
        //xori
        else if(opcode == 14){
            immediate = GetIntFromBin(16,15);
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] ^ immediate;
        	NEXT_STATE.PC += 4;
        }
        //lui
        else if(opcode == 15){
            long immediate2 = GetIntFromBin(16,15);
            NEXT_STATE.REGS[rt] =  immediate2 << 16;
        	NEXT_STATE.PC += 4;
        }
        //lw
        else if(opcode == 35){
            immediate = getIntFromBinMaybeNegative(16,15);
            NEXT_STATE.REGS[rt] = mem_read_32(CURRENT_STATE.REGS[rs] + immediate);
        	NEXT_STATE.PC += 4;
        }
        //sw
        else if(opcode == 43){
            immediate = getIntFromBinMaybeNegative(16,15);
            mem_write_32(CURRENT_STATE.REGS[rs] + immediate,CURRENT_STATE.REGS[rt]);
        	NEXT_STATE.PC += 4;
        }
        //lb
        else if(opcode == 32){
            int8_t a;
            immediate = GetIntFromBin(16,15);
          	immediate = immediate + CURRENT_STATE.REGS[rs];
            a = mem_read_32(immediate);
            NEXT_STATE.REGS[rt] = a;
        	NEXT_STATE.PC += 4;	
        }
        //lbu
        else if(opcode == 36){
            uint8_t a;
            immediate = GetIntFromBin(16,15);
          	immediate = immediate + CURRENT_STATE.REGS[rs];
            a = mem_read_32(immediate);
            NEXT_STATE.REGS[rt] = a;
        	NEXT_STATE.PC += 4;
        }
        //sb
        else if(opcode == 40){
            immediate = getIntFromBinMaybeNegative(16,15);
            int offset = immediate;
            uint32_t aux;
            aux = CURRENT_STATE.REGS[rt];
            uint32_t aux2;
            aux2 = CURRENT_STATE.REGS[rs];
            int i = immediate;
            int j = i+8;
            int save = 0;
            int k = 0;
            //for para ver os bits ativos e com um sll salvar em save
            for(;i<j;i++){
                if(aux & 1 << k){
                    save += 1 << k;
                }
                k++;	
            }
            offset = aux2 + offset;
            mem_write_32(offset,(save));
        	NEXT_STATE.PC += 4;
        }
        //lh
        else if(opcode == 33){
            int16_t a;
            immediate = getIntFromBinMaybeNegative(16,15);
          	immediate = immediate + CURRENT_STATE.REGS[rs];
            a = mem_read_32(immediate);
            NEXT_STATE.REGS[rt] = a;
        	NEXT_STATE.PC += 4;
        }
        //lhu
        else if(opcode == 37){
        	uint16_t a;
            immediate = getIntFromBinMaybeNegative(16,15);
          	immediate = immediate + CURRENT_STATE.REGS[rs];
            a = mem_read_32(immediate);
            NEXT_STATE.REGS[rt] = a;
        	NEXT_STATE.PC += 4;
        }
        //sh
        else if(opcode == 41){
           	immediate = getIntFromBinMaybeNegative(16,15);
            int offset = immediate;
            uint32_t aux;
            aux = CURRENT_STATE.REGS[rt];
            uint32_t aux2;
            aux2 = CURRENT_STATE.REGS[rs];
            int i = 8*immediate;
            int j = i+16;
            int save = 0;
            int k = 0;
            //for para ver os bits ativos e com um sll salvar em save
            for(;i<j;i++){
                if(aux & 1 << k){
                    save += 1 << k;
                }
                k++;	
            }
            offset = aux2 + offset;
            mem_write_32(offset,(save));
        	NEXT_STATE.PC += 4;
        }
    }
}
