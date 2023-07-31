/*-----------------------------------------------------------------------------
 *
 *  GBADoom for DOS
 *  Copyright (C) 2023 Frenkel Smeijers
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 * DESCRIPTION:
 *      DOS implementation of i_system_e32.h
 *
 *-----------------------------------------------------------------------------*/

#ifndef GBA

#include <dos.h>
#include <stdarg.h>
#include <stdint.h>

#include <dpmi.h>
#include <go32.h>
#include <sys/nearptr.h>

#include "doomdef.h"
#include "d_main.h"
#include "i_system_e32.h"


//**************************************************************************************
//
// Keyboard code
//

#define KEYBOARDINT 9
#define KBDQUESIZE 32
static byte keyboardqueue[KBDQUESIZE];
static int32_t kbdtail, kbdhead;
static boolean isKeyboardIsrSet = false;

static _go32_dpmi_seginfo oldkeyboardisr, newkeyboardisr;

static void I_KeyboardISR(void)	
{
	// Get the scan code
	keyboardqueue[kbdhead & (KBDQUESIZE - 1)] = inportb(0x60);
	kbdhead++;

	// acknowledge the interrupt
	outportb(0x20, 0x20);
}

void I_InitScreen_e32(void)
{
	// Set the keyboard interrupt
	_go32_dpmi_get_protected_mode_interrupt_vector(KEYBOARDINT, &oldkeyboardisr);	

	newkeyboardisr.pm_selector = _go32_my_cs(); 								
	newkeyboardisr.pm_offset = (int32_t)I_KeyboardISR;								
	_go32_dpmi_allocate_iret_wrapper(&newkeyboardisr);							
	_go32_dpmi_set_protected_mode_interrupt_vector(KEYBOARDINT, &newkeyboardisr);

	isKeyboardIsrSet = true;
}


#define SC_ESCAPE		0x01
#define SC_TAB			0x0f
#define SC_ENTER		0x1c
#define SC_CTRL			0x1d
#define SC_LSHIFT		0x2a
#define SC_RSHIFT		0x36
#define SC_COMMA		0x33
#define SC_PERIOD		0x34
#define SC_SPACE		0x39
#define SC_F10			0x44
#define SC_UPARROW		0x48
#define SC_DOWNARROW	0x50
#define SC_LEFTARROW	0x4b
#define SC_RIGHTARROW	0x4d

void I_ProcessKeyEvents(void)
{
	//
	// keyboard events
	//
	byte k;
	event_t ev;

	while (kbdtail < kbdhead)
	{
		k = keyboardqueue[kbdtail & (KBDQUESIZE - 1)];
		kbdtail++;

		// extended keyboard shift key bullshit
		if ((k & 0x7f) == SC_LSHIFT || (k & 0x7f) == SC_RSHIFT)
		{
			if (keyboardqueue[(kbdtail - 2) & (KBDQUESIZE - 1)] == 0xe0)
				continue;
			k &= 0x80;
			k |= SC_RSHIFT;
		}

		if (k == 0xe0)
			continue;               // special / pause keys
		if (keyboardqueue[(kbdtail - 2) & (KBDQUESIZE - 1)] == 0xe1)
			continue;                               // pause key bullshit

		if (k == 0xc5 && keyboardqueue[(kbdtail - 2) & (KBDQUESIZE - 1)] == 0x9d)
		{
			//ev.type  = ev_keydown;
			//ev.data1 = KEY_PAUSE;
			//D_PostEvent(&ev);
			continue;
		}

		if (k & 0x80)
			ev.type = ev_keyup;
		else
			ev.type = ev_keydown;

		k &= 0x7f;
		switch (k)
		{
			case SC_ESCAPE:
				ev.data1 = KEYD_START;
				break;
			case SC_ENTER:
			case SC_SPACE:
			case SC_RSHIFT:
				ev.data1= KEYD_A;
				break;
			case SC_UPARROW:
				ev.data1 = KEYD_UP;
				break;
			case SC_DOWNARROW:
				ev.data1 = KEYD_DOWN;
				break;
			case SC_LEFTARROW:
				ev.data1 = KEYD_LEFT;
				break;
			case SC_RIGHTARROW:
				ev.data1 = KEYD_RIGHT;
				break;
			case SC_TAB:
				ev.data1 = KEYD_SELECT;
				break;
			case SC_CTRL:
				ev.data1 = KEYD_B;
				break;
			case SC_COMMA:
				ev.data1 = KEYD_L;
				break;
			case SC_PERIOD:
				ev.data1 = KEYD_R;
				break;
			case SC_F10:
				I_Error("Thanks for playing DOOM.");
			default:
				continue;
		}
		D_PostEvent(&ev);
	}
}


//**************************************************************************************
//
// Screen code
//

static byte *screen;
static unsigned short  backBuffer[SCREENWIDTH * SCREENHEIGHT];
static unsigned short frontBuffer[SCREENWIDTH * SCREENHEIGHT];

unsigned short* I_GetBackBuffer(void)
{
    return &backBuffer[0];
}

unsigned short* I_GetFrontBuffer(void)
{
    return &frontBuffer[0];
}


static void I_SetScreenMode(uint16_t mode)
{
	union REGS regs;
	regs.w.ax = mode;
	int386(0x10, &regs, &regs);
}


void I_CreateBackBuffer_e32(void)
{	
	I_SetScreenMode(0x13);

	__djgpp_nearptr_enable();
	screen = (byte *)(0xa0000 + __djgpp_conventional_base);
}


void I_FinishUpdate_e32(const byte* srcBuffer, const byte* palette, const unsigned int width, const unsigned int height)
{
	uint_fast8_t x, y;
	byte *src, *dst;

	src = srcBuffer;
	dst = screen;
	for (y = 0; y < SCREENHEIGHT; y++) {
		for (x = 0; x < (SCREENWIDTH * 2); x++) {
			*dst++ = *src++;
		}
		dst += (320 - (SCREENWIDTH * 2));
	}
}


#define PEL_WRITE_ADR   0x3c8
#define PEL_DATA        0x3c9

void I_SetPallete_e32(const byte* palette)
{
	int_fast16_t i;

	outportb(PEL_WRITE_ADR, 0);
	for (i = 0; i < 768; i++)
		outportb(PEL_DATA, (*palette++) >> 2);
}


//**************************************************************************************
//
// Bad exit with diagnostic message
//

void I_Error(const char *error, ...)
{
	va_list argptr;

	I_SetScreenMode(3);

	va_start(argptr, error);
	vprintf(error, argptr);
	va_end(argptr);
	printf("\n");

	if (isKeyboardIsrSet) {
		_go32_dpmi_set_protected_mode_interrupt_vector(KEYBOARDINT, &oldkeyboardisr);
		_go32_dpmi_free_iret_wrapper(&newkeyboardisr);
	}

	exit(1);
}


//**************************************************************************************

#endif
