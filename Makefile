#
# $FreeBSD$
#

PROG=	bhyve

DEBUG_FLAGS= -g -O0 

MAN=	bhyve.8

SRCS=	\
	acpi.c			\
	bhyverun.c		\
	block_if.c		\
	consport.c		\
	dbgport.c		\
	inout.c			\
	ioapic.c		\
	mem.c			\
	mevent.c		\
	mptbl.c			\
	pci_ahci.c		\
	pci_emul.c		\
	pci_hostbridge.c	\
	pci_lpc.c		\
	pci_passthru.c		\
	pci_virtio_block.c	\
	pci_virtio_net.c	\
	pci_uart.c		\
	pit_8254.c		\
	pm.c			\
	pmtmr.c			\
	post.c			\
	rtc.c			\
	smbiostbl.c		\
	uart_emul.c		\
	virtio.c		\
	xmsr.c			\
	spinup_ap.c

.PATH:	${.CURDIR}/../../sys/amd64/vmm
SRCS+=	vmm_instruction_emul.c

DPADD=	${LIBVMMAPI} ${LIBMD} ${LIBUTIL} ${LIBPTHREAD}
LDADD=	-lvmmapi -lmd -lutil -lpthread

WARNS?=	2

.include <bsd.prog.mk>
