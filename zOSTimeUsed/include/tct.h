#pragma once

#ifndef __MVS__
#define __ptr32
#endif
/*
 * TCT heading information
 * Common name: SMF TIMING CONTROL TABLE
 * Macro ID: IEFTCT
 * DSECT name: SMFTCT
 * Owning component: System Management Facilities (SC100)
 * Eye-catcher ID: "TCT "
 * Offset: 208 ('D0' in hex)
 * Length: 8 bytes
 * Storage attributes:
 * Subpool: 255
 * Key: 0
 * Residency: Below
 * Size: The common area is 704 bytes ('2C0' in hex)
 * FREQUENCY = 1 per address space
 * Created by: IEFSMFIE
 * Pointed to by: TCBTCT
 * Serialization: Compare and Swap on some fields.
 *
 * Function:
 * This mapping macro is composed of three control blocks (TCT, TCT I/O Measurement table,
 * and Extended TCT I/O table). The TCT consists of a common section (SMFTCT), storage table(TCTCORE),
 * OpenMVS Process table (TCTOMVS), and ARM table (TCTARM).
 *
 * SMFTCT and TCTCORE are one structure and are contiguous in storage. TCTOMVS is not contiguous
 * with SMFTCT or TCTCORE. However, the TCTOMVS and TCTARM are contiguous. The TCT I/O
 * Measurement table (TCTTIOT) and Extended TCT I/O table (ETCTIOT) areas are separate structures, mapped within the IEFTCT
 * mapping macro, and pointed to from fields within the TCT. However, they are NOT contiguous in storage to the TCT or each
 * other.
 *
 */

struct tct
{
   unsigned char tctqa[3]; /* -  Queue Address Of Tct                     */

   union
   {
      unsigned char tctexp; /* - Job/Step Time Indicator Mask */
      unsigned char tctsw;  /* -  Tct Switches                */
   };

   void *__ptr32 tcttcb;   /* -  Address Of The Initiator Tcb           */
   void *__ptr32 tctcrtbl; /* -  Address Of The Tct Storage Table       */
   void *__ptr32 tctiotbl; /* -  Address Of The Tct I/O Table.  Tct I/O */

   int tctpool;            /* -  subpool/length for tct proper */
   short int _filler1;     /* -  subpool in which the tct resides          */
   short int tctsze;       /* -  size in bytes of the tct and the tct      */
   void *__ptr32 tctutl;   /* -  address of user time limit routine        */
   void *__ptr32 tctudata; /* -  address of a one-word parameter list      */
   void *__ptr32 tctjmr;   /* -  address of the job management record      */

   unsigned int tctcpus; /* accum session cpu service(os/vs2)@g50fprl              */
   int tctjstx;          /* -  amount of time that job or step has been */
   unsigned int tcttjlm; /* -           contains remaining job time (32-bit        */

   int tctiocs; /* accum session i/o service(os/vs2)@g50fprl              */

   int tctlin;                /* -  TSO - count of lines of terminal input    */
   int tctlout;               /* -  TSO - count of lines of terminal output   */
   int tctast;                /* -  the time of day (to one hundredth of a    */
   int tctppst;               /* -  the time of day (to one hundredth of a    */
   int tctajs;                /* accumulated session service time*/
   int tctact;                /* accumulated active time*/
   int tctatr;                /* ACCUMULATED TRANSACTION RESIDENCY TIME*/
   int tctmsos;               /* ACCUM SESSION MAIN STORAGE SERVICE */
   int tctsrbs;               /* ACCUM SESSION SRB SERVICE */
   int tctpdasd;              /* - no of mounts for nonspecific dasd @G742PJW */
   int tctrdasd;              /* - no of mounts for specific dasd    @G742PJW */
   int tctptape;              /* - no of mounts for nonspecific tape @G742PJW */
   int tctrtape;              /* - no of mounts for specific tape    @G742PJW */
   int tctpmss;               /* - no of mounts for nonspecific mss  @G742PJW */
   int tctrmss;               /* - no of mounts for specific mss     @G742PJW */
   int tctejst;               /* - last value of elapsed tcb time    @G742PJW */
   int tctsrbt;               /* - last value of elapsed srb time    @G742PJW */
   int tctsvtep;              /* - last value of total block count   @G742PJW */
   int tctlinsv;              /* - last value of tput count          @G742PJW */
   int tctlouts;              /* - last value of tget count          @G742PJW */
   int tcttran;               /* - last value of foreground trans    @G742PJW */
   int tctitcb;               /* - initiator tcb time                @G742PJW */
   int tctisrb;               /* - initiator srb time                @G742PJW */
   int tctt30j;               /* - address of job total type 30 rcd  @G742PJW */
   int tctt30s;               /* - address of step total type 30 rcd @G742PJW */
   int tctt30h;               /* - address of excp hold type 30 rcd  @G742PJW */
   int tctlctad;              /* - address of lct                    @G742PJW */
   int tctt32j;               /* - address of job total type 32 rcd  @G742PJW */
   int tctt32s;               /* - address of step total type 32 rcd @G742PJW */
   int tct32sp;               /* - subpool and size of type 32 rcds  @G742PJW */
   int tct32blk;              /* - address of detail control block   @VS49913 */
   int tctlrrct;              /* - last value of the address space       @D9C */
   int tctiosav;              /* - address of save area for ieasmfex @PCC0508 */
   int tctdcti;               /* - last value of device connect time @G860P27 */
   int tcttimer;              /* - address of smf timer element      @G742PJW */
   int tcttmrsp;              /* - subpool and size of timer elt     @G742PJW */
   int tctparms;              /* - address of timer parameter list   @G742PJW */
   int tctprmsp;              /* - subpool and size of parm list     @G742PJW */
   unsigned char tctsname[8]; /* step name of current step         @VS49841             */
   unsigned char tcttct[8];   /* tct identifier field              @G860P27             */
   int tctmsct;               /* - number of times i/o measurements           */
   int tcteiip;               /* - elapsed i/o interrupt time            @LBC */
   int tcterct;               /* - elapsed rct cpu time                  @LBC */
   int tctrqsvp;              /* pointer to sysevent reqsvdat                           */
   int tcte39pp;              /* pointer to sysevent reqpgdat                           */
   int tcter0ec;              /* reserved, was tctiotlw                @0HC             */
   int tctadmfw;              /* number of pages moved with admf wrITE @02A             */
   int tctadmfr;              /* number of pages moved with admf reAD  @02A             */
   int tctehpt;               /* - elapsed hiperspace processing tiME    @LBC */
   int tcter0fc;              /* - reserved, was tctevfut                @LGC */
   int tcter100;              /* - reserved, was tctevfat                @LGC */
   int tctir104;              /* - reserved, was tctivfut                @LGC */
   int tctir108;              /* - reserved, was tctivfat                @LGC */
   int tctintst;              /* - interval start time                   @L4A */
   int tctintdt;              /* - interval start date                   @L4A */

   int tctfetio;              /* - address of first etctiot block        @D9A */
   int tctletio;              /* - address of last etctiot block         @D9A */
   short int tctesubp;        /* - etctiot subpool                       @D9A */
   short int tctelen;         /* - length of one etctiot block           @D9A */
   int tcteblk;               /* - number of etctiot 4k blocks           @D9A */
   int tctefavl;              /* - 1st available etctiot token           @D9A */
   int tctelavl;              /* - last available etctiot token          @D9A */
   int tctenavl;              /* - number of available etctiot entries   @D9A */
   unsigned char tcteflgs[4]; /* - etctiot flags                         @D9A   */

   int tctansc;               /* - integrated crypto service count       @TEA */
   unsigned char tcttmrfl[2]; /* previous interval timer bit flags     @0KA    */
   unsigned char tctflags;    /* TCT Flags                             @07A    */
   unsigned char tctsrmsp;    /* Subpool for TCTRQSVP,TCTE39PP     @WLMPGMC    */
   int tctt33sp;              /* Address of Type 33 TP Work Area       @DPA    */
   int tctt33j;               /* Address of Type 33 TP JOB Record      @DPA    */
   int tctt33s;               /* Address of Type 33 TP STEP Record     @DPA    */
   int tcttptyp;              /* APPC TP Type (Standard/Multi)         @DPA    */
   int tcttptcb;              /* Last Value of TCB Time for TP         @DPA    */
   int tcttpsrb;              /* Last Value of SRB Time for TP         @DPA    */
   int tcttpexp;              /* Last Value of EXCP Count for TP       @DPA    */
   int tcttpdct;              /* Last Value of Dev Conn Time for TP    @DPA    */
   int tcttpnum;              /* Number of Transactions Processed      @DPA    */
   int tcttpcon;              /* Number of Conversations               @DPA    */
   int tcttptac;              /* Number of Active Cons                 @DPA    */
   int tcttpcna;              /* Number of Cons Allocated              @DPA    */
   int tcttpsen;              /* Number of Sends for TP                @DPA    */
   unsigned char tcttpdat[8]; /* Amount of Data Sent                   @DPA    */
   int tcttprec;              /* Number of Recvs for TP                @DPA    */
   unsigned char tcttpdar[8]; /* Amount of Data Received               @DPA    */
   unsigned char tctsubnm[4]; /* Scheduler of Job                      @DPA    */
   void *__ptr32 tctomvsp;    /* Address of TCTOMVS Table              @LUA    */
   void *__ptr32 tctt30ph;    /* Address of T30AREA for Process Data   @LUA    */
   void *__ptr32 tctt30se;    /* Address of T30AREA for Step EXCP Data @LUA    */
   void *__ptr32 tctt30sp;    /* Address of T30AREA for Step Process   @LUA    */
   void *__ptr32 tctt30je;    /* Address of T30AREA for Job EXCP Data  @LUA    */
   void *__ptr32 tctt30jp;    /* Address of T30AREA for Job Process    @LUA    */
   unsigned char tctiss[8];   /* SMF Interval Start Time (STCK Format) @DVA    */
   int tct30cn;               /* Last Number of Conversations          @01A    */
   int tct30cna;              /* Last Number of Cons Allocated         @01A    */
   int tct30sen;              /* Last Number of Sends for TP           @01A    */
   unsigned char tct30dat[8]; /* Last Amount of Data Sent              @01A    */
   int tct30rec;              /* Last Number of Recvs for TP           @01A    */
   unsigned char tct30dar[8]; /* Last Amount of Data Received          @01A    */
   int tct30atr;              /* Last Number of Transactions Processed @01A    */
   int tctuacl;               /* Usage ACA Lockword                    @04A    */
   void *__ptr32 tctuaca;     /* Address of First ACA for job          @04A    */
   void *__ptr32 tctutcac;    /* Addr of 1st TCA on consolidated chain @09C    */
   void *__ptr32 tctutca;     /* Address of First TCA on chain         @04A    */
   void *__ptr32 tctufcac;    /* Addr of 1st FCA on consolidated chain @08C    */
   void *__ptr32 tctufca;     /* Address of First FCA on chain         @04A    */
   int tctrsmgt;              /* Usage RESMGR Token                    @04A    */
   void *__ptr32 tctutimr;    /* Usage Timer Element                   @04A    */
   void *__ptr32 tctutprm;    /* Usage Timer ParmArea                  @04A    */
   void *__ptr32 tctt30uh;    /* Address of T30AREA Hold area for      @05A    */
   void *__ptr32 tctt30us;    /* Address of T30AREA Step Hold Area for @05A    */
   void *__ptr32 tctt30uj;    /* Address of T30AREA Job Hold Area for  @05A    */
   void *__ptr32 tctarmp;     /* Address of TCTARM table               @L1A    */
   void *__ptr32 tctt30ah;    /* Address of T30AREA for ARM Data       @L1A    */
   void *__ptr32 tctt30sa;    /* Address of T30AREA for Step ARM Data  @L1A    */
   void *__ptr32 tctt30ja;    /* Address of T30AREA for Job ARM Data   @L1A    */
   int tctasst;               /* Additional SRB Service Time           @L3A    */
   int tctecpt;               /* Enclave CPU Time                      @L3A    */
   int tctetim;               /* Enclave Transaction Active Time       @L3A    */
   int tctecpu;               /* Enclave CPU Service Units             @L3A    */
   int tctetc;                /* Enclave Transaction Count             @P5C    */
   int tctasstc;              /* Additional SRB Service Time (Cumulative)      */
   int tctecptc;              /* Enclave CPU Time (Cumulative)                 */
   int tctdet;                /* Dependent enclave CPU time            @D3A    */
   int tct30aic;              /* Saved copy of RQSVAIC                 @D3A    */
   int tct30aid;              /* Saved copy of RQSVAID                 @D3A    */
   int tct30aiw;              /* Saved copy of RQSVAIW                 @D3A    */
   int tct30ais;              /* Saved copy of RQSVAIS                 @D3A    */
   int tct30eic;              /* Saved copy of RQSVEIC                 @D3A    */
   int tct30eid;              /* Saved copy of RQSVEID                 @D3A    */
   int tct30eiw;              /* Saved copy of RQSVEIW                 @D3A    */
   int tct30eis;              /* Saved copy of RQSVEIS                 @D3A    */
   int tctt30sr;              /* Address of STEP area for Remote       @LAA    */
   int tctt30jr;              /* Address of JOB area for Remote        @LAA    */

   int tct_time_on_ifa;                /* Work unit on IFA                      @H5A             */
   int tct_time_ifa_on_cp;             /* IFA-eligible work unit on CP          @H5A             */
   int tct_enclave_time_on_ifa;        /* Work unit on IFA                      @H5A             */
   int tct_enclave_time_ifa_on_cp;     /* IFA-eligible work unit on CP       @H5A                */
   int tct_dep_enclave_time_on_ifa;    /* Work unit on IFA                  @H5A                 */
   int tct_dep_enclave_time_ifa_on_cp; /* IFA-eligible work unit on CP   @H5A                    */

   int tcttmrfl2;                  /* More failure flags                    @H5A             */
   int tct_time_on_cp;             /* Work unit on CP                       @H6A             */
   int tct_enclave_time_on_cp;     /* Work unit on CP                        @H6A            */
   int tct_dep_enclave_time_on_cp; /* Work unit on CP                    @H6A                */
   int tct_cepi;                   /* SMF30CEPI                             @P7A             */

   int tct_time_on_sup;            /* Work unit on SUP                      @H6A             */
   int tct_time_sup_on_cp;         /* SUP-eligible work unit on CP          @H6A             */
   int tct_enclave_time_on_sup;    /* Work unit on SUP                      @H6A             */
   int tct_enclave_time_sup_on_cp; /* SUP-eligible work unit on CP       @H6A                */
   int tct_enclave_time_sup_qual;  /* SUP-qualified time                  @H6A               */
   int tct_depenc_time_on_sup;     /* Work unit on SUP                       @H6A            */
   int tct_depenc_time_sup_on_cp;  /* SUP-eligible work unit on CP        @H6A               */
   int tct_depenc_time_sup_qual;   /* SUP-qualified time                   @H6A              */

   unsigned long long int tctsvtex; /* 64-bit Total Block Count              @0EA             */
   unsigned long long int tcttpexx; /* Last Value of 64-bit EXCP Count for TP@0EA             */
   int tct_crp;                     /* SMF30CRP                              @LWA             */
   int tctsmfxp;                    /* Pointer to SMFTCT extension section   @LIC             */
   int tctlucnt;                    /* Count of DD entries in TCTIOT lookup                   */
   int tct_missed_tctdctr;          /* Accumulated I/O block counts that were                 */
   int tctsv_missed_tctdctr;        /* Last value of TCT_Missed_TCTDCTR,                      */
   int tct_missed_tctconn;          /* Accumulated device connect time that was               */
   int tctsv_missed_tctconn;        /* Last value of TCT_Missed_TCTCONN,                      */
   unsigned char tctbndry[4];       /* Reserved for alignment of TCTEND      @LHC             */
};

/*
 END OF TCT MAPPING - This address ***MUST*** be on doubleword boundary.
Adjust the length of the TCTBNDRY field or comment it out as necessary.
*/

/*
* TCT Storage Table
 a separate table is used to describe the storage obtained
 for a task. the storage table is contiguous to the tct.
 it is pointed to by the tctcrtbl field in the tct common
 section.
*/
struct tctcore
{
   int tctlwm; /* -  max virtual storage in user subpools      */
   int tcthwm; /* -  max virtual storage in swa and lsqa       */

   short int tctminc;            /* - the minimum difference (in 2k blocks)     */
   short int tctrsv00;           /* - reserved.  region field increased to      */
   void *__ptr32 tctrba;         /* - for a v=v problem program, lowest address */
   int tctehwm;                  /* - max virtual storage in swa and lsqa       */
   int tctelwm;                  /* - max virtual storage in user subpools      */
   int tctrgnb;                  /* private area below 16m in bytes      @pvc              */
   int tctergnb;                 /* private area above 16m in bytes      @pvc              */
   int tctrsz;                   /* original region request in 2k blocks @pvm              */
   int tctrsv01;                 /* - reserved                             @lvc */
   unsigned long long inttctmem; /* - memlimit in mb                       @lva */
   unsigned char tctmems;        /* - source of memlimit                   @0da   */
   unsigned char tctslm;         /* - actions taken by smflimxx policy     @0ia   */
   unsigned char tctrsv02[2];    /* - reserved                             @0ic   */
};

/*
770 (302) X'34' 0 TCTCREZ "*-TCTCORE" - length of tct storage table
770 (302) X'304' 0 TCTBIG "*-SMFTCT" - combined length of tct common section and tct storage table
*/

/*
TCT input/output measurement table
the tct i/o measurement table (tcttiot) is composed of the tct i/o lookup table and the tct i/o counter table. it is
used to collect i/o measurements at the dd level. the tcttiot is not contiguous to the tct. the tctiotbl field
in the tct common section points to the tcttiot. the tcttiot is created by iefib660 in subpool 255/key 0
and resides above the 16m line. the tct i/o lookup table contains 1 common section and a
dd lookup table. the dd lookup table is an array with each element representing one dd entry in the tiot (ieftiot).
smf references these dd look-up entries to find the first device entry in the tct i/o counter table associated with
a particular dd.

the tct i/o counter table consists of one dd entry per entry in the dd look-up table. each dd entry consists of
1 or more 24 byte device entries which represent the ucbs associated with the dd. there is one 8 byte output limit
extension which is used by gpd. the size of the tcttiot is dependent on the number of
dds per job. there is 1 dd lookup table per dd and
1 device entry per device (ucb) per dd.
*/
struct tcttiot
{

   unsigned char _filler2;    /* -  subpool in which the tct i/o table        */
   unsigned char tctszext[3]; /* size in bytes of tct i/o table                         */
                              /* -  subpool/length of tct i/o table            */

   int tctszlkp;              /* - number of device entries in the tct       */
   int tctdcbtd;              /* - offset from the tiot origin to the tiot   */
   int tctiotsd;              /* - offset from the tct i/o table origin to   */
   int tctdcble;              /* - end of tct i/o lookup table (zeros)       */
   int tctucbp;               /* - address of the ucb associated   @g860p27  */
   char tctsctr;              /* - number of devices associated with this      */
   unsigned char tctflgs;     /* - flag byte                          mdc013 */
   short int tctblksz;        /* - block size for this dd name     @g742pjw  */
   int tctdctr;               /* - counter for excp's issued against this    */
   int tctdctrs;              /* - saved excp count for this entry @g860p27  */
   int tctconn;               /* - device connect time             @g860p27  */
   int tctconns;              /* - saved device connect time       @g860p27  */
   unsigned char tctxblks[8]; /* blocksize >32k for this dd name     @lda               */
   unsigned char tctrsv10[4]; /* - *** tctoutlm field reserved in os/vs ***    */
   char tctexrld;             /* - a binary number of extents released by      */
   int tcttkrld : 24;         /* - a binary number of tracks released by the   */
};

/*
 * Extended tctiot control block
 * The etctiot is a chain of 4k blocks. Each 4k block consists of a 16 byte header and an array of a maximum of 340 elements. Each
 * element is 12 bytes in length and represents a dd entry inthe tcttiot.
 *
 * The etctiot is not contiguous to the tct common section or the tcttiot. The first etctiot is pointed to by the tctfetio
 * field in the tct common section. Additional fields exist in the tct common section which describe the etctiot chain.
 * The etctiot is created by iefib660 in subpool 255 and key 0. The chain resides above the 16m line.
 *
 * There is 1 etctiot chain per address space. The size of the chain is based on the number of dds per job:
 *
 * minimum chain = 1 4k block (1 4096 = 4096 bytes)
 * average chain = 1 4k block (average job < 100 dds)
 * maximum chain = 10 4k blocks (10 4096 = 40,960 bytes)
 *               = maximum chain is based on 3273 dds* etctiot header (one header per block)
 */

struct etctiot
{
   unsigned char etctid[7]; /* - etctiot identifier = 'etctiot'       @d9a   */
   unsigned char etctver;   /* - etctiot version number = x'01'       @d9a   */
   int etctfchn;            /* -   next etctiot block address           @d9a */
   int etctbchn;            /* -   previous etctiot block address       @d9a */
   int etctnext;            /* -   next token                           @d9a */
   int etctdsab;            /* -   dsab address of entry                @d9a */
   int etctstio;            /* -   tctiot dd lookup entry offset        @d9a */
};

/*
 * TCTOMVS - TCT OpenMVS Process Data Table
 * The OpenMVS Process Data Table is 104 bytes.
 * Size should always be a multiple of 8.
 * the tct openmvs process data table (tctomvs) is pointed
 * to by tctomvsp in the tct common section.
 */
struct tctomvs
{
   unsigned char tctoid[4]; /* Control Block ID  'TCTO'             @LUA              */

   /* -         TCT OpenMVS Header Section           @03A    */

   unsigned char tctosp;    /* - Subpool                            @LUA              */
   unsigned char tctoln[3]; /* - Length                             @LUA              */

   /* -        TCT OpenMVS Data Section             @L9C     */

      int tctopi; /* -  Process ID                           @LUA */
   int tctopg; /* -  Process Group ID                     @LUA */
   int tctoui; /* -  Process User ID                      @LUA */
   int tctoug; /* -  Process User Group ID                @LUA */
   int tctosi; /* -  Process Session ID                   @LUA */
   int tctosc; /* -  Number of syscals requested          @LUA */
   int tctost; /* -  Total CPU Time accumulated by the    @LUA */
   int tctodr; /* -  Number of directory I/O blocks read @D1C  */
   int tctofr; /* -  Number of I/O blocks read for             */
   int tctofw; /* -  Number of I/O blocks written for          */
   int tctopr; /* -  Number of I/O blocks read for pipe        */
   int tctopw; /* -  Number of I/O blocks written for          */
   int tctosr; /* -  Number of I/O blocks read for             */
   int tctosw; /* -  Number of I/O blocks written for          */
   int tctoll; /* -  Number of path name Lookup calls to  @LUA */
   int tctolp; /* -  Number of path name Lookup calls to  @LUA */
   int tctogl; /* -  Number of path name Generation calls @LUA */
   int tctogp; /* -  Number of path name Generation calls @LUA */
   int tctopp; /* -  OpenMVS parent process ID number     @L2A */
   int tctokr; /* -  Number of I/O blocks read for Remote      */
   int tctokw; /* -  Number of I/O blocks written for          */
   int tctoms; /* -  Number of message queues bytes sent  @L8A */
   int tctomr; /* -  Number of message queues bytes received   */
   int tctosy; /* -  Number of sync() function calls      @L9C */
};

/*
 * TCTARM - TCT ARM Data Table
 * The ARM data table is 88 bytes.
 * The TCT ARM Data Table (TCTARM) is pointed to by
 * TCTARMP in the TCT common section.
 */
struct tctarmd
{
   unsigned char tctaid[4]; /* Control Block ID  'TCTA'             @L1A              */

   struct
   {
      unsigned char tctasp;    /* - Subpool                            @L1A              */
      unsigned char tctaln[3]; /* - Length                             @L1A              */
   } tctaspln;                 /* Control Block Subpool and Length     @L1A              */

   unsigned char tctarnm[16]; /* Element Name                         @L1A              */
   unsigned char tctartp[8];  /* Element Type                         @L1A              */
   unsigned char tctarrg[16]; /* Restart Group for Element            @L1A              */
   unsigned char tctarsn[8];  /* The system name for the system on    @L1A              */
   int tctargt;               /* -            Time (local) Element requested       @L1A */
   unsigned char tctargd;     /* -            Date Element requested REGISTER      @L1A */
   unsigned char _filler3[3];
   int tctarwt;           /* -            Time (local) Element requested       @L1A */
   unsigned char tctarwd; /* -            Date Element requested WAITPRED      @L1A */
   unsigned char _filler4[3];
   int tctaryt;           /* -            Time (local) Element was READY,      @L1A */
   unsigned char tctaryd; /* -            Date Element was READY, in the       @L1A */
   unsigned char _filler5[3];
   int tctartt;           /* -            Time (local) Element was             @L1A */
   unsigned char tctartd; /* -            Date Element was DEREGISTERED, in    @L1A */
};

/* Values for field "tctsw" */
#define tctjsti 0x80  /* -         tqe job/step time indicator.             */
#define tctiex 0x40   /* -         error in tct i/o table i/o counts        */
#define tctisk30 0x20 /* -   type 30 interval record skipped  @g743pjw      */
#define tctisk32 0x10 /* -   type 32 interval record skipped  @g743pjw      */
#define tctiabd 0x08  /* -   previous interval abended        @g743pjw      */
#define tctstprn 0x04 /* -   step ran indicator               @zmc1603      */
#define tctactrt 0x02 /* -   iefactrt in control indicator    @za90520      */
#define tctdcopn 0x01 /* -   dmpchck rtn in control indicator @za93106      */

/* Values for field "tctmsct" */
#define tctmsoff 0x80 /* I/O MEASUREMENTS ARE ON           @G860P27         */

/* Values for field "tcteflgs" */
#define tctcomp 0x80  /* -       TCTTIOT BEING MOVED INDICATOR         @D9A */
#define tctdummy 0x40 /* -       When set by IEFIB660, this flag represents */

/* Values for field "tcttmrfl" */
#define tctctf 0x80 /* SMF30CPT TIMER INVALID                @0KA         */
#define tctcsf 0x40 /* SMF30CPS TIMER INVALID                @0KA         */
#define tctvuf 0x20 /* SMF30JVU TIMER INVALID                @0KA         */
#define tctvaf 0x10 /* SMF30JVA TIMER INVALID                @0KA         */
#define tctisf 0x08 /* SMF30ISB TIMER INVALID                @0KA         */
#define tcticf 0x04 /* SMF30ICU TIMER INVALID                @0KA         */
#define tctivf 0x02 /* SMF30IVU TIMER INVALID                @0KA         */
#define tctiaf 0x01 /* SMF30IVA TIMER INVALID                @0KA         */
#define tctiif 0x80 /* SMF30IIP TIMER INVALID                @0KA         */
#define tcthpf 0x40 /* SMF30HPT TIMER INVALID                @0KA         */
#define tctrcf 0x20 /* SMF30RCT TIMER INVALID                @0KA         */
#define tctasf 0x10 /* SMF30ASR TIMER INVALID                @L3A         */
#define tctenf 0x08 /* SMF30ENC TIMER INVALID                @L3A         */
#define tctdef 0x04 /* SMF30DET TIMER INVALID                @D3A         */

/* Values for field "tctflags" */
#define tcttct2 0x80 /* DSABTCT2 should be used to contain    @07A         */

/* Values for field "tcttmrfl2" */
#define tct_time_on_zcbp_f 0x80                /* Failure flag           @LJA                        */
#define tct_time_on_ifa_f 0x80                 /* Failure flag           @H5A                        */
#define tct_time_zcbp_on_cp_f 0x40             /* Failure flag           @LJA                        */
#define tct_time_ifa_on_cp_f 0x40              /* Failure flag           @H5A                        */
#define tct_enclave_time_on_zcbp_f 0x20        /* Failure flag           @LJA                        */
#define tct_enclave_time_on_ifa_f 0x20         /* Failure flag           @H5A                        */
#define tct_enclave_time_zcbp_on_cp_f 0x10     /* Failure flag           @LJA                        */
#define tct_enclave_time_ifa_on_cp_f 0x10      /* Failure flag           @H5A                        */
#define tct_dep_enclave_time_on_zcbp_f 0x08    /* Failure flag           @LJA                        */
#define tct_dep_enclave_time_on_ifa_f 0x08     /* Failure flag           @H5A                        */
#define tct_dep_enclave_time_zcbp_on_cp_f 0x04 /* Failure flag           @LJA                        */
#define tct_dep_enclave_time_ifa_on_cp_f 0x04  /* Failure flag            @H5A                       */
#define tct_time_on_cp_f 0x02                  /* Failure flag           @H5A                        */
#define tct_enclave_time_on_cp_f 0x01          /* Failure flag           @H5A                        */
#define tct_dep_enclave_time_on_cp_f 0x80      /* Failure flag           @H5A                        */
#define tct_cepi_f 0x40                        /* Failure flag           @P7A                        */
#define tct_crp_f 0x20                         /* Failure flag           @LWA                        */
#define tct_time_on_ziip_f 0x80                /* Failure flag           @LJA                        */
#define tct_time_on_sup_f 0x80                 /* Failure flag           @H6A                        */
#define tct_time_ziip_on_cp_f 0x40             /* Failure flag           @LJA                        */
#define tct_time_sup_on_cp_f 0x40              /* Failure flag           @H6A                        */
#define tct_enclave_time_on_ziip_f 0x20        /* Failure flag           @LJA                        */
#define tct_enclave_time_on_sup_f 0x20         /* Failure flag           @H6A                        */
#define tct_enclave_time_ziip_on_cp_f 0x10     /* Failure flag           @LJA                        */
#define tct_enclave_time_sup_on_cp_f 0x10      /* Failure flag           @H6A                        */
#define tct_depenc_time_on_ziip_f 0x08         /* Failure flag           @LJA                        */
#define tct_depenc_time_on_sup_f 0x08          /* Failure flag           @H6A                        */
#define tct_depenc_time_ziip_on_cp_f 0x04      /* Failure flag                @LJA                   */
#define tct_depenc_time_sup_on_cp_f 0x04       /* Failure flag                 @H6A                  */
#define tct_enclave_time_ziip_qual_f 0x80      /* Failure flag           @LJA                        */
#define tct_enclave_time_sup_qual_f 0x80       /* Failure flag           @H6A                        */
#define tct_depenc_time_ziip_qual_f 0x40       /* Failure flag           @LJA                        */
#define tct_depenc_time_sup_qual_f 0x40        /* Failure flag           @H6A                        */

/* Values for field "tctslm" */
#define tctsl1 0x80 /* -        SMFLIMxx set REGION BELOW value      @0IA */
#define tctsl2 0x40 /* -        SMFLIMxx set SYSRESVBELOW value      @0IA */
#define tctsl3 0x20 /* -        SMFLIMxx set REGION ABOVE value      @0IA */
#define tctsl4 0x10 /* -        SMFLIMxx set SYSRESVABOVE value      @0IA */
#define tctsl5 0x08 /* -        SMFLIMxx set a MEMLIMIT              @0IA */
#define tctsl6 0x04 /* -        IEFUSI overrode all SMFLIMxx actions @0IA */

/* Values for field "tctrsv02" */
#define tctcrez 0x34 /* -    LENGTH OF TCT STORAGE TABLE          @PVM     */
#define tctbig 0x304 /* -     COMBINED LENGTH OF TCT COMMON SECTION        */

/* Values for field "tctszlkp" */
#define tctcomio 0x08 /* -    LENGTH OF TCT I/O TABLE COMMON SECTION        */

/* Values for field "tctflgs" */
#define tctddind 0x80 /* -        END OF CONCATENATED DD STRING (OS/VS1)    */
#define tctvamds 0x40 /* -        VAM DATA SET ENTRY.  TCTUCBP FIELD IS     */
#define tctnocnt 0x20 /* -        IF ON, DO NOT COUNT THE EXCP (OS/VS1)     */
#define tctrsv22 0x10 /* -  RESERVED                                        */
#define tctrsv23 0x08 /* -  RESERVED                                        */
#define tctrsv24 0x04 /* -  RESERVED                                        */
#define tctrsv25 0x02 /* -  RESERVED                                        */
#define tctrsv26 0x01 /* -  RESERVED                                        */

/* Values for field "tctblksz" */
#define tctcbsz 0x80 /* CHANGED BLOCK SIZE IF ON        @G742PJW           */

/* Values for field "tctxblks" */
#define tctddlen 0x20 /* @G742PJW                                           */

/* Values for field "etctnext" */
#define etctiuse 0x80 /* -        ENTRY IN USE  (1=IN USE)             @D9A */

#define tctend 0x2D0   /* END OF TCT MAPPING  - This address    @LFC         */
#define tctcomz 0x2D0  /* -    LENGTH OF TCT COMMON SECTION                  */
#define tcttiot 0x304  /* -            BEGINNING OF TCT I/O TABLE            */
#define tctiodsp 0x30C /* -            START OF DD LOOKUP TABLE ENTRY        */
#define tctddent 0x318 /* -            START OF TCT I/O COUNTER TABLE (DEVICE */
#define etctiot 0x340  /* -            EXTENDED TCTIOT                      @D9A */
#define etcthdr 0x340  /* -            ETCTIOT HEADER SECTION               @D9A */
#define etctntry 0x350 /* ETCTIOT DD ENTRY                     @D9A          */
