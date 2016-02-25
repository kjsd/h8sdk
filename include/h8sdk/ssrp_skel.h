/**
 * @file ssrp_skel.h
 *
 * @brief SSRPスケルトン
 *
 * このモジュールはSSRP通信をループバックで行うためのスケルトンである。
 *
 * @see ssrp.h
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
#ifndef SSRP_SKEL_H_
#define SSRP_SKEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

#define SSRP_SKEL_LOOPBACK_ADDR 0xfe


/**
 * @brief バイトストリーム送信
 *
 * 常に成功する送信API。送信データは破棄される。
 * その他仕様はifstub.hに準拠。
 *
 * @see ifstub.h
 */
_SINT SSRP_SKEL_write(const _UBYTE* data, _UBYTE size,
                      _BOOL sync, _SINT tmo_ms);

/**
 * @brief バイトストリーム受信
 *
 * SSRPの内部状態に応じて常に適切な受信データを返す。
 * その他仕様はifstub.hに準拠。
 *
 * @see ifstub.h
 */
_SINT SSRP_SKEL_read(_UBYTE* buf, _UBYTE size, _BOOL sync, _SINT tmo_ms);

#ifdef __cplusplus
}
#endif

#endif /* SSRP_SKEL_H_ */
