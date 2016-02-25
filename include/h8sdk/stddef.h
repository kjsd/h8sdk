/**
 * @file stddef.h
 *
 * @brief 共通型、リテラル定義
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
/**
 * @mainpage はじめに
 *
 * @section abstract この文書について
 * この文書は、H8 Software Development Kit(以下H8SDK)のインタフェース
 * 仕様書である。@n
 * 文書は大きくデータ構造の解説セクションと、ファイルモジュール別のイ
 * ンタフェース解説セクションに分かれており、それぞれのセクションは冒
 * 頭で解説項目を概略説明付きで列挙した後、項目の詳細説明が続くという
 * 構成になっている。
 *
 * @section target 対象
 * H8SDKを使用してH8ボード上アプリケーションの作成を行う開発者向けの文
 * 書であり、H8プラットフォームのハードウェア仕様を理解していることが
 * 前提である。
 *
 * @section namespace 名前空間
 * H8SDKは、以下の規則に基づいて名前空間が規定されている。
 * @li '_'で始まる名前空間
 * @li stddef.h、stdlib.h、stdio.h、assert.h以外のモジュールに
 * おいて、モジュール名として使われている3文字～で始まる名前空間
 *
 * @attention 規則外のシンボルも一部存在する
 *
 ***********************************************************************/
#ifndef _STDDEF_H_
#define _STDDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/** 符号あり8ビット整数型 */
typedef signed char _SBYTE;
/** 符号なし8ビット整数型 */
typedef unsigned char _UBYTE;
/** 符号あり16ビット整数型 */
typedef signed short _SWORD;
/** 符号なし16ビット整数型 */
typedef unsigned short _UWORD;
/** 符号あり16ビット整数型 */
typedef signed int _SINT;
/** 符号なし16ビット整数型 */
typedef unsigned int _UINT;
/** 符号あり32ビット整数型 */
typedef signed long _SDWORD;
/** 符号なし32ビット整数型 */
typedef unsigned long _UDWORD;

/**
 * @brief ブール型
 *
 * 2値判定用ブール型。この型同士での評価以外には使用してはならない。
 */
typedef enum
{
    _FALSE = 0,
    /**< 偽 */
    _TRUE = ~_FALSE
    /**< 真 */
} _BOOL;

/**
 * @brief 配列の要素数取得
 *
 * @param[in] x 取得する配列名
 *
 * @return 配列の要素数
 */
#define _sizeof_array(x) (sizeof(x)/sizeof(x[0]))

/**
 * @brief 構造体メンバの要素へのオフセットを取得
 *
 * @param[in] type memberの構造体型タイプ
 * @param[in] member オフセットを取得するメンバ名
 *
 * @return memberまでのオフセット
 */
#define _offsetof(type, member) ((_UWORD)&((type*)0)->(member))


#ifdef __cplusplus
}
#endif

#endif /* _STDDEF_H_ */
