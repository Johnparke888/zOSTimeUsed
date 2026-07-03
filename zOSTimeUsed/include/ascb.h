#pragma once
/*
ASCB heading information
Common name: ADDRESS SPACE CONTROL BLOCK
Macro ID: IHAASCB
DSECT name: ASCB
Owning
component:
SUPERVISOR CONTROL (SC1C5)
Eye-catcher ID: ASCB
Offset: 0
Length: 4
Storage
attributes:
Subpool: 245
Key: 0
Residency: Below 16M
Size: 384 bytes
Created by: IEAMSWCB, IEAVEMRQ
Pointed to by: CVTASCBH and CVTASCBL fields of the CVT data area
PSAANEW field of the PSA data area
PSAAOLD field of the PSA data area (Master's
Function: Contain information and pointers needed for
Address Space Control. The ASCB is non-swappable.

z/OS Version 2 Release 4
MVS Data Areas Volume 1 (ABE - IAR)
Â© Copyright International Business Machines Corporation 1988, 2020.
*/
struct ascb
{
   union {
      unsigned long long int ascbegin; /* -                BEGINNING OF ASCB */
      struct
      {
         unsigned char ascbascb[4]; /* -   Acronym In Ebcdic -Ascb-               */
         void *__ptr32 ascbfwdp;            /* -   Address Of Next Ascb On Ascb Ready   */
         void *__ptr32 ascbbwdp;            /* -   Address Of Previous Ascb On Ascb     */
         void *__ptr32 ascbltcs;            /* -   Tcb And Preemptable-Class Srb   @07c */
         struct
         {
            struct
            {
               void *__ptr32 ascbsvrb_prezos12; /* - Svrb Pool Address.              @Llc        */
               int ascbsync_prezos12;   /* - Count Used To Synchronize Svrb Pool.       */
            } ascbsupc_prezos12;        /* - Supervisor Cell Field           @Llc        */
         } ascbr010;                    /* Reserved As Of Z/Os 1.12        @Lla                   */
         void *__ptr32 ascbiosp;                /* -                 Pointer To Ios Purge Interface       */
         struct
         {
            unsigned char ascbr01c[2]; /* Reserved, Must Be Zero          @L8a                   */
            short int ascbwqid;        /* Logical Cpu Id Of The Processor @L8a                   */
         } ascbwqlk;                   /* Web Queue Lock Word             @L8a                   */
         struct
         {
            void *__ptr32 ascbsawq_prezos11; /* - Address Of Address Space Srb Web           */
         } ascb_job_step_seqnum;     /* - Sequence Number Incremented At Job             */

         short int ascbasid;         /* -  Address Space Identifier For The     */
                                     /* -  Same As Ascbasid                @L8a  */
         unsigned char ascbdiag026;  /* -  Ibm Use Only                    @0gc */
         unsigned char ascbsrmflags; /* -  Srm Flags                             */
         unsigned char ascbll5;      /* -  Flags. Serialization - Local    @D2a */
         char ascbhlhi;              /* -  Indication Of Suspend Locks     @L4c   */
         struct
         {
            char ascbdphi;       /* - High Order Byte Of Halfword     @L4a   */
            char ascbdp;         /* - Dispatching Priority Range From        */
         } ascbdph;              /* - Halfword Dispatching Priority   @L4a  */
         int ascbtcbe;           /* - Count Of Ready Tcbs In The      @Lcc   */
         void *__ptr32 ascblda;          /* - Pointer To Local Data Area Part Of   */
         unsigned char ascbrsmf; /* - Rsm Address Space Flags              */
         unsigned char ascbflg3; /* - Flags Needing No Serialization  @Lda   */
         struct
         {
            short int ascbhasi_prezos11;  /* - Local Lock Owning Asid.         @Ljc       */
         } ascbr036;                      /* Reserved As Of Z/Os 1.11        @Lja                   */
         void *__ptr32 ascbcscb;                  /* - Address Of Cscb                      */
         void *__ptr32 ascbtsb;                   /* - Address Of Tsb                       */
         unsigned long long int ascbejst; /* - Elapsed Job Step Timing  Unsigned    */
         unsigned long long int ascbewst; /* - Time Of Day Whenever I-Stream Is     */
         int ascbjstl;                    /* - Cpu Time Limit For The Job Step      */
         int ascbecb;                     /* - Rct's Work Ecb                       */
         int ascbubet;                    /* - Time Stamp When User Becomes Ready   */
         void *__ptr32 ascbtlch;                  /* - Chain Field For Time Limit Exceeded  */
         void *__ptr32 ascbdump;                  /* - Svc Dump Task Tcb Address            */
         struct
         {
            short int ascbaffn;     /* -  Cpu Affinity Indicator               */
            unsigned char ascbrctf; /* -  Flags For Rct Serialized By Compare  */
            unsigned char ascbflg1; /* -  Flag Field                           */
         } ascbfw1;                 /* -  Full-Word Label To Be Used For        */
         int ascbtmch;              /* -  Termination Queue Chain              */
         void *__ptr32 ascbasxb;            /* -  Pointer To Address Space Extension   */
         struct
         {
            short int ascbswct;     /* - Number Of Times Memory Enters Short  */
            unsigned char ascbdsp1; /* - Nondispatchability Flags.            */
            unsigned char ascbflg2; /* - Flag Byte.                           */
         } ascbfw2;                 /* - Fullword Label To Address Bits In     */
         struct
         {
            short int _filler1; /* -  First Halfword Of Ascbscnt Must Be   */
            short int ascbsrbs; /* -  Count Of Srb's Suspended In This     */
         } ascbscnt;            /* - Fullword Label For Compare And Swap   */
         void *__ptr32 ascbllwq;        /* -  Address Space Local Lock        @04c */
         void *__ptr32 ascbrctp;        /* -  Pointer To Region Control Task (Rct) */
         struct
         {
            int ascblock;   /* -  Local Lock.  This Offset Fixed By    */
            void *__ptr32 ascblswq; /* -  Address Space Local Lock Web    @L8c */
         } ascblkgp;        /* - Lock Group  (Mdc306)        @Z40fp9a  */
         int ascbqecb;      /* -  Quiesce Ecb                          */
         int ascbmecb;      /* -  Memory Create/Delete Ecb             */
         void *__ptr32 ascboucb;    /* -  System Resources Manager (Srm) User  */
         void *__ptr32 ascbouxb;    /* -  System Resources Manager (Srm) User  */
         struct
         {
            short int ascbfmct;     /* -   Reserved. Allocated Page Frame  @L6c */
            unsigned char ascblevl; /* -   Level Number Of Ascb            @D3a */
            unsigned char ascbfl2a; /* -   Flag Byte.                      @Daa */
         } ascbfw2a;                /* -  Fullword Label To Address       @Daa  */
         struct
         {
            int ascbejst_disps;    /* -  Count Of Task Dispatches.               */
         } ascbhreq_prezos11;      /* -  Local Lock Requestor Address    @0cc        */
         void *__ptr32 ascbiqea;           /* -  Pointer To Iqe For Atcam             */
         void *__ptr32 ascbrtmc;           /* -  Anchor For Sqa Sdwa Queue            */
         unsigned char ascbmcc[4]; /* -  Used To Hold A Memory Termination      */
         void *__ptr32 ascbjbni;           /* -  Pointer To Jobname Field For         */
         void *__ptr32 ascbjbns;           /* -  Pointer To Jobname Field For         */
         struct
         {
            unsigned char ascbsrq1;       /* - First Byte Of Ascbsrq                */
            unsigned char ascbsrq2;       /* - Second Byte Of Ascbsrq               */
            unsigned char ascbsrq3;       /* - Third Byte Of Ascbsrq                */
            unsigned char ascbsrq4;       /* - Fourth Byte Of Ascbsrq               */
         } ascbsrq;                       /* - Dispatcher Serialization Required     */
         void *__ptr32 ascbvgtt;                  /* - Address Of Vsam Global Termination   */
         void *__ptr32 ascbpctt;                  /* - Address Of Private Catalog           */
         short int ascbssrb;              /* - Count Of Status Stop Srb's           */
         char ascbsmct;                   /* - Number Of Outstanding Step Must        */
         unsigned char ascbsrbm;          /* - Model Psw Byte 0 Used By Srb         */
         int ascbswtl;                    /* - Step Wait Time Limit          Mdc029 */
         unsigned long long int ascbsrbt; /* - Accumulated Srb Time          Mdc030 */
         void *__ptr32 ascbltcb;                  /* - Tcb And Preemptable-Class Srb   @07c */
         int ascbltcn;                    /* - Count Of Tcb And Preemptable-   @07a */
         int ascbtcbs;                    /* - Number Of Ready Tcb's.          @L8a */
         int ascblsqt;                    /* - Number Of Tcbs On A Local Lock  @L8a */
         void *__ptr32 ascbwprb;                  /* - Address Of Wait Post Request Block   */
         struct
         {
            char ascbndp;  /* - New Dispatching Priority               */
            char ascbtndp; /* - New Time Slice Dispatching Priority    */
            char ascbntsg; /* - New Time Slice Group                   */
            char ascbiodp; /* - I/O Priority (Mdc374)       @G50ip9a   */
         } ascbsrdp;       /* - System Resource Manager (Srm)         */
         void *__ptr32 ascbloci;   /* - Lock Image, Address Of Ascb          */
         void *__ptr32 ascbcmlw;   /* - Address Of The Web Representing @L8c */
         struct
         {
            int ascbsrbt_disps; /* - Count Of Srb Dispatches.                */
         } ascbcmlc_prezos12;   /* - Count Of Cml Locks Held By      @0cc        */
         struct
         {
            unsigned char ascbsso1[3]; /* - Space Switch Event Owner    @G381p9a   */
            unsigned char ascbsso4;    /* - Space Switch Event Owner    @G381p9a */
         } ascbssom;                   /* - Space Switch Event Owner    @Za58694  */
         void *__ptr32 ascbaste;               /* - Virtual Address Of Address  @G381p9a */
         void *__ptr32 ascbltov;               /* - Virtual Address Of The      @G381p9a */
         void *__ptr32 ascbatov;               /* - Virtual Address Of          @G381p9a */
         short int ascbetc;            /* - Number Of Entry Tables      @G381p9a */
         short int ascbetcn;           /* - Number Of Connections To    @G381p9a */
         short int ascblxr;            /* - Number Of Linkage Indexes   @G381p9a */
         short int ascbaxr;            /* - Number Of Authorization     @G381p9a */
         void *__ptr32 ascbstkh;               /* - Address Of Local Stack Pool @G381p9a */
         struct
         {
            unsigned char ascbcsw0; /* Byte 0                          @0FA                   */
            unsigned char ascbcsw1; /* Byte 1                          @0FA                   */
            unsigned char ascbcsw2; /* Byte 2, Ser: CS                 @0FA                   */
            unsigned char ascbcsw3; /* Byte 3, Ser: CS                 @0FA                   */
         } ascbcswd;                /* CS-serialized word              @0FA                   */
         unsigned char ascbr114[4]; /* Reserved.                       @0FC                   */
         void *__ptr32 ascbjafbaddr;        /* -                Address of the JAFB             @LQA  */
         void *__ptr32 ascbxtcb;            /* -                 ADDRESS OF THE JOB STEP @G381P9A     */
         struct
         {
            unsigned char ascbcs1;        /* - First Byte Of Compare And            */
            unsigned char ascbcs2;        /* - Second Byte Of Compare And Swap @P5a */
            unsigned char ascbr122[2];    /* - Reserved.                       @P5c   */
         } ascbfw3;                       /* - Fullword Label To Address Bits In     */
         void *__ptr32 ascbgxl;                   /* - Address Of Globally Loaded Module    */
         unsigned long long int ascbeatt; /* - Expended And Accounted Task Time.    */
         unsigned long long int ascbints; /* - Job Selection Time Stamp.            */
         struct
         {
            unsigned char ascbll1; /* - First Byte Of Flags.        @G381p9a */
            unsigned char ascbll2; /* - Second Byte Of Flags.       @G381p9a */
            unsigned char ascbll3; /* - Third Byte Of Flags.        @G381p9a */
            unsigned char ascbll4; /* - Fourth Byte Of Flags.       @G381p9a */
         } ascbfw4;                /* - Fullword Label To Address   @G381p9a  */
         void *__ptr32 ascbrcms;           /* Address Of The Requested    @G381pxu                   */
         int ascbiosc;             /* - I/O Service Measure.        @G381pxu */
         short int ascbpkml;       /* - Pkm Of Last Task Dispatched             */
         short int ascbxcnt;       /* - Excp Count Field.               @L1a */
         void *__ptr32 ascbnsqa;           /* - Address Of The Sqa Resident          */
         void *__ptr32 ascbasm;            /* - Address Of The Asm Header.      @L2a */
         void *__ptr32 ascbassb;           /* - Pointer To Address Space        @D6c */
         void *__ptr32 ascbtcme;           /* - Pointer To Tcxtb.               @D1a */
         struct
         {
            unsigned char _filler2;       /* - Byte 0 Of Ascbgqir              @O3a   */
            unsigned char _filler3[2];    /* - Byte 1 And 2 Of Ascbgqir        @O3a   */
            unsigned char ascbgqi3;       /* - Byte 3 Of Ascbgqir              @O3a   */
         } ascbgqir;                      /* -  Isgqscan Information            @O3a  */
         int ascblsqe;                    /* -   Number Of Enclave Tcbs That Are On   */
         unsigned long long int ascbiosx; /* -   I/O Service Measure Extended.   @0ac */
         unsigned char ascbr168[2];       /* - Eserved.                       @0ac    */
         unsigned char ascbsvcn[2];       /* - Vc Number For Type-1 Svc               */
         void *__ptr32 ascbrsme;                  /* - Pointer To Rsm Address Space    @D5a   */
         struct
         {
            unsigned char ascbavm1; /* -  First Byte Of Ascbavm.          @01a */
            unsigned char ascbavm2; /* -  Second Byte Of Ascbavm.         @01a */
            short int ascbagen;     /* -  Avm Asid Reuse Generation       @01a */
         } ascbavm;                 /* -  Availability Manager Address    @01c  */
         int ascbarc;               /* -  Reason Code On Memterm.              */
         struct
         {
            void *__ptr32 ascbrsma; /* -  Address Of Rsm's Control Block         */
         } ascbrsm;         /* -  Address Of Rsm's Control Block        */
         int ascbdcti;      /* -  Accumulated Channel Connect Time        */
                            // __Extension__          Ascbend[0]; /* -                END OF ASCB                     @L7C  */
      };
   };
};

/* Values for field "ascbsawq_prezos11" */
#define ascburrq_prezos11 0x80 /* -      Sysevent User Ready Required    @LJC        */

/* Values for field "ascbsrmflags" */
#define ascbvcmoverride 0x80         /* -      This bit indicates that this                */
#define ascbbrokenup 0x40            /* -      This bit indicates that this                */
#define ascbvcmgivepreemption 0x20   /* -  This bit indicates that this                    */
#define ascbvcmgivesigpany 0x10      /* -  This bit indicates that this                    */
#define ascbinelighonorpriority 0x08 /* When on, specialty engine eligible                 */
#define ascbsrmflagsdiag 0x06        /* Diagnostic data for IBM use only@LSA               */

/* Values for field "ascbll5" */
#define ascbs3s 0x20 /* -             Stage Ii Exit Efector Has       @D2m */

/* Values for field "ascbrsmf" */
#define ascb2lpu 0x80 /* -             Second Level Preferred User.  This   */
#define ascb1lpu 0x40 /* -             First Level Preferred User           */
#define ascbn2lp 0x20 /* -             Srm In Sysevent Transwap Should Not  */
#define ascbveqr 0x10 /* -             V=R Address Space  (Mdc372) @Za17355 */

/* Values for field "ascbflg3" */
#define ascbcnip 0x80 /* -             Address Space Created During Nip     */
#define ascbreus 0x40 /* -             This Is A Reusable Asid. It May Be   */
#define ascbm881 0x20 /* This address Space Went Through                    */

/* Values for field "ascbrctf" */
#define ascbtmno 0x80 /* -             Memory Is Being Quiesced, Is         */
#define ascbfrs 0x40  /* -             Restore Request                      */
#define ascbfqu 0x20  /* -             Quiesce Request                      */
#define ascbjste 0x10 /* -             Job Step Time Exceeded. Not Used By  */
#define ascbwait 0x08 /* -             Long Wait Indicator                  */
#define ascbout 0x04  /* -             Address Space Considered Swapped Out */
#define ascbtmlw 0x02 /* -             Memory Is In A Long Wait             */
#define ascbtoff 0x01 /* -             Memory Should Not Be Checked For Job */

/* Values for field "ascbflg1" */
#define ascblsas 0x80 /* -             Address Space Is Logically Swapped   */
#define ascbdstk 0x40 /* -             Srm Requires A Time Stamp To    @P6c */
#define ascbdstz 0x40 /* -             Bit Constant For Bit Position  @P7a  */
#define ascbterm 0x10 /* -             Address Space Terminating Normally   */
#define ascbabnt 0x08 /* -             Address Space Terminating Abnormally */
#define ascbmemp 0x04 /* -             Memory Termination Purgedq Flag @Lba */

/* Values for field "ascbdsp1" */
#define ascbssnd 0x80 /* -             System Set Nondispatchable And This  */
#define ascbfail 0x40 /* -             A Failure Has Occurred Within The    */
#define ascbsnqs 0x20 /* -             Status Stop Non-Quiescable Level     */
#define ascbssss 0x10 /* -             Status Stop Srb Summary              */
#define ascbstnd 0x08 /* -             Tcb's Nondispatchable                */
#define ascbuwnd 0x04 /* -             Status Set Unlocked Workunits   @Laa */
#define ascbnoq 0x02  /* -             Ascb Not On Swapped In Queue    @L4a */

/* Values for field "ascbflg2" */
#define ascbxmpt 0x80 /* -             Ascb Exempt From System              */
#define ascbpxmt 0x40 /* -             Ascb Permanently Exempt From System  */
#define ascbcext 0x20 /* -             Cancel Timer Extension Because Eot   */
#define ascbs2s 0x10  /* -             For Lock Manager, Entry Made To      */
#define ascbncml 0x08 /* -             Ascb Not Eligible For Cml Lock       */
#define ascbnomt 0x04 /* -             Address Space Must Not Be Memtermed  */
#define ascbnomd 0x02 /* -             If On,Address Space Cannot Be        */

/* Values for field "ascblswq" */
#define ascbs3nl 0x80 /* -             The Local Lock Is Needed By The @L8a */
#define ascbltcl 0x01 /* -            The Local Lock Is Needed By Some      */

/* Values for field "ascblevl" */
#define ascbvs00 0x00 /* -             Hbb2102 (Not In Base)       @Za68643 */
#define ascbvs01 0x01 /* -             Jbb2110                         @D3a */
#define ascbvs02 0x02 /* -             Jbb2133                         @H1a */
#define ascbvs03 0x03 /* -             Hbb4410                         @L7a */
#define ascbvers 0x03 /* -             Level Of This Mapping           @L7c */

/* Values for field "ascbfl2a" */
#define ascbnopr 0x80 /* -             No Preemption Flag              @Daa */

/* Values for field "ascbsrq1" */
#define ascbdsg4 0x80 /* -             Signal Waiting Processors When       */
#define ascbdflt 0x40 /* -             Default Local Intersect              */

/* Values for field "ascbsrq2" */
#define ascbdsg3 0x80 /* -             Signal Waiting Processors When       */
#define ascbsrm1 0x02 /* -             System Resource Manager (Srm)        */
#define ascbqver 0x01 /* -             Queue Verification Intersecting      */

/* Values for field "ascbsrq3" */
#define ascbdsg2 0x80 /* -             Signal Waiting Processors When       */
#define ascbrcti 0x40 /* -             Region Control Task (Rct)            */
#define ascbtcbv 0x20 /* -             Tcb Verification Intersecting        */
#define ascbacha 0x10 /* -             Ascb Chap Intersecting               */
#define ascbmter 0x04 /* -             Memory Termination Intersecting      */
#define ascbmini 0x02 /* -             Memory Initialization Intersecting   */
#define ascbcbve 0x01 /* -             Control Block Verification           */

/* Values for field "ascbsrq4" */
#define ascbdsg1 0x80 /* -             Signal Waiting Processors When       */
#define ascbdeta 0x40 /* -             Detach Intersecting                  */
#define ascbatta 0x20 /* -             Attach Intersecting                  */
#define ascbrtm2 0x10 /* -             Rtm2 Intersecting  (Mdc351) @G50dp9a */
#define ascbrtm1 0x08 /* -             Rtm1 Intersecting  (Mdc352) @G50dp9a */
#define ascbchap 0x04 /* -             Chap Intersecting  (Mdc353) @G50dp9a */
#define ascbstat 0x02 /* -             Status Intersecting                  */
#define ascbpurd 0x01 /* -             Purgedq Intersecting                 */

/* Values for field "ascbsrbm" */
#define ascbper 0x40 /* -             Per Bit In Ascbsrbm - Also Used To   */

/* Values for field "ascbsso4" */
#define ascbsssp 0x02 /* -             Slip/Per Requested          @G381p9a */
#define ascbssjs 0x01 /* -             Job Step Termination        @G381p9a */

/* Values for field "ascbcsw2" */
#define ascbzkf 0x80 /* @0FA                                               */

/* Values for field "ascbcsw3" */
#define ascbzu 0x40 /* @0FA                                               */
#define ascbzf 0x20 /* @0FA                                               */
#define ascbzn 0x10 /* @0FA                                               */
#define ascbzm 0x04 /* @0FA                                               */
#define ascbzs 0x02 /* @0FA                                               */
#define ascbzc 0x01 /* Checked.                        @0FA               */

/* Values for field "ascbcs1" */
#define ascbxmet 0x80 /* -             If One, The Address Space Is    @L3c */
#define ascbxmec 0x40 /* -             Cross Memory Entry Tables   @G381p9a */
#define ascbxmpa 0x20 /* -             If One, The Address Space Is    @L3a */
#define ascbxmlk 0x10 /* -             If One, The Address Space Is    @L3a */
#define ascbpers 0x08 /* -             Communication Bit For       @G381p9a */
#define ascbdter 0x04 /* -             A Dat Error Has Occurred    @G381p9a */
#define ascbpero 0x02 /* -             Per Processing Needs To Be      @L5a */
#define ascbswop 0x01 /* -             Address Space Is Swapped Out    @L5a */

/* Values for field "ascbcs2" */
#define ascbsas 0x80  /* -             Indicates That Storage          @P5m */
#define ascbsmgr 0x40 /* -             This Space Is Or Has Been Associated */
#define ascbdtin 0x20 /* -             This Space Is Or Has Been Associated */
#define ascbxmnr 0x10 /* -             The Address Space Is                 */
#define ascbsdbf 0x08 /* -             A Work Unit In This Address Space    */
#define ascbnoft 0x04 /* -  Set this To Exempt All Tasks In This Address    */
#define ascbpo1m 0x02 /* -             Set This To Indicate That            */
#define ascbp1m0 0x01 /* -             Set This To Indicate That            */

/* Values for field "ascbll1" */
#define ascbsspc 0x80 /* -             Status Stop Tasks Pending   @G381p9a */

/* Values for field "ascbll4" */
#define ascbnrll 0x80 /* -             No Release Of Local Lock Ok.    @Lra */
#define ascbtyp1 0x02 /* -             Type 1 Svc Has Control.  This Offset */

/* Values for field "_filler2" */
#define ascbgqab 0x80 /* -             Isgqscan Information            @O3a */

/* Values for field "ascbgqi3" */
#define ascbgqds 0x01 /* -             Isgqscan Information            @O3a */
