#include "gbcpu.h"



class gbcpu {
private:


	uint8_t vram_init[0x1a0] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0xF0,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0xF3,0x00,0xF3,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0xF3,0x00,0xF3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCF,0x00,0xCF,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x0F,0x00,0x3F,0x00,0x3F,0x00,0x0F,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0xC0,0x00,0x0F,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF3,0x00,0xF3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0xC0,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0xFF,0x00,0xFF,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC3,0x00,0xC3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0xFC,0x00,0xF3,0x00,0xF3,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0x3C,0x00,0x3C,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0x3C,0x00,0x3C,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0x3C,0x00,0x3C,0x00,0x3F,0x00,0x3F,0x00,0x3C,0x00,0x3C,0x00,0x0F,0x00,0x0F,0x00,0x3C,0x00,0x3C,0x00,0xFC,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF0,0x00,0xF0,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xFF,0x00,0xFF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xC3,0x00,0xC3,0x00,0x0F,0x00,0x0F,0x00,0x0F,0x00,0x0F,0x00,0x0F,0x00,0x0F,0x00,0xFC,0x00,0xFC,0x00,0x3C,0x00,0x42,0x00,0xB9,0x00,0xA5,0x00,0xB9,0x00,0xA5,0x00,0x42,0x00,0x3C};  //N logo?
	uint8_t gfx[MAX_NUM_TILES * 8][8];

	/*
	8000-87FF  tile set 1 0-127
	8800-8fff  tile set 1 128-255          in total 384 tiles.
		       tile set 0 -1- -128
	9000-97FF  tile set 0  0-127
	9800-9BFF  tile map 0
	9C00-9FFF  tile map 1
	*/

    SDL_Window* window = NULL;
	SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
	
	/*Flag register (F)bits:

	7	6	5	4	3	2	1	0
	Z	N	H	C	0	0	0	0

		Z - Zero Flag
		N - Subtract Flag
		H - Half Carry Flag
		C - Carry Flag
		0 - Not used, always zero
	*/

	uint8_t memory[0xffff];

	uint16_t pc;
	uint16_t sp;
	uint32_t rhl;

	bool ie;  // interrupt enable flag

	uint16_t ra, rb, rc, rd, re; //registers
	uint16_t sr;

	uint8_t IME, IF;  //Interrupt Master Enable, Interrupt Flags

	/*  Interrupt Enable Register
		-------------------------- - FFFF
		Internal RAM
		-------------------------- - FF80
		Empty but unusable for I / O
		-------------------------- - FF4C
		I / O ports
		-------------------------- - FF00
		Empty but unusable for I / O
		-------------------------- - FEA0
		Sprite Attrib Memory(OAM)
		-------------------------- - FE00
		Echo of 8kB Internal RAM
		-------------------------- - E000
		8kB Internal RAM
		-------------------------- - C000
		8kB switchable RAM bank
		-------------------------- - A000
		8kB Video RAM
		-------------------------- - 8000 --
		16kB switchable ROM bank |
		-------------------------- - 4000 |= 32kB Cartrigbe
		16kB ROM bank #0 |
		-------------------------- - 0000 --
		E000- FE00
			==
		C000 DE00

		*/

	uint8_t opcode;
	uint16_t operand[2];

	int cycle_count;
	uint32_t frame_start_time;


 void wait_next_frame(uint32_t frame_end){  //should already account for instruction time
            while (SDL_GetTicks() < frame_end)
				SDL_Delay(5);

        return;
    }


	uint16_t bbaa() {
		return (operand[1] << 8) + operand[0];
	}

	bool r_sr(char flg) {  //read status register
		switch (flg) {
		case 'c':
			return (sr & 0b00010000);

		case 'h':
			return (sr & 0b00100000);

		case 'n':
			return (sr & 0b01000000);

		case 'z':
			return (sr & 0b10000000);

		}
	}

	void w_sr(char flg, bool value) {  //write status register
		
		switch (flg) {
		case 'c':
			if (value) {
				sr = sr | 0b00010000;
			}
			else {
				sr = sr & 0b11101111;
			}
			break;

		case 'h':
			if (value) {
				sr = sr | 0b00100000;
			}
			else {
				sr = sr & 0b11011111;
			}
			break;

		case 'n':
			if (value) {
				sr = sr | 0b01000000;
			}
			else {
				sr = sr & 0b10111111;
			}
			break;

		case 'z':
			if (value) {
				sr = sr | 0b10000000;
			}
			else {
				sr = sr & 0b01111111;
			}
			break;

		}
		return;
	}

	void check_carry(uint16_t &value) {   
		if (value > 0xff) {
			w_sr('c', 1);
			value = value & 0x00ff;
			return;
		}
		else
			w_sr('c', 0);
		return;
	}

	void check_carry32(uint32_t &value) {
		if (value > 0xffff) {
			w_sr('c', 1);
			value = value & 0x00ffff;
			return;
		}
		else
			w_sr('c', 0);
		return;
	}

	void check_hcarry(uint16_t result, uint16_t anyoperand) {
		if ((((result & 0xf) + (anyoperand & 0xf)) & 0x10 ) > 0 )
			w_sr('h', 1);
		else
			w_sr('h', 0);
		return;
	}

	void check_hcarry32(uint32_t result, uint32_t anyoperand) { // TODO experimental
		if ((result & 0xff) < (anyoperand & 0xff) || (result & 0xffff) < (anyoperand & 0xffff))
			w_sr('h', 1);
		else
			w_sr('h', 0);
		return;
	}

	void check_zero(uint16_t value) {
		if (value == 0) {
			w_sr('z', 1);
			return;
		}
		else
			w_sr('z', 0);
		return;
	}

	void set_subtract(bool value) {
		w_sr('n', value);
		return;
	}

	bool read_carry() {
		return r_sr('c');
	}

	bool read_hcarry() {
		return r_sr('h');
	}

	bool read_subtract() {
		return r_sr('n');
	}

	bool read_zero() {
		return r_sr('z');
	}

	void set_carry(bool value) {
		w_sr('c', value);
		return;
	}

	void set_hcarry(bool value) {
		w_sr('h', value);
		return;
	}

	void set_zero(bool value) {
		w_sr('z', value);
		return;
	}


	uint16_t r_rde() {
		uint16_t temp = 0;
		temp += re;
		temp += (rd << 8);   
		return temp;
	}

	void w_rde(uint16_t input) {
		re = input & 0xff;
		rd = input >> 8;
		return;
	}

	uint16_t r_rbc() {
		uint16_t temp = 0;
		temp += rc;
		temp += (rb << 8);
		return temp;
	}

	void w_rbc(uint16_t input) {
		rc = input & 0xff;
		rb = input >> 8;
		return;
	}

	uint16_t r_raf() {
		uint16_t temp = 0;
		temp += sr;
		temp += (ra << 8);
		return temp;
	}

	void w_raf(uint16_t input) {
		sr = input & 0xff;
		ra = input >> 8;
		return;
	}


	void push8(uint8_t datos) { //TODO validate push pop
		memory[sp] = datos;
		sp--;
		return;
	}

	uint8_t pop8() {
		sp++;
		return memory[sp];
	}

	void push16(uint16_t dat) {
		push8(dat);
		push8(dat >> 8);
		return;
	}

	uint16_t pop16() {
		uint16_t temp = 0;
		temp = pop8();
		temp = temp << 8;
		temp += pop8();
		return temp;
	}

	void wr_mem(uint16_t address, uint8_t data){
		switch(address){
			case 0xff44: 
				memory[address] = 0;
				break;

			case 0xff80: //tetris patch?
				break;

			default:{
				memory[address] = data;
				break;
			}
		};
		return;
	}

	void dump_memory(){
		ofstream outfile ("memory.dump");
		for (int i = 0; i < 0xffff; i++){
		outfile << memory[i];
		}
		outfile.close();

		return;
	}


/* 0	Vblank   0x40
   1	LCD stat 0x48
   2	Timer 	 0x50
   3	Serial	 0x58
   4	Joypad   0x60 */

void interrupt_routine(){
	IME = memory[0xffff];
	IF = memory[0xff0f];

	if ((IME & 0x1) && (IF & 0x1)){  //Vblank
		push16(pc);
		pc = 0x40;
	}
	else if((IME & 0x2) && (IF & 0x2)){  //LCD
			push16(pc);
			pc = 0x48;
	}
		else if ((IME & 0x4) && (IF & 0x4)){   //Timer
				push16(pc);
				pc = 0x50;
		}
			else if ((IME & 0x8) && (IF & 0x8)){  //Serial
					push16(pc);
					pc = 0x58;
			}
				else if ((IME & 0x10) && (IF & 0x10)){  //Joypad
						push16(pc);
						pc = 0x60;
				}

	memory[0xff0f] = 0;
	return;
}

public:

	bool load_binary(string path) { //load rom starting at 0x200

		char cpath[200];
		strcpy(cpath, path.c_str());

		return load_bin_char(cpath);

	}

	bool load_bin_char(char strong[]) {
		unsigned char buffer[0x8100];

		FILE* rom = fopen(strong, "rb");

		fseek(rom, 0, SEEK_END); //seek the end of rom
		long rom_size = ftell(rom); //store the position in the file stream as its size
		rewind(rom); //rewind the rom like a VHS

		fread(buffer, rom_size, 1, rom);

		//load buffer in memory
		if (rom_size > 0x8000) {
			cout << endl << "Rom too big" << endl;
			return 0;
		}

		for (int i = 0; i < rom_size; i++)
			memory[i] = buffer[i];

		fclose(rom);
		//free(buffer);

		return 1;
	}

	void initialize() {

		for (int i = 0; i < 0x8100; i++)
			memory[i] = 0;

		for (int i = 0x8000; i <= 0x819f; i++)
			memory[i] = vram_init[i - 0x8000];

		
		soft_reset();

		return;

	}

	void soft_reset() {
		
		ra = 0x01;
		rb = 0;
		rc = 0x13;
		rd = 0;
		re = 0xd8;  //registers
		rhl = 0x014d;

		//lcd register 0x91

		ie = 0;  //interrupt enable

		sr = 0xb0; //status register

		sp = 0xfffe;  //not dfff?
		pc = 0x100;

		frame_start_time = SDL_GetTicks();
		return;

	}


long lel = 0;   //debug purposes
bool found = false;
int lastpc [10000];
int index = 0;


void cycle() {  //fetch, execute

	if ((lel % 30000) == 0)
		update_tileram();
		
	if (pc== 0x293)
		cout<<endl;
		//TODO find out why it jumps to 1fd after 2ec --- VBlank routine
	if (pc == 0x2ec && rb == 0 )
		cout<<endl;

	if (pc == 0x1fd) {  //ffbf
		for (int i = 0; i < 10000; i++)
			cout <<lastpc[i]<<" ,";
		cout<<endl;	
	}

	if (index < 9998){
		lastpc[index] = pc;
		index ++;
	} else{
	for (int i = 1; i < 10000; i++)
		lastpc[i - 1] = lastpc[i];
	
	lastpc[9999] = pc;
	}

	
		
		lel ++;

		if (lel % 4 == 0)  //temporary LY bypass
			memory[0xff44] = memory[0xff44] + 1;

	//interrupt handling:
	interrupt_routine();

	if (cycle_count > CYCLES_PER_SECOND){
		cycle_count = 0;
		wait_next_frame(frame_start_time + (1000 / 60)); //60 frames every 1000 ms
		frame_start_time = SDL_GetTicks();

		//draw frame
		draw_tileset();	//TEMP
		//vblank interrupt	
		memory [0xff0f] = memory[0xff0f] | 0x1;

	}


	opcode = memory[pc];
	operand[0] = memory[pc + 1];
	operand[1] = memory[pc + 2];

	switch (opcode) {

		case 0x00:    // NOP
			pc += 1;
			cycle_count += 4;
			break;

		case 0x01:    // LD bc bbaa
			w_rbc(bbaa());
			pc += 3;
			cycle_count += 20;
			break;

		case 0x04: {  // increment B
			if ((rb & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			rb++;
			set_subtract(0);
			rb = rb & 0xff;
			check_zero(rb);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x05: {  // 05 DECrement B
			if ((rb & 0xf) == 0xf)
				set_hcarry(0);
			else
				set_hcarry(1);
			
			rb--;
			set_subtract(1);
			rb = rb & 0xff;
			check_zero(rb);
			pc += 1;
			cycle_count += 4;
			break; 	}

		case 0x06: {  // 06 xx LD B,$xx
			rb = operand[0];
			check_zero(rb);
			pc += 2;
			cycle_count += 8;
			break; 	}

		case 0x0b: {  // DEC rbc
			uint32_t tempo = r_rbc();  //TODO more efficient way?
			w_rbc((tempo - 0x1)); 
			pc += 1;
			cycle_count += 4;
			break; 	}

		case 0x0c: {  // increment c
			if ((rc & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			rc++;
			set_subtract(0);
			rc = rc & 0xff;
			check_zero(rc);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x0d: {  // decrement C
			if ((rc & 0xf) == 0xf)
				set_hcarry(0);
			else
				set_hcarry(1);
			
			rc--;
			set_subtract(1);
			rc = rc & 0xff;
			check_zero(rc);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x0e:    // 0E xx LD C,$xx
			rc = operand[0];
			pc += 2;
			cycle_count += 8;
			break;

		case 0x11:    // load bbaa in rde
			w_rde(bbaa());
			pc += 3;
			cycle_count += 12;
			break;

		case 0x12:    // save ra in (rde)
			wr_mem(r_rde(), ra);
			pc += 1;
			cycle_count += 8;
			break;

		case 0x13: {  // INCrement rde
			uint16_t temp = r_rde();
			w_rde(temp + 1);
			pc += 1;
			cycle_count += 8;
			break;	}
		
		case 0x14:    // increment D
			if ((rd & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			rd++;
			set_subtract(0);
			rd = rd & 0xff;
			check_zero(rd);
			pc += 1;
			cycle_count += 4;
			break;	

		case 0x15: {  // decrement D  
			if ((rd & 0xf) == 0xf)
				set_hcarry(0);
			else
				set_hcarry(1);
			
			rd--;
			set_subtract(1);
			rd = rd & 0xff;
			check_zero(rd);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x16:    // load xx into D
			rd = operand[0];
			pc += 2;
			cycle_count += 8;
			break;

		case 0x18:    // JMP signed relative
			if (operand[0] >= 0x80) {
					operand[0] = (operand[0]^0xff) + 1 ;
					pc -= operand[0];
				}
				else {
				pc += operand[0];
				}
					
				pc += 2;
				cycle_count += 16;
			break;

		case 0x19:    // add de to hl
			if ((r_rde() & 0xff) + (rhl & 0xff) > 0xff)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			rhl += r_rde();
			check_carry32(rhl);
			set_subtract(0);
			pc += 1;
			cycle_count += 8;
			break;

		case 0x1a:    // LD ra (de)
			ra = memory[r_rde()];
			pc += 1;
			cycle_count += 8;
			break;

		case 0x1c: {  // INC re
			if ((re & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			re++;
			set_subtract(0);
			re = re & 0xff;
			check_zero(re);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x1e:    // LD E $xx 
			re = operand[0];
			pc += 2;
			cycle_count += 8;
			break;

		case 0x1f: {  // Rotate Right A
			bool temp = read_carry();
			set_carry(bool((ra & 0x80) >> 8));  //TODO check this mess
			ra = (ra * 2) + temp;
			check_carry(ra);
			set_subtract(0);
			set_hcarry(0);
			set_zero(0);
			pc += 1;
			cycle_count += 4;
			break;	}
				   
		case 0x20: {  // 20 xx JR NZ,$xx
			if (read_zero() == 0) {
				if (operand[0] >= 0x80) {
					operand[0] = (operand[0]^0xff) + 1 ;
					pc -= operand[0];
					cycle_count += 16;
				}
				else {
					pc += operand[0];
					cycle_count += 12;
				}
			}
			
				pc += 2;
				
			break;	}

		case 0x21:    // 21 bb aa LD HL,$aabb
			rhl = bbaa();
			pc += 3;
			cycle_count += 12;
			break;

		case 0x22:    // save ra at (hl)+
			wr_mem(rhl, ra);
			rhl ++;
			pc += 1;
			cycle_count += 8;
			break;

		case 0x23:    // increment hl
			rhl++;
			pc += 1;
			cycle_count += 8;
			break;

		case 0x28:    // JZ relative signed
			if (read_zero() != 0) {
				if (operand[0] >= 0x80) {
					operand[0] = (operand[0]^0xff) + 1 ;
					pc -= operand[0];
					cycle_count += 16;
				}
				else {
					pc += operand[0];
					cycle_count += 12;
				}
			}
			
				pc += 2;
			break;

		case 0x2a:    // LD (hl)+, a
			ra = memory[rhl];
			rhl += 0x1;
			pc += 1;
			cycle_count += 8;
			break;

		case 0x2c: {  // INC rl
			uint8_t temp = rhl;
			
			if ((temp & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			temp ++;
			set_subtract(0);
			check_zero(temp);
			rhl = rhl & 0xff00;
			rhl += temp;
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x2f:    // NOT ra
			ra = 0xff - ra;
			set_subtract(1);
			set_hcarry(1);
			pc += 1;
			cycle_count += 4; //?
			break;

		case 0x31:    // LD aabb in SP register
			sp = bbaa();
			pc += 3;
			cycle_count += 12;
			break;

		case 0x32:    // 32 LD (HL)-,A
			wr_mem(rhl, ra);
			rhl--;
			pc += 1;
			cycle_count += 8;
			break;

		case 0x35: {  // DEC (rhl)
			if ((memory[rhl] & 0xf) == 0xf)
				set_hcarry(0);
			else
				set_hcarry(1);
			
			memory[rhl] = memory[rhl] - 1;
			set_subtract(1);
			check_zero(memory[rhl]);
			pc += 1;
			cycle_count += 12;
			break;	}

		case 0x36:    // LD (HL),  operand0
			wr_mem(rhl, operand[0]);
			pc += 2;
			cycle_count += 12;
			break;

		case 0x3e:    // ld a $xx
			ra = operand[0];
			pc += 2;
			cycle_count += 8;
			break;

		case 0x47:    // rb = ra
			rb = ra;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x4f:    // rc = ra
			rc = ra;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x56:    // copy (hl) to d
			rd = memory[rhl];
			pc += 1;
			cycle_count += 8;
			break;

		case 0x5e:    // copy value pointed at by hl in e
			re = memory[rhl];
			pc += 1;
			cycle_count += 8;
			break;

		case 0x5f:    // copy a to e
			re = ra;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x75: {   // copy rl to (rhl)
			wr_mem(rhl, rhl & 0xff);
			pc += 1;
			cycle_count += 8;
			break;	}
		
		case 0x78:    // copy b to a
			ra = rb;
			pc += 1;
			cycle_count += 4;	
			break;
					
		case 0x7a:    // copy d to a
			ra = rd;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x79:    // a = c
			ra = rc;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x7c:    // ra = rh
			ra = rhl >> 8;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x7e: {  // ra = (hl)
			ra = memory[rhl];
			pc += 1;
			cycle_count += 12;
			break;	}

		case 0x82:    // add d to a
			if ((ra & 0xf) + (rd & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);		

			ra += rd;
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;
		
		case 0x83:    // add re to ra
			if ((ra & 0xf) + (re & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			ra += re;
			set_subtract(0);
			check_carry(ra);
			check_zero(ra);
			pc += 1;
			cycle_count += 4;
			break;

		case 0x87: {  // double a
			if ((ra & 0xf) + (ra & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);

			ra += ra;
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x89: {  // adc A c,  add c and carry flag to A
			if ((ra & 0xf) + ((rc + r_sr('c')) & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);

			ra += rc + (r_sr('c'));
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x8f: {  // add a and fc to a
			if ((ra & 0xf) + ((ra + r_sr('c')) & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			uint16_t temp = r_sr('c') + ra;
			ra = (ra * 2) + r_sr('c');
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;	}
		case 0xa1:    // AND rc with ra
			ra = rc & ra;
			set_hcarry(1);
			set_subtract(0);
			set_carry(0);
			check_zero(ra);
			pc +=1;
			cycle_count += 4;
			break;

		case 0xa7:    // AND a with a
			ra = ra & ra;
			set_hcarry(1);
			check_zero(ra);
			set_subtract(0);
			set_carry(0);
			pc += 1;
			cycle_count += 4;
			break;

		case 0xa9:    // xor rc with ra
			ra = rc ^ ra;
			check_zero(ra);
			set_subtract(0);
			set_hcarry(0);
			set_carry(0);
			pc += 1;
			cycle_count += 4;
			break;

		case 0xaf:    // XOR A A
			ra = 0;
			set_zero(1);
			set_hcarry(0);
			set_carry(0);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;

		case 0xb0:    // or rb with ra  
			ra = ra | rb;
			check_zero(ra);
			set_subtract(0);
			set_hcarry(0);
			set_carry(0);
			pc += 1;
			cycle_count += 4;
			break;
		
		case 0xb1:    //  OR C with A
			ra = rc | ra;
			set_hcarry(0);
			set_subtract(0);
			set_carry(0);
			check_zero(ra);
			pc += 1;
			cycle_count += 4;
			break;

		case 0xb7:    // OR A with A
			ra = ra | ra;
			check_zero(ra);
			set_carry(0);
			set_hcarry(0);
			set_subtract(0);
			pc +=2;
			cycle_count += 4;
			break;

		case 0xc0:    // RTS if NZ
			if (read_zero() == 0){
				pc = pop16();
				cycle_count += 20;
			}
			else{
				pc += 1;
				cycle_count += 8;
			}
			break;
		
		case 0xc1:    // POP rbc
			w_rbc(pop16());
			pc += 1;
			cycle_count += 12;
			break;

		case 0xc3:    // JMP bb aa
			pc = bbaa();
			cycle_count += 16;
			break;

		case 0xc5:    // push bc
			push16(r_rbc());
			pc += 1;
			cycle_count += 16;
			break;

		case 0xc8:    // RTS if Z
			if (read_zero() == 1){
				pc = pop16();
				cycle_count += 20;
			}
			else{
				pc += 1;
				cycle_count += 8;
			}
			break;	
			
		case 0xc9:    // RTS
			pc = pop16();
			cycle_count += 16;
			break;

		case 0xca:    // JZ absolute
			if (read_zero() == 1){
				pc = bbaa();
				cycle_count += 16;
			}
			else{
				pc += 3;
				cycle_count += 12;
			}
			break;

		case 0xcb: {  // 2 bytes instructions
			switch (operand[0]){
				
				case 0x37:{  //swap half bytes of ra
					uint8_t temp = (ra & 0xf);
					ra = (ra >> 4) + (temp << 4);
					check_zero(ra);
					set_subtract(0);
					set_hcarry(0);
					set_carry(0);
					break;	}

				case 0x87:  // RES et bit 0 of ra
					  ra = ra & 0xfe;
					break;



				default:{
					cout << "Unknown CB op ";
				
				}
			} 

			pc += 2;
			break;
		}
		case 0xcd:    // call subroutine at bbaa
			push16(pc + 0x3);
			pc = bbaa();
			cycle_count += 24;
			break;

		case 0xcf:    // call subroutine at 08h
			push16(pc);
			pc = 0x08;
			cycle_count += 24;  //?
			break;

		case 0xd1:    // POP rde
			w_rde(pop16());
			pc += 1;
			cycle_count += 12;
			break;

		case 0xd5:    // push de
			push16(r_rde());
			pc += 1;
			cycle_count += 16;
			break;

		case 0xdf:    // call subroutine at 0018h
			push16(pc);
			pc = 0x0018;
			cycle_count += 24; // ?
			break;

		case 0xe0:    // save ra at FF00h + operand0
			wr_mem((0xff00 + operand[0]), ra);
			pc +=2;
			cycle_count += 8;
			break;


		case 0xe1:    // pop into hl
			rhl = pop16();
			check_carry32(rhl);
			//TODO halfcarry check, other operand ?
			pc += 1;
			cycle_count += 12;
			break;

		case 0xe2:    // ld a at ff00h + rc
				wr_mem((0xff00 + rc), ra);
				pc += 1;
				cycle_count += 8;
			break;

		case 0xe5:    // push hl
			push16(rhl);
			pc += 1;
			cycle_count += 16;
			break;

		case 0xe6:    // AND operand 0 , ra
			ra = ra & operand[0];
			set_hcarry(1);
			pc += 2;
			cycle_count += 8;
			break;

		case 0xe9:    // jmp  hl
			pc = rhl;
			cycle_count += 16;
			break;

		case 0xea: {  // ld (nn),rA
			wr_mem(bbaa(), ra);
			pc += 3;
			cycle_count += 16;
			break;	}
		case 0xef:    // call sub at 28h
			push16(pc + 1);
			pc = 0x28;
			cycle_count += 24; //?
			break;

		case 0xf0: {  // ld ra from (ff00h + xx)
			ra = memory[(0xff00 + operand[0])];
			pc += 2;
			cycle_count += 8;
			break;	}
		case 0xf1:    // pop raf
			w_raf(pop16());
			pc += 1;
			cycle_count += 12;
			break;

		case 0xf3: {  // disable interrupts
			//TODO implement interrupts, then disable them.
			ie = 0;
			memory[0xffff] = 0;
			pc += 1;
			cycle_count += 4;
			break;	} 
		case 0xf5: {  // push af
			push16(r_raf());
			pc += 1;
			cycle_count += 16;
			break;	}
		case 0xfa:    // ld ra from bbaa()
			ra = memory[bbaa()];
			pc += 3;
			cycle_count += 16;
			break;

		case 0xfb:    // interrupt enable
			ie = 1;
			memory[0xffff] = 1;
			pc += 1;
			cycle_count += 4;
			break;

		case 0xfe: {  // cmp operand0 with ra : Z if equal, N set, C and H as if it was ra- operand0
			uint16_t temp = 0;
			temp = ra - operand[0];
			
			check_zero(temp);
			check_hcarry(temp, ra);
			check_carry(temp);
			set_subtract(1);

			pc += 2;
			//?
			break;	}
		case 0xff: {  // rst $38
			pc = 0x38;
			cycle_count += 24;//?
			break;	}

		default:   {
			cout << "unknown opcode" << (int)opcode << "   " << (int)pc ;
			break;
		}
		};

		return;
	}

	void dump_fbuffer(){	
		
			for (int i = 0; i < 8; i++){
				cout << endl;
				for(int j = 0; j < 128; j++)
					if (gfx[j][i] == 0){
						cout << " ";
					}
					else
					{
						cout << "X";
					}
					cout << " ";
			}
			cout<<endl;
		
		return;
	}


    void ginit() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return;
		}
		window = SDL_CreateWindow("GBoi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			return;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return;
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		}
	}

	void draw_tileset() {  
		
		//populate gfx
		update_tileram();
		//dump_fbuffer();
		
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);
			
		//draw routine
			
			
		for (int lo = 1; lo < 13; lo++)   //top half logo
			draw_tile(lo , 0, lo);
				
		for (int bi = 1; bi < 20; bi ++)
			for (int go = 1; go < 20; go ++)	//bottom half logo
				draw_tile(go , bi, 12 + go + ((bi - 1) * 19));
		
		// display on screen
		
		SDL_RenderPresent(renderer);
			
	}


	void draw_tile(int xpos, int ypos, int xindex){  // takes input x and y tile position, and x y index of tile in gfx
																
			xpos *= 8;
			ypos *= 8;
			xindex *= 8;			

			for (int y = ypos; y < ypos + 8; y++) {  				
				for (int x = xpos; x < xpos + 8; x++) {
					SDL_Rect fillRect = { x, y, 1, 1};
					SDL_SetRenderDrawColor(renderer, gfx[xindex + (x - xpos)][(y - ypos)] * 0x55, gfx[xindex +(x - xpos)][(y - ypos)] * 0x55, gfx[xindex + (x - xpos)][(y - ypos)] * 0x55, 0xff);
					SDL_RenderFillRect(renderer, &fillRect);	
				}
			}  
	}

	void update_tileram(){

		uint16_t tile_address;
			 
											
		for (int col = 0; col < MAX_NUM_TILES; col++) {

			tile_address = 0x8000 + (col * 16) - 2;
					
			for (int pxline = 0; pxline <= 7; pxline++) {
					
				tile_address +=2;

				gfx [(col * 8)][pxline]     = ((memory[tile_address] & 0b10000000) >> 6) + ((memory[tile_address + 1] & 0b10000000) >> 7);
				gfx [(col * 8) + 1 ][pxline] = ((memory[tile_address] & 0b01000000) >> 5) + ((memory[tile_address + 1] & 0b01000000) >> 6);
				gfx [(col * 8) + 2][pxline] = ((memory[tile_address] & 0b00100000) >> 4) + ((memory[tile_address + 1] & 0b00100000) >> 5);
				gfx [(col * 8) + 3][pxline] = ((memory[tile_address] & 0b00010000) >> 3) + ((memory[tile_address + 1] & 0b00010000) >> 4);
				gfx [(col * 8) + 4][pxline] = ((memory[tile_address] & 0b00001000) >> 2) + ((memory[tile_address + 1] & 0b00001000) >> 3);
				gfx [(col * 8) + 5][pxline] = ((memory[tile_address] & 0b00000100) >> 1) + ((memory[tile_address + 1] & 0b00000100) >> 2);
				gfx [(col * 8) + 6][pxline] = (memory[tile_address] & 0b00000010)        + ((memory[tile_address + 1] & 0b00000010) >> 1);
				gfx [(col * 8) + 7][pxline] = ((memory[tile_address] & 0b00000001) << 1) + (memory[tile_address + 1] & 0b00000001);

						
			}
				
		}

			
	return;
	}

	void write_tile(uint8_t tile_location[], uint16_t tile_address, int tile_index){
		
		tile_address -= 2;
					
			for (int pxline = 0; pxline <= 7; pxline++) {
				
				tile_address +=2;

				gfx [(tile_index * 8)][pxline]     = ((tile_location[tile_address] & 0b10000000) >> 6) + ((tile_location[tile_address + 1] & 0b10000000) >> 7);
				gfx [(tile_index * 8) + 1][pxline] = ((tile_location[tile_address] & 0b01000000) >> 5) + ((tile_location[tile_address + 1] & 0b01000000) >> 6);
				gfx [(tile_index * 8) + 2][pxline] = ((tile_location[tile_address] & 0b00100000) >> 4) + ((tile_location[tile_address + 1] & 0b00100000) >> 5);
				gfx [(tile_index * 8) + 3][pxline] = ((tile_location[tile_address] & 0b00010000) >> 3) + ((tile_location[tile_address + 1] & 0b00010000) >> 4);
				gfx [(tile_index * 8) + 4][pxline] = ((tile_location[tile_address] & 0b00001000) >> 2) + ((tile_location[tile_address + 1] & 0b00001000) >> 3);
				gfx [(tile_index * 8) + 5][pxline] = ((tile_location[tile_address] & 0b00000100) >> 1) + ((tile_location[tile_address + 1] & 0b00000100) >> 2);
				gfx [(tile_index * 8) + 6][pxline] = (tile_location[tile_address] & 0b00000010)        + ((tile_location[tile_address + 1] & 0b00000010) >> 1);
				gfx [(tile_index * 8) + 7][pxline] = ((tile_location[tile_address] & 0b00000001) << 1) + (tile_location[tile_address + 1] & 0b00000001);

						
			}



	}
	



};