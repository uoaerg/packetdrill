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
 * Author: tj@enoti.me (Tom Jones)
 *
 * Interfaces for reading and writing UDP options in their wire format.
 */

#ifndef __UDP_OPTIONS_H__
#define __UDP_OPTIONS_H__

#include "types.h"

#include "packet.h"

#define MAX_UDP_OPTION_BYTES (MAX_UDP_DATAGRAM_BYTES - (int)sizeof(struct udp))

/* Represents a list of UDP options in their wire format. */
struct udp_options {
	u8 data[MAX_UDP_OPTION_BYTES];	/* The options data, in wire format */
	u16 length;		/* The length, in bytes, of the data */
};

/* Represents a single UDP option in its wire format. Note that for
 * EOL and NOP options the length and data field are not included in
 * the on-the-wire data. For other options, the length field describes
 * the number of bytes of the struct that go on the wire. */
struct udp_option {
	u8 kind;
	u8 length;  /* bytes on the wire; includes kind and length byte */
	union {
		struct {
			u16 bytes;	/* in network order */
		} mss;
		struct {
			u32 val;	/* in network order */
			u32 ecr;	/* in network order */
		} time_stamp;
	} data;
} __packed udp_option;

/* Allocate a new options list. */
extern struct udp_options *udp_options_new(void);

/* Allocate a new option and initialize its kind and length fields. */
extern struct udp_option *udp_option_new(u8 kind, u8 length);

/* Appends the given option to the given list of options. Returns
 * STATUS_OK on success; on failure returns STATUS_ERR and sets
 * error message.
 */
extern int udp_options_append(struct udp_options *options,
			      struct udp_option *option);

#endif /* __UDP_OPTIONS_H__ */
