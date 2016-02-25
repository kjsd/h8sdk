/**
 * @file unit_test.h
 *
 * @brief ユニットテストモジュール
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
#ifndef UTEST_H_
#define UTEST_H_

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @brief テスト関数型
 *
 * UTEST_runに与えるテスト関数の型
 */
typedef char* (*UTEST_Func)();

/** 
 * @brief テスト回数パラメータ
 *
 * UTEST_runを実行する度にカウントアップする。テストモジュール本体で実
 * 装しておく。
 */
extern int UTEST_run_count;

/** 
 * @brief 条件評価
 *
 * 指定された条件を評価し、偽ならば指定文字列を返して呼び出し元関数を
 * 抜ける。
 *
 * @param[in] message 評価が偽のときのメッセージ
 * @param[in] test 評価式
 */
#define UTEST_assert(message, test)                 \
    do { if (!(test)) return message; } while (0)

/** 
 * @brief テスト関数実行
 *
 * 指定されたテスト関数を実行し、失敗した場合はメッセージを返して呼び
 * 出し元関数を抜ける。
 *
 * @param[in] test 実行するテスト関数へのポインタ
 */
#define UTEST_run(test)                             \
    do {                                            \
        char *message = (test)();                   \
        UTEST_run_count++;                          \
        if (message) return message;                \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* UTEST_H_ */
