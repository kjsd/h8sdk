/**
 * @file string.h
 *
 * @brief 文字列操作ユーティリティライブラリ
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
#ifndef _STRING_H_
#define _STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/**
 * @brief 文字列長取得
 *
 * 指定文字列先頭からNUL'\0'文字までの数を返す。NULは含まない。
 *
 * @param[in] str 長さを取得する文字列先頭へのポインタ
 *
 * @return 文字列長
 */
_UWORD _strlen(const _SBYTE* str);

/**
 * @brief メモリ領域コピー
 *
 * メモリ領域を指定バイト分コピーする。領域は重なってはならない。
 *
 * @param[in] dst コピー先へのポインタ
 * @param[in] src コピー元へのポインタ
 * @param[in] size コピーバイト数
 *
 * @return dstへのポインタ
 */
void* _memcpy(void* dst, const void* src, _UWORD size);

/**
 * @brief メモリ領域セット
 *
 * メモリ領域に指定値をセットする。
 *
 * @param[in] dst セット先へのポインタ
 * @param[in] c セットする値
 * @param[in] size セットするバイト数
 *
 * @return dstへのポインタ
 */
void* _memset(void* dst, _SINT c, _UWORD size);

#ifdef __cplusplus
}
#endif

#endif /* _STRING_H_ */
