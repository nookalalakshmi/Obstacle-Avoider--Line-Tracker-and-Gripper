<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<!-- saved from url=(0091)http://read.pudn.com/downloads108/sourcecode/comm/448448/avr_sd/avr_sd/Flash/sd_cmd.h__.htm -->
<HTML><HEAD><TITLE>avr_sd.rar sd_cmd.h</TITLE>
<META http-equiv=Content-Type content="text/html; charset=windows-1252"><LINK 
href="sd_cmd_files/read_style.css" type=text/css rel=stylesheet>
<META content="MSHTML 6.00.2900.3314" name=GENERATOR></HEAD>
<BODY>
<P><A href="http://www.pudn.com/">http://www.pudn.com/</A> &gt; <A 
href="http://www.pudn.com/downloads108/sourcecode/comm/detail448448.html">avr_sd.rar</A> 
&gt; sd_cmd.h</P><!-- saved from http://www.pudn.com -->
<SCRIPT src="sd_cmd_files/gg_read1.js"></SCRIPT>
<BR><PRE class=h name="code">/* 
	Progressive Resources LLC 
 
			FlashFile 
 
	Version : 	2.00 
	Date: 		11/01/2004 
	Author: 	Erick M. Higa 
 
	Software License 
	The use of Progressive Resources LLC FlashFile Source Package indicates 
	your understanding and acceptance of the following terms and conditions. 
	This license shall supersede any verbal or prior verbal or written, statement 
	or agreement to the contrary. If you do not understand or accept these terms, 
	or your local regulations prohibit "after sale" license agreements or limited 
	disclaimers, you must cease and desist using this product immediately. 
	This product is © Copyright 2003 by Progressive Resources LLC, all rights 
	reserved. International copyright laws, international treaties and all other 
	applicable national or international laws protect this product. This software 
	product and documentation may not, in whole or in part, be copied, photocopied, 
	translated, or reduced to any electronic medium or machine readable form, without 
	prior consent in writing, from Progressive Resources LLC and according to all 
	applicable laws. The sole owner of this product is Progressive Resources LLC. 
 
	Operating License 
	You have the non-exclusive right to use any enclosed product but have no right 
	to distribute it as a source code product without the express written permission 
	of Progressive Resources LLC. Use over a "local area network" (within the same 
	locale) is permitted provided that only a single person, on a single computer 
	uses the product at a time. Use over a "wide area network" (outside the same 
	locale) is strictly prohibited under any and all circumstances. 
 
	Liability Disclaimer 
	This product and/or license is provided as is, without any representation or 
	warranty of any kind, either express or implied, including without limitation 
	any representations or endorsements regarding the use of, the results of, or 
	performance of the product, Its appropriateness, accuracy, reliability, or 
	correctness. The user and/or licensee assume the entire risk as to the use of 
	this product. Progressive Resources LLC does not assume liability for the use 
	of this product beyond the original purchase price of the software. In no event 
	will Progressive Resources LLC be liable for additional direct or indirect 
	damages including any lost profits, lost savings, or other incidental or 
	consequential damages arising from any defects, or the use or inability to 
	use these products, even if Progressive Resources LLC have been advised of 
	the possibility of such damages. 
*/ 
 
#ifndef _sd_cmd_h_ 
	#define _sd_cmd_h_ 
  #ifdef _ALL_SD_CMDS_ 
	enum	{CMD0=0, CMD1, CMD9, CMD10, CMD12, CMD13, CMD16, 
			CMD17, CMD18, CMD24, CMD25, CMD27, CMD28, CMD29, 
			CMD30, CMD32, CMD33, CMD34, CMD35, CMD36, CMD37, 
			CMD38, CMD42, CMD58, CMD59, ACMD41, CMD_TOT}; 
 
//	uchar _FF_read_csd(void); 
  #else 
	enum	{CMD0=0, CMD1, CMD17, CMD24, CMD_TOT}; 
  #endif 
	enum	{GO_IDLE_STATE=0, SEND_OP_COND, SEND_CSD, SEND_CID, 
			STOP_TRANSMISSION, SEND_STATUS, SET_BLOCKLEN, 
			READ_SINGLE_BLOCK, READ_MULTIPLE_BLOCK, WRITE_BLOCK, 
			WRITE_MULTIPLE_BLOCK, PROGRAM_CSD, SET_WRITE_PROT, 
			CLR_WRITE_PROT, SEND_WRITE_PROT, TAG_SECTOR_START, 
			TAG_SECTOR_END, UNTAG_SECTOR, TAG_ERASE_GROUP_START, 
			TAG_ERASE_GROUP_END, UNTAG_ERASE_GROUP, ERASE, 
			LOCK_UNLOCK, READ_OCR, CRC_ON_OFF}; 
 
	enum	{RESP_1, RESP_1b, RESP_2, RESP_3}; 
 
	enum	{NO_ARG, BLOCK_LEN, DATA_ADDR, STUFF_BITS}; 
 
	// uint CRCCCITT(uchar *data, ulong length, 
	//				      uint seed, uint final); 
	uint send_cmd(uchar command, ulong argument); 
	uchar reset_sd(void); 
	uchar init_sd(void); 
  #ifdef _DEBUG_ON_ 
	uchar _FF_read_disp(ulong sd_addr); 
  #endif 
	uchar _FF_read(ulong sd_addr, uchar *sd_read_buff); 
	uchar initialize_media(void); 
  #ifndef _READ_ONLY_ 
	uchar _FF_write(ulong sd_addr, uchar *sd_write_buff); 
  #endif 
 
  #ifndef _BIG_ENDIAN_ 
	typedef struct { 
		uchar LO; 
		uchar ML; 
		uchar MH; 
		uchar HI; 
	} sHILO32c; 
	typedef struct { 
		uchar LO; 
		uchar HI; 
	} sHILO16c; 
	typedef struct { 
		uint LO; 
		uint HI; 
	} sHILO32i; 
  #else 
	typedef struct { 
		uchar HI; 
		uchar MH; 
		uchar ML; 
		uchar LO; 
	} sHILO32c; 
	typedef struct { 
		uchar HI; 
		uchar LO; 
	} sHILO16c; 
	typedef struct { 
		uint HI; 
		uint LO; 
	} sHILO32i; 
  #endif 
 
	typedef union { 
		ulong lval; 
		sHILO32c cval; 
		sHILO32i ival; 
	} uHILO32; 
 
	typedef union { 
		uint ival; 
		sHILO16c cval; 
	} uHILO16; 
 
#endif 
</PRE>
<SCRIPT src="sd_cmd_files/2259963.js"></SCRIPT>

<SCRIPT src="sd_cmd_files/gg_read2.js"></SCRIPT>
<BR></BODY></HTML>
