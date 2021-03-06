/**
 * COSC 3250 - Project 4
 * Explain briefly the functionality of the program.
 * @author Emma Claire Kinnison David Santiago
 * Instructor Dr. Brylow
 * TA-BOT:MAILTO emma.kinnison@marquette.edu david.santiago@marquette.edu
 */
 /**
 * @file create.c
 * @provides create, newpid, userret
 *
 * COSC 3250 Assignment 4
 */
/* Embedded XINU, Copyright (C) 2008.  All rights reserved. */

#include <xinu.h>
#include<stdarg.h>
#include<stdio.h>
#include <arm.h>


static pid_typ newpid(void);
void userret(void);
void *getstk(ulong);

/**
 * Create a new process to start running a function.
 * @param funcaddr address of function that will begin in new process
 * @param ssize    stack size in bytes
 * @param name     name of the process, used for debugging
 * @param nargs    number of arguments that follow
 * @return the new process id
 */
syscall create(void *funcaddr, ulong ssize, char *name, ulong nargs, ...)
{
    ulong *saddr;               /* stack address                */
    ulong pid;                  /* stores new process id        */
    pcb *ppcb;                  /* pointer to proc control blk  */
    ulong i;
    va_list ap;                 /* points to list of var args   */
    ulong pads = 0;             /* padding entries in record.   */
    void INITRET(void);     //IDK what this is

    if (ssize < MINSTK)
        ssize = MINSTK;
    ssize = (ulong)(ssize + 3) & 0xFFFFFFFC;
    /* round up to even boundary    */
    saddr = (ulong *)getstk(ssize);     /* allocate new stack and pid   */
    pid = newpid();
    /* a little error checking      */
    if ((((ulong *)SYSERR) == saddr) || (SYSERR == pid))
    {
        return SYSERR;
    }

    numproc++;
    ppcb = &proctab[pid];
	
	// TODO: Setup PCB entry for new process.
    ppcb->stkbase = (ulong*)(((ulong)saddr) - ssize);   //given from class
    ppcb->state = PRSUSP; //set to suspend
    ppcb->stkptr = saddr; //strores the pointer
    ppcb->stklen = ssize; //stores the size
    strncpy(ppcb->name, name, PNMLEN);

    /* Initialize stack with accounting block. */
    *saddr = STACKMAGIC;
    *--saddr = pid;
    *--saddr = ppcb->stklen;
    *--saddr = (ulong)ppcb->stkbase;

    /* Handle variable number of arguments passed to starting function   */
    if (nargs)
    {
        pads = ((nargs - 1) / 4) * 4;
    }
    /* If more than 4 args, pad record size to multiple of native memory */
    /*  transfer size.  Reserve space for extra args                     */
    for (i = 0; i < pads; i++)
    {
        *--saddr = 0;
    }
    int *actRecord = saddr;
	// TODO: Initialize process context.
	// TODO:  Place arguments into activation record.
	//        See K&R 7.3 for example using va_start, va_arg and
	//        va_end macros for variable argument functions.
   
  //  *--saddr=funcaddr;
   // *--saddr=&userret;
   

    for (i = 0; i < 16; i++)
        {
            *--saddr = 0;
        }
        saddr[CTX_R0]=0;
        saddr[CTX_LR]=&userret; //assigned to LR
        saddr[CTX_PC]=funcaddr; //assigned to PC

    ppcb->stkptr = saddr; //strores the pointer
    /*kprintf("ppcb->stkptr = 0x%08X\n",ppcb->stkptr);
    kprintf("saddr[CTX_R0] = 0x%08X\n",&saddr[CTX_R0]);
    kprintf("saddr[CTX_R1] = 0x%08X\n",&saddr[CTX_R1]);
    kprintf("saddr[CTX_R2] = 0x%08X\n",&saddr[CTX_R2]);
    kprintf("saddr[CTX_R3] = 0x%08X\n",&saddr[CTX_R3]);
    kprintf("saddr[CTX_R4] = 0x%08X\n",&saddr[CTX_R4]);
    kprintf("saddr[CTX_R5] = 0x%08X\n",&saddr[CTX_R5]);
    kprintf("saddr[CTX_R6] = 0x%08X\n",&saddr[CTX_R6]);
    kprintf("saddr[CTX_R7] = 0x%08X\n",&saddr[CTX_R7]);
    kprintf("saddr[CTX_R8] = 0x%08X\n",&saddr[CTX_R8]);
    kprintf("saddr[CTX_R9] = 0x%08X\n",&saddr[CTX_R9]);
    kprintf("saddr[CTX_R10] = 0x%08X\n",&saddr[CTX_R10]);
    kprintf("saddr[CTX_R11] = 0x%08X\n",&saddr[CTX_R11]);
    kprintf("saddr[CTX_IP] = 0x%08X\n",&saddr[CTX_IP]);
    kprintf("saddr[CTX_SP] = 0x%08X\n",&saddr[CTX_SP]);
    kprintf("saddr[CTX_LR] = 0x%08X\n",&saddr[CTX_LR]);
    kprintf("saddr[CTX_PC] = 0x%08X\n",&saddr[CTX_PC]);*/
     int ival;

    va_start(ap, nargs);

    // goes through amount of arguments to add to stack
    for (int i = 0; i < nargs; i++) {
        if (i < 4) { // iterates through registers
            saddr[i]= va_arg(ap, int);
            kprintf("here 0x%08X\r\n", saddr[i]);
        }
        else { // puts in stack
            actRecord[i-4] = va_arg(ap, int);
            kprintf("here2 0x%08X\r\n", actRecord[i-4]);

        }
    }
    va_end(ap);
    return pid;
}

/**
 * Obtain a new (free) process id.
 * @return a free process id, SYSERR if all ids are used
 */
static pid_typ newpid(void)
{
    pid_typ pid;                /* process id to return     */
    static pid_typ nextpid = 0;

    for (pid = 0; pid < NPROC; pid++)
    {                           /* check all NPROC slots    */
        nextpid = (nextpid + 1) % NPROC;
        if (PRFREE == proctab[nextpid].state)
        {
            return nextpid;
        }
    }
    return SYSERR;
}

/**
 * Entered when a process exits by return.
 */
void userret(void)
{
    kill(currpid);
}