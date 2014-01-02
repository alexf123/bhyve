/*-
 * Copyright (c) 2011 NetApp, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETAPP, INC ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL NETAPP, INC OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/types.h>

#include "inout.h"
#include "pci_lpc.h"

/*
 * EISA interrupt Level Control Register.
 *
 * This is a 16-bit register with one bit for each of the IRQ0 through IRQ15.
 * A level triggered irq is indicated by setting the corresponding bit to '1'.
 */
#define	ELCR_PORT	0x4d0

static uint8_t elcr[2] = { 0x00, 0x00 };

static int
elcr_handler(struct vmctx *ctx, int vcpu, int in, int port, int bytes,
	     uint32_t *eax, void *arg)
{
	int idx;

	if (bytes != 1)
		return (-1);

	idx = port - ELCR_PORT;

	if (in)
		*eax = elcr[idx];
	else
		elcr[idx] = *eax;

	return (0);
}
INOUT_PORT(elcr, ELCR_PORT + 0, IOPORT_F_INOUT, elcr_handler);
INOUT_PORT(elcr, ELCR_PORT + 1, IOPORT_F_INOUT, elcr_handler);
SYSRES_IO(ELCR_PORT, 2);
