/**
 * @file ssrp.h
 *
 * @brief SSRP�ʐM�v���g�R��
 *
 * ���̃��W���[���́A����ʍs�̃����O�^�l�b�g���[�N��ł̒ʐM�v���g�R��
 * SSRP(Simple Single Ring Protocol)�̃V���v���Ȏ����p�^�[���ł���B
 *
 * @see ifstub.h
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
#ifndef SSRP_H_
#define SSRP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/**
 * @brief �ڑ��m�[�h�ő吔
 */
#define SSRP_MAX_NODE 16

/**
 * @brief �ő呗��M�f�[�^�T�C�Y
 *
 * �p�P�b�g�̃y�C���[�h�ő�l
 */
#define SSRP_MAX_DATA 255
/**
 * @brief �����ȃA�h���X
 */
#define SSRP_ADDR_INVALID 0
/**
 * @brief �u���[�h�L���X�g�A�h���X
 */
#define SSRP_ADDR_BROADCAST 0xff
/**
 * @brief ��M�^�C���A�E�g�l
 */
#define SSRP_TMO_RECV 255
/**
 * @brief ���M�^�C���A�E�g�l
 */
#define SSRP_TMO_SEND -1

/**
 * @brief LOOP�R�}���h�l
 *
 * �l�b�g���[�N�ڑ��m�[�h���J�E���g����R�}���h
 */
#define SSRP_CMD_LOOP 0x00

/**
 * @brief JOIN�R�}���h�l
 *
 * �l�b�g���[�N�֎Q������R�}���h
 */
#define SSRP_CMD_JOIN 0x01

/**
 * @brief LEAVE�R�}���h�l
 *
 * �l�b�g���[�N���痣�E����R�}���h
 */
#define SSRP_CMD_LEAVE 0x02

/**
 * @brief �v���A���u���l
 *
 * �p�P�b�g���M�O�ɕt������v���A���u���l
 */
#define SSRP_VAL_PREAMBLE 0xaa

/**
 * @brief ��������̑��M�Ԋu
 *
 * JOIN�ALOOP�ȂǁA����������̑��M�Ԋu
 */
#define SSRP_PACKET_SPC (1U << 8)

/**
 * @brief �A�h���X�^��`
 */
typedef _UBYTE SSRP_Address;

/**
 * @brief ���m�[�h�A�h���X������
 *
 * SSRP_Addr�̒l��2����16�i������Őݒ肳���B
 */
extern _SBYTE SSRP_my_addr[];

/**
 * @brief �R�}���h�^��`
 *
 * ���̃R�}���h�ɂ���đ��m�[�h�ƃf�[�^�̘A�g�����B
 * 0x00�`0x7f�܂ł͓����p�ɗ\�񂳂�Ă���B�O�����W���[�����瑗�M����p�P�b�g
 * �̃R�}���h�l��SSRP_CMD_EX��OR�����Ȃ���΂Ȃ�Ȃ��B
 */
typedef _UBYTE SSRP_Command;
/**
 * @brief �O�����W���[���p�R�}���h�}�X�N
 */
#define SSRP_CMD_EX 0x80
/**
 * @brief �����ȃR�}���h�l
 */
#define SSRP_CMD_INVALID 0xff

/**
 * @brief �t���O��`�^
 *
 * �p�P�b�g�̑�����\���t���O�^�B���̃t���O�ɂ��A���N�G�X�g/���X�|���X/
 * �C�x���g���ǂ����̔�����s���B
 */
typedef _UBYTE SSRP_Flag;
/**
 * @brief �C�x���g�t���O�l
 *
 * ���̃t���O���ݒ肳�ꂽ�p�P�b�g�͒ʒm�݂̂̃C�x���g�ł���B
 */
#define SSRP_FLG_EVT 0x00
/**
 * @brief ���N�G�X�g�t���O�l
 *
 * ���̃t���O���ݒ肳�ꂽ�p�P�b�g�̓��X�|���X���K�v�ȃ��N�G�X�g�ł���B
 */
#define SSRP_FLG_REQ 0x01
/**
 * @brief ���N�G�X�g�t���O�l
 *
 * ���̃t���O���ݒ肳�ꂽ�p�P�b�g�̓��N�G�X�g�ɑ΂��郌�X�|���X�ł���B
 */
#define SSRP_FLG_RES 0x02
/**
 * @brief �����ȃt���O�l
 */
#define SSRP_FLG_INVALID 0xff

/**
 * @brief �g�����U�N�V�����^�C�v���ʎq
 */
typedef enum
{
    SSRP_TRX_RECV = 0,
    /**< ��M�^�C�v */
    SSRP_TRX_SEND,
    /**< ���M�^�C�v */

    SSRP_NUM_OF_TRX
    /**< �g�����U�N�V�����^�C�v�̐� */
} SSRP_Transaction;    

/**
 * @brief �g�����U�N�V����ID�̒�`�^
 *
 * �g�����U�N�V���������ʂ��邽�߂�ID�B���m�[�h����p�P�b�g�𔭐M���閈��
 * �C���N�������g����鑗�M�J�E���^�B�p�P�b�g�w�b�_�ɖ���ݒ肳���B
 */
typedef _UWORD SSRP_TransactionId;
/**
 * @brief �����ȃg�����U�N�V����ID
 */
#define SSRP_TRXID_INVALID ((1U << (sizeof(SSRP_TransactionId) << 3)) - 1)

/**
 * @brief SSRP�p�P�b�g�w�b�_
 *
 * SSRP�p�P�b�g�̏���\���w�b�_�B�p�P�b�g�͂��̃w�b�_�ƃf�[�^�̃y�C���[�h
 * ����\�������B�w�b�_�̃`�F�b�N�T���͖���SSRP�����Ń`�F�b�N����A�s��v
 * �̃p�P�b�g�͎�M���Ă��j������邪�A�y�C���[�h�����̗L�����Ɋւ��Ă�
 * SSRP�����ł͊֒m���Ȃ��B
 */
typedef struct
{
    SSRP_Address from;
    /**< ���M��A�h���X */
    SSRP_Address to;
    /**< ���M���A�h���X */
    SSRP_Command command;
    /**< �R�}���h */
    SSRP_Flag flag;
    /**< �p�P�b�g�t���O */
    _UBYTE hop;
    /**<
     * @brief �z�b�v��
     *
     * �e�m�[�h�ɂ��p�P�b�g�������[�����Ƃ��̒l���C���N�������g�����
     */
    _UBYTE data_length;
    /**< �f�[�^�y�C���[�h�� */
    SSRP_TransactionId trx_id;
    /**< �g�����U�N�V����ID */
    _UWORD cksum;
    /**< �w�b�_�̃`�F�b�N�T�� */
} SSRP_Header;

/**
 * @brief �R�l�N�V������ʒ�`�^
 *
 * SSRP�̓����O�v���g�R���Ȃ̂Őڑ��͑O�ƌ�̓�B
 */
typedef enum
{
    SSRP_CON_FRONT = 0,
    /**< �O�ւ̐ڑ� */
    SSRP_CON_BACK,
    /**< ��ւ̐ڑ� */

    SSRP_NUM_OF_CON
    /**< �ڑ���ʂ̐� */
} SSRP_Connection;

/**
 * @brief �R�}���h/�t���O��v����
 *
 * �w�b�_�̃R�}���h�G���A�ƃt���O�G���A���w�肳�ꂽ���̂Ɠ������ǂ�����
 * ������s��
 *
 * @param[in] hp ��r���w�b�_�ւ̃|�C���^
 * @param[in] com ���肷��R�}���h�l
 * @param[in] flg ���肷��t���O�l
 *
 * @return �R�}���h/�t���O������v���Ă���ΐ��̒l�B�����łȂ����0
 */
#define SSRP_COMMAND_EQ(hp, com, flg)                       \
    (((hp)->command == (com)) && ((hp)->flag ==  (flg)))
    
/**
 * @brief �p�P�b�g������
 *
 * �w�肳�ꂽ�w�b�_�̃p�P�b�g�����������Ė����Ƃ���B
 *
 * @param[in] hp ����������w�b�_�ւ̃|�C���^
 */
#define SSRP_INVALIDATE_PACKET(hp)                              \
    ((hp)->from = SSRP_ADDR_INVALID, (hp)->to = SSRP_ADDR_INVALID)

/**
 * @brief �p�P�b�g��������
 *
 * �w�肳�ꂽ�w�b�_�̃p�P�b�g�������Ȃ��̂��ǂ����𔻒肷��
 *
 * @param[in] hp ���肷��w�b�_�ւ̃|�C���^
 *
 * @return ���������ꂽ�p�P�b�g�Ȃ�ΐ��̒l�B�����łȂ����0
 */
#define SSRP_IS_INVALID_PACKET(hp)                                      \
    (((hp)->from == SSRP_ADDR_INVALID) || ((hp)->to == SSRP_ADDR_INVALID))


/**
 * @brief SSRP������
 *
 * SSRP���W���[��������������B��API�g�p�O�ɕK�����s����B
 */
void SSRP_init(SSRP_Address myaddr);

/**
 * @brief �ڑ��J�n
 *
 * ���m�[�h��SSRP�l�b�g���[�N�ɎQ��������B�ȍ~SSRP_exec�ɂ�莩���ڑ�������
 * �s����悤�ɂȂ�B
 */
void SSRP_start();

/**
 * @brief �ڑ��I��
 *
 * ���m�[�h��SSRP�l�b�g���[�N����E�ނ�����B�ȍ~��SSRP_exec�̓p�P�b�g
 * ���[�e�B���O�����݂̂ƂȂ�B
 */
void SSRP_end();

/**
 * @brief �ėp�p�P�b�g���M
 *
 * �w�b�_���w�肵�ăp�P�b�g�𑗐M����B�񓯊����M�̏ꍇ�A�y�C���[�h���w��T�C�Y
 * ������؂�Ȃ����Ƃ����邪�A���̏ꍇ���ȍ~���g�����U�N�V�����͌p�����Ă���A
 * �w�肷��data�|�C���^�̈ʒu��ς���Α�������f�[�^�𑗂邱�Ƃ��ł���B
 * ���M����߂ăg�����U�N�V���������Z�b�g����ꍇ��SSRP_shutdown���g�p����B
 *
 * @param[in] header ���M����w�b�_�ւ̃|�C���^
 * @param[in] data ���M����f�[�^�y�C���[�h�ւ̃|�C���^
 * @param[in] len ���M����f�[�^�̃T�C�Y
 * @param[in] sync _TRUE:�������M _FALSE:�񓯊����M
 *
 * @retval ���̒l ���M���������f�[�^�T�C�Y
 * @retval ���̒l ���M�G���[
 */
_SINT SSRP_send(SSRP_Header* header, const _UBYTE* data, _UBYTE len, _BOOL sync);

/**
 * @brief �p�P�b�g���M
 *
 * �p�����[�^���w�肵�ăp�P�b�g�𑗐M����B�����I�Ɏ��m�[�h����̑��M�p�P�b�g
 * �ƂȂ�B����ȊO�̓�����SSRP_send�Ɠ����B
 *
 * @param[in] to ���M��A�h���X
 * @param[in] cmd �R�}���h
 * @param[in] flg �t���O
 * @param[in] data �f�[�^�y�C���[�h�̐擪�ւ̃|�C���^
 * @param[in] len ���M����f�[�^�T�C�Y
 * @param[out] trx_id �g�����U�N�V����ID��ۑ�����̈�ւ̃|�C���^�BNULL�Ȃ�
 * ���������
 * @param[in] sync _TRUE:�������M _FALSE:�񓯊����M
 *
 * @retval ���̒l ���M���������f�[�^�T�C�Y
 * @retval ���̒l ���M�G���[
 */
_SINT SSRP_sendto(SSRP_Address to, SSRP_Command cmd, SSRP_Flag flg,
                  const _UBYTE* data, _UBYTE len,
                  SSRP_TransactionId* trx_id, _BOOL sync);

/**
 * @brief �p�P�b�g��M
 *
 * ���ݓ����ŕێ�����Ă���p�P�b�g�f�[�^���擾����B���ۂ̃p�P�b�g��M��
 * SSRP_exec�ɂ����s����1�p�P�b�g���̃w�b�_�ƃf�[�^���ێ�����Ă��邽�߁A
 * ����͂������擾���邾����API�ł���B����ău���b�N�͂��Ȃ��B
 * �܂��A�擾�ł���͎̂��m�[�h�����u���[�h�L���X�g�p�P�b�g�݂̂ł���B
 *
 * @param[out] header_p ��M�p�P�b�g�̃w�b�_�|�C���^���i�[����|�C���^
 * @param[out] data_p ��M�p�P�b�g�̃f�[�^�y�C���[�h�|�C���^���i�[����|�C���^
 *
 * @retval ���̒l ��M�p�P�b�g�̃f�[�^�y�C���[�h�T�C�Y
 * @retval ���̒l ��M�p�P�b�g����
 */
_SINT SSRP_recvfrom(SSRP_Header** header_p, _UBYTE** data_p);

/**
 * @brief ����M�g�����U�N�V���������Z�b�g
 *
 * ���ݏ������̃g�����U�N�V���������Z�b�g���Ė����M/����M��Ԃ֖߂��B
 *
 * @param[in] tr ���Z�b�g����g�����U�N�V�����̎��
 */
void SSRP_shutdown(SSRP_Transaction tr);

/**
 * @brief �m�[�h�A�h���X�擾
 *
 * �l�b�g���[�N�ɎQ�����Ă���m�[�h�̃A�h���X���擾����B
 *
 * @param[in] idx �擾����m�[�h�̃C���f�b�N�X
 *
 * @return �m�[�h�̃A�h���X
 */
SSRP_Address SSRP_getNode(_UBYTE idx);

/**
 * @brief �ڑ���m�[�h�A�h���X�擾
 *
 * �ڑ�����Ă���m�[�h�̃A�h���X��ڑ���ʂɎ擾����B
 *
 * @param[in] con �擾����m�[�h�̐ڑ����
 *
 * @return �m�[�h�̃A�h���X
 */
SSRP_Address SSRP_getPear(SSRP_Connection con);

/**
 * @brief �l�b�g���[�N�̃m�[�h�����擾����
 *
 * SSRP�l�b�g���[�N�ɎQ�����Ă���m�[�h�̑������擾����B���m�[�h���܂ށB
 *
 * @return �m�[�h����
 */
_UBYTE SSRP_getTotalPear();

/**
 * @brief ����M�\��Ԃ̔���
 *
 * SSRP�͍ŏ��ɑ��m�[�h�Ƃ̃R�l�N�V�����𒣂邪�A���̏������������Ȃ���
 * ����M�����͍s���Ȃ����߁A���̏�Ԕ���Ɏg�p����B
 *
 * @retval _TRUE �ڑ��ς݁B����M�\
 * @retval _FALSE ���ڑ��B����M�s��
 */
_BOOL SSRP_ready();

/**
 * @brief ��������̎��s
 *
 * �ڑ�������p�P�b�g�����[�A�p�P�b�g��M�Ȃǂ��s���B����API�����I�Ɏ��s
 * ���邱�Ƃ�SSRP���쓮����BSSRP_start�������s�̏ꍇ�̓p�P�b�g�����[�݂̂�
 * �s����B
 */
void SSRP_exec();


#ifdef __cplusplus
}
#endif

#endif /* SSRP_H_ */
