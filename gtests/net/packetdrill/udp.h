/*
 * Copyright 2013 Google Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
/*
 * Author: ncardwell@google.com (Neal Cardwell)
 *
 * Our own UDP header declarations, so we have something that's
 * portable and somewhat more readable than a typical system header
 * file.
 *
 * We cannot include the kernel's linux/udp.h because this tool tries
 * to compile and work for basically any Linux/BSD kernel version. So
 * we declare our own version of various UDP-related definitions here.
 */

#ifndef __UDP_HEADERS_H__
#define __UDP_HEADERS_H__

#include "types.h"

#define UDPOPT_EOL       0
#define UDPOPT_NOP       1
#define UDPOPT_OCS       2
#define UDPOPT_ACS       3
#define UDPOPT_LITE      4
#define UDPOPT_MSS       5
#define UDPOPT_TIME      6
#define UDPOPT_FRAG      7
#define UDPOPT_AE        8
#define UDPOPT_ECHOREQ   9
#define UDPOPT_ECHORES   10

#define UDPOLEN_EOL      0
#define UDPOLEN_NOP      0
#define UDPOLEN_OCS      2
#define UDPOLEN_ACS      4
#define UDPOLEN_LITE     4
#define UDPOLEN_MSS      4
#define UDPOLEN_TIME     10
#define UDPOLEN_FRAG     12
#define UDPOLEN_ECHOREQ  6
#define UDPOLEN_ECHORES  6


/* UDP header. See RFC 768. */
struct udp {
	__be16	src_port;
	__be16	dst_port;
	__be16	len;		/* UDP length in bytes, includes UDP header */
	__sum16 check;		/* UDP checksum */
};

#endif /* __UDP_HEADERS_H__ */
