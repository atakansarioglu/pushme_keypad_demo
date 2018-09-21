/**
 * @file      main.c
 * @author    Atakan S.
 * @date      01/01/2018
 * @version   1.3
 * @brief     Keypad project, MCU independent embedded code template.
 *
 * @copyright Copyright (c) 2018 Atakan SARIOGLU ~ www.atakansarioglu.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 */

#include "porty.h"

//-- Label definitions (OPTIONAL)
#define KEY_NONE						0
#define KEY_ON							(KEY00)
#define KEY_OFF							(KEY00|KEYLONG)

// The main routine.
int main(void){
	// Init cpu.
	Board_Init();

	// Init Ticker.
	TickerInit();

	// Init the scheduler.
	PunctualInit();

	// Enable global interrupts.
	mIntEnable();

	// The main loop.
	while (true) {
		keypadRead();

		if(isKeyPress(KEY_ON)){// ON
			mPinWrite(LED_Green, LED_Green_ON);
		}else if(isKeyPress(KEY_OFF)){// OFF
			mPinWrite(LED_Green, !mPinRead(LED_Green));
		}
	}
}
