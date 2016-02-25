/**
 * @file 3694s.h
 *
 * @brief 3694s I/O map
 *
 * @htmlonly
 * @version $Id:$
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 * @endhtmlonly
 *
 ***********************************************************************/
#ifndef _3694S_H_
#define _3694S_H_

#ifdef __cplusplus
extern "C" {
#endif

/** LVD構造マップ */
struct _st_lvd
{
    /** LVDCR */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char LVDE  :1;
            unsigned char       :3;
            unsigned char LVDSEL:1;
            unsigned char LVDRE :1;
            unsigned char LVDDE :1;
            unsigned char LVDUE :1;
        } BIT;
        /**<  Bit  Access */
    } CR;
    /** LVDSR */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char      :6;
            unsigned char LVDDF:1;
            unsigned char LVDUF:1;
        } BIT;
        /**<  Bit  Access */
    } SR;
};

/** IIC2構造マップ */
struct _st_iic2 {
    /** ICCR1        */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char ICE :1;
            unsigned char RCVD:1;
            unsigned char MST :1;
            unsigned char TRS :1;
            unsigned char CKS :4;
        } BIT;
        /**<  Bit  Access */
    } ICCR1;
    /** ICCR2 */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char BBSY  :1;
            unsigned char SCP   :1;
            unsigned char SDAO  :1;
            unsigned char SDAOP :1;
            unsigned char SCLO  :1;
            unsigned char       :1;
            unsigned char IICRST:1;
        } BIT;
        /**<  Bit  Access */
    } ICCR2;
    /** ICMR         */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char MLS :1;
            unsigned char WAIT:1;
            unsigned char     :2;
            unsigned char BCWP:1;
            unsigned char BC  :3;
        } BIT;
        /**<  Bit  Access */
    } ICMR;
    /** ICIER        */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char TIE  :1;
            unsigned char TEIE :1;
            unsigned char RIE  :1;
            unsigned char NAKIE:1;
            unsigned char STIE :1;
            unsigned char ACKE :1;
            unsigned char ACKBR:1;
            unsigned char ACKBT:1;
        } BIT;
        /**<  Bit  Access */
    } ICIER;
    /** ICSR         */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char TDRE :1;
            unsigned char TEND :1;
            unsigned char RDRF :1;
            unsigned char NACKF:1;
            unsigned char STOP :1;
            unsigned char ALOVE:1;
            unsigned char AAS  :1;
            unsigned char ADZ  :1;
        } BIT;
        /**<  Bit  Access */
    } ICSR;
    /** SAR          */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char SVA:7;
            unsigned char FS :1;
        } BIT;
        /**<  Bit  Access */
    } SAR;
    unsigned char    ICDRT;
    unsigned char    ICDRR;
};

/** TimerW構造マップ    */
struct _st_tw {
    /** TMRW         */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char CTS  :1;
            unsigned char      :1;
            unsigned char BUFEB:1;
            unsigned char BUFEA:1;
            unsigned char      :1;
            unsigned char PWMD :1;
            unsigned char PWMC :1;
            unsigned char PWMB :1;
        } BIT;
        /**<  Bit  Access */
    } TMRW;
    /** TCRW         */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char CCLR:1;
            unsigned char CKS :3;
            unsigned char TOD :1;
            unsigned char TOC :1;
            unsigned char TOB :1;
            unsigned char TOA :1;
        } BIT;
        /**<  Bit  Access */
    } TCRW;
    /** TIERW        */
    union 
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char OVIE :1;
            unsigned char      :3;
            unsigned char IMIED:1;
            unsigned char IMIEC:1;
            unsigned char IMIEB:1;
            unsigned char IMIEA:1;
        } BIT;
        /**<  Bit  Access */
    } TIERW;
    /** TSRW         */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char OVF :1;
            unsigned char     :3;
            unsigned char IMFD:1;
            unsigned char IMFC:1;
            unsigned char IMFB:1;
            unsigned char IMFA:1;
        } BIT;
        /**<  Bit  Access */
    } TSRW;
    /** TIOR0        */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char    :1;
            unsigned char IOB:3;
            unsigned char    :1;
            unsigned char IOA:3;
        } BIT;
        /**<  Bit  Access */
    } TIOR0;
    /** TIOR1        */
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char    :1;
            unsigned char IOD:3;
            unsigned char    :1;
            unsigned char IOC:3;
        } BIT;
        /**<  Bit  Access */
    } TIOR1;
    unsigned int       TCNT;
    unsigned int       GRA;
    unsigned int       GRB;
    unsigned int       GRC;
    unsigned int       GRD;
};
/* FLASH構造マップ */
struct _st_flash
{
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char    :1;
            unsigned char SWE:1;
            unsigned char ESU:1;
            unsigned char PSU:1;
            unsigned char EV :1;
            unsigned char PV :1;
            unsigned char E  :1;
            unsigned char P  :1;
        } BIT;
        /**<  Bit  Access */
    } FLMCR1;
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char FLER:1;
        } BIT;
        /**<  Bit  Access */
    } FLMCR2;
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char PDWND:1;
        } BIT;
        /**<  Bit  Access */
    } FLPWCR;
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char    :3;
            unsigned char EB4:1;
            unsigned char EB3:1;
            unsigned char EB2:1;
            unsigned char EB1:1;
            unsigned char EB0:1;
        } BIT;
        /**<  Bit  Access */
    } EBR1;
    char wk[7];
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char FLSHE:1;
        } BIT;
        /**<  Bit  Access */
    } FENR;
};
/** TV構造マップ    */
struct _st_tv
{
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char CMIEB:1;
            unsigned char CMIEA:1;
            unsigned char OVIE :1;
            unsigned char CCLR :2;
            unsigned char CKS  :3;
        } BIT;
        /**<  Bit  Access */
    } TCRV0;
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char CMFB:1;
            unsigned char CMFA:1;
            unsigned char OVF :1;
            unsigned char     :1;
            unsigned char OS  :4;
        } BIT;
        /**<  Bit  Access */
    } TCSRV;
    unsigned char      TCORA;
    unsigned char      TCORB;
    unsigned char      TCNTV;
    union
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char     :3;
            unsigned char TVEG:2;
            unsigned char TRGE:1;
            unsigned char     :1;
            unsigned char ICKS:1;
        } BIT;
        /**<  Bit  Access */
    } TCRV1;
};
/** TimerA構造マップ    */
struct _st_ta
{
    union 
    {
        unsigned char BYTE;
        /**<  Byte Access */
        struct
        {
            unsigned char CKSO:3;
            unsigned char     :1;
            unsigned char CKSI:4;
        } BIT;
        /**<  Bit  Access */
    } TMA;
    unsigned char TCA;
};
/** SCI3構造マップ  */
struct _st_sci3 {
    union {                                  /* SMR          */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char COM :1;       /*    COM       */
            unsigned char CHR :1;       /*    CHR       */
            unsigned char PE  :1;       /*    PE        */
            unsigned char PM  :1;       /*    PM        */
            unsigned char STOP:1;       /*    STOP      */
            unsigned char MP  :1;       /*    MP        */
            unsigned char CKS :2;       /*    CKS       */
        }      BIT;                 /*              */
        /**<  Bit  Access */
    }          SMR;                    /*              */
    unsigned char    BRR;                    /* BRR          */
    union {                                  /* SCR3         */
        unsigned char BYTE;                /*  Byte Access */
        struct {                           /*  Bit  Access */
            unsigned char TIE :1;       /*    TIE       */
            unsigned char RIE :1;       /*    RIE       */
            unsigned char TE  :1;       /*    TE        */
            unsigned char RE  :1;       /*    RE        */
            unsigned char MPIE:1;       /*    MPIE      */
            unsigned char TEIE:1;       /*    TEIE      */
            unsigned char CKE :2;       /*    CKE       */
        }      BIT;                 /*              */
    }          SCR3;                   /*              */
    unsigned char    TDR;                    /* TDR          */
    union {                                  /* SSR          */
        unsigned char BYTE;                /*  Byte Access */
        struct {                           /*  Bit  Access */
            unsigned char TDRE:1;       /*    TDRE      */
            unsigned char RDRF:1;       /*    RDRF      */
            unsigned char OER :1;       /*    OER       */
            unsigned char FER :1;       /*    FER       */
            unsigned char PER :1;       /*    PER       */
            unsigned char TEND:1;       /*    TEND      */
            unsigned char MPBR:1;       /*    MPBR      */
            unsigned char MPBT:1;       /*    MPBT      */
        }      BIT;                 /*              */
    }          SSR;                    /*              */
    unsigned char    RDR;                    /* RDR          */
};                                                      /*              */
/** A/D構造マップ   */
struct _st_ad {
    unsigned int       ADDRA;                  /* ADDRA        */
    unsigned int       ADDRB;                  /* ADDRB        */
    unsigned int       ADDRC;                  /* ADDRC        */
    unsigned int       ADDRD;                  /* ADDRD        */
    union {                                    /* ADCSR        */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char ADF :1;         /*    ADF       */
            unsigned char ADIE:1;         /*    ADIE      */
            unsigned char ADST:1;         /*    ADST      */
            unsigned char SCAN:1;         /*    SCAN      */
            unsigned char CKS :1;         /*    CKS       */
            unsigned char CH  :3;         /*    CH        */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            ADCSR;                  /*              */
    union {                                    /* ADCR         */
        unsigned char BYTE;                  /*  Byte Access */
        struct {                             /*  Bit  Access */
            unsigned char TRGE:1;         /*    TRGE      */
        }      BIT;                   /*              */
    }            ADCR;                   /*              */
};                                                      /*              */
/** WDT構造マップ   */
struct _st_wdt {
    union {                                   /* TCSRWD       */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char B6WI  :1;      /*    B6WI      */
            unsigned char TCWE  :1;      /*    TCWE      */
            unsigned char B4WI  :1;      /*    B4WI      */
            unsigned char TCSRWE:1;      /*    TCSRWE    */
            unsigned char B2WI  :1;      /*    B2WI      */
            unsigned char WDON  :1;      /*    WDON      */
            unsigned char B0WI  :1;      /*    B0WI      */
            unsigned char WRST  :1;      /*    WRST      */
        }      BIT;                  /*              */
        /**<  Bit  Access */
    }           TCSRWD;                 /*              */
    unsigned char     TCWD;                   /* TCWD         */
    union {                                   /* TMWD         */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char    :4;         /*              */
            unsigned char CKS:4;         /*    CKS       */
        }      BIT;                  /*              */
        /**<  Bit  Access */
    }           TMWD;                   /*              */
};                                                      /*              */
/** ABRK構造マップ  */
struct _st_abrk {
    union {                                  /* ABRKCR       */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char RTINTE:1;     /*    RTINTE    */
            unsigned char CSEL  :2;     /*    CSEL      */
            unsigned char ACMP  :3;     /*    ACMP      */
            unsigned char DCMP  :2;     /*    DCMP      */
        }      BIT;                 /*              */
        /**<  Bit  Access */
    }          CR;                     /*              */
    union {                                  /* ABRKSR       */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char ABIF:1;       /*    ABIF      */
            unsigned char ABIE:1;       /*    ABIE      */
        }      BIT;                 /*              */
        /**<  Bit  Access */
    }          SR;                     /*              */
    void            *BAR;                    /* BAR          */
    unsigned int     BDR;                    /* BDR          */
};
/* IO構造マップ    */
struct _st_io {
    union {                                    /* PUCR1        */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char B7:1;           /*    Bit 7     */
            unsigned char B6:1;           /*    Bit 6     */
            unsigned char B5:1;           /*    Bit 5     */
            unsigned char B4:1;           /*    Bit 4     */
            unsigned char   :1;           /*    Bit 3     */
            unsigned char B2:1;           /*    Bit 2     */
            unsigned char B1:1;           /*    Bit 1     */
            unsigned char B0:1;           /*    Bit 0     */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            PUCR1;                  /*              */
    union {                                    /* PUCR5        */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char   :2;           /*    Bit 7,6   */
            unsigned char B5:1;           /*    Bit 5     */
            unsigned char B4:1;           /*    Bit 4     */
            unsigned char B3:1;           /*    Bit 3     */
            unsigned char B2:1;           /*    Bit 2     */
            unsigned char B1:1;           /*    Bit 1     */
            unsigned char B0:1;           /*    Bit 0     */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            PUCR5;                  /*              */
    char               wk1[2];                 /*              */
    union {                                    /* PDR1         */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char B7:1;           /*    Bit 7     */
            unsigned char B6:1;           /*    Bit 6     */
            unsigned char B5:1;           /*    Bit 5     */
            unsigned char B4:1;           /*    Bit 4     */
            unsigned char   :1;           /*    Bit 3     */
            unsigned char B2:1;           /*    Bit 2     */
            unsigned char B1:1;           /*    Bit 1     */
            unsigned char B0:1;           /*    Bit 0     */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            PDR1;                   /*              */
    union {                                    /* PDR2         */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char   :5;           /*    Bit 7-3   */
            unsigned char B2:1;           /*    Bit 2     */
            unsigned char B1:1;           /*    Bit 1     */
            unsigned char B0:1;           /*    Bit 0     */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            PDR2;                   /*              */
    char               wk2[2];                 /*              */
    union {                                    /* PDR5         */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char B7:1;           /*    Bit 7     */
            unsigned char B6:1;           /*    Bit 6     */
            unsigned char B5:1;           /*    Bit 5     */
            unsigned char B4:1;           /*    Bit 4     */
            unsigned char B3:1;           /*    Bit 3     */
            unsigned char B2:1;           /*    Bit 2     */
            unsigned char B1:1;           /*    Bit 1     */
            unsigned char B0:1;           /*    Bit 0     */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            PDR5;                   /*              */
    char               wk3;                    /*              */
    union {                                    /* PDR7         */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char   :1;           /*    Bit 7     */
            unsigned char B6:1;           /*    Bit 6     */
            unsigned char B5:1;           /*    Bit 5     */
            unsigned char B4:1;           /*    Bit 4     */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            PDR7;                   /*              */
    union {                                    /* PDR8         */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char B7:1;           /*    Bit 7     */
            unsigned char B6:1;           /*    Bit 6     */
            unsigned char B5:1;           /*    Bit 5     */
            unsigned char B4:1;           /*    Bit 4     */
            unsigned char B3:1;           /*    Bit 3     */
            unsigned char B2:1;           /*    Bit 2     */
            unsigned char B1:1;           /*    Bit 1     */
            unsigned char B0:1;           /*    Bit 0     */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            PDR8;                   /*              */
    char               wk4;                    /*              */
    union {                                    /* PDRB         */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char B7:1;           /*    Bit 7     */
            unsigned char B6:1;           /*    Bit 6     */
            unsigned char B5:1;           /*    Bit 5     */
            unsigned char B4:1;           /*    Bit 4     */
            unsigned char B3:1;           /*    Bit 3     */
            unsigned char B2:1;           /*    Bit 2     */
            unsigned char B1:1;           /*    Bit 1     */
            unsigned char B0:1;           /*    Bit 0     */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            PDRB;                   /*              */
    char               wk5[2];                 /*              */
    union {                                    /* PMR1         */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char IRQ3:1;         /*    IRQ3      */
            unsigned char IRQ2:1;         /*    IRQ2      */
            unsigned char IRQ1:1;         /*    IRQ1      */
            unsigned char IRQ0:1;         /*    IRQ0      */
            unsigned char     :2;         /*              */
            unsigned char TXD :1;         /*    TXD       */
            unsigned char TMOW:1;         /*    TMOW      */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            PMR1;                   /*              */
    union {                                    /* PMR5         */
        unsigned char BYTE;
        /**<  Byte Access */
        struct {
            unsigned char     :2;         /*              */
            unsigned char WKP5:1;         /*    WKP5      */
            unsigned char WKP4:1;         /*    WKP4      */
            unsigned char WKP3:1;         /*    WKP3      */
            unsigned char WKP2:1;         /*    WKP2      */
            unsigned char WKP1:1;         /*    WKP1      */
            unsigned char WKP0:1;         /*    WKP0      */
        }      BIT;                   /*              */
        /**<  Bit  Access */
    }            PMR5;                   /*              */
    char               wk6[2];                 /*              */
    
    unsigned char      PCR1;                   /* PCR1         */
    unsigned char      PCR2;                   /* PCR2         */
    char               wk7[2];                 /*              */
    unsigned char      PCR5;                   /* PCR5         */
    char               wk8;                    /*              */
    unsigned char      PCR7;                   /* PCR7         */
    unsigned char      PCR8;                   /* PCR8         */
};                                                      /*              */
/** SYSCR1構造マップ */
union _un_syscr1 {
    unsigned char BYTE;
    /**<  Byte Access */
    struct {
        unsigned char SSBY :1;           /*    SSBY      */
        unsigned char STS  :3;           /*    STS       */
        unsigned char NESEL:1;           /*    NESEL     */
    }      BIT;                      /*              */
    /**<  Bit  Access */
};                                                      /*              */
/** SYSCR2構造マップ */
union _un_syscr2 {
    unsigned char BYTE;
    /**<  Byte Access */
    struct {
        unsigned char SMSEL:1;           /*    SMSEL     */
        unsigned char LSON :1;           /*    LSON      */
        unsigned char DTON :1;           /*    DTON      */
        unsigned char MA   :3;           /*    MA        */
        unsigned char SA   :2;           /*    SA        */
    }      BIT;                      /*              */
    /**<  Bit  Access */
};                                                      /*              */
/** IEGR1構造マップ  */
union _un_iegr1 {
    unsigned char BYTE;
    /**<  Byte Access */
    struct {
        unsigned char NMIEG:1;            /*    NMIEG     */
        unsigned char      :3;            /*              */
        unsigned char IEG3 :1;            /*    IEG3      */
        unsigned char IEG2 :1;            /*    IEG2      */
        unsigned char IEG1 :1;            /*    IEG1      */
        unsigned char IEG0 :1;            /*    IEG0      */
    }      BIT;                       /*              */
    /**<  Bit  Access */
};                                                      /*              */
/* IEGR2構造マップ  */
union _un_iegr2 {
    unsigned char BYTE;
    /**<  Byte Access */
    struct {
        unsigned char      :2;            /*              */
        unsigned char WPEG5:1;            /*    WPEG5     */
        unsigned char WPEG4:1;            /*    WPEG4     */
        unsigned char WPEG3:1;            /*    WPEG3     */
        unsigned char WPEG2:1;            /*    WPEG2     */
        unsigned char WPEG1:1;            /*    WPEG1     */
        unsigned char WPEG0:1;            /*    WPEG0     */
    }      BIT;                       /*              */
    /**<  Bit  Access */
};                                                      /*              */
/** IENR1構造マップ  */
union _un_ienr1 {
    unsigned char BYTE;
    /**<  Byte Access */
    struct {
        unsigned char IENDT:1;            /*    IENDT     */
        unsigned char IENTA:1;            /*    IENTA     */
        unsigned char IENWP:1;            /*    IENWP     */
        unsigned char      :1;            /*              */
        unsigned char IEN3 :1;            /*    IEN3      */
        unsigned char IEN2 :1;            /*    IEN2      */
        unsigned char IEN1 :1;            /*    IEN1      */
        unsigned char IEN0 :1;            /*    IEN0      */
    }      BIT;                       /*              */
    /**<  Bit  Access */
};                                                      /*              */
/**< IRR1構造マップ   */
union _un_irr1 {
    unsigned char BYTE;
    /**<  Byte Access */
    struct {
        unsigned char IRRDT:1;             /*    IRRDT     */
        unsigned char IRRTA:1;             /*    IRRTA     */
        unsigned char      :2;             /*              */
        unsigned char IRRI3:1;             /*    IRRI3     */
        unsigned char IRRI2:1;             /*    IRRI2     */
        unsigned char IRRI1:1;             /*    IRRI1     */
        unsigned char IRRI0:1;             /*    IRRI0     */
    }      BIT;                        /*              */
    /**<  Bit  Access */
};                                                      /*              */
/** IWPR構造マップ   */
union _un_iwpr {
    unsigned char BYTE;
    /**<  Byte Access */
    struct {
        unsigned char      :2;             /*              */
        unsigned char IWPF5:1;             /*    IWPF5     */
        unsigned char IWPF4:1;             /*    IWPF4     */
        unsigned char IWPF3:1;             /*    IWPF3     */
        unsigned char IWPF2:1;             /*    IWPF2     */
        unsigned char IWPF1:1;             /*    IWPF1     */
        unsigned char IWPF0:1;             /*    IWPF0     */
    }      BIT;                        /*              */
    /**<  Bit  Access */
};                                                      /*              */
/** MSTCR1構造マップ */
union _un_mstcr1 {
    unsigned char BYTE;
    /**<  Byte Access */
    struct {
        unsigned char       :1;          /*              */
        unsigned char MSTIIC:1;          /*    MSTIIC    */
        unsigned char MSTS3 :1;          /*    MSTS3     */
        unsigned char MSTAD :1;          /*    MSTAD     */
        unsigned char MSTWD :1;          /*    MSTWD     */
        unsigned char MSTTW :1;          /*    MSTTW     */
        unsigned char MSTTV :1;          /*    MSTTV     */
        unsigned char MSTTA :1;          /*    MSTTA     */
    }      BIT;                      /*              */
    /**<  Bit  Access */
};

/** LVD   Address*/
#define _LVD     (*(volatile struct _st_lvd   *)0xF730)
/** IIC2  Address*/
#define _IIC2    (*(volatile struct _st_iic2  *)0xF748)
/** TW    Address*/
#define _TW      (*(volatile struct _st_tw    *)0xFF80)
/** FLASH Address*/
#define _FLASH   (*(volatile struct _st_flash *)0xFF90)
/** TV    Address*/
#define _TV      (*(volatile struct _st_tv    *)0xFFA0)
/** TA    Address*/
#define _TA      (*(volatile struct _st_ta    *)0xFFA6)
/** SCI3  Address*/
#define _SCI3    (*(volatile struct _st_sci3  *)0xFFA8)
/** A/D   Address*/
#define _AD      (*(volatile struct _st_ad    *)0xFFB0)
/** WDT   Address*/
#define _WDT     (*(volatile struct _st_wdt   *)0xFFC0)
/** ABRK  Address*/
#define _ABRK    (*(volatile struct _st_abrk  *)0xFFC8)
/** IO    Address*/
#define _IO      (*(volatile struct _st_io    *)0xFFD0)
/** SYSCR1 Address*/
#define _SYSCR1  (*(volatile union  _un_syscr1*)0xFFF0)
/** SYSCR2Address*/
#define _SYSCR2  (*(volatile union  _un_syscr2*)0xFFF1)
/** IEGR1 Address*/
#define _IEGR1   (*(volatile union  _un_iegr1 *)0xFFF2)
/** IEGR2 Address*/
#define _IEGR2   (*(volatile union  _un_iegr2 *)0xFFF3)
/** IENR1 Address*/
#define _IENR1   (*(volatile union  _un_ienr1 *)0xFFF4)
/** IRR1  Address*/
#define _IRR1    (*(volatile union  _un_irr1  *)0xFFF6)
/** IWPR  Address*/
#define _IWPR    (*(volatile union  _un_iwpr  *)0xFFF8)
/** MSTCR1 Address*/
#define _MSTCR1  (*(volatile union  _un_mstcr1*)0xFFF9)

#ifdef __cplusplus
}
#endif

#endif /* _3694S_H_ */
