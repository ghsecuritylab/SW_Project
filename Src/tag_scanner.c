/*
 * tag_scanner.c
 *
 *  Created on: 18.12.2018
 *      Author: wojciech
 */

#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "string.h"
#include "httpserver-netconn.h"
#include "cmsis_os.h"
#include "term_io.h"
#include "tag_scanner.h"
#include "rfid-rc522.h"

static int admin_ids[ADMIN_LIMIT] = {981, 0, 0, 0, 0};

int hash_id(uint8_t cardID[4]) {
	return ((cardID[0] * cardID[1]) % 2017 - cardID[3] + cardID[4]) % 2019;
}

void
adjust_privilages(uint8_t CardID[4]) {
	privilage_status = USER_PRIVILAGE;
	for(int i = 0; i < ADMIN_LIMIT; ++i) {
		if(hash_id(CardID) == admin_ids[i]) {
			privilage_status = ADMIN_PRIVILAGE;
			break;
		}
	}
}

static void
tag_scanner_thread() {
	while(1) {
		osDelay(100);
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

		uint8_t CardID[4];
		uint8_t type;
		char *result;

		int status = TM_MFRC522_Check(CardID, &type);
		if (status == MI_OK) {
			xprintf ((char *)"Found tag: ");
			bin_to_strhex((unsigned char *)CardID, sizeof(CardID), &result);
			xprintf((char *)result);
			xprintf((char *)"\n\r");
			xprintf((char *)"Type is: ");


			bin_to_strhex((unsigned char *)&type, 1, &result);
			xprintf((char *)result);
			xprintf((char *)"\n\r");

			adjust_privilages(CardID);

		} else {
			if (status == MI_TIMEOUT) {
				xprintf((char *)"No tag found.\n\r");
			}
			if (status == MI_ERR) {
				xprintf((char *)"Error.\n\r");
			}
		}
	}
}

void
tag_scanner_init() {
	sys_thread_new("TAGS", tag_scanner_thread, NULL, TAG_SCANNER_THREAD_STACK_SIZE, TAG_SCANNER_THREAD_PRIO);
}

