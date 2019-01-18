/*
 * tag_scanner.h
 *
 *  Created on: 18.12.2018
 *      Author: wojciech
 */

#ifndef TAG_SCANNER_H_
#define TAG_SCANNER_H_

#define TAG_SCANNER_THREAD_STACK_SIZE 256
#define TAG_SCANNER_THREAD_PRIO ( osPriorityHigh )

// constants for variable "privilage_status"

#define ADMIN_PRIVILAGE 0
#define USER_PRIVILAGE 1
#define OTHER_PRIVILAGE 2

extern int privilage_status;

// constants for variable "add_admin"

#define NOT_ACTIVE 0
#define WAITING_FOR_TAG 1
#define ADMIN_JUST_ADDED 2

extern int add_admin;

#define ADMIN_LIMIT 10

void
tag_scanner_init();



#endif /* TAG_SCANNER_H_ */
