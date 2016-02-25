/**
 * @file test.h
 *
 * @brief H8SDKユニットテストモジュール
 *
 * H8SDKインタフェースのテストを行う。実行する前にH8基板とPCをシリアル
 * ポートで接続し、シリアル出力をPCからモニタリングすること。接続設定
 * はSCI_initを参照。@n
 * テスト対象となるモジュールはコンパイルスイッチによって決定する。マ
 * クロ定義は以下。
 *
 * @li @p TEST_ASSERT assert.hのテストを有効
 * @li @p TEST_STDC stdio.h, stdlib.h, string.h のテストを有効
 * @li @p TEST_LCD lcd.hのテストを有効
 * @li @p TEST_PUSH_SWITCH push_switch.hのテストを有効
 * @li @p TEST_ADC adc.hのテストを有効
 * @li @p TEST_PS2 ps2.hのテストを有効
 * @li @p TEST_SOUND sound.hのテストを有効
 * @li @p TEST_MUSIC music.hのテストを有効
 * @li @p TEST_SSRP ssrp.hのテストを有効
 *
 * @note
 * @li music.hのテストをするときはUSE_MUSIC_RECORD、ssrp.hのテストをす
 * るときはUSE_LOOPBACK_SSRPをdefineしてコンパイルしたH8SDKを用意する
 * こと。
 * @li PS/2ドライバをテストするときは基板からE8aエミュレータを外すこと。
 * @li assertモジュールをテストするときは他のドライバとモジュールのテ
 * ストは行われず、確認方法もデバッガ(HEWなど)を使うしかない。
 * @li 全てのモジュールをテストすることはメモリ容量上できないので、テ
 * スト対象ではないモジュールはh8sdk.libから外しておく。
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

/** ユーザーエントリ関数 */
void main(void);

/** 
 * @brief シルアルドライバテスト
 *
 * @par テスト項目
 * @li 正しく初期化されている
 * @li NUL終端文字列を送信できる。また、返り値は送信文字数になっている
 * @li バイトストリームを送信できる。また、返り値は送信データ数になっ
 * ている
 * @li バイトストリームを受信できる。また、返り値は受信データ数になっ
 * ている
 * @li 非同期データ送信が機能する
 * @li 非同期データ受信が機能する
 * 
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/sci.h
 */
static char* test_sci();

/** 
 * @brief stdioモジュールテスト
 *
 * @par テスト項目
 * @li 固定文字列を出力できる
 * @li 符号有り10進数値を出力できる
 * @li 符号なし10進数値を出力できる
 * @li 符号なし16進数値を出力できる
 * @li 符号なし8進数値を出力できる
 * @li '%'を出力できる
 * @li 上記全てを含む文字列を出力できる
 * 
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/stdio.h
 */
static char* test_stdio();

/** 
 * @brief stdlibモジュールテスト
 *
 * @par テスト項目
 * @li 1秒のスリープ機能が動作する。目視確認。
 * @li 次のリングバッファのインデックス値が取得できる。また、最大値の
 * 次は0が返る。
 * @li 前のリングバッファのインデックス値が取得できるか。また、0の次は
 * 最大値が返る。
 * @li size=素数で、size未満のキーを与えたときのハッシュ値は一意的
 * @li チェックサム値が正しく計算できる
 * @li 16bit数値を10進文字列に変換できる
 * @li 16bit数値を16進文字列に変換できる
 * @li 16bit数値を8進文字列に変換できる
 * @li 乱数値が取得できる。
 * @li 種を変えると乱数値が変化する
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/stdlib.h
 */
static char* test_stdlib();

/** 
 * @brief stringモジュールテスト
 *
 * @par テスト項目
 * @li 文字列の長さを取得できる。終端文字は含まない。
 * @li 値が正しくメモリセットできる
 * @li 値が正しくメモリコピーできる
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/string.h
 */
static char* test_string();

/** 
 * @brief assertモジュールテスト
 *
 * @par テスト項目
 * @li 真値を与えた場合はスルーする
 * @li 偽値を与えた場合は処理が停止する
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/assert.h
 */
static char* test_assert();

/** 
 * @brief IOCTLドライバテスト
 *
 * @par テスト項目
 * @li 初期化でレジスタ値が0クリアされる
 * @li セットした値を正しく取得できる
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/ioctl.h
 */
static char* test_ioctl();

/** 
 * @brief LEDドライバテスト
 *
 * @par テスト項目
 * @li 初期化で全LEDポートのビットが立つ(OFF)
 * @li LED別に点灯できる
 * @li LED別に消灯できる
 * @li LED別に点灯状態を反転できる
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/led.h
 */
static char* test_led();

/** 
 * @brief LCDドライバテスト
 *
 * @par テスト項目
 * @li 初期化後LCDデータは全て0x20(空白)になる
 * @li カーソル現在位置を設定/取得できる
 * @li NUL終端文字列を出力できる。横の最大幅を越えた場合は自動改行され
 * る。
 * @li 現在のLCD表示データを正しく取得できる
 * @li バイトストリームデータを出力できる
 * @li 設定最大値までのユーザー文字データを登録できる
 * @li ユーザー文字データを出力できる
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/lcd.h
 */
static char* test_lcd();

/** 
 * @brief プッシュスイッチドライバテスト
 *
 * @par テスト項目
 * @li 初期化が正しく行える
 * @li 瞬間の押下状態が取得でき、チャタリング防止できている
 * @li 押下時に一度だけ状態を取得できる。
 * @li 押下時に一定間隔で状態を取得できる。
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/push_switch.h
 */
static char* test_push_switch();

/** 
 * @brief A/Dコンバータドライバテスト
 *
 * @par テスト項目
 * @li 初期化が正しく行える
 * @li 無効のポートからはデータ取得できない
 * @li 変換スタートしていないとデータ取得できない
 * @li ノーマルモードで全ポートの最小値/最大値が取得できる
 * @li スキャンモードで全ポートの最小値/最大値が取得できる
 * @li ノーマルモードの場合はスタート後一度データを取得するとその後は
 * もう一度スタートするまでデータ取得できない
 * @li スキャンモードの場合は一度スタートすると明示的にストップするま
 * でデータが取得できる
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/adc.h
 */
static char* test_adc();

/** 
 * @brief PS/2ドライバテスト
 *
 * @par テスト項目
 * @li 初期化が正しく行える
 * @li PS/2キーボード スキャンコードセット2のデータを取得できる
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/ps2.h
 */
static char* test_ps2();

/** 
 * @brief サウンドドライバテスト
 *
 * @par テスト項目
 * @li 初期化が正しく行える
 * @li リバーブ、ループなしの単音を再生できる
 * @li 音を停止できる
 * @li リバーブあり、ループなしの単音を再生できる
 * @li リバーブあり、ループありの単音を再生できる
 * @li 3和音を再生できる
 * @li ボリューム調節ができる
 * @li 単音を逆再生できる
 * @li 和音を逆再生できる
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/sound.h
 */
static char* test_sound();

/** 
 * @brief 楽曲演奏モジュールテスト
 *
 * @par テスト項目
 * @li 初期化が正しく行える
 * @li 楽曲登録ができる
 * @li 登録済みの楽曲を取得できる
 * @li シングルパートの楽曲を再生できる
 * @li 再生後自動的にストップ状態になる。
 * @li マルチパートの楽曲を再生できる
 * @li 楽曲を逆再生できる
 * @li 単音を録音できる
 * @li 和音を録音できる
 * @li 録音された楽曲を再生できる
 * @li 録音された楽曲を逆再生できる
 * @li 楽曲再生中に一時停止できる
 * @li 楽曲のループ再生ができる
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/music.h
 */
static char* test_music();

/** 
 * @brief SSRPモジュールテスト
 *
 * @par テスト項目
 * @li 初期化後、自ノードアドレスの数値文字列が設定されている
 * @li 接続スタート前は接続数ゼロ
 * @li 接続スタート前は接続ノードなし
 * @li 接続スタート前は送信準備ができていない
 * @li 接続スタート後、10数カウントでテストノードとの接続が完了する
 * @li このとき、接続数が正しく取得できる
 * @li このとき、接続ノードアドレスが正しく取得できる
 * @li パラメータを指定してパケット送信ができる。返り値は送信ペイロー
 * ドサイズと一致する
 * @li パケットヘッダを指定してパケット送信ができる。返り値は送信ペイロー
 * ドサイズと一致する
 * @li パケットを受信できる
 * @li 接続終了後は接続数ゼロ
 * @li 接続終了後は接続ノードなし
 * @li 接続終了後は送信準備ができていない
 *
 * @retval 0 テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
 *
 * @see h8sdk/ssrp.h
 */
static char* test_ssrp();

/** 
 * @brief テスト実行
 *
 * @param[in] test_list テストする関数リスト
 * @param[in] num テスト関数の個数
 *
 * @retval 0 全テスト成功
 * @retval 0以外 テスト失敗。エラーメッセージ
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
