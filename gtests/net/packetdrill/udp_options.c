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
 * Implementation for reading and writing UDP options in their wire format.
 */

#include "udp_options.h"

#include <stdlib.h>
#include <string.h>
#include "packet.h"

struct udp_options *udp_options_new(void)
{
	return calloc(1, sizeof(struct udp_options));
}

struct udp_option *udp_option_new(u8 kind, u8 length)
{
	struct udp_option *option = calloc(1, sizeof(struct udp_option));
	option->kind = kind;
	option->length = length;
	return option;
}

int udp_options_append(struct udp_options *options,
			       struct udp_option *option)
{
	if (options->length + option->length > sizeof(options->data))
		return STATUS_ERR;
	memcpy(options->data + options->length, option, option->length);
	options->length += option->length;
	assert(options->length <= sizeof(options->data));
	return STATUS_OK;
}
