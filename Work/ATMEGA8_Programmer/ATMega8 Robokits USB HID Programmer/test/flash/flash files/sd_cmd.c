<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<!-- saved from url=(0080)http://read.pudn.com//downloads102/sourcecode/embed/418044/sdCard/sd_cmd.c__.htm -->
<HTML><HEAD><TITLE>SDMMCyuanma.rar sd_cmd.c</TITLE>
<META http-equiv=Content-Type content="text/html; charset=windows-1252"><LINK 
href="sd_mmc_files/read_style.css" type=text/css rel=stylesheet>
<META content="MSHTML 6.00.2900.3314" name=GENERATOR></HEAD>
<BODY>
<P><A href="http://www.pudn.com/">http://www.pudn.com/</A> &gt; <A 
href="http://www.pudn.com/downloads102/sourcecode/embed/detail418044.html">SDMMCyuanma.rar</A> 
&gt; sd_cmd.c</P><!-- saved from http://www.pudn.com -->
<SCRIPT src="sd_mmc_files/gg_read1.js"></SCRIPT>
<BR><PRE class=c name="code"> /*! 
 *@file     sd_cmd.c 
 * 
 *  
 * 
 *@version  v1.0.0 
 *@date     2007 
 *@author   jacky291@126.com 
 */ 
#include "sd_cmd.h" 
 
#ifndef __SD_CONFIG_H 
#include "sd_cfg.h" 
#endif 
/*! 
*@brief 
*        SD_SendCMD() 
*        send the command 
* 
*@param  uint8 cmd:the command sended 
*@param  uint8 *param:the command param addr. 
*@param  uint8 resType:the response type 
*@param  uint8 *response:the response data addr. 
*@retval 0:  right	&gt;0:  error code 
*/ 
uint32 SD_SendCMD(uint8 cmd,uint8 *param,uint8 resType,uint8 *response) 
{ 
       uint8 i,rlen; 
#if SD_CRC_EN  
       uint8 CMD_CRC; 
#endif                                             
       SD_SPI_SendByte((cmd&amp;0x3F)|0x40);                           
       for(i=0;i&lt;=3;i++){ 
          SD_SPI_SendByte(param[3-i]); 
       }; 
#if SD_CRC_EN  
           CMD_CRC=SD_GetCmdByte6(cmd,param); 
           SD_SPI_SendByte(CMD_CRC); 
#else 
           SD_SPI_SendByte(0x95); 
#endif 
       rlen=0; 
       switch(resType){ 
            case R1:  rlen=1; break; 
            case R2:  rlen=2; break; 
            case R3:  rlen=5; break; 
            default:  return CMD_PARAM_ERR; break; 
       }; 
       if(SD_SPI_WaitForLow(200)==SPI_TIMEOUT){ 
          return SD_ERR_CMD_TIMEOUT; 
       }; 
       /**&lt; receive the response */ 
       for(i=0;i&lt;=rlen-1;i++){ 
  
           response[rlen-1-i]=SD_SPI_RecByte(); 
            
       }; 
       SD_SPI_RecByte(); 
       return 0;    
} 
 
/*! 
*@brief 
*        SD_PackParam(uint8 *param, uint32 value) 
*        format the param,div value to 4 Byte 
* 
*@param  *param:param addr(8bits) 
*@param  uint32 value 
*@retval none 
*/ 
void SD_PackParam(uint8 *param, uint32 value) 
{ 
    param[3] = (uint8)(value &gt;&gt; 24); 
    param[2] = (uint8)(value &gt;&gt; 16); 
    param[1] = (uint8)(value &gt;&gt; 8); 
    param[0] = (uint8)(value); 
} 
 
 
 
/*! 
*@brief 
*        SD_BlockCommand(uint8 cmd, uint8 resptype, uint32 parameter) 
*        send the block command 
* 
*@param  uint8 cmd:the command sended 
*@param  uint8 *param:the command param addr. 
*@param  uint8 resType:the response type 
*@param  uint8 *response:the response data addr. 
*@retval 0:  right	&gt;0:  error code 
*/ 
uint8 SD_BlockCommand(uint8 cmd, uint8 resptype, uint32 parameter) 
{ 
	uint8 param[4],resp,ret; 
	SD_PackParam(param, parameter);					/*! change the parameter to bytes form */	 
	ret = SD_SendCMD(cmd, param, resptype, &amp;resp); 
	if (ret != SD_NO_ERR) 
	   	     return ret;							/*! stop transmission operation fail   */ 
	if (resp != 0) 
		     return resp;		 				    /*! response is error         */ 
	return 0; 
} 
 
</PRE>
<SCRIPT src="sd_mmc_files/2259963.js"></SCRIPT>

<SCRIPT src="sd_mmc_files/gg_read2.js"></SCRIPT>
<BR></BODY></HTML>
