/*  
    Progressive Resources LLC  
  
            FlashFile  
  
    Version :   2.00  
    Date:       11/01/2004  
    Author:     Erick M. Higa  
  
    Revision History:  
    12/31/2003 - EMH - v1.00  
                     - Initial Release  
    01/19/2004 - EMH - v1.10  
                     - Fixed FAT access errors by allowing both FAT tables to be updated  
                     - Fixed erase_cluster chain to stop if chain goes to '0'  
                     - Fixed #include's so other non m128 processors could be used  
                     - Fixed fcreate to match 'C' standard for function "creat"  
                     - Fixed fseek so it would not error when in "READ" mode  
                     - Modified SPI interface to use _FF_spi() so it is more universal  
                       (see the "sd_cmd.c" file for the function used)  
                     - Redifined global variables and #defines for more unique names  
                     - Added string functions fputs, fputsc, & fgets  
                     - Added functions fquickformat, fgetfileinfo, & GetVolID()  
                     - Added directory support  
                     - Modified delays in "sd_cmd.c" to increase transfer speed to max  
                     - Updated "options.h" to include additions, and to make #defines  
                       more universal to multiple platforms  
    01/21/2004 - EMH - v1.20  
                     - Added ICC Support to the FlashFileSD  
                     - Fixed card initialization error for MMC/SD's that have only a boot  
                       sector and no partition table  
                     - Fixed intermittant error on fcreate when creating existing file  
                     - Changed "options.h" to #include all required files  
    02/19/2004 - EMH - v1.21  
                     - Replaced all "const" refrances to "flash" to support CodeVision 1.24.1b  
    03/02/2004 - EMH - v1.22 (unofficial release)  
                     - Changed Directory Functions to allow for multi-cluster directory entries  
                     - Added function addr_to_clust() to support long directories  
                     - Fixed FAT table address calculation to support multiple reserved sectors  
                       (previously) assumed one reserved sector, if XP formats card sometimes  
                       multiple reserved sectors - thanks YW  
    03/10/2004 - EMH - v1.30  
                     - Added support for a Compact Flash package  
                     - Renamed read and write to flash function names for multiple media support  
    03/26/2004 - EMH - v1.31  
                     - Added define for easy MEGA128Dev board setup  
                     - Changed demo projects so "option.h" is in the project directory  
    04/01/2004 - EMH - v1.32  
                     - Fixed bug in "prev_cluster()" that didn't use updated FAT table address  
                       calculations.  (effects XP formatted cards see v1.22 notes)  
    05/07/2004 - EMH - v1.33  
                     - Fixed bug in "fflush()" and "fopen()" that was incorrectly handling blank  
                       files on certain MMC/SD cards.  
    05/17/2004 - EMH - v1.34  
                     - Fixed bug "fopen()" that was incorrectly writing to 0xFE00 + _FF_DIR_ADDR  
                       if opening a file in "WRITE" mode (bug since v1.22).  
                     - Fixed bug in "append_toc()" that was incorrectly updating the time/date  
                       stamp if _RTC_ON_ is NOT defined.  
    05/17/2004 - EMH - v1.40  
                     - Added IAR EWAVR Support to the FlashFile  
    06/14/2004 - EMH - v1.41  
                     - Fixed bug in "fflush()" that was incorrectly saving the last sector of a  
                       cluster to the first if saving or closing a file at the end of file AND at  
                       the end of a cluster.  
    11/01/2004 - EMH - v2.00  
                     - Changing code to use structures and unions to optimize code to run faster  
                       and use less code space.  
                     - Fixed bug in fgets() that was reading too long if the line was >= n, and  
                       it was returning the wrong pointer.  
                     - Changing code to use sector addressing rather than direct memory addressing  
                       to save code space and speed up time.  
                     - Added _DIRECTORIES_SUPPORTED_ switch to options.h to enable or disable (less  
                       code space) the use of directories.  
                     - Added _NO_MALLOC_ switch to options.h to enable or disable the need of a  
                       malloc() function.  
                     - Added _BytsPerSec_512_ switch to options.h to enable or disable the BPB_BytsPerSec  
                       variable.  In all current flash media, there are 512 bytes per sector, and there  
                       really is no need to have it as a variable.  Enabling _BytsPerSec_512_ will hard  
                       code all references to BPB_BytsPerSec as 0x200 or 512.  This will cut down on code  
                       space and speed the functions up a bit since << 9 and >> 9 can replace * 512 and  
                       / 512, and & 0x1FF can replace % 512.  
                     - Fixed bug in addr_to_clust() that was checking if sector # was <= FirstDataSector  
                       where it should just be < FirstDataSector.  
                     - Added ability in initialize_media() for the calculations to look for the first  
                       partition location in all four partition entry spaces rather than just the first.  
                     - Fixed bug in scan_directory() that did not always 0xE5 as an empty file location.  
                     - Fixed Directory support (scan_directory(), fcreate(), and mkdir()) so that multi   
                       cluster sub-directories could be read.  
                     - Fixed Initialization of the File Structure that was intermittantly causing errors in   
                       fopen() and fcreate().  
                     - Fixed bug in fcreatec(), fopenc(), and fget_file_infoc() that was not always handling   
                       full length filenames of files correctly.  
                     - Combined code so that CodeVision, ImageCraft, and IAR all use the same base code.  
                     - Updated fprintf() in ImageCraft and IAR versions so that the use vsprintf and can be   
                       used just like a printf().  
                     - Added fread() and fwrite() functions.  
  
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
   
extern uchar _FF_buff[512];   
#ifndef _BytsPerSec_512_    
extern uHILO16 BPB_BytsPerSec;   
#endif    
extern uchar BPB_SecPerClus;   
extern uHILO16 BPB_RsvdSecCnt;   
extern uHILO16 BPB_RootEntCnt;   
extern uHILO16 BPB_FATSz16;   
extern uchar BPB_FATType;   
extern uHILO32 BS_VolSerial;   
extern uchar BS_VolLab[12];   
extern uint _FF_PART_ADDR;   
extern ulong _FF_ROOT_ADDR;   
#ifdef _DIRECTORIES_SUPPORTED_    
extern ulong _FF_DIR_ADDR;   
#endif    
extern uint _FF_FAT1_ADDR;   
extern ulong _FF_FAT2_ADDR;   
extern uint FirstDataSector;   
extern uchar _FF_error;   
extern ulong _FF_buff_addr;   
extern ulong DataClusTot;   
#ifdef _RTC_ON_    
uchar rtc_hour, rtc_min, rtc_sec;   
uchar rtc_date, rtc_month;   
uint rtc_year;   
#endif    
extern uint clus_0_addr, _FF_n_temp;   
extern uchar _FF_FULL_PATH[_FF_PATH_LENGTH];   
extern uint c_counter;   
uchar FILENAME[12];   
#ifdef _NO_MALLOC_    
FILE my_file_struct;   
#endif    
   
   
#ifdef _IAR_EWAVR_    
sint _FF_strncmp(uchar *data_buff1, uchar *data_buff2, sint n)   
{   
    schar c1, c2;   
  for(; n != 0; --n)   
  {   
   
    c1 = *data_buff1;   
    data_buff1++;   
    c2 = *data_buff2;   
    data_buff2++;   
    if (c1 != c2)   
      return c1 < c2 ? -1 : 1;   
    else if (c1 == 0)   
      return 0;   
  }   
   
  return n;   
}   
   
uchar *_FF_strrchr(uchar *s, sint c)   
{   /* find last occurrence of c in char s[] */   
    const schar ch = c;   
    uchar *sc;   
   
    for (sc = 0; ; ++s)   
    {   /* check another char */   
        if (*s == ch)   
            sc = s;   
        if (*s == '\0')   
            return ((uchar *)sc);   
    }   
}   
   
size_t _FF_strlen(uchar *s)   
{   
    uchar *p = s;   
   
    while (*p)   
        p++;   
   
    return (p - s);   
}   
   
#endif    
   
// Conversion file to change an ASCII valued character into the calculated value    
uchar ascii_to_char(uchar ascii_char)   
{   
    uchar temp_char;   
   
    if (ascii_char < 0x30)       // invalid, return error    
        return (0xFF);   
    else if (ascii_char < 0x3A)   
    {   //number, subtract 0x30, retrun value    
        temp_char = ascii_char - 0x30;   
        return (temp_char);   
    }   
    else if (ascii_char < 0x41)  // invalid, return error    
        return (0xFF);   
    else if (ascii_char < 0x47)   
    {   // lower case a-f, subtract 0x37, return value    
        temp_char = ascii_char - 0x37;   
        return (temp_char);   
    }   
    else if (ascii_char < 0x61)  // invalid, return error    
        return (0xFF);   
    else if (ascii_char < 0x67)   
    {   // upper case A-F, subtract 0x57, return value    
        temp_char = ascii_char - 0x57;   
        return (temp_char);   
    }   
    else    // invalid, return error    
        return (0xFF);   
}   
   
// Function to see if the character is a valid FILENAME character    
sint valid_file_char(uchar file_char)   
{   
    if (file_char < 0x20)   
        return ((sint)EOF);   
    else if ((file_char==0x22) || (file_char==0x2A) || (file_char==0x2B) || (file_char==0x2C) ||   
            (file_char==0x2E) || (file_char==0x2F) || ((file_char>=0x3A)&&(file_char<=0x3F)) ||   
            ((file_char>=0x5B)&&(file_char<=0x5D)) || (file_char==0x7C) || (file_char==0xE5))   
        return ((sint)EOF);   
    else   
        return (0);   
}   
   
   
   
// Function will scan the directory @VALID_ADDR and return a    
// '0' if successful (w/ VALID_ADDR changing to location of entry avaliable),    
// and a '-1' if file or folder exists (w/ VALID_ADDR changing to location of    
// entry of exisiting file/folder) or if no more entry space (VALID_ADDR would    
// change to 0).    
sint scan_directory(ulong *VALID_ADDR, uchar *NAME)   
{   
    uint ent_cntr, ent_max, n, c, dir_clus;   
    ulong temp_addr;   
    uchar *sp, *qp, aval_flag, name_store[14];   
   
    aval_flag = 0;   
    ent_cntr = 0;   // set to 0    
   
    qp = NAME;   
    for (c=0; c<11; c++)   
    {   
        if (valid_file_char(*qp)==0)   
        {   
          #ifdef _IAR_EWAVR_    
            name_store[c] = toupper(*qp);   
            qp++;   
          #else    
            name_store[c] = toupper(*qp++);   
          #endif    
        }   
        else if (*qp == '.')   
        {   
            while (c<8)   
            {   
                name_store[c] = 0x20;   
                c++;   
            }   
            c--;   
            qp++;   
            aval_flag |= 1;   
        }   
        else if (*qp == 0)   
        {   
            while (c<11)   
            {   
                name_store[c] = 0x20;   
                c++;   
            }   
        }   
        else   
        {   
            *VALID_ADDR = 0;   
            return ((sint)EOF);   
        }   
    }   
    name_store[11] = 0;   
    if (*VALID_ADDR == _FF_ROOT_ADDR)   
        ent_max = BPB_RootEntCnt.ival;   
    else   
    {   
        dir_clus = addr_to_clust(*VALID_ADDR);   
        if (dir_clus != 0)   
            aval_flag |= 0x80;   
      #ifdef _BytsPerSec_512_    
        ent_max = (uint) BPB_SecPerClus << 4;   
      #else    
        ent_max = (BPB_BytsPerSec.ival >> 5) * (uint) BPB_SecPerClus;   
      #endif    
    }   
    c = 0;   
    while (ent_cntr < ent_max)   
    {   
        if (_FF_read(*VALID_ADDR+c, _FF_buff)==0)   
            break;   
        for (n=0; n<16; n++)   
        {   
            sp = &_FF_buff[n<<5];   
            qp = name_store;   
            if (*sp==0)   
            {   
                if ((aval_flag&0x10)==0)   
                  #ifdef _BytsPerSec_512_    
                    temp_addr = ((*VALID_ADDR + c) << 9) + (n << 5);   
                  #else    
                    temp_addr = ((*VALID_ADDR + c) * BPB_BytsPerSec.ival) + (n << 5);   
                  #endif    
                *VALID_ADDR = temp_addr;   
                return (0);   
            }   
            else if (*sp==0xE5)   
            {   
              #ifdef _BytsPerSec_512_    
                temp_addr = ((*VALID_ADDR + c) << 9) + (n << 5);   
              #else    
                temp_addr = ((*VALID_ADDR + c) * BPB_BytsPerSec.ival) + (n << 5);   
              #endif    
                aval_flag |= 0x10;   
            }   
            else   
            {   
                if (aval_flag & 0x01)   // file    
                {   
                    if (_FF_strncmp(qp, sp, 11)==0)   
                    {   
                      #ifdef _BytsPerSec_512_    
                        temp_addr = ((*VALID_ADDR + c) << 9) + (n << 5);   
                      #else    
                        temp_addr = ((*VALID_ADDR + c) * BPB_BytsPerSec.ival) + (n << 5);   
                      #endif    
                        *VALID_ADDR = temp_addr;   
                        return ((sint)EOF); // file exists @ temp_addr    
                    }   
                }   
                else                    // folder    
                {   
                    if ((_FF_strncmp(qp, sp, 11)==0)&&(*(sp+11)&0x10))   
                    {   
                      #ifdef _BytsPerSec_512_    
                        temp_addr = ((*VALID_ADDR + c) << 9) + (n << 5);   
                      #else    
                        temp_addr = ((*VALID_ADDR + c) * BPB_BytsPerSec.ival) + (n << 5);   
                      #endif    
                        *VALID_ADDR = temp_addr;   
                        return ((sint)EOF); // folder exists @ temp_addr    
                    }   
                }   
            }   
            ent_cntr++;   
        }   
        c++;   
        if (ent_cntr == ent_max)   
        {   
            if (aval_flag & 0x80)       // a folder @ a valid cluster    
            {   
                c = next_cluster(dir_clus, SINGLE);   
                if (c != (uint)EOF)   
                {   // another dir cluster exists    
                    *VALID_ADDR = clust_to_addr(c);   
                    dir_clus = c;   
                    ent_cntr = 0;   
                    c = 0;   
                }   
                else   
                {   
                    if (aval_flag & 0x10)   
                        break;   
                  #ifndef _READ_ONLY_    
                    if (*VALID_ADDR > _FF_ROOT_ADDR)   
                    {   
                        *VALID_ADDR = 0;   
                        return (dir_clus);   
                    }   
                  #endif    
                }   
            }   
        }   
    }   
    if (aval_flag&0x10)   
    {   
        *VALID_ADDR = temp_addr;   
        return (0);   
    }   
    else   
    {   
        *VALID_ADDR = 0;   
        return ((sint)EOF);   
    }   
}   
   
#ifdef _DEBUG_ON_    
schar flash __CR = '\r';   
schar flash __LF = '\n';   
schar flash __Tab = '\t';   
schar flash __OpenBracket = '[';   
schar flash __Period = '.';   
schar flash FileList_str[] = "\r\nFile Listing for:  ROOT\x5c";   
schar flash SC_str[] = "]\t(%X)";   
schar flash Entry_str[] = "\t[%ld] bytes\t(%X)\t";   
   
// Function to display all files and folders in the root directory,    
// with the size of the file in bytes within the [brakets]    
void read_directory(void)   
{   
    uchar valid_flag, attribute_temp;   
    uint c, n, d, m, dir_clus;   
  #ifdef _DIRECTORIES_SUPPORTED_    
    ulong dir_addr;   
  #endif    
    uHILO16 calc_clus;   
    uHILO32 calc;   
   
   
  #ifdef _DIRECTORIES_SUPPORTED_    
    if (_FF_DIR_ADDR != _FF_ROOT_ADDR)   
    {   
        dir_clus = addr_to_clust(_FF_DIR_ADDR);   
        if (dir_clus == 0)   
            return;   
    }   
  #endif    
   
    printf(FileList_str);   
    for (d=0; ((d<_FF_PATH_LENGTH)&&(_FF_FULL_PATH[d])); d++)   
        putchar(_FF_FULL_PATH[d]);   
   
  #ifdef _DIRECTORIES_SUPPORTED_    
    dir_addr = _FF_DIR_ADDR;   
  #endif    
    d = 0;   
    m = 0;   
    while (d<BPB_ROOTENTCNT.IVAL) name (_FF_read(dir_addr+m, #else (_FF_read(_FF_ROOT_ADDR+m, _FF_buff)="=0)" (n="0;" n<16; n++) ((c<11)&&(valid_flag)); make sure all characters the file folder are valid (_FF_buff[(n<<5)]="=0)" ?\0? in this location means no more avaliable n="16;" clear entries (valid_file_char(_FF_buff[(n<<5)+c])) valid_flag="1;" (valid_flag) 0xB; attribute_temp="_FF_buff[calc.ival.LO];" putchar(__Tab); putchar(__OpenBracket); c<8; (attribute_temp & 0x10) printf(SC_str, putchar(__Period); for (c="0;" c<11; c++) calc.ival.LO="(n" 5) c; (_FF_buff[calc.ival.LO]="=0x20)" putchar(_FF_buff[calc.ival.LO]); c="(n" << 5); calc.cval.HI="_FF_buff[c+0x1F];" calc.cval.MH="_FF_buff[c+0x1E];" calc.cval.ML="_FF_buff[c+0x1D];" calc.cval.LO="_FF_buff[c+0x1C];" calc_clus.cval.HI="_FF_buff[c+0x1B];" calc_clus.cval.LO="_FF_buff[c+0x1A];" printf(Entry_str, calc.lval, calc_clus.ival); d++; m++; #ifdef _DIRECTORIES_SUPPORTED_ (_FF_ROOT_ADDR!="_FF_DIR_ADDR)" SINGLE); (m="=BPB_SecPerClus)" !="(uint)EOF)" another exists dir_addr="clust_to_addr(m);" dir_clus="m;" d="BPB_RootEntCnt.ival;" m="next_cluster(dir_clus," else break; putchar(__CR); putchar(__LF); #endif VolSerialStr[]="\r\n\tVolume Serial:\t[0x%lX]" schar flash VolLabelStr[]="\r\n\tVolume Label:\t[%s]\r\n" ; void GetVolID(void) printf(VolSerialStr, BS_VolSerial.lval); printf(VolLabelStr, BS_VolLab); Convert read clust_to_addr(uint clust_no) ulong FirstSectorofCluster; (clust_no FirstSectorofCluster="((clust_no" 2) * BPB_SecPerClus) FirstDataSector; (FirstSectorofCluster _FF_PART_ADDR); Converts an address into a cluster number uint addr_to_clust(ulong clus_addr) < (ulong) FirstDataSector) { return (0); } - clus_addr="BPB_SecPerClus;" + if (clus_addr> 0xFFFF)   
    {   
        return (0);   
    }   
    return ((sint) clus_addr);   
}   
   
// Find the cluster that the current cluster is pointing to    
uint next_cluster(uint current_cluster, uchar mode)   
{   
    uint calc_sec, calc_offset, calc_remainder;   
    uHILO16 next_clust;   
    ulong addr_temp;   
   
    if (current_cluster<=1)      // If cluster is 0 or 1, its the wrong cluster    
        return ((uint)EOF);   
   
    if (BPB_FATType == 0x36)        // if FAT16    
    {   
        // FAT16 table address calculations    
      #ifdef _BytsPerSec_512_    
        calc_sec = (current_cluster >> 8) + BPB_RsvdSecCnt.ival;   
        calc_offset = (current_cluster & 0xFF) << 1;   
      #else    
        calc_sec = current_cluster / (BPB_BytsPerSec.ival >> 1) + BPB_RsvdSecCnt.ival;   
        calc_offset = (current_cluster % (BPB_BytsPerSec.ival >> 1)) << 1;   
      #endif    
   
        addr_temp = _FF_PART_ADDR+(calc_sec);   
        if (mode==SINGLE)   
        {   // This is a single cluster lookup    
            if (_FF_read(addr_temp, _FF_buff)==0)   
                return((uint)EOF);   
        }   
        else if (mode==CHAIN)   
        {   // Mupltiple clusters to lookup    
            if (addr_temp!=_FF_buff_addr)   
            {   // Is the address of lookup is different then the current buffere address    
              #ifndef _READ_ONLY_    
                if (_FF_buff_addr && mode)  // if the buffer address is 0, don't write    
                {   
                  #ifdef _SECOND_FAT_ON_    
                    if (_FF_buff_addr < _FF_FAT2_ADDR)   
                        if (_FF_write(_FF_buff_addr+BPB_FATSz16.ival, _FF_buff)==0)   
                            return((uint)EOF);   
                  #endif    
                    if (_FF_write(_FF_buff_addr, _FF_buff)==0)  // Save buffer data to card    
                        return((uint)EOF);   
                }   
              #endif    
                if (_FF_read(addr_temp, _FF_buff)==0)   // Read new table info    
                    return((uint)EOF);   
            }   
        }   
        next_clust.cval.HI = _FF_buff[calc_offset+1];   
        next_clust.cval.LO = _FF_buff[calc_offset];   
    }   
  #ifdef _FAT12_ON_    
    else if (BPB_FATType == 0x32)   // if FAT12    
    {   
        // FAT12 table address calculations    
        calc_offset = (current_cluster * 3) >> 1;   
        calc_remainder = current_cluster & 1;   
      #ifdef _BytsPerSec_512_    
        calc_sec = (calc_offset >> 9) + BPB_RsvdSecCnt.ival;   
        calc_offset &= 0x1FF;   
      #else    
        calc_sec = (calc_offset / BPB_BytsPerSec.ival) + BPB_RsvdSecCnt.ival;   
        calc_offset %= BPB_BytsPerSec.ival;   
      #endif    
   
        addr_temp = _FF_PART_ADDR+(calc_sec);   
        if (mode==SINGLE)   
        {   // This is a single cluster lookup    
            if (_FF_read(addr_temp, _FF_buff)==0)   
                return((uint)EOF);   
        }   
        else if (mode==CHAIN)   
        {   // Mupltiple clusters to lookup    
            if (addr_temp!=_FF_buff_addr)   
            {   // Is the address of lookup is different then the current buffere address    
              #ifndef _READ_ONLY_    
                if (_FF_buff_addr && mode)  // if the buffer address is 0, don't write    
                {   
                  #ifdef _SECOND_FAT_ON_    
                    if (_FF_buff_addr < _FF_FAT2_ADDR)   
                        if (_FF_write(_FF_buff_addr+BPB_FATSz16.ival, _FF_buff)==0)   
                            return((uint)EOF);   
                  #endif    
                    if (_FF_write(_FF_buff_addr, _FF_buff)==0)  // Save buffer data to card    
                        return((uint)EOF);   
                }   
              #endif    
                if (_FF_read(addr_temp, _FF_buff)==0)   // Read new table info    
                    return((uint)EOF);   
            }   
        }   
        next_clust.cval.LO = _FF_buff[calc_offset];   
      #ifdef _BytsPerSec_512_    
        if (calc_offset == 511)   
      #else    
        if (calc_offset == (BPB_BytsPerSec.ival-1))   
      #endif    
        {   // Is the FAT12 record accross more than one sector?    
            addr_temp = _FF_PART_ADDR+(calc_sec+1);   
            if (mode==CHAIN)   
            {   // multiple chain lookup    
              #ifndef _READ_ONLY_    
               #ifdef _SECOND_FAT_ON_    
                if (_FF_buff_addr < _FF_FAT2_ADDR)   
                    if (_FF_write(_FF_buff_addr+BPB_FATSz16.ival, _FF_buff)==0)   
                        return((uint)EOF);   
               #endif    
                if (_FF_write(_FF_buff_addr, _FF_buff)==0)  // Save buffer data to card    
                    return((uint)EOF);   
              #endif    
                _FF_buff_addr = addr_temp;      // Save new buffer address    
            }   
            if (_FF_read(addr_temp, _FF_buff)==0)   
                return((uint)EOF);   
            next_clust.cval.HI = _FF_buff[0];   
        }   
        else   
            next_clust.cval.HI = _FF_buff[calc_offset+1];   
   
        if (calc_remainder)   
            next_clust.ival >>= 4;   
        else   
            next_clust.cval.HI &= 0x0F;   
   
        if (next_clust.ival >= 0xFF8)   
            next_clust.cval.HI = 0xFF;   
    }   
  #endif    
    else        // not FAT12 or FAT16, return 0    
        return ((uint)EOF);   
    return (next_clust.ival);   
}   
   
   
// Function that tells you the number of available clusters left on the disk    
uint available_clusters(void)   
{   
    uint i, cnt;   
   
    cnt = 0;   
   
    for (i=2; i<(DataClusTot); i++)   
    {   
        if (next_cluster(i, CHAIN) == 0)   
            cnt++;   
    }   
   
    return (cnt);   
}   
   
   
// Convert a constant string file name into the proper 8.3 FAT format    
uchar *file_name_conversion(uchar *current_file)   
{   
    uchar n, c;   
   
    c = 0;   
   
    for (n=0; n<14; n++)   
    {   
        if (valid_file_char(current_file[n])==0)   
        {   
            // If the character is valid, save in uppercase to file name buffer    
            FILENAME[c] = toupper(current_file[n]);   
            c++;   
        }   
        else if (current_file[n]=='.')   
        {   
            // If it is a period, back fill buffer with [spaces], till 8 characters deep    
            while (c<8)   
            {   
                FILENAME[c] = 0x20;   
                c++;   
            }   
        }   
        else if (current_file[n]==0)   
        {   // If it is NULL, back fill buffer with [spaces], till 11 characters deep    
            while (c<11)   
            {   
                FILENAME[c] = 0x20;   
                c++;   
            }   
            break;   
        }   
        else   
        {   
            _FF_error = NAME_ERR;   
            return (0);   
        }   
        if (c>=11)   
            break;   
    }   
    FILENAME[c] = 0;   
    // Return the pointer of the filename    
    return (FILENAME);   
}   
   
// Find the first cluster that is pointing to clus_no    
uint prev_cluster(uint clus_no)   
{   
    uchar read_flag;   
    uint calc_temp, n, c, n_temp;   
    ulong addr_temp;   
    uHILO16 calc_clus;   
   
    addr_temp = _FF_FAT1_ADDR;   
    c = 1;   
    if ((clus_no==0) && (BPB_FATType==0x36))   
    {   
        if (clus_0_addr>addr_temp)   
        {   
            addr_temp = clus_0_addr;   
            c = c_counter;   
        }   
    }   
   
    read_flag = 1;   
   
    while (addr_temp<_FF_FAT2_ADDR)   
    {   
        if (BPB_FATType == 0x36)        // if FAT16    
        {   
            if (clus_no==0)   
            {   
                clus_0_addr = addr_temp;   
                c_counter = c;   
            }   
            if (_FF_read(addr_temp, _FF_buff)==0)       // Read error ==> break    
                return(0);   
            if (_FF_n_temp)   
            {   
                n_temp = _FF_n_temp;   
                _FF_n_temp = 0;   
            }   
            else   
                n_temp = 0;   
   
          #ifdef _BytsPerSec_512_    
            for (n=n_temp; n<256; n++)   
          #else    
            for (n=n_temp; n<(BPB_BytsPerSec.ival>>1); n++)   
          #endif    
            {   
                calc_clus.cval.HI = _FF_buff[(n<<1)+1];   
                calc_clus.cval.LO = _FF_buff[n<<1];   
              #ifdef _BytsPerSec_512_    
                calc_temp = n + ((c - 1) << 8);   
              #else    
                calc_temp = (uint) (n + (((ulong) BPB_BytsPerSec.ival>>1) * ((ulong) c - 1)));   
              #endif    
                if (calc_clus.ival==clus_no)   
                {   
                    if (calc_clus.ival==0)   
                        _FF_n_temp = n;   
                    return(calc_temp);   
                }   
                else if (calc_temp > DataClusTot)   
                {   
                    _FF_error = DISK_FULL;   
                    return (0);   
                }   
            }   
            addr_temp++;   
            c++;   
        }   
      #ifdef _FAT12_ON_    
        else if (BPB_FATType == 0x32)   // if FAT12    
        {   
            if (read_flag)   
            {   
                if (_FF_read(addr_temp, _FF_buff)==0)   
                {   
                    return (0); // if the read fails return 0    
                }   
                read_flag = 0;   
            }   
            calc_temp = ((ulong) c * 3) >> 1;   
          #ifdef _BytsPerSec_512_    
            calc_temp &= 0x1FF;   
          #else    
            calc_temp %= BPB_BytsPerSec.ival;   
          #endif    
            calc_clus.cval.LO = _FF_buff[calc_temp];   
            calc_temp++;   
          #ifdef _BytsPerSec_512_    
            if (calc_temp == 512)   
          #else    
            if (calc_temp == BPB_BytsPerSec.ival)   
          #endif    
            {   // Is the FAT12 record accross a sector?    
                addr_temp++;   
                if (_FF_read(addr_temp, _FF_buff)==0)   
                {   
                    return (0);   
                }   
                calc_clus.cval.HI = _FF_buff[0];   
                calc_temp = 0;   
            }   
            else   
            {   
                calc_clus.cval.HI = _FF_buff[calc_temp];   
                calc_temp++;   
            }   
            if (c & 1)   
                calc_clus.ival >>= 4;   
            else   
                calc_clus.cval.HI &= 0x0F;   
   
            if (calc_clus.ival == clus_no)   
            {   
                return (c);   
            }   
            else if (c > DataClusTot)   
            {   
                _FF_error = DISK_FULL;   
                return (0);   
            }   
          #ifdef _BytsPerSec_512_    
            if ((calc_temp == 512) && (c & 1))   
          #else    
            if ((calc_temp == BPB_BytsPerSec.ival) && (c & 1))   
          #endif    
            {   
                addr_temp++;   
                read_flag = 1;   
            }   
   
            c++;   
        }   
      #endif    
        else   
        {   
            return (0);   
        }   
    }   
    _FF_error = DISK_FULL;   
    return (0);   
}   
   
#ifndef _READ_ONLY_    
// Update cluster table to point to new cluster    
uchar write_clus_table(uint current_cluster, uint next_value, uchar mode)   
{   
    ulong addr_temp;   
    uint calc_sec, calc_offset, calc_temp, calc_remainder;   
    uchar nibble[3];   
    uHILO16 temp_int;   
   
    if (current_cluster <= 1)        // Should never be writing to cluster 0 or 1    
    {   
        return (0);   
    }   
    temp_int.ival = next_value;   
    if (BPB_FATType == 0x36)        // if FAT16    
    {   
      #ifdef _BytsPerSec_512_    
        calc_sec = (current_cluster >> 8) + BPB_RsvdSecCnt.ival;   
        calc_offset = (current_cluster & 0xFF) << 1;   
      #else    
        calc_sec = current_cluster / (BPB_BytsPerSec.ival >> 1) + BPB_RsvdSecCnt.ival;   
        calc_offset = (current_cluster % (BPB_BytsPerSec.ival >> 1)) << 1;   
      #endif    
        addr_temp = _FF_PART_ADDR + calc_sec;   
        if (mode==SINGLE)   
        {   // Updating a single cluster (like writing or saving a file)    
            if (_FF_read(addr_temp, _FF_buff)==0)   
            {   
                return(0);   
            }   
        }   
        else if ((mode==CHAIN) || (mode==END_CHAIN))   
        {   // Multiple table access operation    
            if (addr_temp!=_FF_buff_addr)   
            {   // if the desired address is already in the buffer => skip loading buffer    
                if (_FF_buff_addr)  // if new table address, write buffered, and load new    
                {   
                  #ifdef _SECOND_FAT_ON_    
                    if (_FF_buff_addr < _FF_FAT2_ADDR)   
                    {   
                        if (_FF_write(_FF_buff_addr+BPB_FATSz16.ival, _FF_buff)==0)   
                        {   
                            return(0);   
                        }   
                    }   
                  #endif    
                    if (_FF_write(_FF_buff_addr, _FF_buff)==0)   
                    {   
                        return(0);   
                    }   
                }   
                if (_FF_read(addr_temp, _FF_buff)==0)   
                {   
                    return(0);   
                }   
            }   
        }   
   
        _FF_buff[calc_offset+1] = temp_int.cval.HI;   
        _FF_buff[calc_offset] = temp_int.cval.LO;   
        if ((mode==SINGLE) || (mode==END_CHAIN))   
        {   
          #ifdef _SECOND_FAT_ON_    
            if (_FF_write(addr_temp+BPB_FATSz16.ival, _FF_buff)==0)   
            {   
                return(0);   
            }   
          #endif    
            if (_FF_write(addr_temp, _FF_buff)==0)   
            {   
                return(0);   
            }   
        }   
    }   
  #ifdef _FAT12_ON_    
    else if (BPB_FATType == 0x32)       // if FAT12    
    {   
        calc_offset = (current_cluster * 3) >> 1;   
        calc_remainder = current_cluster & 1;   
      #ifdef _BytsPerSec_512_    
        calc_sec = (calc_offset >> 9) + BPB_RsvdSecCnt.ival;   
        calc_offset &= 0x1FF;   
      #else    
        calc_sec = calc_offset / BPB_BytsPerSec.ival + BPB_RsvdSecCnt.ival;   
        calc_offset %= BPB_BytsPerSec.ival;   
      #endif    
        addr_temp = _FF_PART_ADDR + calc_sec;   
        if (mode==SINGLE)   
        {   
            if (_FF_read(addr_temp, _FF_buff)==0)   
            {   
                return(0);   
            }   
        }   
        else if ((mode==CHAIN) || (mode==END_CHAIN))   
        {   
            if (addr_temp!=_FF_buff_addr)   
            {   
                if (_FF_buff_addr)   
                {   
                  #ifdef _SECOND_FAT_ON_    
                    if (_FF_buff_addr < _FF_FAT2_ADDR)   
                    {   
                        if (_FF_write(_FF_buff_addr+BPB_FATSz16.ival, _FF_buff)==0)   
                        {   
                            return(0);   
                        }   
                    }   
                  #endif    
                    if (_FF_write(_FF_buff_addr, _FF_buff)==0)   
                        return(0);   
                }   
                if (_FF_read(addr_temp, _FF_buff)==0)   
                {   
                    return(0);   
                }   
            }   
        }   
        nibble[0] = temp_int.cval.LO & 0x0F;   
        nibble[1] = (temp_int.ival >> 4) & 0x00F;   
        nibble[2] = temp_int.cval.HI & 0x0F;   
   
      #ifdef _BytsPerSec_512_    
        if (calc_offset == 511)   
      #else    
        if (calc_offset == (BPB_BytsPerSec.ival-1))   
      #endif    
        {   // Is the FAT12 record accross a sector?    
            if (calc_remainder)   
            {   // Record table uses 1 nibble of last byte    
                calc_temp = _FF_buff[calc_offset] & 0x0F;   // Mask to add new value    
                _FF_buff[calc_offset] = calc_temp | (nibble[0] << 4); // store nibble in correct location    
              #ifdef _SECOND_FAT_ON_    
                if (_FF_write(addr_temp+BPB_FATSz16.ival, _FF_buff)==0)   
                {   
                    return(0);   
                }   
              #endif    
                if (_FF_write(addr_temp, _FF_buff)==0)   
                {   
                    return(0);   
                }   
                addr_temp++;   
                if (_FF_read(addr_temp, _FF_buff)==0)   
                {   
                    return(0);  // if the read fails return 0    
                }   
                _FF_buff[0] = (nibble[2] << 4) | nibble[1];   
                if ((mode==SINGLE) || (mode==END_CHAIN))   
                {   
                  #ifdef _SECOND_FAT_ON_    
                    if (_FF_write(addr_temp+BPB_FATSz16.ival, _FF_buff)==0)   
                    {   
                        return(0);   
                    }   
                  #endif    
                    if (_FF_write(addr_temp, _FF_buff)==0)   
                    {   
                        return(0);   
                    }   
                }   
            }   
            else   
            {   // Record table uses whole last byte    
                _FF_buff[calc_offset] = (nibble[1] << 4) | nibble[0];   
              #ifdef _SECOND_FAT_ON_    
                if (_FF_write(addr_temp+BPB_FATSz16.ival, _FF_buff)==0)   
                {   
                    return(0);   
                }   
              #endif    
                if (_FF_write(addr_temp, _FF_buff)==0)   
                {   
                    return(0);   
                }   
                addr_temp++;   
                if (_FF_read(addr_temp, _FF_buff)==0)   
                {   
                    return(0);  // if the read fails return 0    
                }   
                calc_temp = _FF_buff[0] & 0xF0;     // Mask to add new value    
                _FF_buff[0] = calc_temp | nibble[2];    // store nibble in correct location    
                if ((mode==SINGLE) || (mode==END_CHAIN))   
                {   
                  #ifdef _SECOND_FAT_ON_    
                    if (_FF_write(addr_temp+BPB_FATSz16.ival, _FF_buff)==0)   
                    {   
                        return(0);   
                    }   
                  #endif    
                    if (_FF_write(addr_temp, _FF_buff)==0)   
                    {   
                        return(0);   
                    }   
                }   
            }   
        }   
        else   
        {   
            if (calc_remainder)   
            {   // Record table uses 1 nibble of current byte    
                calc_temp = _FF_buff[calc_offset] & 0x0F;   // Mask to add new value    
                _FF_buff[calc_offset] = calc_temp | (nibble[0] << 4); // store nibble in correct location    
                _FF_buff[calc_offset+1] = (nibble[2] << 4) | nibble[1];   
                if ((mode==SINGLE) || (mode==END_CHAIN))   
                {   
                  #ifdef _SECOND_FAT_ON_    
                    if (_FF_write(addr_temp+BPB_FATSz16.ival, _FF_buff)==0)   
                    {   
                        return(0);   
                    }   
                  #endif    
                    if (_FF_write(addr_temp, _FF_buff)==0)   
                    {   
                        return(0);   
                    }   
                }   
            }   
            else   
            {   // Record table uses whole current byte    
                _FF_buff[calc_offset] = (nibble[1] << 4) | nibble[0];   
                calc_temp = _FF_buff[calc_offset+1] & 0xF0;     // Mask to add new value    
                _FF_buff[calc_offset+1] = calc_temp | nibble[2];    // store nibble in correct location    
                if ((mode==SINGLE) || (mode==END_CHAIN))   
                {   
                  #ifdef _SECOND_FAT_ON_    
                    if (_FF_write(addr_temp+BPB_FATSz16.ival, _FF_buff)==0)   
                    {   
                        return(0);   
                    }   
                  #endif    
                    if (_FF_write(addr_temp, _FF_buff)==0)   
                    {   
                        return(0);   
                    }   
                }   
            }   
        }   
    }   
  #endif    
    else        // not FAT12 or FAT16, return 0    
    {   
        return (0);   
    }   
    return(1);   
}   
#endif    
   
#ifndef _READ_ONLY_    
// Save new entry data to FAT entry    
uchar append_toc(FILE *rp)   
{   
    uHILO32 file_data;   
    uint n;   
    uHILO16 calc_temp;   
   
    if (rp==NULL)   
        return (0);   
   
    file_data.lval = rp->length;   
    if (_FF_read(rp->entry_sec_addr, _FF_buff)==0)   
        return (0);   
   
    // Update Starting Cluster    
    n = rp->entry_offset+0x1a;   
    calc_temp.ival = rp->clus_start;   
    _FF_buff[n] = calc_temp.cval.LO;   
    n++;   
    _FF_buff[n] = calc_temp.cval.HI;   
    n++;   
   
    // Update the File Size    
    _FF_buff[n] = file_data.cval.LO;   
    n++;   
    _FF_buff[n] = file_data.cval.ML;   
    n++;   
    _FF_buff[n] = file_data.cval.MH;   
    n++;   
    _FF_buff[n] = file_data.cval.HI;   
    n++;   
   
  #ifdef _RTC_ON_   // Date/Time Stamp file w/ RTC    
    n = rp->entry_offset+0x16;   
    rtc_get_timeNdate(&rtc_hour, &rtc_min, &rtc_sec, &rtc_date, &rtc_month, &rtc_year);   
    calc_temp.ival = ((uint)rtc_sec&0x1F) | (((uint)rtc_min&0x3F)<<5) | (((uint)rtc_hour&0x1F)<<11);   
    _FF_buff[n] = calc_temp.cval.LO;    // File create Time    
    n++;   
    _FF_buff[n] = calc_temp.cval.HI;   
    n++;   
    calc_temp.ival = ((uint)rtc_date&0x1F) | (((uint)rtc_month&0x0F)<<5) | (((rtc_year-1980)&0x7F)<<9);   
    _FF_buff[n] = calc_temp.cval.LO;    // File create Date    
    n++;   
    _FF_buff[n] = calc_temp.cval.HI;   
    n++;   
  #else     // Increment Date Code, no RTC used    
    n = rp->entry_offset+0x19;   
    file_data.cval.HI = _FF_buff[n];   
    n--;   
    file_data.cval.MH = _FF_buff[n];   
    n--;   
    file_data.cval.ML = _FF_buff[n];   
    n--;   
    file_data.cval.LO = _FF_buff[n];   
    file_data.lval++;   
    file_data.cval.LO = _FF_buff[n];   
    n++;   
    file_data.cval.ML = _FF_buff[n];   
    n++;   
    file_data.cval.MH = _FF_buff[n];   
    n++;   
    file_data.cval.HI = _FF_buff[n];   
  #endif    
    if (_FF_write(rp->entry_sec_addr, _FF_buff)==0)   
        return(0);   
   
    return(1);   
}   
#endif    
   
#ifndef _READ_ONLY_    
// Erase a chain of clusters (set table entries to 0 for clusters in chain)    
uchar erase_clus_chain(uint start_clus)   
{   
    uint clus_temp, clus_use;   
   
    if (start_clus==0)   
        return (0);   
    clus_use = start_clus;   
    _FF_buff_addr = 0;   
    while(clus_use <= 0xFFF8)   
    {   
        clus_temp = next_cluster(clus_use, CHAIN);   
        if ((clus_temp >= 0xFFF8) || (clus_temp == 0))   
            break;   
        if (write_clus_table(clus_use, 0, CHAIN) == 0)   
            return (0);   
        clus_use = clus_temp;   
    }   
    if (write_clus_table(clus_use, 0, END_CHAIN) == 0)   
        return (0);   
    clus_0_addr = 0;   
    c_counter = 1;   
   
    return (1);   
}   
   
// Quickformat of a card (erase cluster table and root directory    
sint fquickformat(void)   
{   
    ulong c;   
   
  #ifdef _BytsPerSec_512_    
    for (c=0; c<512; c++)   
  #else    
    for (c=0; c<BPB_BYTSPERSEC.IVAL; #else _FF_buff)="=0)" the means & for (c c++) c; c="_FF_FAT1_ADDR" <<="9;" #ifdef _DIRECTORIES_SUPPORTED_ else #endif ulong *="BPB_BytsPerSec.ival;" into a uint < { return (0); } + if _FF_buff[c]="0;" BPB_RsvdSecCnt.ival; while (_FF_ROOT_ADDR ((uint) BPB_SecPerClus<<2))) (_FF_write(c, c++; _FF_buff[0]="0xF8;" _FF_buff[1]="0xFF;" _FF_buff[2]="0xFF;" (BPB_FATType="=" 0x36) _FF_buff[3]="0xFF;" ((_FF_write(_FF_FAT1_ADDR, (_FF_write(_FF_FAT2_ADDR, _FF_error="WRITE_ERR;" function checks directory changes then gets working form _FF_checkdir(uchar *F_PATH, *SAVE_ADDR, *path_temp) *SAVE_ADDR="_FF_DIR_ADDR;" qp="F_PATH;" If there is \ that it starts at root while(*qp) ((valid_file_char(*qp)="=0)" _IAR_EWAVR_ sp++; *sp++="toupper(*qp++);" (*qp="='\\')" (_FF_chdir(path_temp)) sp="path_temp;" qp++; *sp="toupper(*qp);" terminate string #ifndef _READ_ONLY_ mkdir(uchar *F_PATH) *sp, *qp; uchar fpath[14]; calc_temp; clus_temp; _RTC_ON_ uHILO16 calc_time, calc_date; sint s; addr_temp, path_addr_temp; addr_temp="0;" save local addr (_FF_checkdir(F_PATH, &addr_temp, fpath)) s="scan_directory(&path_addr_temp," fpath); ((s="=(sint)EOF)" (path_addr_temp="=0))" ((clus_temp.ival="=" || (write_clus_table(s, clus_temp.ival, CHAIN)="=" 0)) (write_clus_table(clus_temp.ival, (uint)EOF, END_CHAIN)="=0)" s<512; (s="=(sint)EOF)" s<BPB_BytsPerSec.ival; s++) _FF_buff[s]="0;" c<BPB_SecPerClus; (_FF_write(path_addr_temp c, 0) _FF_DIR_ADDR="_FF_ROOT_ADDR;" ((sint)EOF); clus_temp.ival="prev_cluster(0);" _BytsPerSec_512_ calc_temp="path_addr_temp" 0x1FF; path_addr_temp="_FF_DIR_ADDR;">>= 9;   
  #else    
    calc_temp = path_addr_temp % BPB_BytsPerSec.ival;   
    path_addr_temp /= BPB_BytsPerSec.ival;   
  #endif    
   
    if (_FF_read(path_addr_temp, _FF_buff)==0)   
    {   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
   
    sp = &_FF_buff[calc_temp];   
    qp = fpath;   
   
  #ifdef _IAR_EWAVR_    
    for (c=0; c<11; c++) // Write Folder name    
    {   
        if (*qp)   
        {   
            *sp = *qp;   
            sp++;   
            qp++;   
        }   
        else   
        {   
            *sp = 0x20; // '0' pad    
            sp++;   
        }   
    }   
    *sp = 0x10;             // Attribute bit auto set to "Directory"    
    sp++;   
    *sp = 0;                    // Reserved for WinNT    
    sp++;   
    *sp = 0;                    // Mili-second stamp for create    
    sp++;   
    for (c=0; c<4; c++)          // set create and modify time to '0'    
    {   
        *sp = 0;   
        sp++;   
    }   
    *sp = 0;                    // File access date (2 bytes)    
    sp++;   
    *sp = 0;   
    sp++;   
    *sp = 0;                    // 0 for FAT12/16 (2 bytes)    
    sp++;   
    *sp = 0;   
    sp++;   
   #ifdef _RTC_ON_    
    rtc_get_timeNdate(&rtc_hour, &rtc_min, &rtc_sec, &rtc_date, &rtc_month, &rtc_year);   
    calc_time.ival = ((sint)rtc_sec&0x1F) | (((sint)rtc_min&0x3F)<<5) | (((sint)rtc_hour&0x1F)<<11);   
    *sp = calc_time.cval.LO;    // File modify Time    
    sp++;   
    *sp = calc_time.cval.HI;   
    sp++;   
    calc_date.ival = ((sint)rtc_date&0x1F) | (((sint)rtc_month&0x0F)<<5) | (((rtc_year-1980)&0x7F)<<9);   
    *sp = calc_date.cval.LO;    // File modify Date    
    sp++;   
    *sp = calc_date.cval.HI;   
    sp++;   
   #else    
    for (c=0; c<4; c++)          // set file create and modify time to '0'    
    {   
        *sp = 0;            // File length (0 for folder)    
        sp++;   
    }   
   #endif    
   
    *sp = clus_temp.cval.LO;                // Starting cluster (2 bytes)    
    sp++;   
    *sp = clus_temp.cval.HI;   
    sp++;   
    for (c=0; c<4; c++)   
    {   
        *sp = 0;            // File length (0 for folder)    
        sp++;   
    }   
  #else    
    for (c=0; c<11; c++) // Write Folder name    
    {   
        if (*qp)   
            *sp++ = *qp++;   
        else   
            *sp++ = 0x20;   // '0' pad    
    }   
    *sp++ = 0x10;               // Attribute bit auto set to "Directory"    
    *sp++ = 0;                  // Reserved for WinNT    
    *sp++ = 0;                  // Mili-second stamp for create    
    for (c=0; c<4; c++)          // set create and modify time to '0'    
        *sp++ = 0;   
    *sp++ = 0;                  // File access date (2 bytes)    
    *sp++ = 0;   
    *sp++ = 0;                  // 0 for FAT12/16 (2 bytes)    
    *sp++ = 0;   
   #ifdef _RTC_ON_    
    rtc_get_timeNdate(&rtc_hour, &rtc_min, &rtc_sec, &rtc_date, &rtc_month, &rtc_year);   
    calc_time.ival = ((sint)rtc_sec&0x1F) | (((sint)rtc_min&0x3F)<<5) | (((sint)rtc_hour&0x1F)<<11);   
    *sp++ = calc_time.cval.LO;  // File modify Time    
    *sp++ = calc_time.cval.HI;   
    calc_date.ival = ((sint)rtc_date&0x1F) | (((sint)rtc_month&0x0F)<<5) | (((rtc_year-1980)&0x7F)<<9);   
    *sp++ = calc_date.cval.LO;  // File modify Date    
    *sp++ = calc_date.cval.HI;   
   #else    
    for (c=0; c<4; c++)          // set file create and modify time to '0'    
        *sp++ = 0;   
   #endif    
   
    *sp++ = clus_temp.cval.LO;              // Starting cluster (2 bytes)    
    *sp++ = clus_temp.cval.HI;   
    for (c=0; c<4; c++)   
        *sp++ = 0;          // File length (0 for folder)    
  #endif    
    if (_FF_write(path_addr_temp, _FF_buff)==0) // write entry to card    
    {   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
    if (write_clus_table(clus_temp.ival, 0xFFFF, SINGLE)==0)   
    {   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
    if (_FF_read(_FF_DIR_ADDR, _FF_buff)==0)   
    {   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
    if (_FF_DIR_ADDR != _FF_ROOT_ADDR)   
    {   
        sp = &_FF_buff[0];   
        qp = &_FF_buff[0x20];   
        for (c=0; c<0x20; c++)   
          #ifdef _IAR_EWAVR_    
        {   
            *qp = *sp;   
            qp++;   
            sp++;   
        }   
          #else    
            *qp++ = *sp++;   
          #endif    
        _FF_buff[1] = ' ';   
        for (c=0x3C; c<0x40; c++)   
            _FF_buff[c] = 0;   
    }   
    else   
    {   
        for (c=0x01; c<0x0B; c++)   
            _FF_buff[c] = 0x20;   
        for (c=0x0C; c<0x20; c++)   
            _FF_buff[c] = 0;   
        _FF_buff[0] = '.';   
        _FF_buff[0x0B] = 0x10;   
      #ifdef _RTC_ON_    
        _FF_buff[0x0E] = calc_time.cval.LO; // File modify Time    
        _FF_buff[0x0F] = calc_time.cval.HI;   
        _FF_buff[0x10] = calc_date.cval.LO; // File modify Date    
        _FF_buff[0x11] = calc_date.cval.HI;   
        _FF_buff[0x16] = calc_time.cval.LO; // File modify Time    
        _FF_buff[0x17] = calc_time.cval.HI;   
        _FF_buff[0x18] = calc_date.cval.LO; // File modify Date    
        _FF_buff[0x19] = calc_date.cval.HI;   
      #endif    
        for (c=0x3A; c<0x40; c++)   
            _FF_buff[c] = 0;   
    }   
    for (c=0x22; c<0x2B; c++)   
        _FF_buff[c] = 0x20;   
  #ifdef _RTC_ON_    
    _FF_buff[0x2E] = calc_time.cval.LO; // File modify Time    
    _FF_buff[0x2F] = calc_time.cval.HI;   
    _FF_buff[0x30] = calc_date.cval.LO; // File modify Date    
    _FF_buff[0x31] = calc_date.cval.HI;   
    _FF_buff[0x36] = calc_time.cval.LO; // File modify Time    
    _FF_buff[0x37] = calc_time.cval.HI;   
    _FF_buff[0x38] = calc_date.cval.LO; // File modify Date    
    _FF_buff[0x39] = calc_date.cval.HI;   
  #endif    
   
    _FF_buff[0x20] = '.';   
    _FF_buff[0x21] = '.';   
    _FF_buff[0x2B] = 0x10;   
   
    _FF_buff[0x1A] = clus_temp.cval.LO;             // Starting cluster (2 bytes)    
    _FF_buff[0x1B] = clus_temp.cval.HI;   
   
  #ifdef _BytsPerSec_512_    
    for (s=0x40; s<512; s++)   
  #else    
    for (s=0x40; s<BPB_BYTSPERSEC.IVAL; _FF_buff)="=0)" (n="0;" n++) file folder valid n="2;" entries & for (c="0;" c++) c="BPB_SecPerClus;" #ifdef !="(sint)EOF)" break; #endif read ulong address a uint { return (0); } if _FF_buff[c]="0;" while directory is it sp++; sp="&_FF_buff[n<<5];" *F_PATH) uchar fpath[14]; calc_temp; clus_temp; uHILO16 sint s; addr_temp, path_addr_temp; addr_temp="0;" save local addr (_FF_checkdir(F_PATH, &addr_temp, fpath)) s="scan_directory(&path_addr_temp," fpath); (s s++) _FF_buff[s]="0;" c<BPB_SecPerClus; c, _FF_DIR_ADDR="addr_temp;" ((sint)EOF); _BytsPerSec_512_ calc_temp="path_addr_temp" 0x1FF; path_addr_temp="clust_to_addr(clus_temp.ival);" (_FF_write(path_addr_temp, c<0x40; (_FF_write(path_addr_temp+c, rmdir(uchar *sp; n, (fpath[0]="=0)" later (_FF_chdir(fpath)) Change be deleted ((_FF_DIR_ADDR="=_FF_ROOT_ADDR)||(_FF_DIR_ADDR==addr_temp))" trying root, current error scan through see empty (_FF_read(_FF_DIR_ADDR+c, sectors n<0x10; ((c="=0)&&(n==0))" skip first 2 (*sp="=0)" (valid_file_char(*sp)="=0)" (sp="=" &_FF_buff[(n<<5)+0x0A]) or found empty, delete go back to previous reset>>= 9;   
  #else    
    calc_temp = path_addr_temp % BPB_BytsPerSec.ival;   
    path_addr_temp /= BPB_BytsPerSec.ival;   
  #endif    
   
    if (_FF_read(path_addr_temp, _FF_buff)==0)   
        return ((sint)EOF);   
   
    clus_temp.cval.HI = _FF_buff[calc_temp+0x1B];   
    clus_temp.cval.LO = _FF_buff[calc_temp+0x1A];   
    _FF_buff[calc_temp] = 0xE5;   
   
    if (_FF_buff[calc_temp+0x0B]&0x02)   
        return ((sint)EOF);   
    if (_FF_write(path_addr_temp, _FF_buff)==0)   
        return ((sint)EOF);   
    if (erase_clus_chain(clus_temp.ival)==0)   
        return ((sint)EOF);   
   
    return (0);   
}   
#endif    
   
 #if defined(_CVAVR_) || defined(_ICCAVR_)    
sint chdirc(uchar flash *F_PATH)   
 #else    
sint chdirc(PGM_P F_PATH)   
 #endif    
{   
    uchar fpath[_FF_PATH_LENGTH];   
    sint c;   
   
    for (c=0; c<_FF_PATH_LENGTH; c++)   
    {   
        fpath[c] = F_PATH[c];   
        if (F_PATH[c]==0)   
            break;   
    }   
    return (chdir(fpath));   
}   
   
sint chdir(uchar *F_PATH)   
{   
    uchar *qp, *sp, fpath[14], valid_flag;   
    uint n, d, calc;   
    uHILO16 temp16, m;   
    ulong addr_temp;   
   
   
    addr_temp = 0;  // save local dir addr    
   
    if ((F_PATH[0]=='\\') && (F_PATH[1]==0))   
    {   
        _FF_DIR_ADDR = _FF_ROOT_ADDR;   
        _FF_FULL_PATH[1] = 0;   
        return (0);   
    }   
   
    if (_FF_checkdir(F_PATH, &addr_temp, fpath))   
    {   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
    if (fpath[0]==0)   
        return ((sint)EOF);   
   
    if ((fpath[0]=='.') && (fpath[1]=='.') && (fpath[2]==0))   
    {   // trying to get back to prev dir    
        if (_FF_DIR_ADDR == _FF_ROOT_ADDR)      // already as far back as can go    
            return ((sint)EOF);   
        if (_FF_read(_FF_DIR_ADDR, _FF_buff)==0)   
            return ((sint)EOF);   
        m.cval.HI = _FF_buff[0x3B];   
        m.cval.LO = _FF_buff[0x3A];   
        if (m.ival > 1)   
            _FF_DIR_ADDR = clust_to_addr(m.ival);   
        else   
            _FF_DIR_ADDR = _FF_ROOT_ADDR;   
   
        sp = F_PATH;   
        qp = _FF_FULL_PATH + _FF_strlen(_FF_FULL_PATH);   
        while (*sp)   
        {   
            if ((*sp=='.')&&(*(sp+1)=='.'))   
            {   
              #if defined(_ICCAVR_) || defined(_IAR_EWAVR_)    
                qp = _FF_strrchr(_FF_FULL_PATH, '\\');   
                if (qp==0)   
                   return ((sint)EOF);   
                *qp = 0;   
                qp = _FF_strrchr(_FF_FULL_PATH, '\\');   
                if (qp==0)   
                   return ((sint)EOF);   
                qp++;   
              #endif    
              #ifdef _CVAVR_    
                _FF_FULL_PATH[strrpos(_FF_FULL_PATH, '\\')] = 0;   
                temp16.cval.LO = strrpos(_FF_FULL_PATH, '\\');   
                if (temp16.cval.LO==(uchar)EOF)   
                    return ((sint)EOF);   
                qp = _FF_FULL_PATH + temp16.cval.LO;   
              #endif    
                *qp = 0;   
                sp += 2;   
            }   
            else   
      #ifdef _IAR_EWAVR_    
            {   
                *qp = toupper(*sp);   
                qp++;   
                sp++;   
            }   
        }   
        *qp = '\\';   
        qp++;   
      #else    
                *qp++ = toupper(*sp++);   
        }   
        *qp++ = '\\';   
      #endif    
        *qp = 0;   
   
        return (0);   
    }   
   
    qp = fpath;   
    sp = fpath;   
    while(sp < (fpath+11))   
    {   
      #ifdef _IAR_EWAVR_    
        if (*qp)   
        {   
            *sp = toupper(*qp);   
            sp++;   
            qp++;   
        }   
        else    // (*qp==0)    
        {   
            *sp = 0x20;   
            sp++;   
        }   
      #else    
        if (*qp)   
            *sp++ = toupper(*qp++);   
        else    // (*qp==0)    
            *sp++ = 0x20;   
      #endif    
    }   
    *sp = 0;   
   
    qp = fpath;   
    m.ival = 0;   
    d = 0;   
    valid_flag = 0;   
    while (d<BPB_ROOTENTCNT.IVAL) name (n="0;" n<16; n++) in no more entries valid_flag="1;" (valid_flag) for !="0x10)" else a { return } if directory 0) _FF_DIR_ADDR="addr_temp;" ((sint)EOF); _FF_read(_FF_DIR_ADDR+m.ival, _FF_buff); (_FF_buff[n<<5]="=" calc="(n<<5);" (temp16.cval.LO="0;" temp16.cval.LO<11; temp16.cval.LO++) check match _FF_buff[calc+temp16.cval.LO]) (fpath[temp16.cval.LO]="=" (_FF_buff[calc+temp16.cval.LO]="=0x20)" (_FF_buff[calc+0xB] not temp16.cval.HI="_FF_buff[calc+0x1B];" temp16.cval.LO="11;" (temp16.ival> 1)   
                        _FF_DIR_ADDR = clust_to_addr(temp16.ival);   
                    else   
                        return ((sint)EOF);   
                    sp = F_PATH;   
                    if (*sp=='\\')   
                    {   // Restart String @root    
                        qp = _FF_FULL_PATH + 1;   
                        *qp = 0;   
                        sp++;   
                    }   
                    else   
                        qp = _FF_FULL_PATH + _FF_strlen(_FF_FULL_PATH);   
                    while (*sp)   
                    {   
                        if ((*sp=='.')&&(*(sp+1)=='.'))   
                        {   
                          #if defined(_ICCAVR_) || defined(_IAR_EWAVR_)    
                            qp = _FF_strrchr(_FF_FULL_PATH, '\\');   
                            if (qp==0)   
                               return ((sint)EOF);   
                            *qp = 0;   
                            qp = _FF_strrchr(_FF_FULL_PATH, '\\');   
                            if (qp==0)   
                               return ((sint)EOF);   
                            qp++;   
                          #endif    
                          #ifdef _CVAVR_    
                            _FF_FULL_PATH[strrpos(_FF_FULL_PATH, '\\')] = 0;   
                            temp16.cval.LO = strrpos(_FF_FULL_PATH, '\\');   
                            if (temp16.cval.LO==(uchar)EOF)   
                               return ((sint)EOF);   
                            qp = _FF_FULL_PATH + temp16.cval.LO;   
                          #endif    
                            *qp = 0;   
                            sp += 2;   
                        }   
                        else   
                  #ifdef _IAR_EWAVR_    
                        {   
                            *qp = toupper(*sp);   
                            qp++;   
                            sp++;   
                        }   
                    }   
                    *qp = '\\';   
                    qp++;   
                  #else    
                            *qp++ = toupper(*sp++);   
                    }   
                    *qp++ = '\\';   
                  #endif    
                    *qp = 0;   
                    return (0);   
                }   
            }   
            d++;   
        }   
        m.ival++;   
    }   
    _FF_DIR_ADDR = addr_temp;   
    return ((sint)EOF);   
}   
   
// Function to change directories one at a time, not effecting the working dir string    
sint _FF_chdir(uchar *F_PATH)   
{   
    uchar *qp, *sp, valid_flag, fpath[14];   
    uint n, d, calc;   
    uHILO16 c, m;   
   
    if ((F_PATH[0]=='.') && (F_PATH[1]=='.') && (F_PATH[2]==0))   
    {   // trying to get back to prev dir    
        if (_FF_DIR_ADDR == _FF_ROOT_ADDR)      // already as far back as can go    
            return ((sint)EOF);   
        if (_FF_read(_FF_DIR_ADDR, _FF_buff)==0)   
            return ((sint)EOF);   
        m.cval.HI = _FF_buff[0x3B];   
        m.cval.LO = _FF_buff[0x3A];   
        if (m.ival > 1)   
            _FF_DIR_ADDR = clust_to_addr(m.ival);   
        else   
            _FF_DIR_ADDR = _FF_ROOT_ADDR;   
        return (0);   
    }   
   
    qp = F_PATH;   
    sp = fpath;   
    while(sp < (fpath+11))   
    {   
      #ifdef _IAR_EWAVR_    
        if (valid_file_char(*qp)==0)   
        {   
            *sp = toupper(*qp);   
            sp++;   
            qp++;   
        }   
        else if (*qp==0)   
        {   
            *sp = 0x20;   
            sp++;   
        }   
      #else    
        if (valid_file_char(*qp)==0)   
            *sp++ = toupper(*qp++);   
        else if (*qp==0)   
            *sp++ = 0x20;   
      #endif    
        else   
            return ((sint)EOF);   
    }   
    *sp = 0;   
    m.ival = 0;   
    d = 0;   
    valid_flag = 0;   
    while (d<BPB_ROOTENTCNT.IVAL) name (n="0;" n<16; n++) in no more entries valid_flag="1;" (valid_flag) for !="0x10)" else a { return } if directory 0) ((sint)EOF); _FF_read(_FF_DIR_ADDR+m.ival, _FF_buff); calc="(n<<5);" check match (_FF_buff[calc+0xB] not (_FF_buff[calc]="=" (c.cval.LO="0;" c.cval.LO<11; c.cval.LO++) (fpath[c.cval.LO]="=" _FF_buff[calc+c.cval.LO]) c.cval.HI="_FF_buff[calc+0x1B];" c.cval.LO="11;" (c.ival> 1)   
                        _FF_DIR_ADDR = clust_to_addr(c.ival);   
                    else   
                        return ((sint)EOF);   
                    return (0);   
                }   
            }   
            d++;   
        }   
        m.ival++;   
    }   
    return ((sint)EOF);   
}   
#endif    
   
#if !defined(_SECOND_FAT_ON_) && !defined(_READ_ONLY_)    
// Function that clears the secondary FAT table    
sint clear_second_FAT(void)   
{   
    uint c, d;   
    ulong n;   
   
    for (n=1; n<BPB_FATSZ16.IVAL; name #else _FF_buff)="=0)" n++) in clear & for (c="0;" c++) #ifdef _DIRECTORIES_SUPPORTED_ !="0)" break; #endif flash ulong a uint { return (0); } if _FF_buff[0]="0xF8;" _FF_buff[1]="0xFF;" _FF_buff[2]="0xFF;" (BPB_FATType="=" 0x36) _FF_buff[3]="0xFF;" (_FF_write(_FF_FAT2_ADDR, _FF_error="ALLOC_ERR;" is it string #ifndef _READ_ONLY_ *sp, *qp; uchar fpath[14]; calc_temp; addr_temp, path_addr_temp; addr_temp="0;" save local addr &addr_temp, fpath)) fpath); || c, 0) _FF_DIR_ADDR="addr_temp;" ((sint)EOF); _BytsPerSec_512_ calc_temp="path_addr_temp" 0x1FF; path_addr_temp="_FF_DIR_ADDR;" (fpath[0]="=0)" see to not (_FF_read(_FF_FAT2_ADDR+n, c<512; c<BPB_BytsPerSec.ival; Check already clear, (_FF_buff[c] (_FF_write(_FF_FAT2_ADDR+n, d<512; (d="0;" d<BPB_BytsPerSec.ival; d++) _FF_buff[d]="0;" (1); Open file, stored fileopen #if defined(_CVAVR_) defined(_ICCAVR_) *fopenc(uchar *NAMEC, *fopenc(PGM_P NAMEC, MODEC) temp_data[14]; *tp; c<14; temp_data[c]="NAMEC[c];" tp="fopen(temp_data," MODEC); return(tp); *fopen(uchar *NAME, MODE) uHILO32 ltemp; FILE *rp; (MODE!="READ)" (_FF_checkdir(NAME, ltemp.ival.LO="scan_directory(&path_addr_temp," ((path_addr_temp="=0)" (ltemp.ival.LO="=0))" _NO_MALLOC_ (rp="=" Could allocate requested memory rp="0;">>= 9;   
  #else    
    calc_temp = path_addr_temp % BPB_BytsPerSec.ival;   
    path_addr_temp /= BPB_BytsPerSec.ival;   
  #endif    
   
    if (_FF_read(path_addr_temp, _FF_buff)==0)   
    {   
      #ifdef _DIRECTORIES_SUPPORTED_    
        _FF_DIR_ADDR = addr_temp;   
      #endif    
      #ifndef _NO_MALLOC_    
        free(rp);   
      #endif    
        return (0);   
    }   
    // Get the filename into a form we can use to compare    
    qp = file_name_conversion(fpath);   
    if (qp==0)   
    {   // If File name entered is NOT valid, return 0    
      #ifdef _DIRECTORIES_SUPPORTED_    
        _FF_DIR_ADDR = addr_temp;   
      #endif    
      #ifndef _NO_MALLOC_    
        free(rp);   
      #endif    
        return (0);   
    }   
   
    sp = &_FF_buff[calc_temp];   
   
    if (ltemp.ival.LO)   
    {   // File exists, open    
        if (((MODE==WRITE) || (MODE==APPEND)) && (_FF_buff[calc_temp+0x0B]&0x01))   
        {   // if writing to file verify it is not "READ ONLY"    
            _FF_error = MODE_ERR;   
          #ifndef _NO_MALLOC_    
            free(rp);   
          #endif    
          #ifdef _DIRECTORIES_SUPPORTED_    
            _FF_DIR_ADDR = addr_temp;   
          #endif    
            return (0);   
        }   
        for (c=0; c<12; c++) // Save Filename to Buffer    
            rp->name[c] = FILENAME[c];   
        // Save Starting Cluster    
        ltemp.cval.ML = _FF_buff[calc_temp+0x1B];   
        ltemp.cval.LO = _FF_buff[calc_temp+0x1A];   
        rp->clus_start = ltemp.ival.LO;   
        // Set Current Cluster    
        rp->clus_current = rp->clus_start;   
        // Set Previous Cluster to 0 (indicating @start)    
        rp->clus_prev = 0;   
        // Save file length    
        ltemp.cval.HI = _FF_buff[calc_temp+0x1F];   
        ltemp.cval.MH = _FF_buff[calc_temp+0x1E];   
        ltemp.cval.ML = _FF_buff[calc_temp+0x1D];   
        ltemp.cval.LO = _FF_buff[calc_temp+0x1C];   
        rp->length = ltemp.lval;   
        // Set Current Position to 0    
        rp->position = 0;   
      #ifndef _READ_ONLY_    
        if (MODE==WRITE)   
        {   // Change file to blank    
            sp = _FF_buff + calc_temp + 0x1F;   
            for (c=0; c<6; c++)   
          #ifdef _IAR_EWAVR_    
            {   
                *sp = 0;   
                sp--;   
            }   
          #else    
                *sp-- = 0;   
          #endif    
            if (rp->length)   
            {   
                if (_FF_write(path_addr_temp, _FF_buff)==0)   
                {   
                  #ifndef _NO_MALLOC_    
                    free(rp);   
                  #endif    
                  #ifdef _DIRECTORIES_SUPPORTED_    
                    _FF_DIR_ADDR = addr_temp;   
                  #endif    
                    return (0);   
                }   
                rp->length = 0;   
                erase_clus_chain(rp->clus_start);   
                rp->clus_start = 0;   
            }   
        }   
      #endif    
        // Set and save next cluster #    
        rp->clus_next = next_cluster(rp->clus_current, SINGLE);   
        if ((rp->length==0) && (rp->clus_start==0))   
        {   // Check for Blank File    
            if (MODE==READ)   
            {   // IF trying to open a blank file to read, ERROR    
                _FF_error = MODE_ERR;   
              #ifndef _NO_MALLOC_    
                free(rp);   
              #endif    
              #ifdef _DIRECTORIES_SUPPORTED_    
                _FF_DIR_ADDR = addr_temp;   
              #endif    
                return (0);   
            }   
            //Setup blank FILE characteristics    
          #ifndef _READ_ONLY_    
            MODE = WRITE;   
          #endif    
        }   
        // Save the file offset to read entry    
        rp->entry_sec_addr = path_addr_temp;   
        rp->entry_offset =  calc_temp;   
        // Set sector offset to 1    
        rp->sec_offset = 1;   
        if (MODE==APPEND)   
        {   
            if (fseek(rp, 0,SEEK_END)==(sint)EOF)   
            {   
              #ifndef _NO_MALLOC_    
                free(rp);   
              #endif    
              #ifdef _DIRECTORIES_SUPPORTED_    
                _FF_DIR_ADDR = addr_temp;   
              #endif    
                return (0);   
            }   
        }   
        else   
        {   // Set pointer to the begining of the file    
            if (MODE==READ)   
            {   
          #ifndef _NO_FILE_DATA_BUFFER_    
                _FF_read(clust_to_addr(rp->clus_current), rp->buff);   
            }   
            rp->pntr = rp->buff;   
          #else    
                _FF_read(clust_to_addr(rp->clus_current), _FF_buff);   
            }   
            rp->pntr = _FF_buff;   
          #endif    
        }   
      #ifndef _READ_ONLY_    
       #ifndef _SECOND_FAT_ON_    
        if ((MODE==WRITE) || (MODE==APPEND))   
            clear_second_FAT();   
       #endif    
      #endif    
        rp->mode = MODE;   
        _FF_error = NO_ERR;   
      #ifdef _DIRECTORIES_SUPPORTED_    
        _FF_DIR_ADDR = addr_temp;   
      #endif    
        return(rp);   
    }   
    else   
    {   
        _FF_error = FILE_ERR;   
      #ifndef _NO_MALLOC_    
        free(rp);   
      #endif    
      #ifdef _DIRECTORIES_SUPPORTED_    
        _FF_DIR_ADDR = addr_temp;   
      #endif    
        return(0);   
    }   
}   
   
#ifndef _READ_ONLY_    
// Create a file    
  #if defined(_CVAVR_) || defined(_ICCAVR_)    
FILE *fcreatec(uchar flash *NAMEC, uchar MODE)   
  #else    
FILE *fcreatec(PGM_P NAMEC, uchar MODE)   
  #endif    
{   
    uchar sd_temp[14];   
    sint c;   
   
    for (c=0; c<14; c++)   
        sd_temp[c] = NAMEC[c];   
   
    return (fcreate(sd_temp, MODE));   
}   
   
FILE *fcreate(uchar *NAME, uchar MODE)   
{   
    uchar fpath[14];   
    uint c, s, calc_temp;   
    uchar *sp, *qp;   
    ulong addr_temp, path_addr_temp;   
    FILE *temp_file_pntr;   
  #ifdef _RTC_ON_    
    uHILO16 calc_time;   
  #endif    
   
    addr_temp = 0;  // save local dir addr    
   
  #ifdef _DIRECTORIES_SUPPORTED_    
    // Get the Proper path set for the file (if nessisary)    
    if (_FF_checkdir(NAME, &addr_temp, fpath))   
    {   
        _FF_error = PATH_ERR;   
        _FF_DIR_ADDR = addr_temp;   
        return (0);   
    }   
    if (fpath[0]==0)   
    {   
        _FF_error = NAME_ERR;   
        _FF_DIR_ADDR = addr_temp;   
        return (0);   
    }   
    path_addr_temp = _FF_DIR_ADDR;   
  #else    
    path_addr_temp = _FF_ROOT_ADDR;   
  #endif    
    // Scan through the directory entries to find a place to create the file    
    //  or see if the file already exists    
    s = scan_directory(&path_addr_temp, fpath);   
    if (path_addr_temp==0)   
    {   
        if (s==(uint)EOF)   
        {   // File does not exist, and no entry space avalible    
            _FF_error = NO_ENTRY_AVAL;   
          #ifdef _DIRECTORIES_SUPPORTED_    
            _FF_DIR_ADDR = addr_temp;   
          #endif    
            return (0);   
        }   
        calc_temp = prev_cluster(0);   
        if ((calc_temp == 0) || (write_clus_table(s, calc_temp, CHAIN) == 0))   
        {   
          #ifdef _DIRECTORIES_SUPPORTED_    
            _FF_DIR_ADDR = addr_temp;   
          #endif    
            return (0);   
        }   
        if (write_clus_table(calc_temp, (uint)EOF, END_CHAIN) == 0)   
        {   
          #ifdef _DIRECTORIES_SUPPORTED_    
            _FF_DIR_ADDR = addr_temp;   
          #endif    
            return (0);   
        }   
        path_addr_temp = clust_to_addr(calc_temp);   
      #ifdef _BytsPerSec_512_    
        for (c=0; c<512; c++)   
      #else    
        for (c=0; c<BPB_BYTSPERSEC.IVAL; #else _FF_buff)="=" & for (c="0;" c++) <<="9;" #ifdef _DIRECTORIES_SUPPORTED_ #endif *="BPB_BytsPerSec.ival;" { return (0); } + if _FF_buff[c]="0;" c<BPB_SecPerClus; (_FF_write(path_addr_temp c, 0) _FF_DIR_ADDR="addr_temp;" _BytsPerSec_512_ calc_temp="path_addr_temp" 0x1FF; path_addr_temp>>= 9;   
  #else    
    calc_temp = path_addr_temp % BPB_BytsPerSec.ival;   
    path_addr_temp /= BPB_BytsPerSec.ival;   
  #endif    
    if (_FF_read(path_addr_temp, _FF_buff)==0)   
    {   
        _FF_error = READ_ERR;   
      #ifdef _DIRECTORIES_SUPPORTED_    
        _FF_DIR_ADDR = addr_temp;   
      #endif    
        return (0);   
    }   
   
    // Get the filename into a form we can use to compare    
    qp = file_name_conversion(fpath);   
    if (qp==0)   
    {   
        _FF_error = NAME_ERR;   
      #ifdef _DIRECTORIES_SUPPORTED_    
        _FF_DIR_ADDR = addr_temp;   
      #endif    
        return (0);   
    }   
    sp = &_FF_buff[calc_temp];   
   
    if (s)   
    {   
        if ((_FF_buff[calc_temp+0x0B]&0x1)==1)  // is file read only    
        {   
            _FF_error = READONLY_ERR;   
          #ifdef _DIRECTORIES_SUPPORTED_    
            _FF_DIR_ADDR = addr_temp;   
          #endif    
            return (0);   
        }   
    }   
    else   
    {   
      #ifdef _IAR_EWAVR_    
        for (c=0; c<11; c++) // Write Filename    
        {   
            *sp = *qp;   
            sp++;   
            qp++;   
        }   
        *sp = 0x20;             // Attribute bit auto set to "ARCHIVE"    
        sp++;   
        *sp = 0;                // Reserved for WinNT    
        sp++;   
        *sp = 0;                // Mili-second stamp for create    
        sp++;   
   
       #ifdef _RTC_ON_    
        rtc_get_timeNdate(&rtc_hour, &rtc_min, &rtc_sec, &rtc_date, &rtc_month, &rtc_year);   
        calc_time.ival = ((sint)rtc_sec&0x1F) | (((sint)rtc_min&0x3F)<<5) | (((sint)rtc_hour&0x1F)<<11);   
        *sp = calc_time.cval.LO;    // File create Time    
        sp++;   
        *sp = calc_time.cval.HI;   
        sp++;   
        calc_time.ival = ((sint)rtc_date&0x1F) | (((sint)rtc_month&0x0F)<<5) | (((rtc_year-1980)&0x7F)<<9);   
        *sp = calc_time.cval.LO;    // File create Date    
        sp++;   
        *sp = calc_time.cval.HI;   
        sp++;   
       #else    
        *sp = 0;        // File Create Time    
        sp++;   
        *sp = 0;        //   set to 12:00:00AM    
        sp++;   
        *sp = 0x21;     // File Create Date    
        sp++;   
        *sp = 0;        //   set to 01/01/1980    
        sp++;   
       #endif    
   
        *sp = 0;                // File access date (2 bytes)    
        sp++;   
        *sp = 0;   
        sp++;   
        *sp = 0;                // 0 for FAT12/16 (2 bytes)    
        sp++;   
        *sp = 0;   
        sp++;   
        *sp = 0;        // File Modify Time    
        sp++;   
        *sp = 0;        //   set to 12:00:00AM    
        sp++;   
        *sp = 0x21;     // File Modify Date    
        sp++;   
        *sp = 0;        //   set to 01/01/1980    
        sp++;   
        *sp = 0;                // Starting cluster (2 bytes)    
        sp++;   
        *sp = 0;   
        sp++;   
        for (c=0; c<4; c++)   
        {   
            *sp = 0;            // File length (0 for new)    
            sp++;   
        }   
      #else    
        for (c=0; c<11; c++) // Write Filename    
            *sp++ = *qp++;   
        *sp++ = 0x20;               // Attribute bit auto set to "ARCHIVE"    
        *sp++ = 0;              // Reserved for WinNT    
        *sp++ = 0;              // Mili-second stamp for create    
   
       #ifdef _RTC_ON_    
        rtc_get_timeNdate(&rtc_hour, &rtc_min, &rtc_sec, &rtc_date, &rtc_month, &rtc_year);   
        calc_time.ival = ((sint)rtc_sec&0x1F) | (((sint)rtc_min&0x3F)<<5) | (((sint)rtc_hour&0x1F)<<11);   
        *sp++ = calc_time.cval.LO;  // File create Time    
        *sp++ = calc_time.cval.HI;   
        calc_time.ival = ((sint)rtc_date&0x1F) | (((sint)rtc_month&0x0F)<<5) | (((rtc_year-1980)&0x7F)<<9);   
        *sp++ = calc_time.cval.LO;  // File create Date    
        *sp++ = calc_time.cval.HI;   
       #else    
        *sp++ = 0;      // File Create Time    
        *sp++ = 0;      //   set to 12:00:00AM    
        *sp++ = 0x21;   // File Create Date    
        *sp++ = 0;      //   set to 01/01/1980    
       #endif    
   
        *sp++ = 0;              // File access date (2 bytes)    
        *sp++ = 0;   
        *sp++ = 0;              // 0 for FAT12/16 (2 bytes)    
        *sp++ = 0;   
        *sp++ = 0;      // File Modify Time    
        *sp++ = 0;      //   set to 12:00:00AM    
        *sp++ = 0x21;   // File Modify Date    
        *sp++ = 0;      //   set to 01/01/1980    
        *sp++ = 0;              // Starting cluster (2 bytes)    
        *sp++ = 0;   
        for (c=0; c<4; c++)   
            *sp++ = 0;          // File length (0 for new)    
      #endif    
   
   
        if (_FF_write(path_addr_temp, _FF_buff)==0)   
        {   
            _FF_error = WRITE_ERR;   
          #ifdef _DIRECTORIES_SUPPORTED_    
            _FF_DIR_ADDR = addr_temp;   
          #endif    
            return (0);   
        }   
    }   
  #ifdef _DIRECTORIES_SUPPORTED_    
    _FF_DIR_ADDR = addr_temp;   
  #endif    
    temp_file_pntr = fopen(NAME, WRITE);   
    if (temp_file_pntr == 0)    // Will file open    
    {   
        return (0);   
    }   
    if (MODE)   
    {   // need to set the file/folder attributes for the entry    
        if (_FF_read(path_addr_temp, _FF_buff)==0)   
        {   
            _FF_error = READ_ERR;   
          #ifndef _NO_MALLOC_    
            free(temp_file_pntr);   
          #endif    
            return (0);   
        }   
        _FF_buff[calc_temp+12] |= MODE;   
        if (_FF_write(path_addr_temp, _FF_buff)==0)   
        {   
            _FF_error = WRITE_ERR;   
          #ifndef _NO_MALLOC_    
            free(temp_file_pntr);   
          #endif    
            return (0);   
        }   
    }   
    _FF_error = NO_ERR;   
    return (temp_file_pntr);   
}   
#endif    
   
#ifndef _READ_ONLY_    
// Open a file, name stored in string fileopen    
  #if defined(_CVAVR_) || defined(_ICCAVR_)    
sint removec(uchar flash *NAMEC)   
  #else    
sint removec(PGM_P NAMEC)   
  #endif    
{   
    sint c;   
    uchar sd_temp[14];   
   
    for (c=0; c<14; c++)   
        sd_temp[c] = NAMEC[c];   
   
    c = remove(sd_temp);   
    return (c);   
}   
   
// Remove a file from the root directory    
sint remove(uchar *NAME)   
{   
    uchar fpath[14];   
    uint calc_temp;   
    uHILO16 clus_temp;   
    ulong addr_temp, path_addr_temp;   
   
  #ifndef _SECOND_FAT_ON_    
    clear_second_FAT();   
  #endif    
   
    addr_temp = 0;  // save local dir addr    
   
  #ifdef _DIRECTORIES_SUPPORTED_    
    if (_FF_checkdir(NAME, &addr_temp, fpath))   
    {   
        _FF_error = PATH_ERR;   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
    if (fpath[0]==0)   
    {   
        _FF_error = NAME_ERR;   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
    path_addr_temp = _FF_DIR_ADDR;   
  #else    
    path_addr_temp = _FF_ROOT_ADDR;   
  #endif    
    calc_temp = scan_directory(&path_addr_temp, fpath);   
    if ((path_addr_temp==0) || (calc_temp!=(uint)EOF))   
    {   
        _FF_error = NO_ENTRY_AVAL;   
      #ifdef _DIRECTORIES_SUPPORTED_    
        _FF_DIR_ADDR = addr_temp;   
      #endif    
        return ((sint)EOF);   
    }   
  #ifdef _DIRECTORIES_SUPPORTED_    
    _FF_DIR_ADDR = addr_temp;       // Reset current dir    
  #endif    
   
  #ifdef _BytsPerSec_512_    
    calc_temp = path_addr_temp & 0x1FF;   
    path_addr_temp >>= 9;   
  #else    
    calc_temp = path_addr_temp % BPB_BytsPerSec.ival;   
    path_addr_temp /= BPB_BytsPerSec.ival;   
  #endif    
   
    if (_FF_read(path_addr_temp, _FF_buff)==0)   
    {   
        _FF_error = READ_ERR;   
        return ((sint)EOF);   
    }   
   
    // Erase entry (put 0xE5 into start of the filename    
    _FF_buff[calc_temp] = 0xE5;   
    if (_FF_write(path_addr_temp, _FF_buff)==0)   
    {   
        _FF_error = WRITE_ERR;   
        return ((sint)EOF);   
    }   
    // Save Starting Cluster    
    clus_temp.cval.HI = _FF_buff[calc_temp+0x1B];   
    clus_temp.cval.LO = _FF_buff[calc_temp+0x1A];   
    // Destroy cluster chain    
    if (clus_temp.ival)   
        if (erase_clus_chain(clus_temp.ival) == 0)   
            return ((sint)EOF);   
   
    return (1);   
}   
#endif    
   
#ifndef _READ_ONLY_    
// Rename a file in the Root Directory    
sint rename(uchar *NAME_OLD, uchar *NAME_NEW)   
{   
    uchar c;   
    uint calc_temp;   
    ulong addr_temp, path_addr_temp;   
    uchar *sp, *qp;   
    uchar fpath[14];   
   
    // Get the filename into a form we can use to compare    
    qp = file_name_conversion(NAME_NEW);   
    if (qp==0)   
    {   
        _FF_error = NAME_ERR;   
        return ((sint)EOF);   
    }   
   
    addr_temp = 0;  // save local dir addr    
   
  #ifdef _DIRECTORIES_SUPPORTED_    
    if (_FF_checkdir(NAME_OLD, &addr_temp, fpath))   
    {   
        _FF_error = PATH_ERR;   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
    if (fpath[0]==0)   
    {   
        _FF_error = NAME_ERR;   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
    path_addr_temp = _FF_DIR_ADDR;   
  #else    
    path_addr_temp = _FF_ROOT_ADDR;   
  #endif    
    calc_temp = scan_directory(&path_addr_temp, NAME_NEW);   
    if (calc_temp != (uint)EOF)   
    {   // does new name alread exist?    
      #ifdef _DIRECTORIES_SUPPORTED_    
        _FF_DIR_ADDR = addr_temp;   
      #endif    
        _FF_error = EXIST_ERR;   
        return ((sint)EOF);   
    }   
   
  #ifdef _DIRECTORIES_SUPPORTED_    
    path_addr_temp = _FF_DIR_ADDR;   
  #else    
    path_addr_temp = _FF_ROOT_ADDR;   
  #endif    
    calc_temp = scan_directory(&path_addr_temp, fpath);   
    if ((path_addr_temp==0) || (calc_temp != (uint)EOF))   
    {   
      #ifdef _DIRECTORIES_SUPPORTED_    
        _FF_DIR_ADDR = addr_temp;   
      #endif    
        _FF_error = EXIST_ERR;   
        return ((sint)EOF);   
    }   
   
  #ifdef _DIRECTORIES_SUPPORTED_    
    _FF_DIR_ADDR = addr_temp;       // Reset current dir    
  #endif    
   
  #ifdef _BytsPerSec_512_    
    calc_temp = path_addr_temp & 0x1FF;   
    path_addr_temp >>= 9;   
  #else    
    calc_temp = path_addr_temp % BPB_BytsPerSec.ival;   
    path_addr_temp /= BPB_BytsPerSec.ival;   
  #endif    
   
    if (_FF_read(path_addr_temp, _FF_buff)==0)   
    {   
        _FF_error = READ_ERR;   
        return ((sint)EOF);   
    }   
   
    // Rename entry    
    sp = &_FF_buff[calc_temp];   
    for (c=0; c<11; c++)   
    {   
      #ifdef _IAR_EWAVR_    
        *sp = *qp;   
        sp++;   
        qp++;   
      #else    
        *sp++ = *qp++;   
      #endif    
    }   
    if (_FF_write(path_addr_temp, _FF_buff)==0)   
        return ((sint)EOF);   
   
    return(0);   
}   
#endif    
   
#ifndef _READ_ONLY_    
   
#ifdef _FULL_DEBUG_MODE_    
schar flash FFLUSH_STR[] = "FFLUSH Called";   
#endif    
   
// Save Contents of file, w/o closing    
sint fflush(FILE *rp)   
{   
    ulong addr_temp;   
   
#ifdef _FULL_DEBUG_MODE_    
printf(FFLUSH_STR);   
#endif    
   
    if ((rp==NULL) || (rp->mode==READ))   
        return ((sint)EOF);   
   
    if ((rp->mode==WRITE) || (rp->mode==APPEND))   
    {   
        if (rp->clus_current == 0)   
        {   
            if (rp->length != 0)   
                return ((sint)EOF);   
        }   
        else if ((rp->EOF_flag) == 0)    // Info already saved    
        {   
            addr_temp = (clust_to_addr(rp->clus_current) + (rp->sec_offset-1));   
          #ifndef _NO_FILE_DATA_BUFFER_    
            if (_FF_write(addr_temp, rp->buff)==0)   // Write SD buffer to disk    
          #else    
            if (_FF_write(addr_temp, _FF_buff)==0)  // Write SD buffer to disk    
          #endif    
                return ((sint)EOF);   
        }   
        if (append_toc(rp)==0)  // Update Entry or Error    
            return ((sint)EOF);   
    }   
  #ifdef _NO_FILE_DATA_BUFFER_    
    if (_FF_read(addr_temp, _FF_buff)==0)   // Read SD So file data is back in _FF_buff    
        return ((sint)EOF);   
  #endif    
   
   
    return (0);   
}   
#endif    
   
   
// Close an open file    
sint fclose(FILE *rp)   
{   
  #ifndef _READ_ONLY_    
    if (rp->mode!=READ)   
        if (fflush(rp)==(sint)EOF)   
            return ((sint)EOF);   
  #endif    
    // Clear File Structure    
  #ifndef _NO_MALLOC_    
    free(rp);   
  #endif    
   
    return(0);   
}   
   
#ifndef _NO_MALLOC_    
sint ffreemem(FILE *rp)   
{   
    // Clear File Structure    
    if (rp==0)   
        return ((sint)EOF);   
    free(rp);   
    return(0);   
}   
#endif    
   
 #if defined(_CVAVR_) || defined(_ICCAVR_)    
sint fget_file_infoc(uchar flash *NAMEC, ulong *F_SIZE, uchar *F_CREATE,   
                uchar *F_MODIFY, uchar *F_ATTRIBUTE, uint *F_CLUS_START)   
 #else    
sint fget_file_infoc(PGM_P NAMEC, ulong *F_SIZE, uchar *F_CREATE,   
                uchar *F_MODIFY, uchar *F_ATTRIBUTE, uint *F_CLUS_START)   
 #endif    
{   
    sint c;   
    uchar sd_temp[14];   
   
    for (c=0; c<14; c++)   
        sd_temp[c] = NAMEC[c];   
   
    c = fget_file_info(sd_temp, F_SIZE, F_CREATE, F_MODIFY, F_ATTRIBUTE, F_CLUS_START);   
    return (c);   
}   
   
sint fget_file_info(uchar *NAME, ulong *F_SIZE, uchar *F_CREATE,   
                uchar *F_MODIFY, uchar *F_ATTRIBUTE, uint *F_CLUS_START)   
{   
    uchar fpath[14];   
    uint s, calc_temp;   
    ulong addr_temp, path_addr_temp;   
    uHILO32 file_calc_temp;   
    uchar *qp;   
   
  #ifdef _DIRECTORIES_SUPPORTED_    
    if (_FF_checkdir(NAME, &addr_temp, fpath))   
    {   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
    if (fpath[0]==0)   
    {   
        _FF_DIR_ADDR = addr_temp;   
        return ((sint)EOF);   
    }   
    path_addr_temp = _FF_DIR_ADDR;   
  #else    
    path_addr_temp = _FF_ROOT_ADDR;   
  #endif    
   
    s = scan_directory(&path_addr_temp, fpath);   
    if ((path_addr_temp==0) || (s==0))   
    {   
      #ifdef _DIRECTORIES_SUPPORTED_    
        _FF_DIR_ADDR = addr_temp;   
      #endif    
        return ((sint)EOF);   
    }   
   
  #ifdef _BytsPerSec_512_    
    calc_temp = path_addr_temp & 0x1FF;   
    path_addr_temp >>= 9;   
  #else    
    calc_temp = path_addr_temp % BPB_BytsPerSec.ival;   
    path_addr_temp /= BPB_BytsPerSec.ival;   
  #endif    
   
    if (_FF_read(path_addr_temp, _FF_buff)==0)   
        return ((sint)EOF);   
   
    // Save ATTRIBUTE Byte from location    
    *F_ATTRIBUTE = _FF_buff[calc_temp+11];   
   
    // Get the Starting cluster and save it to the location *F_CLUS_START    
    file_calc_temp.cval.LO = _FF_buff[calc_temp+26];   
    file_calc_temp.cval.ML = _FF_buff[calc_temp+27];   
    *F_CLUS_START = file_calc_temp.ival.LO;   
   
    // Get File Size and save it to the location *F_SIZE    
    file_calc_temp.cval.LO = _FF_buff[calc_temp+28];   
    file_calc_temp.cval.ML = _FF_buff[calc_temp+29];   
    file_calc_temp.cval.MH = _FF_buff[calc_temp+30];   
    file_calc_temp.cval.HI = _FF_buff[calc_temp+31];   
    *F_SIZE = file_calc_temp.lval;   
   
    // Get the Create time/date and save it to the location *F_CREATE    
    file_calc_temp.cval.ML = _FF_buff[calc_temp+17];   
    file_calc_temp.cval.LO = _FF_buff[calc_temp+16];   
   
    qp = F_CREATE;   
  #ifdef _IAR_EWAVR_    
    *qp = (((file_calc_temp.ival.LO >> 5) & 0x0F) / 10) + '0';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO >> 5) & 0x0F) % 10) + '0';   
    qp++;   
    *qp = '/';   
    qp++;   
    *qp = ((file_calc_temp.ival.LO & 0x1F) / 10) + '0';   
    qp++;   
    *qp = ((file_calc_temp.ival.LO & 0x1F) % 10) + '0';   
    qp++;   
    *qp = '/';   
    qp++;   
    file_calc_temp.ival.LO = ((file_calc_temp.ival.LO >> 9) & 0x7F) + 1980;   
    *qp = (file_calc_temp.ival.LO / 1000) + '0';   
    qp++;   
    file_calc_temp.ival.LO %= 1000;   
    *qp = (file_calc_temp.ival.LO / 100) + '0';   
    qp++;   
    file_calc_temp.ival.LO %= 100;   
    *qp = (file_calc_temp.ival.LO / 10) + '0';   
    qp++;   
    *qp = (file_calc_temp.ival.LO % 10) + '0';   
    qp++;   
    *qp = ' ';   
    qp++;   
    *qp = ' ';   
    qp++;   
    file_calc_temp.cval.ML = _FF_buff[calc_temp+15];   
    file_calc_temp.cval.LO = _FF_buff[calc_temp+14];   
    *qp = (((file_calc_temp.ival.LO >> 11) & 0x1F) / 10) + '0';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO >> 11) & 0x1F) % 10) + '0';   
    qp++;   
    *qp = ':';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO >> 5) & 0x3F) / 10) + '0';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO >> 5) & 0x3F) % 10) + '0';   
    qp++;   
    *qp = ':';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO & 0x1F) >> 1) / 10) + '0';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO & 0x1F) >> 1) % 10) + '0';   
    qp++;   
    *qp = 0;   
    // Get the Modify time/date and save it to the location *F_MODIFY    
    file_calc_temp.cval.ML = _FF_buff[calc_temp+25];   
    file_calc_temp.cval.LO = _FF_buff[calc_temp+24];   
    qp = F_MODIFY;   
    *qp = (((file_calc_temp.ival.LO >> 5) & 0x0F) / 10) + '0';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO >> 5) & 0x0F) % 10) + '0';   
    qp++;   
    *qp = '/';   
    qp++;   
    *qp = ((file_calc_temp.ival.LO & 0x1F) / 10) + '0';   
    qp++;   
    *qp = ((file_calc_temp.ival.LO & 0x1F) % 10) + '0';   
    qp++;   
    *qp = '/';   
    qp++;   
    file_calc_temp.ival.LO = ((file_calc_temp.ival.LO >> 9) & 0x7F) + 1980;   
    *qp = (file_calc_temp.ival.LO / 1000) + '0';   
    qp++;   
    file_calc_temp.ival.LO %= 1000;   
    *qp = (file_calc_temp.ival.LO / 100) + '0';   
    qp++;   
    file_calc_temp.ival.LO %= 100;   
    *qp = (file_calc_temp.ival.LO / 10) + '0';   
    qp++;   
    *qp = (file_calc_temp.ival.LO % 10) + '0';   
    qp++;   
    *qp = ' ';   
    qp++;   
    *qp = ' ';   
    qp++;   
    file_calc_temp.cval.ML = _FF_buff[calc_temp+23];   
    file_calc_temp.cval.LO = _FF_buff[calc_temp+22];   
    *qp = (((file_calc_temp.ival.LO >> 11) & 0x1F) / 10) + '0';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO >> 11) & 0x1F) % 10) + '0';   
    qp++;   
    *qp = ':';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO >> 5) & 0x3F) / 10) + '0';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO >> 5) & 0x3F) % 10) + '0';   
    qp++;   
    *qp = ':';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO & 0x1F) << 1) / 10) + '0';   
    qp++;   
    *qp = (((file_calc_temp.ival.LO & 0x1F) << 1) % 10) + '0';   
    qp++;   
    *qp = 0;   
  #else    
    *qp++ = (((file_calc_temp.ival.LO >> 5) & 0x0F) / 10) + '0';   
    *qp++ = (((file_calc_temp.ival.LO >> 5) & 0x0F) % 10) + '0';   
    *qp++ = '/';   
    *qp++ = ((file_calc_temp.ival.LO & 0x1F) / 10) + '0';   
    *qp++ = ((file_calc_temp.ival.LO & 0x1F) % 10) + '0';   
    *qp++ = '/';   
    file_calc_temp.ival.LO = ((file_calc_temp.ival.LO >> 9) & 0x7F) + 1980;   
    *qp++ = (file_calc_temp.ival.LO / 1000) + '0';   
    file_calc_temp.ival.LO %= 1000;   
    *qp++ = (file_calc_temp.ival.LO / 100) + '0';   
    file_calc_temp.ival.LO %= 100;   
    *qp++ = (file_calc_temp.ival.LO / 10) + '0';   
    *qp++ = (file_calc_temp.ival.LO % 10) + '0';   
    *qp++ = ' ';   
    *qp++ = ' ';   
    file_calc_temp.cval.ML = _FF_buff[calc_temp+15];   
    file_calc_temp.cval.LO = _FF_buff[calc_temp+14];   
    *qp++ = (((file_calc_temp.ival.LO >> 11) & 0x1F) / 10) + '0';   
    *qp++ = (((file_calc_temp.ival.LO >> 11) & 0x1F) % 10) + '0';   
    *qp++ = ':';   
    *qp++ = (((file_calc_temp.ival.LO >> 5) & 0x3F) / 10) + '0';   
    *qp++ = (((file_calc_temp.ival.LO >> 5) & 0x3F) % 10) + '0';   
    *qp++ = ':';   
    *qp++ = (((file_calc_temp.ival.LO & 0x1F) >> 1) / 10) + '0';   
    *qp++ = (((file_calc_temp.ival.LO & 0x1F) >> 1) % 10) + '0';   
    *qp = 0;   
    // Get the Modify time/date and save it to the location *F_MODIFY    
    file_calc_temp.cval.ML = _FF_buff[calc_temp+25];   
    file_calc_temp.cval.LO = _FF_buff[calc_temp+24];   
    qp = F_MODIFY;   
    *qp++ = (((file_calc_temp.ival.LO >> 5) & 0x0F) / 10) + '0';   
    *qp++ = (((file_calc_temp.ival.LO >> 5) & 0x0F) % 10) + '0';   
    *qp++ = '/';   
    *qp++ = ((file_calc_temp.ival.LO & 0x1F) / 10) + '0';   
    *qp++ = ((file_calc_temp.ival.LO & 0x1F) % 10) + '0';   
    *qp++ = '/';   
    file_calc_temp.ival.LO = ((file_calc_temp.ival.LO >> 9) & 0x7F) + 1980;   
    *qp++ = (file_calc_temp.ival.LO / 1000) + '0';   
    file_calc_temp.ival.LO %= 1000;   
    *qp++ = (file_calc_temp.ival.LO / 100) + '0';   
    file_calc_temp.ival.LO %= 100;   
    *qp++ = (file_calc_temp.ival.LO / 10) + '0';   
    *qp++ = (file_calc_temp.ival.LO % 10) + '0';   
    *qp++ = ' ';   
    *qp++ = ' ';   
    file_calc_temp.cval.ML = _FF_buff[calc_temp+23];   
    file_calc_temp.cval.LO = _FF_buff[calc_temp+22];   
    *qp++ = (((file_calc_temp.ival.LO >> 11) & 0x1F) / 10) + '0';   
    *qp++ = (((file_calc_temp.ival.LO >> 11) & 0x1F) % 10) + '0';   
    *qp++ = ':';   
    *qp++ = (((file_calc_temp.ival.LO >> 5) & 0x3F) / 10) + '0';   
    *qp++ = (((file_calc_temp.ival.LO >> 5) & 0x3F) % 10) + '0';   
    *qp++ = ':';   
    *qp++ = (((file_calc_temp.ival.LO & 0x1F) << 1) / 10) + '0';   
    *qp++ = (((file_calc_temp.ival.LO & 0x1F) << 1) % 10) + '0';   
    *qp = 0;   
  #endif    
    return (0);   
}   
   
// Get File data and increment file pointer    
sint fgetc_(FILE *rp)   
{   
    uchar get_data;   
//  uint n;    
    ulong addr_temp;   
   
    if (rp==NULL)   
        return ((sint)EOF);   
   
    if (rp->position == rp->length)   
    {   
        rp->error = POS_ERR;   
        return ((sint)EOF);   
    }   
   
    get_data = *rp->pntr;   
   
  #ifndef _NO_FILE_DATA_BUFFER_    
   #ifdef _BytsPerSec_512_    
    if (rp->pntr == &rp->buff[511])   
   #else    
    if (rp->pntr == &rp->buff[BPB_BytsPerSec.ival-1])   
   #endif    
  #else    
   #ifdef _BytsPerSec_512_    
    if (rp->pntr == &_FF_buff[511])   
   #else    
    if (rp->pntr == &_FF_buff[BPB_BytsPerSec.ival-1])   
   #endif    
  #endif    
    {   // Check to see if pointer is at the end of a sector    
        #ifndef _READ_ONLY_    
        if ((rp->mode==WRITE) || (rp->mode==APPEND))   
        {   // if in write or append mode, update the current sector before loading next    
            addr_temp = clust_to_addr(rp->clus_current) + ((rp->sec_offset)-1);   
          #ifndef _NO_FILE_DATA_BUFFER_    
            if (_FF_write(addr_temp, rp->buff)==0)   
          #else    
            if (_FF_write(addr_temp, _FF_buff)==0)   
          #endif    
                return ((sint)EOF);   
        }   
        #endif    
        if (rp->sec_offset < BPB_SecPerClus)   
        {   // Goto next sector if not at the end of a cluster    
            addr_temp = clust_to_addr(rp->clus_current) + (rp->sec_offset);   
            rp->sec_offset++;   
        }   
        else   
        {   // End of Cluster, find next    
            if (rp->clus_next>=0xFFF8)    // No next cluster, EOF marker    
            {   
                rp->EOF_flag = 1;    // Set flag so Putchar knows to get new cluster    
                rp->position++;      // Only time doing this, position + 1 should equal length    
                return(get_data);   
            }   
            addr_temp = clust_to_addr(rp->clus_next);   
            rp->sec_offset = 1;   
            rp->clus_prev = rp->clus_current;   
            rp->clus_current = rp->clus_next;   
            rp->clus_next = next_cluster(rp->clus_current, SINGLE);   
        }   
      #ifndef _NO_FILE_DATA_BUFFER_    
        if (_FF_read(addr_temp, rp->buff)==0)   
            return ((sint)EOF);   
        rp->pntr = &rp->buff[0];   
      #else    
        if (_FF_read(addr_temp, _FF_buff)==0)   
            return ((sint)EOF);   
        rp->pntr = _FF_buff[0];   
      #endif    
    }   
    else   
        rp->pntr++;   
   
    rp->position++;   
    return(get_data);   
}   
   
sint fread(void *rd_buff, uint dat_size, uint num_items, FILE *rp)   
{   
    uchar *temp_char_pntr;   
    uint temp_int, temp_int2;   
    uint no_bytes_cntr, i;   
   
    no_bytes_cntr = 0;   
    temp_char_pntr = rd_buff;   
    temp_int = dat_size * num_items;   
   
    for (i=0; i<TEMP_INT; #else file & for (c="0;" c++) #ifdef else #endif ; ulong uint { return } if then _IAR_EWAVR_ #ifndef _READ_ONLY_ uchar sint || c, n, FILE i++) temp_int2="fgetc_(rp);" (temp_int2="=" (uint)EOF) (no_bytes_cntr); *temp_char_pntr="(uchar)" temp_char_pntr++; *temp_char_pntr++="(uchar)" temp_int2; no_bytes_cntr++; (no_bytes_cntr dat_size); *fgets(uchar *buffer, temp_data; *temp_pntr; temp_pntr="buffer;" ((c<(n-1))&&(temp_data!="\n" )&&(temp_data!="(sint)EOF));" temp_pntr++; *temp_pntr++="(uchar)" 0xFF; temp_data="fgetc_(rp);" *temp_pntr="(uchar)" (temp_data="=" (sint)EOF) (NULL); (buffer); Decrement pointer, get data ungetc(uchar file_data, *rp) n; addr_temp; ((rp="=NULL)" (rp->position==0))   
        return ((sint)EOF);   
    if ((rp->mode!=APPEND) && (rp->mode!=WRITE))   
        return ((sint)EOF); // needs to be in WRITE or APPEND mode    
   
    if (((rp->position)==(rp->length)) && (rp->EOF_flag))   
    {   // if the file posisition is equal to the length, return data, turn flag off    
        rp->EOF_flag = 0;   
        *rp->pntr = file_data;   
        return (*rp->pntr);   
    }   
  #ifndef _NO_FILE_DATA_BUFFER_    
    if ((rp->pntr)==(&rp->buff[0]))   
    {   // Check to see if pointer is at the beginning of a Sector    
        // Update the current sector before loading next    
  #else    
    if ((rp->pntr)==(&_FF_buff[0]))   
    {   // Check to see if pointer is at the beginning of a Sector    
  #endif    
        addr_temp = clust_to_addr(rp->clus_current) + ((rp->sec_offset)-1);   
      #ifndef _NO_FILE_DATA_BUFFER_    
        if (_FF_write(addr_temp, rp->buff)==0)   
      #else    
        if (_FF_write(addr_temp, _FF_buff)==0)   
      #endif    
            return ((sint)EOF);   
   
        if (rp->sec_offset > 1)   
        {   // Goto previous sector if not at the beginning of a cluster    
            addr_temp = clust_to_addr(rp->clus_current) + (rp->sec_offset-2);   
            rp->sec_offset--;   
        }   
        else   
        {   // Beginning of Cluster, find previous    
            if (rp->clus_start==rp->clus_current)   
            {   // Positioned @ Beginning of File    
                _FF_error = SOF_ERR;   
                return((sint)EOF);   
            }   
            rp->sec_offset = BPB_SecPerClus; // Set sector offset to last sector    
            rp->clus_next = rp->clus_current;   
            rp->clus_current = rp->clus_prev;   
            if (rp->clus_current != rp->clus_start)   
                rp->clus_prev = prev_cluster(rp->clus_current);   
            else   
                rp->clus_prev = 0;   
            addr_temp = clust_to_addr(rp->clus_current) + (BPB_SecPerClus-1);   
        }   
   
      #ifndef _NO_FILE_DATA_BUFFER_    
        if (_FF_read(addr_temp, rp->buff)==0)   
            return ((sint)EOF);   
        rp->pntr = &rp->buff[511];   
      #else    
        if (_FF_read(addr_temp, _FF_buff)==0)   
            return ((sint)EOF);   
        rp->pntr = &_FF_buff[511];   
      #endif    
    }   
    else   
        rp->pntr--;   
   
    rp->position--;   
    *rp->pntr = file_data;   
    return(*rp->pntr);   // Get data    
}   
#endif    
   
#ifndef _READ_ONLY_    
/**************************************************************************  
This function writes one character to the to the open file buffer.  It  
verifies that a valid file pointer was input to the function, and verifies  
the file was not in "READ" mode.  The length of the file is then checked  
to see if the file is blank (length = 0).  If it is blank, a starting  
cluster will be calculated and written to the FAT table.  
**************************************************************************/   
sint fputc_(uchar file_data, FILE *rp)   
{   
    ulong addr_temp;   
   
    if (rp==NULL)   
        return ((sint)EOF);   
   
    if (rp->mode == READ)   
    {   
        _FF_error = READONLY_ERR;   
        return((sint)EOF);   
    }   
    if (rp->length == 0)   
    {   // Blank file start writing cluster table    
        rp->clus_start = prev_cluster(0);   
        rp->clus_next = 0xFFFF;   
        rp->clus_current = rp->clus_start;   
        if (write_clus_table(rp->clus_current, rp->clus_next, SINGLE)==0)   
        {   
            return ((sint)EOF);   
        }   
        rp->EOF_flag = 0;   
    }   
   
    if ((rp->position==rp->length) && (rp->EOF_flag))   
    {   // At end of file, and end of cluster, flagged    
        rp->clus_prev = rp->clus_current;   
        rp->clus_current = prev_cluster(0);  // Find first cluster pointing to '0'    
        rp->clus_next = 0xFFFF;   
        rp->sec_offset = 1;   
        if (write_clus_table(rp->clus_prev, rp->clus_current, CHAIN)==0)   
        {   
            return ((sint)EOF);   
        }   
        if (write_clus_table(rp->clus_current, rp->clus_next, END_CHAIN)==0)   
        {   
            return ((sint)EOF);   
        }   
        if (append_toc(rp)==0)   
        {   
            return ((sint)EOF);   
        }   
        rp->EOF_flag = 0;   
      #ifndef _NO_FILE_DATA_BUFFER_    
        rp->pntr = &rp->buff[0];   
      #else    
        rp->pntr = &_FF_buff[0];   
      #endif    
    }   
   
    *rp->pntr = file_data;   
   
  #ifndef _NO_FILE_DATA_BUFFER_    
   #ifdef _BytsPerSec_512_    
    if (rp->pntr == &rp->buff[511])   
   #else    
    if (rp->pntr == &rp->buff[BPB_BytsPerSec.ival-1])   
   #endif    
  #else    
   #ifdef _BytsPerSec_512_    
    if (rp->pntr == &_FF_buff[511])   
   #else    
    if (rp->pntr == &_FF_buff[BPB_BytsPerSec.ival-1])   
   #endif    
  #endif    
    {   // This is on the Sector Limit    
        if (rp->position > rp->length)   
        {   // ERROR, position should never be greater than length    
            _FF_error = 0x10;       // file position ERROR    
            return ((sint)EOF);   
        }   
        // Position is at end of a sector?    
   
        addr_temp = (clust_to_addr(rp->clus_current) + (rp->sec_offset-1));   
      #ifndef _NO_FILE_DATA_BUFFER_    
        _FF_write(addr_temp, rp->buff);   
      #else    
        _FF_write(addr_temp, _FF_buff);   
      #endif    
            // Save MMC buffer to card, set pointer to begining of new buffer    
        if (rp->sec_offset < BPB_SecPerClus)   
        {   // Are there more sectors in this cluster?    
            addr_temp = clust_to_addr(rp->clus_current) + (rp->sec_offset);   
            rp->sec_offset++;   
        }   
        else   
        {   // Find next cluster, load first sector into file.buff    
            if (((rp->clus_next>=0xFFF8)&&(BPB_FATType==0x36)) ||   
                ((rp->clus_next>=0xFF8)&&(BPB_FATType==0x32)))   
            {   // EOF, need to find new empty cluster    
                if (rp->position != rp->length)   
                {   // if not equal there's an error    
                    _FF_error = 0x20;       // EOF position error    
                    return ((sint)EOF);   
                }   
                rp->EOF_flag = 1;   
            }   
            else   
            {   // Not EOF, find next cluster    
                rp->clus_prev = rp->clus_current;   
                rp->clus_current = rp->clus_next;   
                rp->clus_next = next_cluster(rp->clus_current, SINGLE);   
            }   
            rp->sec_offset = 1;   
            addr_temp = clust_to_addr(rp->clus_current);   
        }   
   
        if (append_toc(rp)==0)   
        {   
            return((sint)EOF);   
        }   
        if (rp->EOF_flag == 0)   
        {   
          #ifndef _NO_FILE_DATA_BUFFER_    
            if (_FF_read(addr_temp, rp->buff)==0)   
            {   
                return((sint)EOF);   
            }   
            rp->pntr = &rp->buff[0];  // Set pointer to next location    
          #else    
            if (_FF_read(addr_temp, _FF_buff)==0)   
                return((sint)EOF);   
            rp->pntr = _FF_buff;   
          #endif    
        }   
        if (rp->length==rp->position)   
            rp->length++;   
    }   
    else   
    {   
        rp->pntr++;   
        if (rp->length==rp->position)   
            rp->length++;   
    }   
    rp->position++;   
    return(file_data);   
}   
   
   
//**********************************************************************//    
// Writes the buffer *wr_buff to disk.  dat_size indicates the size of  //    
// each item (in bytes ie. 1 for 8-bit, 2 for 16-bit, etc.).  num_items //    
// indicates the number of items to be written.  returns the number of  //    
// items written - number of errors.                                    //    
//**********************************************************************//    
sint fwrite(void *wr_buff, uint dat_size, uint num_items, FILE *rp)   
{   
    uchar *temp_char_pntr;   
    uint temp_int;   
    uint no_bytes_cntr, i;   
   
    no_bytes_cntr = 0;   
    temp_char_pntr = wr_buff;   
    temp_int = dat_size * num_items;   
   
    for (i=0; i<TEMP_INT; #else the file #ifdef else #endif schar flash void ulong a uint <="_FF_MAX_FPRINTF))" { return (0); } +="rp-" if while _FF_error="FILE_ERR;" is _IAR_EWAVR_ #ifndef _READ_ONLY_ uchar clus_temp; sint || ((sint)EOF); current to #if defined(_CVAVR_) defined(_ICCAVR_) FILE (rp="=NULL)" i++) no_bytes_cntr++; (no_bytes_cntr dat_size); (sint)EOF) file_data, *rp) (fputc_(temp_char_pntr[i], rp)="=" temp_char_pntr[i]) no_bytes_cntr--; fputs(uchar fputsc(uchar *file_data, fputsc(PGM_P while(*file_data) (fputc_(*file_data,rp)="=" file_data++; (fputc_(*file_data++,rp)="=" (fputc_(?\r?,rp)="=" (fputc_(?\n?,rp)="=" *pstr, fprintf(FILE PGM_P ...) va_list arglist; _CVAVR_ pstr, temp_buff[_FF_MAX_FPRINTF], *fp; pstr_sram[_FF_MAX_FPRINTF]; cntr; cntr="0;" ((pstr[cntr]) && (cntr cntr++; pstr_sram[cntr]="pstr[cntr];" va_start(arglist, pstr); vsprintf(temp_buff, pstr_sram, arglist); va_end(arglist); fp="temp_buff;" (*fp) fputc_(*fp, fp++; fputc_(*fp++, rp); Set end fend(FILE (fseek(rp, 0, SEEK_END)); Goto ?off_set? of fseek(FILE *rp, off_set, mode) length_check, addr_calc; ERROR NULL (mode="=SEEK_CUR)" Trying pointer offset from position off_set>position;   
    }   
    if (off_set > rp->length)   
    {   // trying to position beyond or before file    
        rp->error = POS_ERR;   
        _FF_error = POS_ERR;   
        return ((sint)EOF);   
    }   
    if (mode==SEEK_END)   
    {   // Trying to position pointer to offset from EOF    
        off_set = rp->length - off_set;   
    }   
    #ifndef _READ_ONLY_    
    if (rp->mode != READ)   
        if (fflush(rp))   
            return ((sint)EOF);   
    #endif    
    clus_temp = rp->clus_start;   
    rp->clus_current = clus_temp;   
    rp->clus_next = next_cluster(clus_temp, SINGLE);   
    rp->clus_prev = 0;   
   
  #ifdef _BytsPerSec_512_    
    addr_calc = off_set / ((ulong) BPB_SecPerClus << 9);   
    length_check = off_set % ((ulong) BPB_SecPerClus << 9);   
  #else    
    addr_calc = off_set / ((ulong) BPB_BytsPerSec.ival * (ulong) BPB_SecPerClus);   
    length_check = off_set % ((ulong) BPB_BytsPerSec.ival * (ulong) BPB_SecPerClus);   
  #endif    
    rp->EOF_flag = 0;   
   
    while (addr_calc)   
    {   
        if (rp->clus_next >= 0xFFF8)   
        {   // trying to position beyond or before file    
            if ((addr_calc==1) && (length_check==0))   
            {   
                rp->EOF_flag = 1;   
                break;   
            }   
            rp->error = POS_ERR;   
            _FF_error = POS_ERR;   
            return ((sint)EOF);   
        }   
        clus_temp = rp->clus_next;   
        rp->clus_prev = rp->clus_current;   
        rp->clus_current = clus_temp;   
        rp->clus_next = next_cluster(clus_temp, CHAIN);   
        addr_calc--;   
    }   
   
    addr_calc = clust_to_addr(rp->clus_current);   
    rp->sec_offset = 1;          // Reset Reading Sector    
   
  #ifdef _BytsPerSec_512_    
    while (length_check >= 512)   
    {   
        length_check -= 512;   
  #else    
    while (length_check >= BPB_BytsPerSec.ival)   
    {   
        length_check -= BPB_BytsPerSec.ival;   
  #endif    
        addr_calc++;   
        rp->sec_offset++;   
    }   
   
  #ifndef _NO_FILE_DATA_BUFFER_    
    if (_FF_read(addr_calc, rp->buff)==0)        // Read Current Data Sector    
        return((sint)EOF);      // Read Error    
   
    if ((rp->EOF_flag == 1) && (length_check == 0))   
      #ifdef _BytsPerSec_512_    
        rp->pntr = &rp->buff[511];   
      #else    
        rp->pntr = &rp->buff[BPB_BytsPerSec.ival-1];   
      #endif    
    else   
        rp->pntr = &rp->buff[length_check];   
  #else    
    if (_FF_read(addr_calc, _FF_buff)==0)       // Read Current Data Sector    
        return((sint)EOF);      // Read Error    
   
    if ((rp->EOF_flag == 1) && (length_check == 0))   
      #ifdef _BytsPerSec_512_    
        rp->pntr = &_FF_buff[511];   
      #else    
        rp->pntr = &_FF_buff[BPB_BytsPerSec.ival-1];   
      #endif    
    else   
        rp->pntr = &_FF_buff[length_check];   
  #endif    
    rp->position = off_set;   
   
    return (0);   
}   
   
// Return the current position of the file rp with respect to the begining of the file    
ulong ftell(FILE *rp)   
{   
    if (rp==NULL)   
        return ((ulong)EOF);   
    else   
        return (rp->position);   
}   
   
// Funtion that returns a '1' for @EOF, '0' otherwise    
sint feof(FILE *rp)   
{   
    if (rp==NULL)   
        return ((sint)EOF);   
   
    if (rp->length==rp->position)   
        return (1);   
    else   
        return (0);   
}   
   
#ifdef _DEBUG_ON_    
#ifndef _NO_FILE_DATA_BUFFER_    
extern flash schar __CRLF[];   
extern flash schar __Xstr[];   
   
void dump_file_data_hex(FILE *rp)   
{   
    uint n, c;   
   
    if (rp == NULL)   
        return;   
   
    for (n=0; n<0x20; n++)   
    {   
        printf(__CRLF);   
        for (c=0; c<0x10; c++)   
            printf(__Xstr, rp->buff[(n<<5)+c]);   
    }   
}   
   
void dump_file_data_view(FILE *rp)   
{   
    uint n;   
   
    if (rp == NULL)   
        return;   
   
    printf(__CRLF);   
  #ifdef _BytsPerSec_512_    
    for (n=0; n<512; n++)   
  #else    
    for (n=0; n<BPB_BYTSPERSEC.IVAL; n++) #endif putchar(rp->buff[n]);   
}   
#endif    
#endif   
