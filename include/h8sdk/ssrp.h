/**
 * @file ssrp.h
 *
 * @brief SSRP通信プロトコル
 *
 * このモジュールは、一方通行のリング型ネットワーク上での通信プロトコル
 * SSRP(Simple Single Ring Protocol)のシンプルな実装パターンである。
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
 * @brief 接続ノード最大数
 */
#define SSRP_MAX_NODE 16

/**
 * @brief 最大送受信データサイズ
 *
 * パケットのペイロード最大値
 */
#define SSRP_MAX_DATA 255
/**
 * @brief 無効なアドレス
 */
#define SSRP_ADDR_INVALID 0
/**
 * @brief ブロードキャストアドレス
 */
#define SSRP_ADDR_BROADCAST 0xff
/**
 * @brief 受信タイムアウト値
 */
#define SSRP_TMO_RECV 255
/**
 * @brief 送信タイムアウト値
 */
#define SSRP_TMO_SEND -1

/**
 * @brief LOOPコマンド値
 *
 * ネットワーク接続ノードをカウントするコマンド
 */
#define SSRP_CMD_LOOP 0x00

/**
 * @brief JOINコマンド値
 *
 * ネットワークへ参加するコマンド
 */
#define SSRP_CMD_JOIN 0x01

/**
 * @brief LEAVEコマンド値
 *
 * ネットワークから離脱するコマンド
 */
#define SSRP_CMD_LEAVE 0x02

/**
 * @brief プリアンブル値
 *
 * パケット送信前に付加するプリアンブル値
 */
#define SSRP_VAL_PREAMBLE 0xaa

/**
 * @brief 定期処理の送信間隔
 *
 * JOIN、LOOPなど、定期処理時の送信間隔
 */
#define SSRP_PACKET_SPC (1U << 8)

/**
 * @brief アドレス型定義
 */
typedef _UBYTE SSRP_Address;

/**
 * @brief 自ノードアドレス文字列
 *
 * SSRP_Addrの値が2桁の16進数字列で設定される。
 */
extern _SBYTE SSRP_my_addr[];

/**
 * @brief コマンド型定義
 *
 * このコマンドによって他ノードとデータの連携を取る。
 * 0x00～0x7fまでは内部用に予約されている。外部モジュールから送信するパケット
 * のコマンド値はSSRP_CMD_EXとORを取らなければならない。
 */
typedef _UBYTE SSRP_Command;
/**
 * @brief 外部モジュール用コマンドマスク
 */
#define SSRP_CMD_EX 0x80
/**
 * @brief 無効なコマンド値
 */
#define SSRP_CMD_INVALID 0xff

/**
 * @brief フラグ定義型
 *
 * パケットの属性を表すフラグ型。このフラグにより、リクエスト/レスポンス/
 * イベントかどうかの判定を行う。
 */
typedef _UBYTE SSRP_Flag;
/**
 * @brief イベントフラグ値
 *
 * このフラグが設定されたパケットは通知のみのイベントである。
 */
#define SSRP_FLG_EVT 0x00
/**
 * @brief リクエストフラグ値
 *
 * このフラグが設定されたパケットはレスポンスが必要なリクエストである。
 */
#define SSRP_FLG_REQ 0x01
/**
 * @brief リクエストフラグ値
 *
 * このフラグが設定されたパケットはリクエストに対するレスポンスである。
 */
#define SSRP_FLG_RES 0x02
/**
 * @brief 無効なフラグ値
 */
#define SSRP_FLG_INVALID 0xff

/**
 * @brief トランザクションタイプ識別子
 */
typedef enum
{
    SSRP_TRX_RECV = 0,
    /**< 受信タイプ */
    SSRP_TRX_SEND,
    /**< 送信タイプ */

    SSRP_NUM_OF_TRX
    /**< トランザクションタイプの数 */
} SSRP_Transaction;    

/**
 * @brief トランザクションIDの定義型
 *
 * トランザクションを識別するためのID。自ノードからパケットを発信する毎に
 * インクリメントされる送信カウンタ。パケットヘッダに毎回設定される。
 */
typedef _UWORD SSRP_TransactionId;
/**
 * @brief 無効なトランザクションID
 */
#define SSRP_TRXID_INVALID ((1U << (sizeof(SSRP_TransactionId) << 3)) - 1)

/**
 * @brief SSRPパケットヘッダ
 *
 * SSRPパケットの情報を表すヘッダ。パケットはこのヘッダとデータのペイロード
 * から構成される。ヘッダのチェックサムは毎回SSRP内部でチェックされ、不一致
 * のパケットは受信しても破棄されるが、ペイロード部分の有効性に関しては
 * SSRP内部では関知しない。
 */
typedef struct
{
    SSRP_Address from;
    /**< 送信先アドレス */
    SSRP_Address to;
    /**< 送信元アドレス */
    SSRP_Command command;
    /**< コマンド */
    SSRP_Flag flag;
    /**< パケットフラグ */
    _UBYTE hop;
    /**<
     * @brief ホップ数
     *
     * 各ノードによりパケットがリレーされるとこの値がインクリメントされる
     */
    _UBYTE data_length;
    /**< データペイロード長 */
    SSRP_TransactionId trx_id;
    /**< トランザクションID */
    _UWORD cksum;
    /**< ヘッダのチェックサム */
} SSRP_Header;

/**
 * @brief コネクション種別定義型
 *
 * SSRPはリングプロトコルなので接続は前と後の二つ。
 */
typedef enum
{
    SSRP_CON_FRONT = 0,
    /**< 前への接続 */
    SSRP_CON_BACK,
    /**< 後への接続 */

    SSRP_NUM_OF_CON
    /**< 接続種別の数 */
} SSRP_Connection;

/**
 * @brief コマンド/フラグ一致判定
 *
 * ヘッダのコマンドエリアとフラグエリアが指定されたものと同じかどうかの
 * 判定を行う
 *
 * @param[in] hp 比較元ヘッダへのポインタ
 * @param[in] com 判定するコマンド値
 * @param[in] flg 判定するフラグ値
 *
 * @return コマンド/フラグ両方一致していれば正の値。そうでなければ0
 */
#define SSRP_COMMAND_EQ(hp, com, flg)                       \
    (((hp)->command == (com)) && ((hp)->flag ==  (flg)))
    
/**
 * @brief パケット無効化
 *
 * 指定されたヘッダのパケットを初期化して無効とする。
 *
 * @param[in] hp 無効化するヘッダへのポインタ
 */
#define SSRP_INVALIDATE_PACKET(hp)                              \
    ((hp)->from = SSRP_ADDR_INVALID, (hp)->to = SSRP_ADDR_INVALID)

/**
 * @brief パケット無効判定
 *
 * 指定されたヘッダのパケットが無効なものかどうかを判定する
 *
 * @param[in] hp 判定するヘッダへのポインタ
 *
 * @return 無効化されたパケットならば正の値。そうでなければ0
 */
#define SSRP_IS_INVALID_PACKET(hp)                                      \
    (((hp)->from == SSRP_ADDR_INVALID) || ((hp)->to == SSRP_ADDR_INVALID))


/**
 * @brief SSRP初期化
 *
 * SSRPモジュールを初期化する。他API使用前に必ず実行する。
 */
void SSRP_init(SSRP_Address myaddr);

/**
 * @brief 接続開始
 *
 * 自ノードをSSRPネットワークに参加させる。以降SSRP_execにより自律接続処理が
 * 行われるようになる。
 */
void SSRP_start();

/**
 * @brief 接続終了
 *
 * 自ノードをSSRPネットワークから脱退させる。以降のSSRP_execはパケット
 * ルーティング処理のみとなる。
 */
void SSRP_end();

/**
 * @brief 汎用パケット送信
 *
 * ヘッダを指定してパケットを送信する。非同期送信の場合、ペイロードを指定サイズ
 * 分送り切れないことがあるが、この場合次以降もトランザクションは継続しており、
 * 指定するdataポインタの位置を変えれば続きからデータを送ることができる。
 * 送信を諦めてトランザクションをリセットする場合はSSRP_shutdownを使用する。
 *
 * @param[in] header 送信するヘッダへのポインタ
 * @param[in] data 送信するデータペイロードへのポインタ
 * @param[in] len 送信するデータのサイズ
 * @param[in] sync _TRUE:同期送信 _FALSE:非同期送信
 *
 * @retval 正の値 送信完了したデータサイズ
 * @retval 負の値 送信エラー
 */
_SINT SSRP_send(SSRP_Header* header, const _UBYTE* data, _UBYTE len, _BOOL sync);

/**
 * @brief パケット送信
 *
 * パラメータを指定してパケットを送信する。自動的に自ノードからの送信パケット
 * となる。それ以外の特徴はSSRP_sendと同じ。
 *
 * @param[in] to 送信先アドレス
 * @param[in] cmd コマンド
 * @param[in] flg フラグ
 * @param[in] data データペイロードの先頭へのポインタ
 * @param[in] len 送信するデータサイズ
 * @param[out] trx_id トランザクションIDを保存する領域へのポインタ。NULLなら
 * 無視される
 * @param[in] sync _TRUE:同期送信 _FALSE:非同期送信
 *
 * @retval 正の値 送信完了したデータサイズ
 * @retval 負の値 送信エラー
 */
_SINT SSRP_sendto(SSRP_Address to, SSRP_Command cmd, SSRP_Flag flg,
                  const _UBYTE* data, _UBYTE len,
                  SSRP_TransactionId* trx_id, _BOOL sync);

/**
 * @brief パケット受信
 *
 * 現在内部で保持されているパケットデータを取得する。実際のパケット受信は
 * SSRP_execにより実行され1パケット分のヘッダとデータが保持されているため、
 * これはそれらを取得するだけのAPIである。よってブロックはしない。
 * また、取得できるのは自ノード宛かブロードキャストパケットのみである。
 *
 * @param[out] header_p 受信パケットのヘッダポインタを格納するポインタ
 * @param[out] data_p 受信パケットのデータペイロードポインタを格納するポインタ
 *
 * @retval 正の値 受信パケットのデータペイロードサイズ
 * @retval 負の値 受信パケット無し
 */
_SINT SSRP_recvfrom(SSRP_Header** header_p, _UBYTE** data_p);

/**
 * @brief 送受信トランザクションをリセット
 *
 * 現在処理中のトランザクションをリセットして未送信/未受信状態へ戻す。
 *
 * @param[in] tr リセットするトランザクションの種別
 */
void SSRP_shutdown(SSRP_Transaction tr);

/**
 * @brief ノードアドレス取得
 *
 * ネットワークに参加しているノードのアドレスを取得する。
 *
 * @param[in] idx 取得するノードのインデックス
 *
 * @return ノードのアドレス
 */
SSRP_Address SSRP_getNode(_UBYTE idx);

/**
 * @brief 接続先ノードアドレス取得
 *
 * 接続されているノードのアドレスを接続種別に取得する。
 *
 * @param[in] con 取得するノードの接続種別
 *
 * @return ノードのアドレス
 */
SSRP_Address SSRP_getPear(SSRP_Connection con);

/**
 * @brief ネットワークのノード数を取得する
 *
 * SSRPネットワークに参加しているノードの総数を取得する。自ノードも含む。
 *
 * @return ノード総数
 */
_UBYTE SSRP_getTotalPear();

/**
 * @brief 送受信可能状態の判定
 *
 * SSRPは最初に他ノードとのコネクションを張るが、この処理が完了しないと
 * 送受信処理は行えないため、その状態判定に使用する。
 *
 * @retval _TRUE 接続済み。送受信可能
 * @retval _FALSE 未接続。送受信不可
 */
_BOOL SSRP_ready();

/**
 * @brief 定期処理の実行
 *
 * 接続処理やパケットリレー、パケット受信などを行う。このAPIを定期的に実行
 * することでSSRPが駆動する。SSRP_startが未実行の場合はパケットリレーのみが
 * 行われる。
 */
void SSRP_exec();


#ifdef __cplusplus
}
#endif

#endif /* SSRP_H_ */
