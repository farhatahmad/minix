/* Global constants used in RS.
 */
#ifndef RS_CONST_H
#define RS_CONST_H

#define DEBUG_DEFAULT 0

#ifndef DEBUG
#define DEBUG DEBUG_DEFAULT
#endif

/* Space reserved for program and arguments. */
#define MAX_COMMAND_LEN     512         /* maximum argument string length */
#define MAX_SCRIPT_LEN      256         /* maximum restart script name length */
#define MAX_NR_ARGS           4         /* maximum number of arguments */

#define MAX_IPC_LIST        256         /* Max size of list for IPC target
                                         * process names
                                         */

/* Flag values. */
#define RS_IN_USE       0x001    /* set when process slot is in use */
#define RS_EXITING      0x002    /* set when exit is expected */
#define RS_REFRESHING   0x004    /* set when refresh must be done */
#define RS_NOPINGREPLY  0x008    /* service failed to reply to a ping request */
#define RS_TERMINATED   0x010    /* service has terminated */
#define RS_LATEREPLY    0x020    /* no reply sent to RS_DOWN caller yet */
#define RS_INITIALIZING 0x040    /* set when init is in progress */
#define RS_UPDATING     0x080    /* set when update is in progress */
#define RS_ACTIVE       0x100    /* set for the active instance of a service */

/* Sys flag values. */
#define SF_CORE_SRV     0x001    /* set for core system services */
#define SF_SYNCH_BOOT   0X002    /* set when process needs synch boot init */
#define SF_NEED_COPY    0x004    /* set when process needs copy to start */
#define SF_USE_COPY     0x008    /* set when process has a copy in memory */
#define SF_NEED_REPL    0x010    /* set when process needs replica to start */
#define SF_USE_REPL     0x020    /* set when process has a replica */

/* Constants determining RS period and binary exponential backoff. */
#define RS_INIT_T	(system_hz * 10)	/* allow T ticks for init */
#define RS_DELTA_T	(system_hz)		/* check every T ticks */
#define BACKOFF_BITS    (sizeof(long)*8)        /* bits in backoff field */
#define MAX_BACKOFF      30                     /* max backoff in RS_DELTA_T */

/* Magic process table addresses. */
#define BEG_RPROC_ADDR  (&rproc[0])
#define END_RPROC_ADDR  (&rproc[NR_SYS_PROCS])

/* Constants for live update. */
#define RS_DEFAULT_PREPARE_MAXTIME 2*RS_DELTA_T   /* default prepare max time */
#define RS_MAX_PREPARE_MAXTIME     20*RS_DELTA_T  /* max prepare max time */


/* Definitions for boot info tables. */
#define NULL_BOOT_NR    NR_BOOT_PROCS        /* marks a null boot entry */
#define DEFAULT_BOOT_NR NR_BOOT_PROCS        /* marks the default boot entry */
#define SYS_ALL_C       (-1)                 /* specifies all calls */
#define SYS_NULL_C      (-2)                 /* marks a null call entry */

/* Define privilege flags for the various process types. */
#define SRV_F  (SYS_PROC | PREEMPTIBLE)            /* system services */
#define DSRV_F (SRV_F | DYN_PRIV_ID | CHECK_IO_PORT | CHECK_IRQ)
                                                   /* dynamic system services */
#define VM_F   (SYS_PROC)                          /* vm  */
#define RUSR_F (BILLABLE | PREEMPTIBLE)            /* root user proc */

/* Define system call traps for the various process types. These call masks
 * determine what system call traps a process is allowed to make.
 */
#define SRV_T   (~0)                               /* system services */
#define DSRV_T  SRV_T                              /* dynamic system services */
#define RUSR_T  (1 << SENDREC)                     /* root user proc */

/* Send masks determine to whom processes can send messages or notifications. */
#define SRV_M   (~0)                               /* system services */
#define RUSR_M \
    ( spi_to(PM_PROC_NR) | spi_to(FS_PROC_NR) | spi_to(RS_PROC_NR) \
    | spi_to(VM_PROC_NR) )                         /* root user proc */

/* Define the signal manager for the various process types. */
#define SRV_SM  RS_PROC_NR                         /* system services */
#define DSRV_SM RS_PROC_NR                         /* dynamic system services */
#define RUSR_SM PM_PROC_NR                         /* root user proc */

/* Define sys flags for the various process types. */
#define SRV_SF   (SF_CORE_SRV | SF_NEED_COPY)  /* system services */
#define SRVR_SF  (SRV_SF | SF_NEED_REPL)       /* services needing a replica */
#define DSRV_SF  (0)                           /* dynamic system services */
#define VM_SF    (SRVR_SF | SF_SYNCH_BOOT)     /* vm */

/* Define device flags for the various process types. */
#define SRV_DF   (DRV_FORCED)            /* system services */
#define DSRV_DF  (SRV_DF)                /* dynamic system services */

#endif /* RS_CONST_H */

