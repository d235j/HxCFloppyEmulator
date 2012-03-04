/*
//
// Copyright (C) 2006, 2007, 2008, 2009, 2010, 2011 Jean-Fran�ois DEL NERO
//
// This file is part of HxCFloppyEmulator.
//
// HxCFloppyEmulator may be used and distributed without restriction provided
// that this copyright statement is not removed from the file and that any
// derivative work contains the original copyright notice and the associated
// disclaimer.
//
// HxCFloppyEmulator is free software; you can redistribute it
// and/or modify  it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// HxCFloppyEmulator is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HxCFloppyEmulator; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
*/
///////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//
//-----------H----H--X----X-----CCCCC----22222----0000-----0000------11----------//
//----------H----H----X-X-----C--------------2---0----0---0----0--1--1-----------//
//---------HHHHHH-----X------C----------22222---0----0---0----0-----1------------//
//--------H----H----X--X----C----------2-------0----0---0----0-----1-------------//
//-------H----H---X-----X---CCCCC-----222222----0000-----0000----1111------------//
//-------------------------------------------------------------------------------//
//----------------------------------------------------- http://hxc2001.free.fr --//
///////////////////////////////////////////////////////////////////////////////////
// File : emuii_track.c
// Contains: Emulator II track builder/encoder
//
// Written by:	DEL NERO Jean Francois
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hxc_floppy_emulator.h"

#include "crc.h"
#include "emuii_track.h"

unsigned char bit_inverter_emuii[]=
{
        0x00,0x80,0x40,0xC0,0x20,0xA0,0x60,0xE0,
        0x10,0x90,0x50,0xD0,0x30,0xB0,0x70,0xF0,
        0x08,0x88,0x48,0xC8,0x28,0xA8,0x68,0xE8,
        0x18,0x98,0x58,0xD8,0x38,0xB8,0x78,0xF8,
        0x04,0x84,0x44,0xC4,0x24,0xA4,0x64,0xE4,
        0x14,0x94,0x54,0xD4,0x34,0xB4,0x74,0xF4,
        0x0C,0x8C,0x4C,0xCC,0x2C,0xAC,0x6C,0xEC,
        0x1C,0x9C,0x5C,0xDC,0x3C,0xBC,0x7C,0xFC,
        0x02,0x82,0x42,0xC2,0x22,0xA2,0x62,0xE2,
        0x12,0x92,0x52,0xD2,0x32,0xB2,0x72,0xF2,
        0x0A,0x8A,0x4A,0xCA,0x2A,0xAA,0x6A,0xEA,
        0x1A,0x9A,0x5A,0xDA,0x3A,0xBA,0x7A,0xFA,
        0x06,0x86,0x46,0xC6,0x26,0xA6,0x66,0xE6,
        0x16,0x96,0x56,0xD6,0x36,0xB6,0x76,0xF6,
        0x0E,0x8E,0x4E,0xCE,0x2E,0xAE,0x6E,0xEE,
        0x1E,0x9E,0x5E,0xDE,0x3E,0xBE,0x7E,0xFE,
        0x01,0x81,0x41,0xC1,0x21,0xA1,0x61,0xE1,
        0x11,0x91,0x51,0xD1,0x31,0xB1,0x71,0xF1,
        0x09,0x89,0x49,0xC9,0x29,0xA9,0x69,0xE9,
        0x19,0x99,0x59,0xD9,0x39,0xB9,0x79,0xF9,
        0x05,0x85,0x45,0xC5,0x25,0xA5,0x65,0xE5,
        0x15,0x95,0x55,0xD5,0x35,0xB5,0x75,0xF5,
        0x0D,0x8D,0x4D,0xCD,0x2D,0xAD,0x6D,0xED,
        0x1D,0x9D,0x5D,0xDD,0x3D,0xBD,0x7D,0xFD,
        0x03,0x83,0x43,0xC3,0x23,0xA3,0x63,0xE3,
        0x13,0x93,0x53,0xD3,0x33,0xB3,0x73,0xF3,
        0x0B,0x8B,0x4B,0xCB,0x2B,0xAB,0x6B,0xEB,
        0x1B,0x9B,0x5B,0xDB,0x3B,0xBB,0x7B,0xFB,
        0x07,0x87,0x47,0xC7,0x27,0xA7,0x67,0xE7,
        0x17,0x97,0x57,0xD7,0x37,0xB7,0x77,0xF7,
        0x0F,0x8F,0x4F,0xCF,0x2F,0xAF,0x6F,0xEF,
        0x1F,0x9F,0x5F,0xDF,0x3F,0xBF,0x7F,0xFF
};



// FM encoder
void BuildFMCylinder(char * buffer,int fmtracksize,char * bufferclk,char * track,int size);

void setbit(unsigned char * dstbuffer,unsigned char byte,int bitoffset,int size)
{
	int i,j,k;

	k=0;
	i=bitoffset;
	for(j=0;j<size;j++)
	{
		if(byte&((0x80)>>(j&7)))
			dstbuffer[i>>3]=dstbuffer[i>>3]|( (0x80>>(i&7)));
		else
			dstbuffer[i>>3]=dstbuffer[i>>3]&(~(0x80>>(i&7)));

		i++;
	}

}


int BuildEmuIITrack(HXCFLOPPYEMULATOR* floppycontext,unsigned int tracknumber,unsigned int sidenumber,unsigned char* datain,unsigned char * fmdata,unsigned long * fmsizebuffer,int trackformat)
{
	unsigned int i,j,k;
	unsigned char CRC16_High;
	unsigned char CRC16_Low;
	unsigned char *tempdata;
	unsigned char *tempclock;
	unsigned long finalsize;
	unsigned long current_buffer_size;
	
	unsigned char crctable[32];

	unsigned long sectorsize;
	unsigned char track_num;
	unsigned long buffersize;


	buffersize=*fmsizebuffer/8;

	sectorsize=3584;

	switch(trackformat)
	{
		case 1:
			track_num=tracknumber;
		break;

		case 2:
			track_num=tracknumber*2+sidenumber;
		break;
	}	

	current_buffer_size=buffersize/4;
	finalsize=20 + 10 +8 + 6 + sectorsize + 2 + 2 + 20;

	if(finalsize<=current_buffer_size)
	{

		j=0;

		tempdata=(char *)malloc((buffersize/4)+1);
		tempclock=(char *)malloc((buffersize/4)+1);

		memset(tempclock,0xFF,(buffersize/4)+1);
		memset(tempdata, 0xFF,(buffersize/4)+1);


		/////////////////////////////////////////////////////////////////////////////////////////////
		//Track GAP
		for(k=0;k<20;k++)
		{
			setbit(tempdata,bit_inverter_emuii[0xFF],j,8);
			j=j+8;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
		//Sector Header
		for(k=0;k<4;k++)
		{
			setbit(tempdata,bit_inverter_emuii[0x00],j=j+8,8);
		}

		setbit(tempdata,bit_inverter_emuii[0xFA],j=j+8,8);
		setbit(tempdata,bit_inverter_emuii[0x96],j=j+8,8);
		setbit(tempdata,bit_inverter_emuii[track_num],j=j+8,8);

		//CRC The sector Header CRC
		CRC16_Init(&CRC16_High,&CRC16_Low,(unsigned char*)&crctable,0x8005,0x0000);
		CRC16_Update(&CRC16_High,&CRC16_Low,bit_inverter_emuii[track_num],(unsigned char*)&crctable );

		setbit(tempdata,CRC16_High,j=j+8,8);
		setbit(tempdata,CRC16_Low,j=j+8,8);

		switch(trackformat)
		{

			// Emu 1
			case 1:
				setbit(tempdata,bit_inverter_emuii[0x00],j=j+8,8);
				setbit(tempdata,bit_inverter_emuii[0x00],j=j+8,8);

				for(k=0;k<7;k++)
					setbit(tempdata,bit_inverter_emuii[0xFF],j=j+8,8);
					//tempdata[j++]=bit_inverter_emuii[0xFF];

			break;

			// Emu 2
			case 2:
				setbit(tempdata,bit_inverter_emuii[0x00],j=j+8,8);
				for(k=0;k<7;k++)
				{
					setbit(tempdata,bit_inverter_emuii[0xFF],j=j+8,8);
				}

				setbit(tempdata,bit_inverter_emuii[0xFF],j=j+4,4);
			break;
		}


		/////////////////////////////////////////////////////////////////////////////////////////////
		//Sector Data	

		for(k=0;k<4;k++)
		{
			setbit(tempdata,bit_inverter_emuii[0x00],j=j+8,8);
		}

		setbit(tempdata,bit_inverter_emuii[0xFA],j=j+8,8);
		setbit(tempdata,bit_inverter_emuii[0x96],j=j+8,8);
		
		//CRC The sector data CRC
		CRC16_Init(&CRC16_High,&CRC16_Low,(unsigned char*)&crctable,0x8005,0x0000);
		
		for(k=0;k<sectorsize;k++)
		{
			setbit(tempdata,bit_inverter_emuii[datain[k]],j=j+8,8);
			CRC16_Update(&CRC16_High,&CRC16_Low,bit_inverter_emuii[datain[k]],(unsigned char*)&crctable );
		}

		setbit(tempdata,CRC16_High,j=j+8,8);
		setbit(tempdata,CRC16_Low,j=j+8,8);


		setbit(tempdata,bit_inverter_emuii[0x00],j=j+8,8);
		setbit(tempdata,bit_inverter_emuii[0x00],j=j+8,8);


		for(k=0;k<20;k++)
			setbit(tempdata,bit_inverter_emuii[0xFF],j=j+8,8);
		/////////////////////////////////////////////////////////////////////////////////////////////

		if((j/8)<=current_buffer_size)
		{	
			for(i=(j/8);i<(current_buffer_size+1);i++)
			{	
				setbit(tempdata,bit_inverter_emuii[0xFF],j=j+8,8);
			}
		}

		BuildFMCylinder(fmdata,buffersize,tempclock,tempdata,(buffersize)/4);

		free(tempdata);
		free(tempclock);
		return 0;
	}
	else
	{
		floppycontext->hxc_printf(MSG_ERROR,"BuildEmuIITrack : No enough space on this track !");
		return finalsize;
	}

}
