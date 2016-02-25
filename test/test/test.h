/**
 * @file test.h
 *
 * @brief H8SDK���j�b�g�e�X�g���W���[��
 *
 * H8SDK�C���^�t�F�[�X�̃e�X�g���s���B���s����O��H8���PC���V���A��
 * �|�[�g�Őڑ����A�V���A���o�͂�PC���烂�j�^�����O���邱�ƁB�ڑ��ݒ�
 * ��SCI_init���Q�ƁB@n
 * �e�X�g�ΏۂƂȂ郂�W���[���̓R���p�C���X�C�b�`�ɂ���Č��肷��B�}
 * �N����`�͈ȉ��B
 *
 * @li @p TEST_ASSERT assert.h�̃e�X�g��L��
 * @li @p TEST_STDC stdio.h, stdlib.h, string.h �̃e�X�g��L��
 * @li @p TEST_LCD lcd.h�̃e�X�g��L��
 * @li @p TEST_PUSH_SWITCH push_switch.h�̃e�X�g��L��
 * @li @p TEST_ADC adc.h�̃e�X�g��L��
 * @li @p TEST_PS2 ps2.h�̃e�X�g��L��
 * @li @p TEST_SOUND sound.h�̃e�X�g��L��
 * @li @p TEST_MUSIC music.h�̃e�X�g��L��
 * @li @p TEST_SSRP ssrp.h�̃e�X�g��L��
 *
 * @note
 * @li music.h�̃e�X�g������Ƃ���USE_MUSIC_RECORD�Assrp.h�̃e�X�g����
 * ��Ƃ���USE_LOOPBACK_SSRP��define���ăR���p�C������H8SDK��p�ӂ���
 * ���ƁB
 * @li PS/2�h���C�o���e�X�g����Ƃ��͊����E8a�G�~�����[�^���O�����ƁB
 * @li assert���W���[�����e�X�g����Ƃ��͑��̃h���C�o�ƃ��W���[���̃e
 * �X�g�͍s��ꂸ�A�m�F���@���f�o�b�K(HEW�Ȃ�)���g�������Ȃ��B
 * @li �S�Ẵ��W���[�����e�X�g���邱�Ƃ̓������e�ʏ�ł��Ȃ��̂ŁA�e
 * �X�g�Ώۂł͂Ȃ����W���[����h8sdk.lib����O���Ă����B
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
#ifndef TEST_H_
#define TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <h8sdk/unit_test.h>

#if defined(TEST_SOUND) || defined(TEST_MUSIC)
#if SOUND_MAX_PRONOUNCE < 3
#error "Please define the SOUND_MAX_PRONOUNCE >= 3."
#endif
#endif

#define TEST_FAILURE(x) _printf("*** Failed: %s\r\n", (x));

/** ���[�U�[�G���g���֐� */
void main(void);

/** 
 * @brief �V���A���h���C�o�e�X�g
 *
 * @par �e�X�g����
 * @li ����������������Ă���
 * @li NUL�I�[������𑗐M�ł���B�܂��A�Ԃ�l�͑��M�������ɂȂ��Ă���
 * @li �o�C�g�X�g���[���𑗐M�ł���B�܂��A�Ԃ�l�͑��M�f�[�^���ɂȂ�
 * �Ă���
 * @li �o�C�g�X�g���[������M�ł���B�܂��A�Ԃ�l�͎�M�f�[�^���ɂȂ�
 * �Ă���
 * @li �񓯊��f�[�^���M���@�\����
 * @li �񓯊��f�[�^��M���@�\����
 * 
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/sci.h
 */
static char* test_sci();

/** 
 * @brief stdio���W���[���e�X�g
 *
 * @par �e�X�g����
 * @li �Œ蕶������o�͂ł���
 * @li �����L��10�i���l���o�͂ł���
 * @li �����Ȃ�10�i���l���o�͂ł���
 * @li �����Ȃ�16�i���l���o�͂ł���
 * @li �����Ȃ�8�i���l���o�͂ł���
 * @li '%'���o�͂ł���
 * @li ��L�S�Ă��܂ޕ�������o�͂ł���
 * 
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/stdio.h
 */
static char* test_stdio();

/** 
 * @brief stdlib���W���[���e�X�g
 *
 * @par �e�X�g����
 * @li 1�b�̃X���[�v�@�\�����삷��B�ڎ��m�F�B
 * @li ���̃����O�o�b�t�@�̃C���f�b�N�X�l���擾�ł���B�܂��A�ő�l��
 * ����0���Ԃ�B
 * @li �O�̃����O�o�b�t�@�̃C���f�b�N�X�l���擾�ł��邩�B�܂��A0�̎���
 * �ő�l���Ԃ�B
 * @li size=�f���ŁAsize�����̃L�[��^�����Ƃ��̃n�b�V���l�͈�ӓI
 * @li �`�F�b�N�T���l���������v�Z�ł���
 * @li 16bit���l��10�i������ɕϊ��ł���
 * @li 16bit���l��16�i������ɕϊ��ł���
 * @li 16bit���l��8�i������ɕϊ��ł���
 * @li �����l���擾�ł���B
 * @li ���ς���Ɨ����l���ω�����
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/stdlib.h
 */
static char* test_stdlib();

/** 
 * @brief string���W���[���e�X�g
 *
 * @par �e�X�g����
 * @li ������̒������擾�ł���B�I�[�����͊܂܂Ȃ��B
 * @li �l���������������Z�b�g�ł���
 * @li �l���������������R�s�[�ł���
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/string.h
 */
static char* test_string();

/** 
 * @brief assert���W���[���e�X�g
 *
 * @par �e�X�g����
 * @li �^�l��^�����ꍇ�̓X���[����
 * @li �U�l��^�����ꍇ�͏�������~����
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/assert.h
 */
static char* test_assert();

/** 
 * @brief IOCTL�h���C�o�e�X�g
 *
 * @par �e�X�g����
 * @li �������Ń��W�X�^�l��0�N���A�����
 * @li �Z�b�g�����l�𐳂����擾�ł���
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/ioctl.h
 */
static char* test_ioctl();

/** 
 * @brief LED�h���C�o�e�X�g
 *
 * @par �e�X�g����
 * @li �������őSLED�|�[�g�̃r�b�g������(OFF)
 * @li LED�ʂɓ_���ł���
 * @li LED�ʂɏ����ł���
 * @li LED�ʂɓ_����Ԃ𔽓]�ł���
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/led.h
 */
static char* test_led();

/** 
 * @brief LCD�h���C�o�e�X�g
 *
 * @par �e�X�g����
 * @li ��������LCD�f�[�^�͑S��0x20(��)�ɂȂ�
 * @li �J�[�\�����݈ʒu��ݒ�/�擾�ł���
 * @li NUL�I�[��������o�͂ł���B���̍ő啝���z�����ꍇ�͎������s����
 * ��B
 * @li ���݂�LCD�\���f�[�^�𐳂����擾�ł���
 * @li �o�C�g�X�g���[���f�[�^���o�͂ł���
 * @li �ݒ�ő�l�܂ł̃��[�U�[�����f�[�^��o�^�ł���
 * @li ���[�U�[�����f�[�^���o�͂ł���
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/lcd.h
 */
static char* test_lcd();

/** 
 * @brief �v�b�V���X�C�b�`�h���C�o�e�X�g
 *
 * @par �e�X�g����
 * @li ���������������s����
 * @li �u�Ԃ̉�����Ԃ��擾�ł��A�`���^�����O�h�~�ł��Ă���
 * @li �������Ɉ�x������Ԃ��擾�ł���B
 * @li �������Ɉ��Ԋu�ŏ�Ԃ��擾�ł���B
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/push_switch.h
 */
static char* test_push_switch();

/** 
 * @brief A/D�R���o�[�^�h���C�o�e�X�g
 *
 * @par �e�X�g����
 * @li ���������������s����
 * @li �����̃|�[�g����̓f�[�^�擾�ł��Ȃ�
 * @li �ϊ��X�^�[�g���Ă��Ȃ��ƃf�[�^�擾�ł��Ȃ�
 * @li �m�[�}�����[�h�őS�|�[�g�̍ŏ��l/�ő�l���擾�ł���
 * @li �X�L�������[�h�őS�|�[�g�̍ŏ��l/�ő�l���擾�ł���
 * @li �m�[�}�����[�h�̏ꍇ�̓X�^�[�g���x�f�[�^���擾����Ƃ��̌��
 * ������x�X�^�[�g����܂Ńf�[�^�擾�ł��Ȃ�
 * @li �X�L�������[�h�̏ꍇ�͈�x�X�^�[�g����Ɩ����I�ɃX�g�b�v�����
 * �Ńf�[�^���擾�ł���
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/adc.h
 */
static char* test_adc();

/** 
 * @brief PS/2�h���C�o�e�X�g
 *
 * @par �e�X�g����
 * @li ���������������s����
 * @li PS/2�L�[�{�[�h �X�L�����R�[�h�Z�b�g2�̃f�[�^���擾�ł���
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/ps2.h
 */
static char* test_ps2();

/** 
 * @brief �T�E���h�h���C�o�e�X�g
 *
 * @par �e�X�g����
 * @li ���������������s����
 * @li ���o�[�u�A���[�v�Ȃ��̒P�����Đ��ł���
 * @li �����~�ł���
 * @li ���o�[�u����A���[�v�Ȃ��̒P�����Đ��ł���
 * @li ���o�[�u����A���[�v����̒P�����Đ��ł���
 * @li 3�a�����Đ��ł���
 * @li �{�����[�����߂��ł���
 * @li �P�����t�Đ��ł���
 * @li �a�����t�Đ��ł���
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/sound.h
 */
static char* test_sound();

/** 
 * @brief �y�ȉ��t���W���[���e�X�g
 *
 * @par �e�X�g����
 * @li ���������������s����
 * @li �y�ȓo�^���ł���
 * @li �o�^�ς݂̊y�Ȃ��擾�ł���
 * @li �V���O���p�[�g�̊y�Ȃ��Đ��ł���
 * @li �Đ��㎩���I�ɃX�g�b�v��ԂɂȂ�B
 * @li �}���`�p�[�g�̊y�Ȃ��Đ��ł���
 * @li �y�Ȃ��t�Đ��ł���
 * @li �P����^���ł���
 * @li �a����^���ł���
 * @li �^�����ꂽ�y�Ȃ��Đ��ł���
 * @li �^�����ꂽ�y�Ȃ��t�Đ��ł���
 * @li �y�ȍĐ����Ɉꎞ��~�ł���
 * @li �y�Ȃ̃��[�v�Đ����ł���
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/music.h
 */
static char* test_music();

/** 
 * @brief SSRP���W���[���e�X�g
 *
 * @par �e�X�g����
 * @li ��������A���m�[�h�A�h���X�̐��l�����񂪐ݒ肳��Ă���
 * @li �ڑ��X�^�[�g�O�͐ڑ����[��
 * @li �ڑ��X�^�[�g�O�͐ڑ��m�[�h�Ȃ�
 * @li �ڑ��X�^�[�g�O�͑��M�������ł��Ă��Ȃ�
 * @li �ڑ��X�^�[�g��A10���J�E���g�Ńe�X�g�m�[�h�Ƃ̐ڑ�����������
 * @li ���̂Ƃ��A�ڑ������������擾�ł���
 * @li ���̂Ƃ��A�ڑ��m�[�h�A�h���X���������擾�ł���
 * @li �p�����[�^���w�肵�ăp�P�b�g���M���ł���B�Ԃ�l�͑��M�y�C���[
 * �h�T�C�Y�ƈ�v����
 * @li �p�P�b�g�w�b�_���w�肵�ăp�P�b�g���M���ł���B�Ԃ�l�͑��M�y�C���[
 * �h�T�C�Y�ƈ�v����
 * @li �p�P�b�g����M�ł���
 * @li �ڑ��I����͐ڑ����[��
 * @li �ڑ��I����͐ڑ��m�[�h�Ȃ�
 * @li �ڑ��I����͑��M�������ł��Ă��Ȃ�
 *
 * @retval 0 �e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 *
 * @see h8sdk/ssrp.h
 */
static char* test_ssrp();

/** 
 * @brief �e�X�g���s
 *
 * @param[in] test_list �e�X�g����֐����X�g
 * @param[in] num �e�X�g�֐��̌�
 *
 * @retval 0 �S�e�X�g����
 * @retval 0�ȊO �e�X�g���s�B�G���[���b�Z�[�W
 */
static char* test_run(const UTEST_Func* test_list, _UWORD num);

static const UTEST_Func test_basic_drivers_[] = {
    test_ioctl,
    test_led,
    test_sci
};

static const UTEST_Func test_drivers_[] = {
#ifdef TEST_ASSERT
    test_assert,
#endif /* TEST_ASSERT */
#ifdef TEST_STDC
    test_stdio,
    test_stdlib,
    test_string,
#endif /* TEST_STDC */
#ifdef TEST_LCD
    test_lcd,
#endif /* TEST_PS2 */
#ifdef TEST_PUSH_SWITCH
    test_push_switch,
#endif /* TEST_PUSH_SWITCH */
#ifdef TEST_ADC
    test_adc,
#endif /* TEST_ADC */
#ifdef TEST_PS2
    test_ps2,
#endif /* TEST_PS2 */
#ifdef TEST_SOUND
    test_sound
#endif /* TEST_SOUND */
};

static const UTEST_Func test_modules_[] = {
#ifdef TEST_MUSIC
    test_music,
#endif /* TEST_MUSIC */
#ifdef TEST_SSRP
    test_ssrp
#endif /* TEST_SSRP */
};


#ifdef __cplusplus
}
#endif

#endif /* TEST_H_ */
