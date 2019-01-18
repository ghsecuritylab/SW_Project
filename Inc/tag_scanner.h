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

#define ADMIN_PRIVILAGE 0
#define USER_PRIVILAGE 1
#define OTHER_PRIVILAGE 2

#define ADMIN_LIMIT 10

void
tag_scanner_init();



#endif /* TAG_SCANNER_H_ */
