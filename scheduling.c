#include <stdio.h>
#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h> 
#include <stdbool.h>


typedef struct process { 
	int PID;							
	int	BT;								
	int AT;							 	
	int PRI;							
	int WT,TAT,RPT;						
	int firstBT;						
	bool done;							
}pc;


int isNumber(char x[]);
void FCFS(pc p[], int n);
void SJF(pc p[], int n);
void RR(pc p[], int n, int quan);
struct process createProcess(int numOfPro, pc p[], int data[]);

int main(int argc, char *argv[]) {
	
	if (argc != 3)
	{
		fprintf(stderr, "USAGE:./scheduler <input-file> <scheduling algorithm> \n");
		exit(-1);
	}
	
	FILE *fp;
	int check, quantum, o=0, i=0, count=0, numOfPro=0;
	int data[500];
	char *token;	
	char buff[255],cont[255],choice[500],filepath[500], ch;
	char delimit[] = ",\n";		

	strcpy(filepath, argv[1]);						
	strcpy(choice, argv[2]);							
	
	fp = fopen( filepath , "r");
	while (ch = fgetc(fp))
	{
		if (feof (fp))
		{
			break;
		}
		buff[i] = ch;
		i++;
		count++;
	}							
	fclose(fp);
	
	for(i = 1 ; i<count ; i++)
	{ 
		cont[i-2] = buff[i];
	}
                                             
	token = strtok(cont, delimit);
	while(token != NULL) 
	{
		data[o] = atoi(token);
		token = strtok(NULL, delimit);
		o++;
	}	
	
	numOfPro = buff[0] - '0';
    struct process p[numOfPro];			
    *p = createProcess(numOfPro,p,data);
    
    printf("===========================\n");
    printf("PID\tBT\tAT\tPRI\n");
	for (i = 0 ; i<numOfPro ; i++)
	{
		printf("%d\t%d\t%d\t%d\n", p[i].PID, p[i].BT, p[i].AT, p[i].PRI);
	}
	printf("===========================\n");
	printf("\t  OUTPUT");
	
	char str1[] = "FCFS";
	char str2[] = "SJF";
	
	check = isNumber(choice);
	
	if (check == 0)
	{
		quantum = atoi(choice);
		printf("\nRR with q = %d: ",quantum);	
		RR(p,numOfPro,quantum);
	}
	else
	{
		if(strcmp(str1, choice) == 0 )
		{
			printf("\nFCFS: ");
			FCFS(p,numOfPro);
		}	
		else if(strcmp(str2, choice) == 0 )
		{
			printf("\n\nSJF: ");
			SJF(p,numOfPro);
		}
		else
		{
			printf("\nWrong Input!!! *You allow to input \"FCFS\",\"SJF\",and number for RR only\n");
		}
	}
}

int isNumber(char x[])
{
	int i,check = 0;
	for(i = 0; i<strlen(x) ; i++)
	{
		if(48 > x[i] || 57 < x[i])
		{
			check = 1;
			break;
		}
	}
	return check;
}

struct process createProcess(int numOfPro, pc p[], int data[])
{
	int n = 0;
	int i = 0;
    for(i=0; i<numOfPro; i++)
    {
        if(i==0)
        {
            p[i].PID = data[i];
            p[i].BT  = data[i+1];
            p[i].AT = data[i+2];
            p[i].PRI = data[i+3];
        }
        else
        {
            n = i*4;
            p[i].PID = data[n];
            p[i].BT  = data[n+1];
            p[i].AT = data[n+2];
            p[i].PRI = data[n+3];
        }
    }
	return *p;
}

void sort_AT_FCFS(pc p[], int n)
{
	pc temp;
	int i,j;
	for(i = 1 ; i<n ;i++)
	{
		for(j = 0; j<n-1 ; j++)
		{
			if(p[j].AT > p[j+1].AT)
			{
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
			else if(p[j].AT == p[j+1].AT)
			{
				if(p[j].PRI > p[j+1].PRI)
				{
					temp = p[j];
					p[j] = p[j+1];
					p[j+1] = temp;
				}
				else if (p[j].PRI == p[j+1].PRI)
				{
					if(p[j].BT > p[j+1].BT)
					{
						temp = p[j];
						p[j] = p[j+1];
						p[j+1] = temp;
					}
					else if(p[j].BT == p[j+1].BT)
					{
						if(p[j].PID > p[j+1].PID)
						{
							temp = p[j];
							p[j] = p[j+1];
							p[j+1] = temp;
						}
					}
				}
			}
		}
	}
}

void sort_AT_SJF(pc p[], int n)
{
	pc temp;
	int i,j;
	for(i = 1 ; i<n ;i++)
	{
		for(j = 0; j<n-1 ; j++)
		{
			if(p[j].AT > p[j+1].AT)
			{
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
			else if(p[j].AT == p[j+1].AT)
			{
				if(p[j].BT > p[j+1].BT)
				{
					temp = p[j];
					p[j] = p[j+1];
					p[j+1] = temp;
				}
				else if (p[j].BT == p[j+1].BT)
				{
					if(p[j].PRI > p[j+1].PRI)
					{
						temp = p[j];
						p[j] = p[j+1];
						p[j+1] = temp;
					}
					else if(p[j].PRI == p[j+1].PRI)
					{
						if(p[j].PID > p[j+1].PID)
						{
							temp = p[j];
							p[j] = p[j+1];
							p[j+1] = temp;
						}
					}
				}
			}
		}
	}
}

void sort_AT_RR(pc p[], int n)
{
	pc temp;
	int i,j;
	for(i = 1 ; i<n ;i++)
	{
		for(j = 0; j<n-1 ; j++)
		{
			if(p[j].AT > p[j+1].AT)
			{
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
			else if(p[j].AT == p[j+1].AT)
			{
				if(p[j].PRI > p[j+1].PRI)
				{
					temp = p[j];
					p[j] = p[j+1];
					p[j+1] = temp;
				}
				else if (p[j].PRI == p[j+1].PRI)
				{
					if(p[j].BT > p[j+1].BT)
					{
						temp = p[j];
						p[j] = p[j+1];
						p[j+1] = temp;
					}
					else if(p[j].BT == p[j+1].BT)
					{
						if(p[j].PID > p[j+1].PID)
						{
							temp = p[j];
							p[j] = p[j+1];
							p[j+1] = temp;
						}
					}
				}
			}
		}
	}
}

void FCFS(pc p[], int n)
{
	pc temp[n];
	double sumRPT = 0, sumWT = 0, sumTAT = 0 , sTP = 0 , TP = 0; 
	double avgRPT = 0, avgWT = 0, avgTAT = 0;
	int i,j;
	
	sort_AT_FCFS(p,n);
	
	for(i = 0 ; i < n ; i++)
	{
		temp[i] = p[i];
	}
	for(i = 0; i < n; i++)
	{
		if(i == 0)
		{
			temp[0].RPT = 0;
			temp[0].WT = 0;
			temp[0].TAT = temp[0].BT;
		}
		else
		{
			temp[i].RPT = temp[i].WT = (temp[i-1].BT + temp[i-1].AT + temp[i-1].WT) - temp[i].AT;
			temp[i].TAT = temp[i].BT + temp[i].WT;
		}
		sTP += temp[i].BT;
		sumRPT += temp[i].RPT;
		sumWT += temp[i].WT;
		sumTAT += temp[i].TAT;
		printf("\n%d,%d,%d,%d",temp[i].PID,temp[i].RPT,temp[i].WT,temp[i].TAT);
	}
	TP = n/sTP;
	avgRPT = sumRPT/n;
	avgWT = sumWT/n;
	avgTAT = sumTAT/n;
	printf("\n%0.2lf,%0.2lf,%0.2lf,%0.2lf\n",TP,avgRPT,avgWT,avgTAT);
}

void SJF(pc p[], int n)
{
	pc temp[n],tp;
	double sumRPT = 0, sumWT = 0, sumTAT = 0, sTP = 0 , TP = 0; 
	double avgRPT = 0, avgWT = 0, avgTAT = 0;
	int i,j,k,sum_Pre_BT = 0;
	
	sort_AT_SJF(p, n);
	
	for (i = 0; i< n; i++)
	{
		temp[i] = p[i];
	}
	for(i = 1 ; i < n-1 ; i++)
	{
		for( j = 1 ; j < n-i ; j++)
		{
			if((j-1) == 0)
			{
				if(temp[j].BT > temp[j+1].BT && temp[j+1].AT < temp[j-1].BT)
				{
					tp = temp[j];
					temp[j] = temp[j+1];
					temp[j+1] = tp;
				}
			}
			else
			{
				for(k = 0 ; k < j ; k++)
				{
					sum_Pre_BT += temp[k].BT;
				}
				if(temp[j].BT > temp[j+1].BT && temp[j+1].AT < sum_Pre_BT)
				{
					tp = temp[j];
					temp[j] = temp[j+1];
					temp[j+1] = tp;
				}
				sum_Pre_BT = 0;
			}
		}
	}
	for(i = 0; i < n; i++)
	{
		if(i == 0)
		{
			temp[0].RPT = 0;
			temp[0].WT = 0;
			temp[0].TAT = temp[0].BT;
		}
		else
		{
			temp[i].RPT = temp[i].WT = (temp[i-1].BT + temp[i-1].AT + temp[i-1].WT) - temp[i].AT;
			temp[i].TAT = temp[i].BT + temp[i].WT;
		}
		sTP += temp[i].BT;
		sumRPT += temp[i].RPT;
		sumWT += temp[i].WT;
		sumTAT += temp[i].TAT;
		printf("\n%d,%d,%d,%d",temp[i].PID,temp[i].RPT,temp[i].WT,temp[i].TAT);
	}
	TP = n/sTP;
	avgRPT = sumRPT/n;
	avgWT = sumWT/n;
	avgTAT = sumTAT/n;
	printf("\n%0.2lf,%0.2lf,%0.2lf,%0.2lf\n",TP,avgRPT,avgWT,avgTAT);
	
}

void RR(pc p[], int n, int quan)
{
	pc temp[n];
	double sumRPT = 0, sumWT = 0, sumTAT = 0, sTP = 0 , TP = 0; 
	double avgRPT = 0, avgWT = 0, avgTAT = 0;
	int burstTime[n],firstTimePC[n];
	int i,j,k = 0,q = 0,currentTime = 0, eTime = 0,allDone = 0, check = 0;
	int quantum ;
	
	quantum = quan;
	sort_AT_RR(p,n);
	
	for (i = 0 ; i < n ; i++)
	{
		temp[i] = p[i];
		burstTime[i] = temp[i].BT;
	}
	for(i = 0 ; i < n ; i++)
	{
		firstTimePC[i] = -1;
	}	
	while(allDone != n)
	{
		eTime = 0;
		if( q > n-1 )
		{
			q = 0;
		}
		if(temp[q].done == false)
		{
			if(temp[q].BT > 0)
			{
				for(j = 0; j<n ; j++)
				{
					if(temp[q].PID == firstTimePC[j])
					{
						check = 0;
						break;
					}
					else
					{
						check = 1;
					}
				}
				if(check == 1)
				{
					firstTimePC[k] = temp[q].PID;
					temp[q].firstBT = currentTime;
					check = 0;
					k++;
				}
				while(temp[q].BT > 0 && eTime < quantum)
				{
					temp[q].BT--;
					eTime++;
					currentTime++;
				}
			}
			if(temp[q].BT == 0)
			{
				temp[q].RPT = temp[q].firstBT - temp[q].AT;
				temp[q].WT = currentTime - (burstTime[q] + temp[q].AT);
				temp[q].TAT = currentTime - temp[q].AT;
				sTP += burstTime[q];
				sumRPT += temp[q].RPT;
				sumWT += temp[q].WT;
				sumTAT += temp[q].TAT;
				printf("\n%d,%d,%d,%d",temp[q].PID,temp[q].RPT,temp[q].WT,temp[q].TAT);
				temp[q].done = true;
				allDone++;
			}
		}
		q++;
	}
	TP = n/sTP;
	avgRPT = sumRPT/n;
	avgWT = sumWT/n;
	avgTAT = sumTAT/n;
	printf("\n%0.2lf,%0.2lf,%0.2lf,%0.2lf\n",TP,avgRPT,avgWT,avgTAT);
	printf("\n***This output is ordered by termination of processes\n");
	printf("***First ------> Last\n");
}