<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<!-- saved from url=(0091)http://read.pudn.com//downloads109/sourcecode/others/452147/??10%20MP3????/FILE_SYS.H__.htm -->
<HTML><HEAD><TITLE>10.rar FILE_SYS.H</TITLE>
<META http-equiv=Content-Type content="text/html; charset=windows-1252"><LINK 
href="file_sys_files/read_style.css" type=text/css rel=stylesheet>
<META content="MSHTML 6.00.2900.3314" name=GENERATOR></HEAD>
<BODY>
<P><A href="http://www.pudn.com/">http://www.pudn.com/</A> &gt; <A 
href="http://www.pudn.com/downloads109/sourcecode/others/detail452147.html">10.rar</A> 
&gt; FILE_SYS.H</P><!-- saved from http://www.pudn.com -->
<SCRIPT src="file_sys_files/gg_read1.js"></SCRIPT>
<BR><PRE class=H name="code"> 
#define	K9F_FUN				P5 
#define K9F5608				*((unsigned char xdata *)0x4000) 
#define	COMMAND				0x03	 
#define	ADDRESS				0x05	 
#define	D_DATA				0x01 
#define	INACTIVE			0x09	 
#define	RB					0x01 
 
 
 
 
#define FAT12            (12) 
#define FAT16            (16) 
#define FAT32            (32) 
 
 
extern unsigned char PageBuf[512]; 
 
void Flash_Reset(); 
void ReadPage(unsigned int BlockPage,unsigned char *PageBuf); 
void Init_FAT_Info(void); 
unsigned char  OpenFile(unsigned char *FileName); 
unsigned int ReadFile(); 
</PRE>
<SCRIPT src="file_sys_files/2259963.js"></SCRIPT>

<SCRIPT src="file_sys_files/gg_read2.js"></SCRIPT>
<BR></BODY></HTML>
