/**
 * @file ifstub.c
 *
 * @version $Id: ifstub.c 156 2009-03-19 08:04:25Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * Communication Interface Stub.
 *
 * @component H8 development platform
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#include "../include/h8sdk/assert.h"
#include "../include/h8sdk/sci.h"

#ifdef USE_LOOPBACK_SSRP
#include "../include/h8sdk/ssrp_skel.h"
#endif /* USE_LOOPBACK_SSRP */

#include "../include/h8sdk/ifstub.h"


static const IFSTUB_Class instances_[] = {
    { SCI_write, SCI_read },

#ifdef USE_LOOPBACK_SSRP
    { SSRP_SKEL_write, SSRP_SKEL_read },
#endif /* USE_LOOPBACK_SSRP */
};


const IFSTUB_Class* IFSTUB_getInstance(IFSTUB_Type t)
{
    _assert(t < IFSTUB_NUM_OF_TYPE);

    return &instances_[t];
}
