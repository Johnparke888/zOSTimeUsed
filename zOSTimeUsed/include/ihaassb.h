#pragma pack(packed)

struct assb {
  union {
    double         assbegin; /* BEGINNING OF ASSB. */
    struct {
      unsigned char  assbassb[4];                      /* ACRONYM IN EBCDIC - ASSB.             */
      int            assbsmfl;                         /* Lock word for BMFLSD lock for TCTIOT  */
      void          *assbubav;                         /* @0TC                                  */
      void          *assbubad;                         /* @0TC                                  */
      void          *assbupav;                         /* @0TC                                  */
      unsigned char  assbr014[4];                      /* @0TC                                  */
      unsigned char  assbxmf1;                         /* CROSS MEMORY FLAGS 1            @L4A  */
      unsigned char  assbxmf2;                         /* CROSS MEMORY FLAGS 2            @L4A  */
      short int      assbxmcc;                         /* CROSS MEMORY CONNECTIONS COUNT. @L1A  */
      void          *assbcbtp;                         /* POINTER TO IHAACBT              @LEC  */
      int            assbvsc;                          /* VIO SLOT ALLOCATED COUNT.       @D3A  */
      int            assbnvsc;                         /* NON-VIO SLOT ALLOCATED COUNT.   @D3A  */
      int            assbasrr;                         /* ADDRESS SPACE RE-READS TO BE    @D4C  */
      void          *assbdexp;                         /* POINTER TO IHADEXP              @LDC  */
      struct {
        int            assbstw1; /* FIRST WORD OF ASSBSTKN.         @L2C  */
        int            assbisqn; /* Initial address space sequence  @L2C  */
        } assbstkn;              /* STOKEN.                         @L2C  */
      void          *assbbpsa;                         /* IBMPM ANCHOR BLOCK.             @02C  */
      int            assbcsct;                         /* CACHING FACILITY STOP COUNT     @LGA  */
      void          *assbbalv;                         /* VIRTUAL ADDRESS OF THE BASIC    @L2C  */
      void          *assbbald;                         /* BASIC ACCESS LIST DESIGNATOR.   @L2C  */
      void          *assbxmse;                         /* ADDRESS OF XMSE FOR THIS        @L2A  */
      int            assbtsqn;                         /* NEXT TTOKEN SEQUENCE NUMBER.    @L3A  */
      int            assbvcnt;                         /* COUNT OF CURRENT TASKS WITH     @D5A  */
      void          *assbpalv;                         /* PASN ACCESS LIST VIRTUAL        @D6C  */
      void          *assbasei;                         /* ADDRESS OF ADDRESS SPACE        @D6C  */
      void          *assbrma;                          /* ADDRESS OF ADDRESS SPACE        @D6C  */
      double         assbhst;                          /* CPU time for Hiperspace               */
      double         assbiipt;                         /* CPU time for I/O interrupt            */
      int            assbanec;                         /* ALESERV ADD WITH NO EAX COUNT.  @L6A  */
      void          *assbsdov;                         /* ADDRESS OF SHARED DATA OBJECT   @LDC  */
      int            assbmcso;                         /* NUMBER OF CONSOLE IDS ACTIVATED @LAA  */
      void          *assbdfas;                         /* ADDRESS OF DFP=SMSX STRUCTURE   @L7A  */
      struct {
        unsigned char  assbflg0; /* ASSB FLAG BYTE 0.               @D7C  */
        unsigned char  assbflg1; /* ASSB FLAG BYTE 1                @LIC  */
        unsigned char  assbflg2; /* ASSB FLAG BYTE 2.               @D7C  */
        unsigned char  assbflg3; /* ASSB FLAG BYTE 3                @D7C  */
        } assbflgs;              /* ASSB FLAGS.                     @D7C  */
      void          *assbascb;                         /* ADDRESS OF ASCB.                @L9C  */
      void          *assbasrf;                         /* CREATED ASSB FORWARD POINTER.   @L9A  */
      void          *assbasrb;                         /* CREATED ASSB BACKWARD POINTER.  @L9A  */
      void          *assbssd;                          /* ADDRESS OF THE SUSPENDED SRB    @D8A  */
      void          *assbmqma;                         /* CONTROL BLOCK ANCHOR FOR        @06C  */
      double         assblasb;                         /* TOKEN INDICATING IF MVS/APPC    @LBC  */
      void          *assbsch;                          /* POINTER TO APPC SCHEDULER       @LBA  */
      int            assbfsc;                          /* COUNT ACCUMULATED BY IEAMFCNT   @01A  */
      void          *assbjsab;                         /* ADDRESS OF JOB SCHEDULER        @D9A  */
      void          *assbrctw;                         /* ADDRESS OF RCT's WEB.           @LSA  */
      struct {
        unsigned char  assbldxh[4]; /* High half                       @0PA  */
        void          *assbldxl;    /* Low half of address             @0PA  */
        } assbldax;                 /* Address of LDAX for this space  @0PC  */
      void          *assbtlmi;                         /* ADDRESS OF TAILORED LOCK        @LOA  */
      void          *assbsdas;                         /* POINTER TO WORKING STORAGE      @DBA  */
      int            assbtpin;                         /* THE COUNT OF UCB PIN REQUESTS   @LFA  */
      int            assbspin;                         /* THE COUNT OF UCB PIN REQUESTS   @LFA  */
      int            assbect1;                         /* THE COUNT OF ALLOCATION         @H2A  */
      int            assbect2;                         /* THE COUNT OF ALLOCATION         @H2A  */
      int            assbmt_;                          /* MEMTERM DISABLE COUNT.  WHEN    @DAA  */
      unsigned char  assbdfp[4];                       /* RESERVED FOR USE BY DFP.        @03A  */
      short int      assbsasi;                         /* SASI info                       @NUC  */
      short int      assbsnew;                         /* Count of SASN=NEW connections         */
      void          *assbnttp;                         /* ADDRESS OF ADDRESS SPACE LEVEL  @LIA  */
      struct {
        unsigned char  assboepc; /* POST CODE: '81'X=>BPX1EXC       @LMA  */
        struct {
          unsigned char  _filler1[2]; /* Unused.                         @LMA  */
          unsigned char  assboees;    /* Exit Status passed on BPX1EXI.  @LMA  */
          } assboecd;                 /* OpenMVS completion codes.       @LMA  */
        } assboecb;              /* ECB WHICH IS WAITED ON BY THE   @LMC  */
      void          *assboasb;                         /* OpenMVS ADDRESS SPACE BLOCK.    @LLA  */
      void          *assbxsba;                         /* XSB POOL QUEUE.                 @LKA  */
      void          *assbdlcb;                         /* Contains the address of the Dynamic   */
      void          *assbvab;                          /* ADDRESS OF VSM ADDRESS SPACE    @LNC  */
      void          *assblmab;                         /* LATCH MANAGER ADDRESS SPACE     @LNC  */
      int            assbioct;                         /* DIV/IO count                    @0HC  */
      void          *assbctt;                          /* CTT field                       @H3A  */
      int            assbxrct;                         /* XES REQUEST COUNT               @LQA  */
      struct {
        int            assb_nonenct_psrb_cp_disps; /* Count of non-enclave preemptable SRB  */
        } assbetsc_prezos11;                       /* Enclave TCB Summary Count       @0PC  */
      void          *assbtasb;                         /* TCPIP ASSB Extension            @07A  */
      int            assbtpma;                         /* OWNER:  IOS.                    @DCA  */
      int            assbrosu;                         /* OWNER:  IOS.                    @DCA  */
      int            assbtpmt;                         /* OWNER:  IOS.                    @DCA  */
      unsigned char  assbssdt[4];                      /* SSD Trailer                     @LSC  */
      void          *assbtawq;                         /* ADDRESS OF TASK WEB QUEUE.      @LSA  */
      void          *assbwcml;                         /* ADDRESS OF CML PROMOTION WEB.   @LSA  */
      void          *assbws3s;                         /* ADDRESS OF ASYNCHRONOUS EXIT    @LSA  */
      void          *assbwsss;                         /* ADDRESS OF SUSPENDED STATUS     @LSA  */
      void          *assbcapq;                         /* ADDRESS OF FIRST WEB ON THE     @LSC  */
      void          *assbptar;                         /* Pointer used by RTM processing  @09C  */
      int            assbwtct;                         /* When this counter is non-zero,        */
      int            assbsbct;                         /* XES-owned count of requests     @05A  */
      void          *assbarbp;                         /* ARM (Automatic Restart Manager) @LVA  */
      void          *assbrctr;                         /* ADDRESS OF RCT's RB                   */
      void          *assbscah;                         /* Address of the SCA (SPIE/ESPIE  @PAA  */
      unsigned char  assbttfl;                         /* Transaction Trace flags.        @MCA  */
      unsigned char  assbwmf1;                         /* WLM flags                       @M8A  */
      short int      assbpswc;                         /* Preemptable-class SRB short     @P5A  */
      void          *assbixga;                         /* Pointer to SLC address space    @LXC  */
      double         assbjbni;                         /* Jobname for the Initiated       @P1A  */
      double         assbjbns;                         /* Jobname for the START/MOUNT/    @P1A  */
      double         assbasst;                         /* Additional SRB Service Time.    @LYA  */
      double         assbphtm;                         /* Preemptable-class Time. The     @0PC  */
      void          *assbcrwq;                         /* Client Related WEB Queue.       @LYA  */
      void          *assbscwq;                         /* Suspended Client related WEB    @LYA  */
      int            assblcnt;                         /* Number of latched operations    @LZA  */
      int            assbacnt;                         /* Number of asynchronous requests @M1C  */
      int            assblcpd;                         /* CPOOLID of the cpool created    @M1A  */
      struct {
        short int      assbslpc; /* Slip PER serialization count    @NxA  */
        short int      assbslnc; /* Slip Non-PER serialization count      */
        } assbslsc;              /* Slip serialization counts.            */
      void          *assbpvtc;                         /* Queue of privately managed      @M4A  */
      struct {
        unsigned char  assbctxf;    /* Context Services flags          @MAM  */
        unsigned char  assbctx2[3]; /* Reserved context services.      @MAA  */
        } assbctx;                  /* Context Services Word           @MAA  */
      unsigned char  assbhale[16];                     /* Copy of Home ALE                @P7A  */
      struct {
        int            assb_time_on_zaap_disps; /* Count of task dispatches for zAAP     */
        } assb_time_on_zcbp_disps;              /* Count of task dispatches for zCBP     */
      int            assbsrsn;                         /* Suspend/Resume sequence number        */
      void          *assbwlms;                         /* Address of WLM managed server   @M8A  */
      void          *assbbcba;                         /* Address of SOMObjects data structure  */
      unsigned char  assbcsm[4];                       /* CSM user bitmap                 @P9A  */
      int            assbpect;                         /* Number of Pause elements allocated    */
      void          *assbrrsa;                         /* RRS data area pointer           @0EA  */
      struct {
        unsigned char  assbofl0; /* ASSB USS flag byte 0            @DEA  */
        unsigned char  assbofl1; /* ASSB USS flag byte 1            @DEA  */
        } assboflg;              /* ASSB USS flags                  @DEA  */
      unsigned char  assbscaf[2];                      /* CPU affinity indicator          @MDA  */
      int            assbctxc;                         /* Number of private contexts owned by   */
      int            assbrmct;                         /* Number of PKM 8 to 15 resource        */
      void          *assblrba;                         /* License manager resource block  @MFA  */
      void          *assbslfa;                         /* Shadow LFT address              @MIA  */
      unsigned char  assbr1d0;                         /* Reserved                        @0NC  */
      unsigned char  assbfabricpriority;               /* Fabric I/O Priority. Will be zero if  */
      unsigned char  assbioms[2];                      /* I/O Management Support Data.          */
      short int      assbpromotioncount;               /* Number of WEBs to promote.            */
      char           assbtiop;                         /* Tape I/O Priority               @MPA  */
      char           assbcsdp;                         /* Channel Subsystem I/O Priority. @MEA  */
      struct {
        struct {
          struct {
            double         assb_time_ifa_on_cp; /* @H4C                                  */
            } assb_time_zcbp_on_cp;             /* @NWA                                  */
          struct {
            struct {
              double         assb_time_on_ifa; /* @H4C                                  */
              } assb_time_on_zaap;             /* zAAP time. Enclave time not     @0PA  */
            } assb_time_on_zcbp; /* zCBP time. Enclave time not     @NWA  */
          } assb_ifa_time_area; /* @H3A                                  */
        } assb_zcbp_time_area; /* @NWA                                  */
      struct {
        double         assb_time_on_cp; /* Synonym for ASSB_TASK_TIME_ON_CP      */
        } assb_task_time_on_cp;         /* Time on CP in task mode for this      */
      unsigned char  assbmtci[5];                      /* Memterm component ID. Set only  @MJA  */
      char           assbflg4;                         /* Flags                           @MLA  */
      char           assbqiop;                         /* Queued Director I/O Priority          */
      unsigned char  assbcryp;                         /* Crypto flags. Serialization:    @MTA  */
      double         assbphtm_base;                    /* Value in ASSBPHTM at the end of @PCA  */
      void          *assbearlymemtermrm;               /* Address of Early Memterm Resource     */
      int            assb_laa_cpid;                    /* Anchor for LAA CPOOL            @MOA  */
      struct {
        struct {
          double         assb_ifa_phtm; /* @0PA                                  */
          } assb_zaap_phtm;             /* zAAP-only equivalent of ASSBPHTM @0PC */
        } assb_zcbp_phtm; /* zCBP-only equivalent of ASSBPHTM @NWA */
      struct {
        int            assb_time_on_ziip_disps; /* Count of task dispatches for zIIP     */
        int            assb_ziip_enct_disps;    /* Count of enclave dispatches for zIIP  */
        } assb_enct_prezos11;                   /* Enclave time in an address space@0PC  */
      struct {
        struct {
          int            assb_nonenct_psrb_zaap_disps; /* Count of non-enclave preemptable      */
          } assb_nonenct_psrb_zcbp_disps;              /* Count of non-enclave preemptable      */
        int            assb_nonenct_psrb_ziip_disps; /* Count of non-enclave preemptable      */
        } assb_ifa_enct_prezos11;                    /* Enclave IFA time in an address  @0PC  */
      double         assb_base_phtm;                   /* Base value, set by WLM          @MQA  */
      struct {
        double         assb_ifa_base_phtm; /* Base value, set by WLM          @MQA  */
        } assb_zcbp_base_phtm;             /* Base value, set by WLM          @NWA  */
      double         assb_base_enct;                   /* Base value, set by WLM          @MQA  */
      struct {
        double         assb_ifa_base_enct; /* Base value, set by WLM          @MQA  */
        } assb_zcbp_base_enct;             /* Base value, set by WLM          @NWA  */
      void          *assb_cp_affinity_node;            /* WUQ for CP affinity             @MQA  */
      struct {
        void          *assb_ifa_affinity_node; /* WUQ for IFA affinity            @MQA  */
        } assb_zcbp_affinity_node;             /* WUQ for zCBP affinity           @NWA  */
      struct {
        void          *assb_sup_affinity_node;
        } assb_ziip_affinity_node;             /* WUQ for zIIP affinity           @H4A  */
      int            assbsrbcpoolpmecount;             /* Count of active SRB CPOOL PMEs        */
      struct {
        double         assb_time_on_sup; /* @H4A                                  */
        } assb_time_on_ziip;             /* zIIP time. Enclave time not     @H4A  */
      struct {
        double         assb_time_sup_on_cp; /* @H4A                                  */
        } assb_time_ziip_on_cp;             /* zIIP time on CP. Enclave time   @H4A  */
      struct {
        double         assb_sup_phtm;
        } assb_ziip_phtm;             /* zIIP-only equivalent of ASSBPHTM @H4A */
      double         assb_srb_time_on_cp;              /* Time on CP in SRB mode for this       */
      struct {
        double         assb_sup_enct;
        } assb_ziip_enct;             /* Enclave zIIP time in an address       */
      struct {
        double         assb_ifa_on_cp_enct; /* Enclave time for IFA on CP in an      */
        } assb_zcbp_on_cp_enct;             /* Enclave time for zCBP on CP in an     */
      void          *assbsown;                         /* Address of the Suspended SRB    @MOC  */
      void          *assbsowt;                         /* SSD Static Ownership queue      @MSA  */
      struct {
        double         assb_ifa_on_cp_base_enct; /* Enclave base time for IFA on CP in    */
        } assb_zcbp_on_cp_base_enct;             /* Enclave base time for zCBP on CP in   */
      double         assb_time_at_pdp;                 /* Trickle promotion CPU time (PDP       */
      double         assb_srbt_base;                   /* BASE TIME FOR ASCBSRBT          @MWA  */
      void          *assbcasc;                         /* Address of the Console Address  @PEA  */
      int            assbnumberunauthpets;             /* Number of unauthorized PETs           */
      double         assb_asst_time_on_cp;             /* Additional SRB Service Time     @H5A  */
      double         assb_switch_to_zaapziip_count;    /* When not zAAP_On_zIIP initially,      */
      double         assbasab;                         /* Address of IQP ASAB             @N6A  */
      struct {
        double         assb_sup_base_enct; /* Base value, set by WLM          @N3A  */
        } assb_ziip_base_enct;             /* Base value, set by WLM          @NWA  */
      struct {
        double         assb_sup_on_cp_enct; /* Enclave time for SUP on CP in an      */
        } assb_ziip_on_cp_enct;             /* Enclave time for zIIP on CP in an     */
      struct {
        double         assb_sup_on_cp_base_enct; /* Enclave base time for SUP on CP in    */
        } assb_ziip_on_cp_base_enct;             /* Enclave base time for zIIP on CP in   */
      void          *assbrmin;                         /* Address of RTM's reserved RMPL        */
      void          *assbrtma;                         /* Address of RTM's reserved RTM2WA      */
      double         assb_hdlockpromotion_time_at_pdp; /* Non-enclave HD=YES lock promote       */
      struct {
        void          *assb_smfcms_lockinst_addr; /* Address of the SMF CMS                */
        } assb_lockinst_ptrs;                     /* @NHA                                  */
      void          *assb_enqdeq_cms_lockinst_addr;    /* Address of the ENQ/DEQ CMS            */
      void          *assb_latch_cms_lockinst_addr;     /* Address of the Latch CMS              */
      void          *assb_cms_lockinst_addr;           /* Address of the CMS                    */
      void          *assb_local_lockinst_addr;         /* Address of the local and CML lock     */
      int            assb_hdlockpromote_disps;         /* Count of non-enclave HD=YES lock      */
      struct {
        void          *assbsawq;      /* -                 ADDRESS OF ADDRESS SPACE SRB WEB */
        unsigned char  assbr304[252]; /* Reserved. DO NOT USE            @N8A               */
        } assb_300;                   /* @N8A                                               */
      struct {
        void          *assbhreq;      /* -                 Local lock requestor address    @N8A */
        short int      assbhasi;      /* -               Local lock owning ASID          @N8A   */
        unsigned char  assbr406[250]; /* Reserved. DO NOT USE            @N8A                   */
        } assb_400;                   /* @N8A                                                   */
      struct {
        double         assb_enct;                     /* Enclave time in an address space      */
        int            assb_enct_disps;               /* Count of enclave dispatches for cp    */
        int            assb_enct_hdlockpromote_disps; /* Count of enclave HD=YES lock          */
        double         assb_enct_hdlockpromote_time;  /* Enclave HD=YES lock promote CPU       */
        unsigned char  assbr518[232];                 /* Reserved. DO NOT USE            @0PC  */
        } assb_500;                                   /* @N8A                                  */
      struct {
        struct {
          struct {
            double         assb_ifa_enct; /* @0PA                                  */
            } assb_zaap_enct;             /* Enclave zAAP time in an address @0PC  */
          } assb_zcbp_enct; /* Enclave zCBP time in an address @NWA  */
        struct {
          int            assb_zaap_enct_disps; /* Count of enclave                      */
          } assb_zcbp_enct_disps;              /* Count of enclave                      */
        int            assbbrokenup_seqnum;          /* Sequence number of changes to         */
        unsigned char  assbdiag610[160];             /* Diagnostic data for IBM use only@NWC  */
        unsigned char  assbr6b0[56];                 /* Reserved. DO NOT USE            @NWC  */
        double         assb_srb_time_on_zcbp;        /* Non-preemptable SRB time on zCBP      */
        double         assb_asst_time_on_zcbp;       /* non-enclave                           */
        int            assb_srb_time_on_zcbp_disps;  /* Count of dispatches for               */
        int            assb_asst_time_on_zcbp_disps; /* Count of dispatches for non-enclave   */
        } assb_600;                                  /* @N8A                                  */
      struct {
        int            assbetsc;      /* Enclave TCB Summary Count       @N8M  */
        unsigned char  assbr704[252]; /* Reserved. DO NOT USE            @N8A  */
        } assb_700;                   /* @N8A                                  */
      struct {
        int            assbcmlc;      /* -                 Count of CML locks held by */
        unsigned char  assbr804[4];   /* Reserved.                       @NFA         */
        struct {
          void          *assbsvrb; /* Address of first available SVRB @NFA         */
          int            assbsync; /* Synchronization count           @NFA         */
          } assbsupc;              /* SVRB pool header                @NFA         */
        unsigned char  assbr810[240]; /* Reserved. DO NOT USE            @NFA         */
        } assb_800;                   /* @NFA                                         */
      union {
        unsigned char  assb_900[176]; /* @NVC                                  */
        struct {
          double         assb_vartime_at_pdp;          /* Total time promoted to a variable     */
          double         assb_varweighted_time_at_pdp; /* Time promoted to a variable           */
          unsigned char  assb_hcwa[8];                 /* HCW                             @NNC  */
          double         assb_scmbc;                   /* Storage Class Memory (SCM) block      */
          double         assb_ziip_phtm_base;          /* Value in ASSB_zIIP_PHTM at the end    */
          int            assb_majors_preempted;        /* Number of times major timeslices      */
          int            assb_minors_preempted;        /* Number of times minor timeslices      */
          double         assbinitiatorjobid;           /* Initiator JOB ID                      */
          int            assbinitiatorseqnum;          /* Initiator Sequence Number.            */
          unsigned char  assbr93c[4];                  /* Reserved                        @0PA  */
          unsigned char  assbdiag940[112];             /* Diagnostic data for IBM use only@NVC  */
          __extension__ double         assbend[0];     /* END OF ASSB.                          */
          };
        };
      };
    };
  };

/* Values for field "assbxmf1" */
#define assbxeax                    0x80 /* ADDRESS SPACE OWNS ENTRY TABLES @L4A               */

/* Values for field "assbstw1" */
#define assbstyp                    0xF0 /* FIRST 4 BITS REPRESENT STOKEN   @L3A               */

/* Values for field "assbmcso" */
#define assbemcs_activated          0x80 /* At least one EMCS console was   @MKA               */

/* Values for field "assbflg0" */
#define assbbsdn                    0x80 /* BYPASS SVC DUMP                 @D7C               */
#define assbcdsi                    0x40 /* CDSI Resources Held             @DDA               */
#define assbpsch                    0x20 /* Parallel Detach SRB scheduled   @09A               */
#define assbpnsw                    0x10 /* If on, this space is declared by                   */
#define assbnoml                    0x08 /* NoML used internally                               */
#define assbsdumpas                 0x04 /* SDUMP is dumping this address   @0JC               */
#define assbsdumpnd                 0x02 /* SDUMP set the tasks in this     @0JA               */
#define assbsdumpresetnd            0x01 /* Request SDUMP to set tasks      @0JA               */

/* Values for field "assbflg1" */
#define assbntsl                    0x20 /* JOB STEP HAS CREATED            @LIA               */
#define assbfrst                    0x10 /* The first pool of SVRBs has     @0CA               */

/* Values for field "assbflg2" */
#define assbenfl                    0x80 /* IF ON, INDICATES ADDRESS SPACE  @LRA               */
#define assbnswf                    0x40 /* If on, indicates IEAVEGR found  @LSA               */
#define assbpran                    0x20 /* No longer set - kept for        @09C               */

/* Values for field "assbflg3" */
#define assbarm                     0x80 /* The job or STC running in this  @LVA               */
#define assbnrst                    0x40 /* The Automatic Restart Manager   @LVA               */
#define assbgdps                    0x20 /* If on, indicates this is the                       */
#define assbmdip                    0x10 /* If on, indicates that a Memterm                    */
#define assbbcpiiused               0x08 /* If on, indicates this                              */
#define assb_initially_zaap_on_ziip 0x04 /* Indicates that zAAP on zIIP was                    */
#define assbmtdc                    0x02 /* If on, indicates that Memterm dump                 */

/* Values for field "assbmt_" */
#define assbmtp                     0x80 /* MEMTERM PENDING.  TURNED ON     @DAA               */

/* Values for field "assbdfp" */
#define assboam                     0x80 /* ADDRESS SPACE IS A USER OF OAM  @03A               */

/* Values for field "assbttfl" */
#define assbttrc                    0x80 /* Transaction Trace has been used.@MCA               */

/* Values for field "assbwmf1" */
#define assbwini                    0x80 /* WLM Managed Batch initiator     @M8A               */
#define assbfsas                    0x40 /* WLM Managed OE Forked/Spawned   @M8A               */

/* Values for field "assbctxf" */
#define assbncl                     0x80 /* There is no limit to the number @MAM               */
#define assbmsgi                    0x40 /* The message to relax the above  @MAM               */
#define assburmx                    0x20 /* There is no limit to the number @MAA               */
#define assburmm                    0x10 /* The message to relax the above  @MAA               */

/* Values for field "assbofl0" */
#define assbomsc                    0x80 /* USS address space must remain   @DEA               */
#define assbodwt                    0x40 /* USS process awaiting dub.       @MHA               */
#define assbosdb                    0x20 /* Allow address space to dub at                      */
#define assbtdaff                   0x10 /* CInet Addr Sp Transport Dr                         */

/* Values for field "assbflg4" */
#define assb_authle                 0x80 /* Resources have been allocated.  @MLA               */

/* Values for field "assbcryp" */
#define assbsods                    0x80 /* If set to '1'b, the address     @MTA               */
#define assbcrnq                    0x40 /* If set to '1'b, the address     @NCA               */
#define assbssl                     0x01 /* If set to '1'b, the address                        */

/* Values for field "assb_cp_affinity_node" */
#define assb_entitle_nominee        0x80 /* Entitle nominee                 @NGA               */

/* Values for field "assbrmin" */
#define assbrtmi                    0x80 /* When on, the reserved RMPL pointed                 */

/* Values for field "assbsawq" */
#define assburrq                    0x80 /* -             SYSEVENT USER READY REQUIRED    @N8A */

#pragma pack(reset)
