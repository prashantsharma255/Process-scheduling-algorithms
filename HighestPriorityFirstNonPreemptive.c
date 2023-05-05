#include <stdio.h>
#include <stdlib.h>
#include "stat.h"
#include "utility.h"

int compare_priority(void * data1, void * data2);
void printqueue(queue * q);

average_stats highest_priority_first_np(linked_list * processes)
{
  int t = 0; // quanta //
  // creation of a queue of processes
  queue * process_queue_1 = create_queue();
  queue * process_queue_2 = create_queue();
  queue * process_queue_3 = create_queue();
  queue * process_queue_4 = create_queue();
  // creation of linked list for managaing process order in preemeption
  linked_list * ll_1 = create_linked_list();
  linked_list * ll_2 = create_linked_list();
  linked_list * ll_3 = create_linked_list();
  linked_list * ll_4 = create_linked_list();
  node * process_pointer = processes->head;
  if(processes->head == NULL) {
		fprintf(stderr,"No Process to schedule\n");
	}
  printf("\nHighest Priority First Non Preemptive:\n");
  //while process queue is not empty or time quanta is less than 100
  process_stat * scheduled_process = NULL;
  while(t<100 || scheduled_process!=NULL )
  {
    //check for incoming new process and enqueue it in the queue
		if(process_pointer != NULL) {
			process * new_process = (process *)(process_pointer->data);
			while(process_pointer !=NULL && new_process->arrival_time <= t) {
        if(new_process->priority == 1) enqueue(process_queue_1,create_process_stat(new_process));
        if(new_process->priority == 2) enqueue(process_queue_2,create_process_stat(new_process));
        if(new_process->priority == 3) enqueue(process_queue_3,create_process_stat(new_process));
        if(new_process->priority == 4) enqueue(process_queue_3,create_process_stat(new_process));
				//sort(process_queue,compare_priority);
				process_pointer = process_pointer->next;
				if(process_pointer!=NULL)
        {
					new_process = (process *)(process_pointer->data);
        }
			}
      // sort all the processes that have arrived based on their priority //
      //sort(process_queue,compare_priority);
    }
    //printqueue(process_queue);
    //if there is no scheduled process, then check process queue and schedule it //
		if(scheduled_process == NULL) {
      if (process_queue_1->size > 0) scheduled_process = (process_stat *) dequeue(process_queue_1);
      else if (process_queue_2->size > 0) scheduled_process = (process_stat *) dequeue(process_queue_2);
      else if (process_queue_3->size > 0) scheduled_process = (process_stat *) dequeue(process_queue_3);
      else if (process_queue_4->size > 0) scheduled_process = (process_stat *) dequeue(process_queue_4);
      // If the process has not started before quanta 100, remove the process from the queue and take the next process in queue for execution //
      /*
      while(t>=100 && scheduled_process->start_time == -1)
      {
        scheduled_process = (process_stat *) dequeue(process_queue);
      }*/
      if (t>=100 && scheduled_process->start_time == -1){
        //free(scheduled_process);
        scheduled_process = NULL;
        continue;
      }
    }


    if(scheduled_process != NULL) {
  			process * proc = scheduled_process->proc;

  			//add current running process to the time chart
  			printf("%c",proc->pid);

  			//update current processes stat
  			if(scheduled_process->start_time == -1) {
  				scheduled_process->start_time = t;
  			}

  			scheduled_process->run_time++;

        //printf("Process name %c", proc->pid);

        if(scheduled_process->run_time >= proc->run_time) {
          scheduled_process->end_time = t;
          if(scheduled_process->proc->priority == 1) add_node(ll_1,scheduled_process);
          else if(scheduled_process->proc->priority == 2) add_node(ll_2,scheduled_process);
          else if(scheduled_process->proc->priority == 3) add_node(ll_3,scheduled_process);
          else if(scheduled_process->proc->priority == 4) add_node(ll_4,scheduled_process);
          //add_node(ll,scheduled_process);
          scheduled_process = NULL;
          //free(scheduled_process);
        }
      }else {
    			printf("_");
  		}
  		//increase the time
  		t++;
    }
    //Print Process Stat
    average_stats avg1,avg2,avg3,avg4,avg;
    printf("\nFor Priority Queue 1");
    avg1 = print_policy_stat(ll_1);
    printf("\nFor Priority Queue 2");
    avg2 = print_policy_stat(ll_2);
    printf("\nFor Priority Queue 3");
    avg3 = print_policy_stat(ll_3);
    printf("\nFor Priority Queue 4");
    avg4 = print_policy_stat(ll_4);

    avg.avg_response_time = (avg1.avg_response_time + avg2.avg_response_time + avg3.avg_response_time + avg4.avg_response_time)/4 ;
    avg.avg_wait_time = (avg1.avg_wait_time + avg2.avg_wait_time + avg3.avg_wait_time + avg4.avg_wait_time)/4 ;
    avg.avg_turnaround = (avg1.avg_turnaround + avg2.avg_turnaround + avg3.avg_turnaround + avg4.avg_turnaround)/4 ;
    avg.avg_throughput = (avg1.avg_throughput + avg2.avg_throughput + avg3.avg_throughput + avg4.avg_throughput) ;

    printf("The average statistics High Priority First Non Preemptive considering all priority queues is:\n");
    printf("Average Response Time : %.1f\n",avg.avg_response_time);
    printf("Average Wait Time : %.1f\n",avg.avg_wait_time);
    printf("Average Turn Around Time :%.1f\n",avg.avg_turnaround);

    return avg;
}

process_stat * create_process_stat(process* proc);