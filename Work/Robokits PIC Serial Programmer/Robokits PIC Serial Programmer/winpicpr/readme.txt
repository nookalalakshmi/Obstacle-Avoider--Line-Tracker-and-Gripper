Information about DL4YHF's Pic Programmer for Windows
------------------------------------------------------

   Last updated: 2007-05-20 (ISO-format,YYYY-MM-DD)

   Authors: 
     - WinPic by Wolfgang Buescher (DL4YHF), Spenge, Germany .
     - PIC18F support by Martin van der Werff .
     - Translations into other languages: see 'About'-box.

   THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS 
   OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
   THE IMPLIED WARRANTIES OF MERCHANTABILITY
   AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
   IN NO EVENT SHALL THE AUTHOR AND CONTRIBUTORS BE 
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
    OR PROFITS; OR BUSINESS INTERRUPTION) 
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
   (INCLUDING NEGLIGENCE OR OTHERWISE) 
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   In other words, the entire risk is with you ...
    .. what else would you expect from a freeware program ?
    
   Permission to use, copy, modify, and distribute this 
   software and its documentation for any purpose and 
   without fee is hereby granted, provided that the above 
   copyright notice and disclaimer appear in all copies 
   and supporting documentation.

  Namings for products in the software and this manual, that are
  registered trademarks, are not separately marked. The same applies
  to copyrighted material. Therefore the missing (r) or (c) character
  does not implicate, that the naming is a free trade name. Furthermore
  the used names do not indicate patent rights or anything similar.
      Anyway..
      MPLAB, PIC, PICmicro are registered trademarks 
              of Microchip Technology Incorporated .
  
  NOTE THAT THIS PROGRAMMER DOES NOT MEET MICROCHIP'S REQUIREMENTS FOR
       A "PRODUCTION GRADE" PROGRAMMER BECAUSE IT CANNOT VERIFY THE PIC
       AT DIFFERENT SUPPLY VOLTAGES.


Short Description
-------------------
A PIC is a small single-chip controller which can be used for many purposes.
A simple piece of hardware is required to program a PIC via the serial 
interface of a PC (COM1..COM4), or via parallel interface (LPT1..LPT2).
There was a simple DOS-program called "PIP-02" to do this, but that program
did not work properly on my PC under windows, so I decided to write my own.
Supported devices are: PIC16C84, 16F84, 16F626, 12F675, 12F508/9,
                       16F818, 16F87x, 16F87xA 16F88,.. 16F9xx,..
                       PIC18F2xx0   (tested with PIC18F2550),
                       dsPIC30F2xxx (tested with dsPIC30F2010),
          ... and hopefully some more.

Supported interfaces:  COM84, JDM, Tait(-ish), Velleman K8048,
                       SM6LKM PIP84, 
              and other "simple" programmers which do *NOT*
              require a programmed PIC to program other PIC's !


The programer runs on a PC with WIN95/Win98/Win2000/Win XP .
Under Windows NT 4, you will need an administrator account 
otherwise the SmallPort utility will not work properly.

After installing the software, there is MORE UP-TO-DATE INFO in the manual, 
 see html\index.htm .  

What you will find in THIS document, but not in the manual (html),
 is how to customize WinPic and how to translate the user interface
 into other languages. 
 See chapter  Customizing WinPic for special applications
         and  Translating WinPic into other languages 
 near the end of this readme file.



Supplementary files which are NOT contained in the WinPic archive
-------------------------------------------------------------------
 
To have an up-to-date selection list on the "Device/Config" tab,
you may copy one of the DEV-files from Microchip's MPLAB IDE(tm)
into WinPic's \devices subdirectory. 
Please note that the *.DEV files are Microchip's property,
and the MPLAB(tm) IDE LICENSE GRANT does not allow me to
include these files in the WinPic installation. 
For more info on this subject, read \devices\readme_dev.txt !




Command Line Arguments
-------------------------------------------------------------------

You may call WinPic from a batch file, or an integrated development environment 
to do an automated job without any user intervention. 
For example, you can tell WinPic to load a program from a hexfile, 
write it into the target device, and terminate itself afterwards.
The following list shows all command line parameters which are accepted:

<any string not beginning with a slash>
  considered a file name which will be loaded or saved (depending on /p or /r).
  If a file name is specified but no other argument, the file will
  be LOADED from disk but not programmed into the device. 

/p
  program (write data from HEX file into the connected device).

/r 
  read the contents of the device and dump them into a HEX file.

/q 
  terminates WinPic. Helpful for "batch programming" from a shell.

/nodelay
  suppress the "pause" before command-line driven operation starts.

/overwrite
  With this option, WinPic won't ask before overwriting an already
  existing disk file. Use it together with the /r command if necessary.

/device=XXXX
  Override the PIC device from the last session.

/config_word=XXXX
  Override the configuration word loaded from a HEX file. 4-letters HEX
  without prefix !

The command-line driven operation can be cancelled by pressing ESCAPE. 
The main menu will be enabled anyway. Selecting certain menu items also 
cancels command-line mode (and 'batch' mode).

Example (in a DOS batchfile):
  winpic.exe keyer1.hex /p /q

Loads the file KEYER1.HEX, programs it into the connected device, 
and terminates WinPic ("quit").



Interface for PIC16x84
----------------------
The required interface is a very common *SERIAL* interface. The connections
between COM-Port and the PIC are:

  Serial Interface  | direction           |      PIC signal
 -------------------+---------------------+-----------------------------
     RTS (pin 7)    |   >>                |   Pin 12 = RB6   = clock
     DTR (pin 4)    |   >> (via resistor) |   Pin 13 = RB7   = data
     CTS (pin 8)    |   <<                |   Pin 13 = RB7   = data
     TXD (pin 3)    |   >> (12 Volts!)    |   Pin  4 = MCLR  = Vpp
     TXD (pin 3)    |   >> ( 5 Volts)     |   Pin 14 = "Vdd" = +5V supply
     GND (pin 5)    |    -                |   Pin  5 = "Vss" = ground

There is a schematic for the simplest possible PIC programmer below;
however I don't prefer this one but a slightly improved version which appeared
in the German "Funkamateuer" magazine, May 1998, page 544 
(Warning: The circuit diagram in the FUNKAMATEUR article has some design flaws.
          See comments below !)

If your interface for the serial port uses inverted control signals (because 
you have an inverting RS-232 level converter like the MAX232), you can drive 
your interface with a customized interface definition file. This is explained
in the HTML document.
 


EXTRA SIMPLE Interface schematics (not recommended)
----------------------------------------------------
Before building this, check the output voltage of your TXD signal (the programmer
software allows you to "switch" the signals manually for this purpose !).
If it is less than 12 Volts, you should prefer an interface which uses the TXD
signal to switch a stabilized Vpp and Vdd instead of directly driving the PIC.

   (use a fixed font like COURIER NEW to display this diagram)

                   -------------------------<< TXD(3)
        __         |   __
  |----|__|-----------|__|----
  |     10k            2k2   |      |/ D1
  |                          |------|------------------|
  |     ----------------     |      |\ Zener 5.6V      |
  |   --| 1          18|--  \|/D2                      |
  |   --| 2          17|--  ---     ||  C1             |
  |   --| 3          16|--   |------||-----------------|
  |-----| 4 MCLR     15|--   |     +||- 10uF           |
   -----| 5 gnd  Vdd 14|------                         |
   |  --| 6      RB7 13|-------------------->> CTS(8)  |
   |  --| 7      RB6 12|------  |     __               |
   |  --| 8          11|--   |  -----|__|---<< DTR(4)  |
   |  --| 9          10|--   |    2k2 __               |
   |    ----------------     --------|__|---<< RTS(7)  |
   |                              22k                  |
   |------------------------------------------------------() GND(5)


Note: I do not RECOMMEND this schematics, though some folks use it
(see the link list at the end of this document).
You should add a few diodes to limit the voltages on RB6 and RB7 to the
range of 0V to 5V (the serial interface produces up to +- 12V !) 
to prevent latch up. 
D1, D2 and C1 produce the supply voltage for the PIC from the programming
voltage. Not all serial interfaces are strong enough on TXD to produce
the required Vpp pulse (on MCLR) ! The schematics for a better programmer
which programs EPROM-based PICs too can be found in the manual 
(see html\index.htm ).


Adaptions for other PIC programmer hardware
---------------------------------------------
It would be easy to modify the programmer to support some other 
PIC programmers, especially those using the parallel port.
The problem is I do not have/need other PIC programming hardware,
so I cannot test it...
Since February 2002, its possible to use some PIC programmers
for the parallel port, though Windows (especially the newer 
versions like XP) sometimes play a trick on us, it fiddles around
with the ports if some input signals (like "PAPER OUT") change.
However, you may try to get your old parallel programmer running.
Maybe it helps to de-activate (or even uninstall ?!) the printer
driver but IMO that is a bad situation.
Since October 2002, you can define the hardware connections
of your programming interface in a simple text file
(the HTML documents have more info how to achive this,
 at least one sample file is contained in the program archive).

You can test the behaviour of the LPT port with the interface
test built inside the programmer. You can modify the control
signals and watch the state of the data input signal.
I connected a couple LEDs to the parallel port and noticed them
flashing while the "PAPER OUT" line changed. 


Notes on the "AllPic2"-Programmer from "FUNKAMATEUR 5/1998"
------------------------------------------------------------
This article appeare in the German amateur radio magazine "FUNKAMATEUR" in
May 1998 on page 544. The principle is basically the same as the above circuit,
but it uses an external power supply and a stabilized +5V and +13V source.
The basic idea is ok, but the realization is not as good as it COULD be...
   - The "positive" protecting diodes for RB6 and RB7 must be connected to 
     the PIC's Vdd pin, not Vpp like the author did. Vpp carries 13V, but the
     voltage at RB6 and RB7 must never exceed Vdd to avoid latch-up.
     Connecting D6 and D9 to Vpp is really stupid. Connect them to Vdd,
     and add a 5.6V-Zener to prevent Vdd from rising too high.
   - Do NOT use 1N4148 as "protection" diodes against ground and Vcc because
     their forward voltage is too high to protect the PIC.
     Use a BAT42 or similar schottky type ! (D6,D7,D8,D9)
   - Reduce C1 to 4.7 uF or even less. There is no need for C1 to be 22uF !
     Because this programmer switches Vdd together with Vpp, a problem may
     result if C1 charges too slowly (the PIC needs a steep slope at Vpp).
   - Connect a 220 Ohm resistor in series with the collector of Q4 .
     Without this, too much current is drawn when charging C1, as a result
     the Vpp signal does not rise fast enough, possibly causing trouble.
   - Some newer devices (like PIC12F675) *REQUIRE* Vpp raised before Vdd.
     Older programming specifications did not mention Vdd in the sequence
     to enter programming mode. This may cause some trouble, also related
     with C1 having a too high capacity in this design !



Software Installation
----------------------
Since November 2005, there is an installer for WinPic. 
Just unzip the installer, then let it do it's job.. which is
installing the following files into a directory of your choice:

  WinPic.exe          =  the executable file
  SampleInterfaceX.ini=  some sample programming interface definition files
  AN589Interface.ini  =  programming interface definition for "AN589" programmer
  topic_interface.ini =  programming interface definition for D.Tait's "TOPIC"
  html\*.htm,*.gif    =  the manual (keep this directory structure!)
  smport.sys, smport.vxd = (slow) driver for direct port access under 
              Win95, Win98, Win ME, 2000, Win NT and Win XP.
              The SmallPort utility was written by A.Weitzman.
  PortTalk.sys        =  slightly faster port driver, should work on most machines.
                         By Craig Peacock ( http://www.beyondlogic.org ) .
  translations\*.txt  =  translations of the user interface into other languages.
       At the moment, the "language pack" contains:

 - Czech
 - Dutch
 - French
 - Greek
 - Polish
 - Portuguese
 - Russian
 - Spanish
 - Turkish

Some of these translations may be a bit outdated since they were made
for an earlier version of WinPic. For English and German, the 
"language pack" is not required. How to add support for your own 
language (or update one of the existing translations) is described 
further down in this document .


After the first successful program start, select your PIC type and your
programmer hardware. Don't forget to choose the COM port where you want to
connect the programmer (usually COM1 or COM2). You will only have to do
that once, because all important settings are saved in a INI-file.
   Note on serial interfaces: Because WinPic needs to set the TxD line
   to a permanently low or high level, it accesses the modem control 
   register. This is the reason why WinPic does (at the moment) **NOT**
   work with USB<->RS232 port adapters.


Operation
-----------------------
Not much to say about this.. if you have ever used PIP02, you will find
almost the same functions and menu structure in this programmer.

The usual operation sequence is:
1.) Start the programmer (and, if required, connect a 13V-power supply)
2.) If not done before, select the proper device type
3.) Load a HEX-file with "File..Load"
4.) Insert a PIC in your programmer
5.) Program the PIC with "Device..Program"

You don't have to erase the PIC before programming, the software will do
that automatically.

It is important to select the proper device type *before* loading the
HEX file, because if you try to load a 2kWord program into a 512Word
buffer, something may be truncated (you'll get an error message).

The help system (in html format) offers a solution if you want to program
PICs which are not listed in the combo box on the "device" sheet.

The software will always show you the success or errors of all actions.
If there is an error message in the status line at the bottom of the
programmer's window, change to the "message"-tab where you see a complete
list of all errors (with more infos about the cause of the error, etc).

Also the configuration word and the initial DATA EEPROM will be programmed,
if the HEX-file you loaded contains data in the equivalent memory ranges.
For more information on this, you should look into Microchip's data sheets.



Customizing WinPic for special applications
----------------------------------------------
What you will not find in the manual: It is possible to turn off
some parts of WinPic's user interface. You can use this if your
'customer' shall not use all options. For this purpose, you must
supply your own SETTINGS.INI (or at least some fragments) with 
the WinPic archive. In the segment [PicMain] you must add the 
parameter 'Customize' with a text editor, for example:

[PicMain]
Customize=3

The 'customize' value is a bit-combination with the following 
meaning (maybe more, look into APPL.H if you have it):
  bit 0 : "don't show the interface selection list"
  bit 1 : "don't use the internal device list"
  bit 2 : "don't allow using the HEX-EDITOR"
  bit 3 : "don't allow editing the CONFIG word"
  bit 4 : "hide the EDIT menu and all its contents"
  bit 5 : "hide the SPECIALS submenu"




Translating the WinPic user interface into other languages
-------------------------------------------------------------
You can translate WinPic's user interface into your own
language if you like. Most strings are read from a lookup-table
which can be loaded from a textfile. 
The language used by WinPic can be selected from a combo-list .
Only English and German are "built-in" (hard-coded) in WinPic .
Translations into other languages are available on
in the "language pack" on DL4YHF's WinPic website, which contains
a french, greek, portugese, spanish, and turkish translation.

To add other languages, you do NOT need to have the
sourcecodes of WinPic - because the language can be read from a
textfile (which is not included in the standard distribution).
All files in the 'translations' folder will be read
during the initialisation, and all languages in these files
will appear in the language selection list (on the "Options" tab).
If such a file for "your" language does not already exist,
you can generate a template for such a textfile with WinPic itself.
For example, from the 'Tools' menu, select 'Specials', 
 and then 'Dump translation table to file'.
This will produce a file named 'translation_test.txt' in the WinPic
directory, which you can edit and extend with a text editor.
Immediately rename this file into something else, for example
into "french.txt".

For example, a french translation file will look like this:

:<languages>
en:English
fr:Français      <<<<< modify this line for your language !
:Insert..
f:insérer..
(...)

Each line in the file contains exactly one translation.
Usually there is only English and "your" language in a single file.
 ( Theoretically there can be more than one translation
   in a single file, but this makes maintenance difficult
   if different authors have to work on a single file.  )

The first characters in a line define if it's the reference string
(which is searched in the table when translating a string),
and the translations in the following lines. 
A colon (:) in the first column indicates a reference string,
which YOU MUST NOT MODIFY otherwise WinPic cannot find the translation
(there a no "string reference numbers" or similar stuff).
One or two lower-case letters followed by a colon indicate the language
of the translation which follows in the text line.
For example, in the default file you will find something like this:

:Delete
de:Löschen  <<<<  the German translation of "Delete" 

If you want to add a French translation, you would add a new line
after this (in the same group of translations for "Delete") like this:

:Delete
fr:Couper

Do this with a few hundred other lines, too ... and if it works,
and its one of the "common" languages listed below, please send me a copy !
The language identifiers use the ISO 639-1 language codes :
  en:  english   (may be abbreviated as e: here)
  de:  german    (may be abbreviated as d: here)
  fr:  french    (may be abbreviated as f: here)
  it:  italian   (may be abbreviated as i: here)
  es:  spanish   (may be abbreviated as s: here)
  da:  danish
  nl:  dutch; flemish
  pt:  portuguese
  sv:  swedish
To check if all translations are complete, you can activate the 
LanguageTestMode by setting this parameter to 1 (one) in SETTINGS.INI :

[PicMain]
LanguageTestMode=0        (usually zero, but ONE for "language-test")
Language=de               (ISO 639-1 code for user's language)

With 'LanguageTestMode' set to 1 (ONE), WinPic will show a list 
of untranslated strings in that case, and show the missing strings 
in the main window. You can easily copy it from there and append it
to "your" translation.

There are a few special characters in the translation table 
which must be treated carefully. These are so-called "format strings"
which are replaced by variables (numbers or strings) during run-time.
Some examples:  %d = integer number,   %s = placeholder for a string.
The count, sequence, and correct spelling of these numbers is very
important, otherwise WinPic (or, to be precise, the sprintf function)
will crash !
 ( Note: There are some format strings like %06lX which print a 6-digit
   hexadecimal number. The "l" is a lower case "L", not a "one" !
   To avoid problems with this, DO NOT TYPE THE FORMAT STRINGS YOURSELF,
   instead use an already existing translation file as a template,
   but DO NOT CHANGE the sequence of the arguments, of the format strings.
 )


If you are considering to produce a translation into your native 
language : Many thanks in advance ! But please contact me before you
start, because only one translator (person) can modify the translation
table at a time - I have no utility to "merge" two translations into
one file. Contact me before you start, to make sure you translate
the very latest version ! (I may be working on an unreleased version
at the moment you read this).

Since WinPic is still growing, some new menu items may be missing
in an old translation file. If WinPic cannot find a string in the 
translation table, it lists them on the message tab, after the error 
message "UNTRANSLATED STRINGS FOUND".
WinPic also lists the string (below that message) in the message list,
so you can easily copy & paste them into the language file to update it.
If you found such an error message, but don't know how to update the
message file, you can also mail me a copy of the error message, and the
translation into your language. Example (copied from message list):
------ UNTRANSLATED STRINGS FOUND (FromLang=en, ToLang=de) ------
  "slow mode (to check for timing problems)", 
In german, a possible translation of this string would be:
  "Langsame Programmierung (Timing-Probleme)" .
If possible, don't make the translated string much longer than the
original (in english language), because otherwise the controls may
overlap on the screen. A 10% safety margin is usually possible.





Revision History
-------------------------
 Please note: Meanwhile there are a few other programs called "WinPic"
  on the web, so if you look for an update of this one search the net
  for "WinPic" AND "DL4YHF" (which is the author's amateur radio call).

 V2.9g, June 2007:
       A.Kibler added support for PIC12F609, PIC12F610, 615 and 616.
       Thanks !

 V2.9f, May 2007:
       Modfied the GUI, so non-standard I/O addresses for the LPT port
       are accepted now (like B800, on the "Interface" tab).

 V2.9e, January 2007:
       Microchip has changed the command pattern for "Bulk Erase"
       for some PIC18F4xxx devices, somewhere between DS39622B
       and DS39622J (="Flash Memory Programming Specification").
       Read the FAQ list if you have problems with erasing a certain
       PIC18F2xxx / PIC18F4xxx ! The device database (DEVICES.INI)
       can be modified if the "new" erase algo doesn't work with one
       of the "older" chips.

 V2.9d, February 2006:
       Changed the verification of CONFIG BITS for the PIC18F series.

 V2.9c, December 2005: Tried to add support for PIC16F716, 
       but couldn't test this due to lack of samples ,
     + modified the installer so it asks before overwriting
       DEVICES.INI  .
      

 V2.9b, November 2005: Fixed a bug in the dsPIC code, which caused an
                 error when reading or verifying code memory 
                 in dsPIC30F6010 above address 0x010000 (caused by
                 missing carry into the TBLPAG register) .
     + Added the option to use PortTalk instead of SMPORT,
       which works faster on some machines (especially for PIC18F + dsPIC),
     + Finally made an installation script for WinPic,
       using Russel Jordan's nice freeware "Inno Setup Compiler",
     + Emphasized the importance of "PGC & PGD filtering" in the manual
       ( low pass fiters on clock- and data signals) for PIC18F + dsPIC
     + fixed a blank-check-issue with PIC16F628A (2005-11-26)

 V2.9, October 2005: Now loading DEVICES.INI as a text file, because
                 under Win98 there is a 64 kByte limit for INI-files.
 V2.8,  August 2005: Tried to fix a problem with PIC16F73/74/76/77 .

 V2.7,  June 2005: More PIC18F devices now contained in DEVICES.INI .
                   Thanks to Nam Nguyen-Quang for testing them .
                 + Added a toolbar with "speed buttons" which I hardly
                   use myself.. please let me know if something misses.

 V2.6,  May 2005 : More PIC18F-devices supported (see manual).
                 + PIC10F200/202/204/206 now supported, tested
                   with SM6LKM programmer, COM84, and "JDM2"-interface.

 V2.5,  Feb-March 2005: Added support for dsPIC30F (and "simple" interfaces).
                       Support for PIC18F by Martin van der Werff .
                       Optional import of Microchip's DEV-files if they
                       are specified in the device definition, and can be
                       found in subdirectory \devices .
      ToDo: Any idea how to detect the full path where these
            files are located within "MPLAB IDE" ?
          ( Not asking for the path itself, which depends on where you 
            installed MPLAB... but for some kind of registry query trick.. )
                 

 V2.46, January 2005:  Added greek translation, thanks Kateris Ioannis .
                       Added spanish translation, thanks Ruben Dominguez .

 V2.45, November 2004:  Added the option "DataOutWhileReading" in the
                        interface definition file (see manual).
                        Added the automatic detection of translations.
                        Added French translation, thanks Alain Pierre.
        December 2004:  The 16F737 programming algorithm doesn't seem 
                        to work -> changed the ERASE time, but don't think
                        this was the reason. If YOU have this chip,
                        and successfully programmed it using WinPic,
                        please let me know so I can remove this paragraph !

 V2.44, September 2004: Edited the device definition list (DEVICES.INI).
                        Changed the Vpp/Vdd-switching sequence for 16F87xA.

 V2.43, August 2004:    Support for 16F737 (etc), new options for editing
                        the configuration memory (formerly ID Locations).
                        Now prepared for PIC with up to 64 config memory
                        locations.

 V2.42, May 2004:       Added a small delay between "program" and "verify"
                        to discharge a capacitor between MCLR and GROUND
                        (required for certain boards when programming
                         PIC16F8xxA, but not for PIC16F84 ).
                        Added support for the JDM-PIC-programmer 2.

 V2.41, March 2004:     A few minor bugfixes, and
                        added two interface definition files for the 
                        Bojan Dobaj programmer - thanks Ricardo Teves !
                        Added support for PIC16F648A - thanks Mikkel !
 V2.4, January 2004:    Added support for PIC16F873A(!) .. PIC16F877A   
                        in the file DEVICES.INI. Only tested PIC16F873A .
                        Also for PIC16F628A(!) which has a different
                        'bulk erase' algorithm compared to the 16F628 .
 V2.3, December 2003:   Added support for PIC16F88 (with TWO config words),
                        and implemented the 'most recent file' list in the
                        FILE menu.
 V2.2, November 2003:   Fixed a bug which caused problems with the
                        manual replacement of the bandgap calibration bits 
                        in a 12F675 .
 V2.1, November 2003:   Added a test for the DELAY routine.
                        Added command line option "\v" (verify).
                        Added the "ID location" tab.
 V2.0, September 2003:  Added support for PIC16F818. New devices may be
                        added by the USER now by modifying DEVICES.INI .
 V1.9, May 2003:        Algorithm for PIC16F73..77 modified, but not tested.
                        Plans for an optional "production grade" programmer
                        which can VERIFY at different supply voltages.
 V1.8, February 2003:   Interfaces on the serial port (other than COM84)
                        can be driven by WinPic now, customizable via 
                        interface definition file (macros txd,dtr,rts,cts,
                        also invertable for MAX232 etc).
 V1.7, January 2003:    Changed the DEFAULT programming sequence
                         to "First Vpp the Vdd". If this causes problems,
                        you can manually select "First Vdd then Vpp" which
                        may be reqired for some stoneage devices.
                      + Added option "no special treatment for Bandgap calib"
                      + Changed control signal "ICSP connect" for
                        SM6LKM's "PIC FLASH programmer 2002-10".
                        (a transistor has been added, so D7 HIGH = disconnect,
                         which is better because for most PC's this is the
                         state after power-on)
                      + added the "PullMclrDown" control signal for "AN589"
                      + Improved the "SmallPort" interface so SMPORT.SYS
                        will be found even its neither in the "system"
                        directory nor in the "current" directory
                          (but in the directory where WinPic.exe is located).
 V1.6, November 2002:   The file selector for "Load Hex File" refused
                        to work if a path didn't exist (?!?).
                        Hopefully fixed now. There are some rare
                        devices listed now which are not supported
                        yet...
 V1.5, October 2002:    Support for almost any "simple" programmer
                        on the parallel port by means of the
                        'interface definition file'.
                        PIC16C63 tested (with 16C61 settings).
                        "Batch" and "Command-line-driven" operation.
 V1.4, September 2002:  Added support for new device PIC12F675
                        (8 pins, 10 bit ADC, FLASH+EEPROM).
                        Programming adapter described in manual.
 V1.3, February 2002:   PIC16F87x now supported, also a few
                        programmer interfaces for the parallel
                        port (LPT1 or LPT2).
 V1.2, January 2002:    Now using A.Weitzman's SmallPort utility
                        for port access, WinPic works properly
                        under Windows XP (and under W95,W98, NT).
                        Increased the max CODE memory size to 
                        8kWord so programming "other" PICs
                        like the 16F876 may work too (not tested).
 V1.1, December 2001:   PIC16F628, PIC16C711 and a few others 
                        also supported... but not properly tested.
                        The PIC16F628 fails on DATA EEPROM Verify,
                        but the code programming looks good.
 V1.0, November 2000:   PIC16C84 and PIC16F84 supported
                 

Literature, PIC Links
----------------------
 All PIC links have been moved to the HTML file completely.
 
 http://people.freenet.de/dl4yhf/winpicpr.html
    Is the present author's HAM RADIO homepage where you will find
    the latest release of this program.
    If my homepage has moved, search the web for
    "DL4YHF PIC Programmer". There are a lot of programs out there
    called "WinPic" but they have nothing to do with PIC micros .




  .-.-.  ...-.-
