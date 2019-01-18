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

static int admin_ids[ADMIN_LIMIT] = {74821, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int hash_id(uint8_t cardID[4]) {
	int result = 0;
	result += (int) cardID[3];
	result += (int) cardID[2];
	result *= 2*2*2*2*2*2*2*2;
	result += (int) cardID[1];
	result += (int) cardID[0];
	return result;
	//return (((int)cardID[0] * (int)cardID[1]) % 2017 - (int)cardID[3] + (int)cardID[4]) % 2019;
}

void
add_to_admin_list(int cardID_hash) {
	for(int i = 0; i < ADMIN_LIMIT; i++) {
		if(admin_ids[i] == 0) {
			admin_ids[i] = cardID_hash;
			break;
		}
	}
}

void
adjust_privilages(uint8_t CardID[4]) {
	privilage_status = USER_PRIVILAGE;
	xprintf("%d\r\n", hash_id(CardID));
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

			if(privilage_status == ADMIN_PRIVILAGE && add_admin == 1) {
				add_to_admin_list(hash_id(CardID));
			} else {
				adjust_privilages(CardID);
			}

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

