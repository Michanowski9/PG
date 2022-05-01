#include "LSFRGenerator.h"

LSFRGenerator::LSFRGenerator(int x0) : xn(x0) {

}

int LSFRGenerator::Random() {
	xn &= 0b1111111;							//obciêcie czêœci innej ni¿ 7 najmniej znacz¹cych bitów

	for (int i = 0; i < 24; i++) {				//24, bo tyle zosta³o do przesuniêcia, aby utworzyæ liczbê 31-bitow¹, 31-7 = 24
		xn <<= 1;								//przesuniêcie liczby o 1 bit w lewo
		xn |= ((xn >> p) ^ (xn >> q)) & 1;		//ustawienie najmniej znacz¹cego bitu na xor bitu p i q
	}
	return xn;
}
