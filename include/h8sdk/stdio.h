/**
 * @file stdio.h
 *
 * @brief I/Oユーティリティライブラリ
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
#ifndef _STDIO_H_
#define _STDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ifstub.h"

/** 標準出力ポート。デフォルトはシリアルポート */
extern IFSTUB_Type _STDOUT;
/** 標準入力ポート。デフォルトはシリアルポート */
extern IFSTUB_Type _STDIN;
/** 標準エラー出力ポート。デフォルトはシリアルポート */
extern IFSTUB_Type _STDERR;

/**
 * @brief 書式付き文字出力
 *
 * 指定フォーマットのパターンに従って文字列を
 * 呼び出し前にシリアルドライバモジュールが初期化されている必要がある。
 *
 * @param[in] format 出力書式。使用できる変換形式は "%d"(符号あり10進
 * 数値), "%u"(符号なし10進数値), "%x"(16進数値), "%o"(8進数値),
 * "%s"(文字列)のみ。"%"を出力するときは "%%" と記述する。
 * @param[in] ... 出力パラメータ列
 *
 * @see sci.h
 */
void _printf(const _SBYTE* format, ...);

#ifdef NDEBUG
#define _dprintf(x)
#else

#if __STDC_VERSION__ == 199901L
#define _dprintf(...) _printf(__VA_ARGS__)
#else
/**
 * @brief デバッグ用文字列出力
 *
 * @param[in] x 出力書式とパラメータ。必ず括弧付きで呼び出すこと。@n
 * e.g. _dprintf(("aaa = %d\n", aaa));
 */
#define _dprintf(x) (_printf x)
#endif

#endif /* NDEBUG */

#ifdef __cplusplus
}
#endif

#endif /* _STDIO_H_ */
