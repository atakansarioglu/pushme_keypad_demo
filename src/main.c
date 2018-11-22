/**
 * @file      board.c
 * @author    Atakan S.
 * @date      01/01/2018
 * @version   1.0
 * @brief     PushME on FreeRTOS demo code.
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

// PORTY
#include <porty.h>

// FreeRTOS Kernel includes.
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>

// Definitions
typedef enum {
	TOGGLE_LED_Blue_KEY = (KEY00),
	TOGGLE_LED_Green_KEY = (KEY00 | KEYLONG),
} tToggleKeys;

// LED Blue Toggle Task.
static void prvTaskToggleLEDBlue(void * param) {
	uint32_t keypadValue;
	while (true) {
		if (xQueueReceive(keypadQueue, &keypadValue, portMAX_DELAY) && (keypadValue == TOGGLE_LED_Blue_KEY))
			mPinWrite(LED_Blue, !mPinRead(LED_Blue));
	}
}

// LED Blue Toggle Task.
static void prvTaskToggleLEDGreen(void * param) {
	while (true) {
		// Wait on the desired key combination.
		xEventGroupWaitBits(keypadEventGroup, TOGGLE_LED_Green_KEY, pdTRUE, pdTRUE, portMAX_DELAY);
		mPinWrite(LED_Green, !mPinRead(LED_Green));
	}
}

int main(void) {
	// Initialize hardware: GPIO, CLOCKS and NVIC.
	Board_Init();

	// Create LED Toggling tasks.
	xTaskCreate(prvTaskToggleLEDBlue, "LEDBlue", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1), NULL);
	xTaskCreate(prvTaskToggleLEDGreen, "LEDGreen", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2), NULL);

	// Create PushME poller task with highest priority.
	xTaskCreate(keypadRead, "PushME", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3), NULL);

	// Start FreeRTOS scheduler.
	vTaskStartScheduler();
	while (true);

	// Program should not reach here.
	return 1;
}
