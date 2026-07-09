/*
TCT heading information
Common name: SMF TIMING CONTROL TABLE
Macro ID: IEFTCT
DSECT name: SMFTCT
Owning component: System Management Facilities (SC100)
Eye-catcher ID: "TCT "
Offset: 208 ('D0' in hex)
Length: 8 bytes
Storage attributes:
Subpool: 255
Key: 0
Residency: Below
Size: The common area is 704 bytes ('2C0' in hex)
FREQUENCY = 1 per address space
Created by: IEFSMFIE
Pointed to by: TCBTCT
Serialization: Compare and Swap on some fields.

Function:
This mapping macro is composed of three control blocks (TCT, TCT I/O Measurement table,
and Extended TCT I/O table). The TCT consists of a common section (SMFTCT), storage table
(TCTCORE), OpenMVS Process table (TCTOMVS), and ARM table (TCTARM).

SMFTCT and TCTCORE are one structure and are contiguous in storage. TCTOMVS is not contiguous
with SMFTCT or TCTCORE. However, the TCTOMVS and TCTARM are contiguous. The TCT I/O
Measurement table (TCTTIOT) and Extended TCT I/O table (ETCTIOT) areas are separate structures, mapped within the IEFTCT
mapping macro, and pointed to from fields within the TCT. However, they are NOT contiguous in storage to the TCT or each
other.
*/

struct smftct
{
   unsigned char tctqa[3]; /* -          QUEUE ADDRESS OF TCT                     */
   union {
      unsigned char tctexp; /* -           JOB/STEP TIME INDICATOR MASK */
      unsigned char tctsw;  /* -            TCT SWITCHES                */
   };
   void *tcttcb;   /* -            ADDRESS OF THE INITIATOR TCB           */
   void *tctcrtbl; /* -            ADDRESS OF THE TCT STORAGE TABLE       */
   void *tctiotbl; /* -            ADDRESS OF THE TCT I/O TABLE.  TCT I/O */
   union {
      int tctpool; /* -           SUBPOOL/LENGTH FOR TCT PROPER */
      struct
      {
         short int _filler1; /* -  SUBPOOL IN WHICH THE TCT RESIDES          */
         short int tctsze;   /* -  SIZE IN BYTES OF THE TCT AND THE TCT      */
         void *tctutl;       /* -  ADDRESS OF USER TIME LIMIT ROUTINE        */
         void *tctudata;     /* -  ADDRESS OF A ONE-WORD PARAMETER LIST      */
         void *tctjmr;       /* -  ADDRESS OF THE JOB MANAGEMENT RECORD      */
         struct
         {
            unsigned char tctrsv08[4]; /* -          *** TCTUSO FIELD RESERVED IN OS/VS ***      */
         } tctcpus;                    /* ACCUM SESSION CPU SERVICE(OS/VS2)@G50FPRL              */
         struct
         {
            int tctstof; /* -            OVERFLOW FIELD FOR USER-SUPPLIED STEP     */
         } tctjstx;      /* -           AMOUNT OF TIME THAT JOB OR STEP HAS BEEN   */
         struct
         {
            int tctsact; /* -            A RUNNING TOTAL OF THE USER-SUPPLIED STEP */
         } tcttjlm;      /* -           CONTAINS REMAINING JOB TIME (32-BIT        */
         struct
         {
            int tctwlmt; /* -            THE JOB OR STEP MAXIMUM WAIT TIME LIMIT   */
         } tctiocs;      /* ACCUM SESSION I/O SERVICE(OS/VS2)@G50FPRL              */
         int tctlin;     /* -            TSO - COUNT OF LINES OF TERMINAL INPUT    */
         int tctlout;    /* -            TSO - COUNT OF LINES OF TERMINAL OUTPUT   */
         int tctast;     /* -            THE TIME OF DAY (TO ONE HUNDREDTH OF A    */
         int tctppst;    /* -            THE TIME OF DAY (TO ONE HUNDREDTH OF A    */
         struct
         {
            struct
            {
               int tctpgin; /* -            TOTAL PAGE-INS FOR THIS REGION            */
            } tctajs;       /* -           ACCUMULATED SESSION SERVICE TIME           */
            struct
            {
               int tctpgout; /* -            TOTAL PAGE-OUTS FOR THIS REGION           */
            } tctact;        /* -           ACCUMULATED ACTIVE TIME (OS/VS2)           */
            struct
            {
               int tctrgns; /* -            TOTAL SWAPS PERFORMED FOR THIS TSO        */
            } tctatr;       /* -           ACCUMULATED TRANSACTION RESIDENCY TIME     */
            struct
            {
               int tctsin; /* -            TOTAL PAGES SWAPPED-IN FOR THIS TSO       */
            } tctmsos;     /* ACCUM SESSION MAIN STORAGE SERVICE                     */
            struct
            {
               int tctsout;         /* -            TOTAL PAGES SWAPPED-OUT FOR THIS TSO      */
            } tctsrbs;              /* ACCUM SESSION SRB SERVICE (OS/VS2)                     */
         } tctpgsmf;                /* -        SMF REGION-RELATED STATISTICS                 */
         int tctpdasd;              /* -           NO OF MOUNTS FOR NONSPECIFIC DASD @G742PJW */
         int tctrdasd;              /* -           NO OF MOUNTS FOR SPECIFIC DASD    @G742PJW */
         int tctptape;              /* -           NO OF MOUNTS FOR NONSPECIFIC TAPE @G742PJW */
         int tctrtape;              /* -           NO OF MOUNTS FOR SPECIFIC TAPE    @G742PJW */
         int tctpmss;               /* -           NO OF MOUNTS FOR NONSPECIFIC MSS  @G742PJW */
         int tctrmss;               /* -           NO OF MOUNTS FOR SPECIFIC MSS     @G742PJW */
         int tctejst;               /* -           LAST VALUE OF ELAPSED TCB TIME    @G742PJW */
         int tctsrbt;               /* -           LAST VALUE OF ELAPSED SRB TIME    @G742PJW */
         int tctsvtep;              /* -           LAST VALUE OF TOTAL BLOCK COUNT   @G742PJW */
         int tctlinsv;              /* -           LAST VALUE OF TPUT COUNT          @G742PJW */
         int tctlouts;              /* -           LAST VALUE OF TGET COUNT          @G742PJW */
         int tcttran;               /* -           LAST VALUE OF FOREGROUND TRANS    @G742PJW */
         int tctitcb;               /* -           INITIATOR TCB TIME                @G742PJW */
         int tctisrb;               /* -           INITIATOR SRB TIME                @G742PJW */
         int tctt30j;               /* -           ADDRESS OF JOB TOTAL TYPE 30 RCD  @G742PJW */
         int tctt30s;               /* -           ADDRESS OF STEP TOTAL TYPE 30 RCD @G742PJW */
         int tctt30h;               /* -           ADDRESS OF EXCP HOLD TYPE 30 RCD  @G742PJW */
         int tctlctad;              /* -           ADDRESS OF LCT                    @G742PJW */
         int tctt32j;               /* -           ADDRESS OF JOB TOTAL TYPE 32 RCD  @G742PJW */
         int tctt32s;               /* -           ADDRESS OF STEP TOTAL TYPE 32 RCD @G742PJW */
         int tct32sp;               /* -           SUBPOOL AND SIZE OF TYPE 32 RCDS  @G742PJW */
         int tct32blk;              /* -           ADDRESS OF DETAIL CONTROL BLOCK   @VS49913 */
         int tctlrrct;              /* -           LAST VALUE OF THE ADDRESS SPACE       @D9C */
         int tctiosav;              /* -           ADDRESS OF SAVE AREA FOR IEASMFEX @PCC0508 */
         int tctdcti;               /* -           LAST VALUE OF DEVICE CONNECT TIME @G860P27 */
         int tcttimer;              /* -           ADDRESS OF SMF TIMER ELEMENT      @G742PJW */
         int tcttmrsp;              /* -           SUBPOOL AND SIZE OF TIMER ELT     @G742PJW */
         int tctparms;              /* -           ADDRESS OF TIMER PARAMETER LIST   @G742PJW */
         int tctprmsp;              /* -           SUBPOOL AND SIZE OF PARM LIST     @G742PJW */
         unsigned char tctsname[8]; /* STEP NAME OF CURRENT STEP         @VS49841             */
         unsigned char tcttct[8];   /* TCT IDENTIFIER FIELD              @G860P27             */
         int tctmsct;               /* -           NUMBER OF TIMES I/O MEASUREMENTS           */
         int tcteiip;               /* -           ELAPSED I/O INTERRUPT TIME            @LBC */
         int tcterct;               /* -           ELAPSED RCT CPU TIME                  @LBC */
         int tctrqsvp;              /* Pointer to sysevent REQSVDAT                           */
         int tcte39pp;              /* Pointer to sysevent REQPGDAT                           */
         int tcter0ec;              /* Reserved, was TCTIOTLW                @0HC             */
         int tctadmfw;              /* Number of pages moved with ADMF WRITE @02A             */
         int tctadmfr;              /* Number of pages moved with ADMF READ  @02A             */
         int tctehpt;               /* -           ELAPSED HIPERSPACE PROCESSING TIME    @LBC */
         int tcter0fc;              /* -           RESERVED, WAS TCTEVFUT                @LGC */
         int tcter100;              /* -           RESERVED, WAS TCTEVFAT                @LGC */
         int tctir104;              /* -           RESERVED, WAS TCTIVFUT                @LGC */
         int tctir108;              /* -           RESERVED, WAS TCTIVFAT                @LGC */
         int tctintst;              /* -           INTERVAL START TIME                   @L4A */
         int tctintdt;              /* -           INTERVAL START DATE                   @L4A */
         struct
         {
            int tctfetio;              /* -           ADDRESS OF FIRST ETCTIOT BLOCK        @D9A */
            int tctletio;              /* -           ADDRESS OF LAST ETCTIOT BLOCK         @D9A */
            short int tctesubp;        /* -           ETCTIOT SUBPOOL                       @D9A */
            short int tctelen;         /* -           LENGTH OF ONE ETCTIOT BLOCK           @D9A */
            int tcteblk;               /* -           NUMBER OF ETCTIOT 4K BLOCKS           @D9A */
            int tctefavl;              /* -           1ST AVAILABLE ETCTIOT TOKEN           @D9A */
            int tctelavl;              /* -           LAST AVAILABLE ETCTIOT TOKEN          @D9A */
            int tctenavl;              /* -           NUMBER OF AVAILABLE ETCTIOT ENTRIES   @D9A */
            unsigned char tcteflgs[4]; /* -         ETCTIOT FLAGS                         @D9A   */
         } tcteinfo;                   /* ETCTIOT INFORMATION                   @Q8A             */
         int tctansc;                  /* -           INTEGRATED CRYPTO SERVICE COUNT       @TEA */
         unsigned char tcttmrfl[2];    /* PREVIOUS INTERVAL TIMER BIT FLAGS     @0KA             */
         unsigned char tctflags;       /* TCT Flags                             @07A             */
         unsigned char tctsrmsp;       /* Subpool for TCTRQSVP,TCTE39PP     @WLMPGMC             */
         int tctt33sp;                 /* Address of Type 33 TP Work Area       @DPA             */
         int tctt33j;                  /* Address of Type 33 TP JOB Record      @DPA             */
         int tctt33s;                  /* Address of Type 33 TP STEP Record     @DPA             */
         int tcttptyp;                 /* APPC TP Type (Standard/Multi)         @DPA             */
         int tcttptcb;                 /* Last Value of TCB Time for TP         @DPA             */
         int tcttpsrb;                 /* Last Value of SRB Time for TP         @DPA             */
         int tcttpexp;                 /* Last Value of EXCP Count for TP       @DPA             */
         int tcttpdct;                 /* Last Value of Dev Conn Time for TP    @DPA             */
         int tcttpnum;                 /* Number of Transactions Processed      @DPA             */
         int tcttpcon;                 /* Number of Conversations               @DPA             */
         int tcttptac;                 /* Number of Active Cons                 @DPA             */
         int tcttpcna;                 /* Number of Cons Allocated              @DPA             */
         int tcttpsen;                 /* Number of Sends for TP                @DPA             */
         unsigned char tcttpdat[8];    /* Amount of Data Sent                   @DPA             */
         int tcttprec;                 /* Number of Recvs for TP                @DPA             */
         unsigned char tcttpdar[8];    /* Amount of Data Received               @DPA             */
         unsigned char tctsubnm[4];    /* Scheduler of Job                      @DPA             */
         void *tctomvsp;               /* Address of TCTOMVS Table              @LUA             */
         void *tctt30ph;               /* Address of T30AREA for Process Data   @LUA             */
         void *tctt30se;               /* Address of T30AREA for Step EXCP Data @LUA             */
         void *tctt30sp;               /* Address of T30AREA for Step Process   @LUA             */
         void *tctt30je;               /* Address of T30AREA for Job EXCP Data  @LUA             */
         void *tctt30jp;               /* Address of T30AREA for Job Process    @LUA             */
         unsigned char tctiss[8];      /* SMF Interval Start Time (STCK Format) @DVA             */
         int tct30cn;                  /* Last Number of Conversations          @01A             */
         int tct30cna;                 /* Last Number of Cons Allocated         @01A             */
         int tct30sen;                 /* Last Number of Sends for TP           @01A             */
         unsigned char tct30dat[8];    /* Last Amount of Data Sent              @01A             */
         int tct30rec;                 /* Last Number of Recvs for TP           @01A             */
         unsigned char tct30dar[8];    /* Last Amount of Data Received          @01A             */
         int tct30atr;                 /* Last Number of Transactions Processed @01A             */
         int tctuacl;                  /* Usage ACA Lockword                    @04A             */
         void *tctuaca;                /* Address of First ACA for job          @04A             */
         void *tctutcac;               /* Addr of 1st TCA on consolidated chain @09C             */
         void *tctutca;                /* Address of First TCA on chain         @04A             */
         void *tctufcac;               /* Addr of 1st FCA on consolidated chain @08C             */
         void *tctufca;                /* Address of First FCA on chain         @04A             */
         int tctrsmgt;                 /* Usage RESMGR Token                    @04A             */
         void *tctutimr;               /* Usage Timer Element                   @04A             */
         void *tctutprm;               /* Usage Timer ParmArea                  @04A             */
         void *tctt30uh;               /* Address of T30AREA Hold area for      @05A             */
         void *tctt30us;               /* Address of T30AREA Step Hold Area for @05A             */
         void *tctt30uj;               /* Address of T30AREA Job Hold Area for  @05A             */
         void *tctarmp;                /* Address of TCTARM table               @L1A             */
         void *tctt30ah;               /* Address of T30AREA for ARM Data       @L1A             */
         void *tctt30sa;               /* Address of T30AREA for Step ARM Data  @L1A             */
         void *tctt30ja;               /* Address of T30AREA for Job ARM Data   @L1A             */
         int tctasst;                  /* Additional SRB Service Time           @L3A             */
         int tctecpt;                  /* Enclave CPU Time                      @L3A             */
         int tctetim;                  /* Enclave Transaction Active Time       @L3A             */
         int tctecpu;                  /* Enclave CPU Service Units             @L3A             */
         int tctetc;                   /* Enclave Transaction Count             @P5C             */
         int tctasstc;                 /* Additional SRB Service Time (Cumulative)               */
         int tctecptc;                 /* Enclave CPU Time (Cumulative)                          */
         int tctdet;                   /* Dependent enclave CPU time            @D3A             */
         int tct30aic;                 /* Saved copy of RQSVAIC                 @D3A             */
         int tct30aid;                 /* Saved copy of RQSVAID                 @D3A             */
         int tct30aiw;                 /* Saved copy of RQSVAIW                 @D3A             */
         int tct30ais;                 /* Saved copy of RQSVAIS                 @D3A             */
         int tct30eic;                 /* Saved copy of RQSVEIC                 @D3A             */
         int tct30eid;                 /* Saved copy of RQSVEID                 @D3A             */
         int tct30eiw;                 /* Saved copy of RQSVEIW                 @D3A             */
         int tct30eis;                 /* Saved copy of RQSVEIS                 @D3A             */
         int tctt30sr;                 /* Address of STEP area for Remote       @LAA             */
         int tctt30jr;                 /* Address of JOB area for Remote        @LAA             */
         struct
         {
            int tct_time_on_ifa; /* Work unit on IFA                      @H5A             */
         } tct_time_on_zcbp;     /* Work unit on zCBP                     @LJA             */
         struct
         {
            int tct_time_ifa_on_cp; /* IFA-eligible work unit on CP          @H5A             */
         } tct_time_zcbp_on_cp;     /* zCBP-eligible work unit on CP         @LJA             */
         struct
         {
            int tct_enclave_time_on_ifa; /* Work unit on IFA                      @H5A             */
         } tct_enclave_time_on_zcbp;     /* Work unit on zCBP                   @LJA               */
         struct
         {
            int tct_enclave_time_ifa_on_cp; /* IFA-eligible work unit on CP       @H5A                */
         } tct_enclave_time_zcbp_on_cp;     /* zCBP-eligible work unit on CP    @LJA                  */
         struct
         {
            int tct_dep_enclave_time_on_ifa; /* Work unit on IFA                  @H5A                 */
         } tct_dep_enclave_time_on_zcbp;     /* Work unit on zCBP               @LJA                   */
         struct
         {
            int tct_dep_enclave_time_ifa_on_cp; /* IFA-eligible work unit on CP   @H5A                    */
         } tct_dep_enclave_time_zcbp_on_cp;     /* zCBP-eligible work unit on CP@LJA                      */
         int tcttmrfl2;                         /* More failure flags                    @H5A             */
         int tct_time_on_cp;                    /* Work unit on CP                       @H6A             */
         int tct_enclave_time_on_cp;            /* Work unit on CP                        @H6A            */
         int tct_dep_enclave_time_on_cp;        /* Work unit on CP                    @H6A                */
         int tct_cepi;                          /* SMF30CEPI                             @P7A             */
         struct
         {
            int tct_time_on_sup; /* Work unit on SUP                      @H6A             */
         } tct_time_on_ziip;     /* Work unit on zIIP                     @LJA             */
         struct
         {
            int tct_time_sup_on_cp; /* SUP-eligible work unit on CP          @H6A             */
         } tct_time_ziip_on_cp;     /* zIIP-eligible work unit on CP         @LJA             */
         struct
         {
            int tct_enclave_time_on_sup; /* Work unit on SUP                      @H6A             */
         } tct_enclave_time_on_ziip;     /* Work unit on zIIP                   @LJA               */
         struct
         {
            int tct_enclave_time_sup_on_cp; /* SUP-eligible work unit on CP       @H6A                */
         } tct_enclave_time_ziip_on_cp;     /* zIIP-eligible work unit on CP    @LJA                  */
         struct
         {
            int tct_enclave_time_sup_qual; /* SUP-qualified time                  @H6A               */
         } tct_enclave_time_ziip_qual;     /* zIIP-qualified time               @LJA                 */
         struct
         {
            int tct_depenc_time_on_sup; /* Work unit on SUP                       @H6A            */
         } tct_depenc_time_on_ziip;     /* Work unit on zIIP                    @LJA              */
         struct
         {
            int tct_depenc_time_sup_on_cp; /* SUP-eligible work unit on CP        @H6A               */
         } tct_depenc_time_ziip_on_cp;     /* zIIP-eligible work unit on CP     @LJA                 */
         struct
         {
            int tct_depenc_time_sup_qual; /* SUP-qualified time                   @H6A              */
         } tct_depenc_time_ziip_qual;     /* zIIP-qualified time                @LJA                */
         double tctsvtex;                 /* 64-bit Total Block Count              @0EA             */
         double tcttpexx;                 /* Last Value of 64-bit EXCP Count for TP@0EA             */
         int tct_crp;                     /* SMF30CRP                              @LWA             */
         int tctsmfxp;                    /* Pointer to SMFTCT extension section   @LIC             */
         int tctlucnt;                    /* Count of DD entries in TCTIOT lookup                   */
         int tct_missed_tctdctr;          /* Accumulated I/O block counts that were                 */
         int tctsv_missed_tctdctr;        /* Last value of TCT_Missed_TCTDCTR,                      */
         int tct_missed_tctconn;          /* Accumulated device connect time that was               */
         int tctsv_missed_tctconn;        /* Last value of TCT_Missed_TCTCONN,                      */
         unsigned char tctbndry[4];       /* Reserved for alignment of TCTEND      @LHC             */
         struct
         {
            int tctlwm;             /* -            MAX VIRTUAL STORAGE IN USER SUBPOOLS      */
            int tcthwm;             /* -            MAX VIRTUAL STORAGE IN SWA AND LSQA       */
         } tctcore;                 /* -           START OF TCT STORAGE TABLE POINTED TO      */
         short int tctminc;         /* -            THE MINIMUM DIFFERENCE (IN 2K BLOCKS)     */
         short int tctrsv00;        /* -            RESERVED.  REGION FIELD INCREASED TO      */
         void *tctrba;              /* -            FOR A V=V PROBLEM PROGRAM, LOWEST ADDRESS */
         int tctehwm;               /* -            MAX VIRTUAL STORAGE IN SWA AND LSQA       */
         int tctelwm;               /* -            MAX VIRTUAL STORAGE IN USER SUBPOOLS      */
         int tctrgnb;               /* PRIVATE AREA BELOW 16M IN BYTES      @PVC              */
         int tctergnb;              /* PRIVATE AREA ABOVE 16M IN BYTES      @PVC              */
         int tctrsz;                /* ORIGINAL REGION REQUEST IN 2K BLOCKS @PVM              */
         int tctrsv01;              /* -            RESERVED                             @LVC */
         double tctmem;             /* -            MEMLIMIT IN MB                       @LVA */
         unsigned char tctmems;     /* -          SOURCE OF MEMLIMIT                   @0DA   */
         unsigned char tctslm;      /* -          Actions taken by SMFLIMxx policy     @0IA   */
         unsigned char tctrsv02[2]; /* -          RESERVED                             @0IC   */
         struct
         {
            unsigned char _filler2;    /* -            SUBPOOL IN WHICH THE TCT I/O TABLE        */
            unsigned char tctszext[3]; /* SIZE IN BYTES OF TCT I/O TABLE                         */
         } tctplext;                   /* -           SUBPOOL/LENGTH OF TCT I/O TABLE            */
         int tctszlkp;                 /* -            NUMBER OF DEVICE ENTRIES IN THE TCT       */
         int tctdcbtd;                 /* -            OFFSET FROM THE TIOT ORIGIN TO THE TIOT   */
         int tctiotsd;                 /* -            OFFSET FROM THE TCT I/O TABLE ORIGIN TO   */
         int tctdcble;                 /* -            END OF TCT I/O LOOKUP TABLE (ZEROS)       */
         int tctucbp;                  /* -            ADDRESS OF THE UCB ASSOCIATED   @G860P27  */
         char tctsctr;                 /* -          NUMBER OF DEVICES ASSOCIATED WITH THIS      */
         unsigned char tctflgs;        /* -            FLAG BYTE                          MDC013 */
         short int tctblksz;           /* -            BLOCK SIZE FOR THIS DD NAME     @G742PJW  */
         int tctdctr;                  /* -            COUNTER FOR EXCP'S ISSUED AGAINST THIS    */
         int tctdctrs;                 /* -            SAVED EXCP COUNT FOR THIS ENTRY @G860P27  */
         int tctconn;                  /* -            DEVICE CONNECT TIME             @G860P27  */
         int tctconns;                 /* -            SAVED DEVICE CONNECT TIME       @G860P27  */
         unsigned char tctxblks[8];    /* BLOCKSIZE >32K FOR THIS DD NAME     @LDA               */
         unsigned char tctrsv10[4];    /* -          *** TCTOUTLM FIELD RESERVED IN OS/VS ***    */
         char tctexrld;                /* -          A BINARY NUMBER OF EXTENTS RELEASED BY      */
         int tcttkrld : 24;            /* -          A BINARY NUMBER OF TRACKS RELEASED BY THE   */
         unsigned char etctid[7];      /* -          ETCTIOT IDENTIFIER = 'ETCTIOT'       @D9A   */
         unsigned char etctver;        /* -          ETCTIOT VERSION NUMBER = X'01'       @D9A   */
         int etctfchn;                 /* -            NEXT ETCTIOT BLOCK ADDRESS           @D9A */
         int etctbchn;                 /* -            PREVIOUS ETCTIOT BLOCK ADDRESS       @D9A */
         int etctnext;                 /* -            NEXT TOKEN                           @D9A */
         int etctdsab;                 /* -            DSAB ADDRESS OF ENTRY                @D9A */
         int etctstio;                 /* -            TCTIOT DD LOOKUP ENTRY OFFSET        @D9A */
         struct
         {
            unsigned char tctoid[4]; /* Control Block ID  'TCTO'             @LUA              */
            struct
            {
               unsigned char tctosp;    /* - Subpool                            @LUA              */
               unsigned char tctoln[3]; /* - Length                             @LUA              */
            } tctospln;                 /* Control Block Subpool and Length     @LUA              */
         } tctomvsh;                    /* -         TCT OpenMVS Header Section           @03A    */
         struct
         {
            int tctopi;           /* -            Process ID                           @LUA */
            int tctopg;           /* -            Process Group ID                     @LUA */
            int tctoui;           /* -            Process User ID                      @LUA */
            int tctoug;           /* -            Process User Group ID                @LUA */
            int tctosi;           /* -            Process Session ID                   @LUA */
            int tctosc;           /* -            Number of syscals requested          @LUA */
            int tctost;           /* -            Total CPU Time accumulated by the    @LUA */
            int tctodr;           /* -            Number of directory I/O blocks read @D1C  */
            int tctofr;           /* -            Number of I/O blocks read for             */
            int tctofw;           /* -            Number of I/O blocks written for          */
            int tctopr;           /* -            Number of I/O blocks read for pipe        */
            int tctopw;           /* -            Number of I/O blocks written for          */
            int tctosr;           /* -            Number of I/O blocks read for             */
            int tctosw;           /* -            Number of I/O blocks written for          */
            int tctoll;           /* -            Number of path name Lookup calls to  @LUA */
            int tctolp;           /* -            Number of path name Lookup calls to  @LUA */
            int tctogl;           /* -            Number of path name Generation calls @LUA */
            int tctogp;           /* -            Number of path name Generation calls @LUA */
            int tctopp;           /* -            OpenMVS parent process ID number     @L2A */
            int tctokr;           /* -            Number of I/O blocks read for Remote      */
            int tctokw;           /* -            Number of I/O blocks written for          */
            int tctoms;           /* -            Number of message queues bytes sent  @L8A */
            int tctomr;           /* -            Number of message queues bytes received   */
            int tctosy;           /* -            Number of sync() function calls      @L9C */
         } tctomvsd;              /* -        TCT OpenMVS Data Section             @L9C     */
         unsigned char tctaid[4]; /* Control Block ID  'TCTA'             @L1A              */
         struct
         {
            unsigned char tctasp;    /* - Subpool                            @L1A              */
            unsigned char tctaln[3]; /* - Length                             @L1A              */
         } tctaspln;                 /* Control Block Subpool and Length     @L1A              */
         union {
            __extension__ unsigned char tctarmd[0][80]; /* -        TCT ARM Data                         @L1A     */
            struct
            {
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
         };
      };
   };
};

/* Values for field "tctsw" */
#define tctjsti 0x80  /* -         TQE JOB/STEP TIME INDICATOR.             */
#define tctiex 0x40   /* -         ERROR IN TCT I/O TABLE I/O COUNTS        */
#define tctisk30 0x20 /* -   TYPE 30 INTERVAL RECORD SKIPPED  @G743PJW      */
#define tctisk32 0x10 /* -   TYPE 32 INTERVAL RECORD SKIPPED  @G743PJW      */
#define tctiabd 0x08  /* -   PREVIOUS INTERVAL ABENDED        @G743PJW      */
#define tctstprn 0x04 /* -   STEP RAN INDICATOR               @ZMC1603      */
#define tctactrt 0x02 /* -   IEFACTRT IN CONTROL INDICATOR    @ZA90520      */
#define tctdcopn 0x01 /* -   DMPCHCK RTN IN CONTROL INDICATOR @ZA93106      */

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
#define tctomvs 0x35C  /* -            TCT OpenMVS Table                    @P2C */
#define tctarm 0x3C4   /* -            TCT ARM Table                        @L1A */

#pragma pack(reset)
