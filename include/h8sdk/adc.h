/**
 * @file adc.h
 *
 * @brief A/D�R���o�[�^�h���C�o
 *
 * ���̃��W���[����A/D�R���o�[�^�ւ̃C���^�t�F�[�X��񋟂���B@n
 * �������A�g�p�`���l���̐ݒ���s�����Ƃŕϊ��f�[�^���擾�ł���悤��
 * �Ȃ�B
 *
 * @see H83694�O���[�v_�n�[�h�E�F�A�}�j���A��.pdf 16��
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
#ifndef _ADC_H_
#define _ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"


/**
 * @brief �ݒ胂�[�h���ʎq
 */
typedef enum
{
    ADC_NORMAL = 0,
    /**< �m�[�}�����[�h */
    ADC_SCAN,
    /**< �X�L�������[�h */
    ADC_NUM_OF_MODE
    /**< ���[�h�� */
} ADC_Mode;

/**
 * @brief �`���l�����ʎq
 */
typedef enum
{
    ADC_AN0 = 0,
    /**< �`���l���|�[�gAN0 */
    ADC_AN1,
    /**< �`���l���|�[�gAN1 */
    ADC_AN2,
    /**< �`���l���|�[�gAN2 */
    ADC_AN3,
    /**< �`���l���|�[�gAN3 */
    ADC_NUM_OF_CHANNEL
    /**< �`���l���|�[�g�� */
} ADC_Channel;

/**
 * @brief A/D�R���o�[�^������
 *
 * A/D�R���o�[�^�������B��API�g�p�O�ɕK�����s����B
 *
 * @param[in] mode �g�p���郂�[�h�̎��
 * @param[in] interrupt _TRUE�F���荞�݂��g���B@n
 * _FALSE�F���荞�݂��g��Ȃ��B
 *
 * @note ���荞�݃n���h���͊O���Œ�`����B
 */
void ADC_init(ADC_Mode mode, _BOOL interrupt);

/**
 * @brief �`���l���L����
 *
 * �g�p����`���l����ݒ肷��B�m�[�}�����[�h���͎w��`���l���̂݁B�X
 * �L�������[�h���͎w��`���l�����Ⴂ�ԍ��̃`���l���͑S�Ďg�p�\��
 * �Z�b�g�����B�Ⴆ�΁AADC_AN2 ��^�����ꍇ AN0�`AN2�̃`���l�����L��
 * �ɂȂ�B
 *
 * @param[in] ch �L���ɂ���`���l��
 *
 * @see ADC_disable
 */
void ADC_enable(ADC_Channel ch);

/**
 * @brief �`���l��������
 *
 * �g�p��~����`���l����ݒ肷��B�m�[�}�����[�h���͎w��`���l���̂݁B
 * �w��`���l�����Ⴂ�ԍ��̃`���l���͑S�Ďg�p�s�ɃZ�b�g�����B��
 * ���΁AADC_AN2 ��^�����ꍇ AN0�`AN2�̃`���l���������ɂȂ�B
 *
 * @param[in] ch �����ɂ���`���l��
 *
 * @see ADC_enable
 */
void ADC_disable(ADC_Channel ch);

/**
 * @brief A/D�ϊ��J�n
 *
 * A/D�ϊ����J�n�����B�X�L�������[�h���͕ϊ��f�[�^�������擾�ł����
 * ���ɂȂ�B�m�[�}�����[�h���͈��̂݁B
 *
 * @see ADC_stop
 */
void ADC_start();

/**
 * @brief A/D�ϊ���~
 *
 * A/D�ϊ�����~�����B�ȍ~�ϊ��f�[�^�͎擾�ł��Ȃ��B
 *
 * @see ADC_start
 */
void ADC_stop();

/**
 * @brief A/D�ϊ��f�[�^���擾����
 *
 * A/D�ϊ��f�[�^���擾����B�ǂݍ��ރ`���l�����S�Ċ��������Ƃ��͕K����
 * ��last��_TRUE���Z�b�g���Ď��s����B
 *
 * @param[in] anx �f�[�^���擾����`���l��
 * @param[in] last ���̎擾�ō���̕ϊ��f�[�^��S�`���l���Ŕj�����邩�ǂ���
 *
 * @retval ���̒l �ϊ������f�[�^�B�L���l��10bit
 * @retval -1 �ϊ�����������
 */
_SDWORD ADC_get(ADC_Channel anx, _BOOL last);

#ifdef __cplusplus
}
#endif

#endif /* _ADC_H_ */
