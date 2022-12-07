/*
 * scheduler.c
 *
 *  Created on: Nov 11, 2022
 *      Author: Phuc
 */


#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;
void SCH_Init(void) {
	current_index_task = 0;
	TIME = 0;
}

void get_time() {
	uart_print_with_num("TIME: ", TIME);
}
void get_time_2() {
	uart_print_with_num("TIME 2: ", TIME);
}
void SCH_Add_Task( void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD) {
	if (current_index_task < SCH_MAX_TASKS) {
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period =  PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;
		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		uart_print_with_num(">>>>> Added task ID = ", current_index_task);
		uart_print_with_num("DELAY = ", DELAY);
		uart_print_with_num("PERIOD = ", PERIOD);
		current_index_task++;
	}
}

void SCH_Update(void){
	for(int i = 0; i < current_index_task; i++) {
		if (SCH_tasks_G[i].Delay > 0) {
			SCH_tasks_G[i].Delay--;
		}
		if (SCH_tasks_G[i].Delay == 0) {
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe++;
		}
	}
}

void SCH_Dispatch_Tasks(void) {
	for(int i = 0; i < current_index_task; i++) {
		if(SCH_tasks_G[i].RunMe > 0) {
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();	//Function pointer to call a task to execute
			if (SCH_tasks_G[i].Period == 0) {	//That is one-shot task, delete it after running first time
				SCH_Delete_Task(i);
			}
		}
	}
}

void SCH_Delete_Task(uint32_t taskID) {
	if (taskID >= 0) {	//Check if we delete valid task ID
		if (taskID < SCH_MAX_TASKS - 1) {
			//If the index isn't last element, we need to shift all elements to the right of [taskID]
			for (int i = taskID; i < SCH_MAX_TASKS - 1; i++) {
				SCH_tasks_G[i].Delay = SCH_tasks_G[i+1].Delay;
				SCH_tasks_G[i].Period = SCH_tasks_G[i+1].Period;
				SCH_tasks_G[i].RunMe = SCH_tasks_G[i+1].RunMe;
				SCH_tasks_G[i].TaskID = SCH_tasks_G[i+1].TaskID;
				SCH_tasks_G[i].pTask = SCH_tasks_G[i+1].pTask;
			}
		}
		if (current_index_task > 0) current_index_task--;	//Decrease the array size
		uart_print_with_num("Successfully deleted task with ID = ", taskID);
	}
}
