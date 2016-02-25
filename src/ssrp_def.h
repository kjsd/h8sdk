/**
 * @file ssrp_def.h
 *
 * @version $Id: ssrp_def.h 156 2009-03-19 08:04:25Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * local definitions of Simple Single Ring Protocol.
 *
 * @component H8 development platform.
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#ifndef SSRP_DEF_H
#define SSRP_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/h8sdk/ssrp.h"
#include "../include/h8sdk/stdlib.h"
#include "../include/h8sdk/assert.h"
#include "../include/h8sdk/ifstub.h"

typedef enum
{
    TRXST_PREAMBLE_ = 0,
    TRXST_HEADER_,
    TRXST_DATA_,

    NUM_OF_TRXST_
} TransactionState_;

typedef enum
{
    ST_DEALLOCATE_ = 0,
    ST_DISCONNECT_,
    ST_CONNECT_,
    
    NUM_OF_STATE_
} State_;

typedef _BOOL (*StateHandle_)();

/**
 * @brief �l�b�g���[�N��̑��m�[�h��`�^
 *
 * �v���g�R���̊Ǘ��ɕK�v�Ȑڑ��m�[�h�ƃ����O�ɎQ�����Ă���m�[�h�̑�����
 * ��`�����B
 */
typedef struct
{
    SSRP_Address addr[SSRP_MAX_NODE];
    /**< �l�b�g���[�N�Ɍq�����Ă��鑼�m�[�h�̃A�h���X */
    SSRP_Address con[SSRP_NUM_OF_CON];
    /**< ���m�[�h�ƒ��ɐڑ����Ă���m�[�h�̃A�h���X */
    _UBYTE total;
    /**< �l�b�g���[�N�Ɍq�����Ă��鑼�m�[�h�̑��� */
    _UBYTE addr_count;
} Pear_;

typedef struct
{
    StateHandle_ handle;
    State_ next;
} StateTable_;

typedef struct
{
    SSRP_Header header;
    _UBYTE* buffer;
    TransactionState_ state;
} TransactionParam_;


#ifdef __cplusplus
}
#endif

#endif /* SSRP_DEF_H */
