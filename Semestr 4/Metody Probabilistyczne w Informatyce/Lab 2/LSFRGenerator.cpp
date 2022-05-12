#include "LSFRGenerator.h"

LSFRGenerator::LSFRGenerator(int x0) : xn(x0) {

}

int LSFRGenerator::Random() {
	xn &= 0b1111111;							//obci�cie cz�ci innej ni� 7 najmniej znacz�cych bit�w

	for (int i = 0; i < 24; i++) {				//24, bo tyle zosta�o do przesuni�cia, aby utworzy� liczb� 31-bitow�, 31-7 = 24
		xn <<= 1;								//przesuni�cie liczby o 1 bit w lewo
		xn |= ((xn >> p) ^ (xn >> q)) & 1;		//ustawienie najmniej znacz�cego bitu na xor bitu p i q
	}
	return xn;
}
