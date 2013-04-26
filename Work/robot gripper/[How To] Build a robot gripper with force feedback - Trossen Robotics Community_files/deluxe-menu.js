/*
   Deluxe Menu Data File
   Created by Deluxe Tuner v3.2
   http://deluxe-menu.com
*/

var key="171b2027es5id";
var key1="199b3442es5id";
var key2="185b2741es5id";
var key3="181b2493es5id";

// -- Deluxe Tuner Style Names
var itemStylesNames=["topItem0","topItem1",];
var menuStylesNames=["submenu1","submenu2",];
// -- End of Deluxe Tuner Style Names

//--- Common
var isHorizontal=1;
var smColumns=1;
var smOrientation=0;
var dmRTL=0;
var pressedItem=-2;
var itemCursor="pointer";
var itemTarget="_self";
var statusString="link";
var blankImage="data.files/blank.gif";
var pathPrefix_img="/tr-horz-menu/";
var pathPrefix_link="/tr-horz-menu/";

//--- Dimensions
var menuWidth="100%";
var menuHeight="38px";
var smWidth="";
var smHeight="";

//--- Positioning
var absolutePos=0;
var posX="0px";
var posY="0px";
var topDX=0;
var topDY=-1;
var DX=-7;
var DY=-4;
var subMenuAlign="left";
var subMenuVAlign="center";

//--- Font
var fontStyle=["bold 10px Verdana, Arial, Helvetica, sans-serif","bold 10px Verdana, Arial, Helvetica, sans-serif"];
var fontColor=["",""];
var fontDecoration=["none","none"];
var fontColorDisabled="";

//--- Appearance
var menuBackColor="";
var menuBackImage="";
var menuBackRepeat="no-repeat";
var menuBorderColor="";
var menuBorderWidth=0;
var menuBorderStyle="none";

//--- Item Appearance
var itemBackColor=["#edeef0","#b2c9f7"];
var itemBackImage=["",""];
var beforeItemImage=["",""];
var afterItemImage=["",""];
var beforeItemImageW=0;
var afterItemImageW=0;
var beforeItemImageH=0;
var afterItemImageH=0;
var itemBorderWidth=0;
var itemBorderColor=["",""];
var itemBorderStyle=["none","none"];
var itemSpacing=0;
var itemPadding="0px 2px 0px 2px";
var itemAlignTop="center";
var itemAlign="right";

//--- Icons
var iconTopWidth="";
var iconTopHeight="";
var iconWidth="";
var iconHeight="";
var arrowWidth="";
var arrowHeight="";
var arrowImageMain=["",""];
var arrowWidthSub=0;
var arrowHeightSub=0;
var arrowImageSub=["",""];

//--- Separators
var separatorImage="";
var separatorWidth="0px";
var separatorHeight="0px";
var separatorAlignment="center";
var separatorVImage="data.files/separator.gif";
var separatorVWidth="26PX";
var separatorVHeight="38px";
var separatorPadding="";

//--- Floatable Menu
var floatable=0;
var floatIterations=6;
var floatableX=1;
var floatableY=1;
var floatableDX=15;
var floatableDY=15;

//--- Movable Menu
var movable=0;
var moveWidth=12;
var moveHeight=20;
var moveColor="#AA0000";
var moveImage="";
var moveCursor="default";
var smMovable=0;
var closeBtnW=15;
var closeBtnH=15;
var closeBtn="";

//--- Transitional Effects & Filters
var transparency="100";
var transition=-1;
var transOptions="";
var transDuration=300;
var transDuration2=200;
var shadowLen="";
var shadowColor="";
var shadowTop=0;

//--- CSS Support (CSS-based Menu)
var cssStyle=0;
var cssSubmenu="";
var cssItem=["",""];
var cssItemText=["",""];

//--- Advanced
var dmObjectsCheck=0;
var saveNavigationPath=1;
var showByClick=0;
var noWrap=1;
var smShowPause=100;
var smHidePause=1000;
var smSmartScroll=1;
var topSmartScroll=1;
var smHideOnClick=1;
var dm_writeAll=0;
var useIFRAME=0;
var dmSearch=0;

//--- AJAX-like Technology
var dmAJAX=0;
var dmAJAXCount=0;
var ajaxReload=0;

//--- Dynamic Menu
var dynamic=0;

//--- Keystrokes Support
var keystrokes=1;
var dm_focus=1;
var dm_actKey=113;

//--- Sound
var onOverSnd="";
var onClickSnd="";

var itemStyles = [
    ["itemWidth=100%","itemHeight=38px","itemBackImage=data.files/HeaderRepeat.gif,","itemBorderWidth=0","itemBorderStyle=none,none","fontStyle='normal 10px Verdana, Arial, Helvetica, sans-serif','normal 10px Verdana, Arial, Helvetica, sans-serif'","fontColor=#000000,#000000","fontDecoration=none,underline","arrowImageMain=data.files/arr_black.gif,data.files/arrv_black.gif","showByClick=0"],
    ["itemBackColor=#edeef0,","itemBorderWidth=1","itemBorderStyle=none,none","fontDecoration=none,underline","arrowImageSub=data.files/arr_black.gif,data.files/arrv_black.gif","showByClick=0"],
];
var menuStyles = [
    ["menuBackColor=#edeef0","menuBorderWidth=1","menuBorderStyle=solid","menuBorderColor=#c7ced3","smColumns=1","itemPadding=5px 10px 5px 10px","smOrientation=0"],
    ["menuBackColor=#edeef0","menuBorderWidth=1","menuBorderStyle=solid","menuBorderColor=#c7ced3","smColumns=1","itemPadding=20px 10px 5px 10px","smOrientation=0"],
];

var menuItems = [

    ["-","", "", "", "", "", "", "", "", "", "", ],
    ["SHOPPING","http://www.trossenrobotics.com/", "", "", "", "", "0", "-1", "", "", "", ],
        ["|Robot Kits","http://www.trossenrobotics.com/Robots.aspx", "", "", "", "", "-1", "0", "", "", "", ],
        ["|Robot Parts","http://www.trossenrobotics.com/robot-parts.aspx", "", "", "", "", "-1", "0", "", "", "", ],
        ["|Educational Robotics","http://www.trossenrobotics.com/educational-robotics-division.aspx", "", "", "", "", "-1", "0", "", "", "", ],
        ["|RFID","http://www.trossenrobotics.com/c/usb-serial-rfid-readers-tags-kits.aspx", "", "", "", "", "-1", "0", "", "", "", ],
    ["-","", "", "", "", "", "", "", "", "", "", ],
    ["CONTACT","http://www.trossenrobotics.com/contact.aspx", "", "", "", "", "0", "", "", "", "", ],
    ["-","", "", "", "", "", "", "", "", "", "", ],
    ["SHOPPING HELP","http://www.trossenrobotics.com/shoppinghelp.aspx", "", "", "", "", "0", "", "", "", "", ],
        ["|Contact","http://www.trossenrobotics.com/contact.aspx", "", "", "", "", "", "0", "", "", "", ],
        ["|Log In / Order Status","https://www.trossenrobotics.com/store/login.aspx", "", "", "", "", "", "0", "", "", "", ],
        ["|View Cart","http://www.trossenrobotics.com/store/ShopCart.aspx", "", "", "", "", "", "0", "", "", "", ],
        ["|Terms, Conditions & Policies","http://www.trossenrobotics.com/terms-conditions-policies.aspx", "", "", "", "", "1", "-1", "", "", "", ],
    ["-","", "", "", "", "", "", "", "", "", "", ],
    ["COMMUNITY","http://forums.trossenrobotics.com/", "", "", "", "", "0", "", "", "", "", ],
        ["|Community Home","http://forums.trossenrobotics.com/", "", "", "", "", "", "0", "", "", "", ],
        ["|Forums","http://forums.trossenrobotics.com/vb_index.php", "", "", "", "", "", "0", "", "", "", ],
        ["|TRC Tutorials","http://forums.trossenrobotics.com/forumdisplay.php?f=118", "", "", "", "", "", "0", "", "", "", ],
        ["|Member Blogs","http://forums.trossenrobotics.com/blog.php", "", "", "", "", "", "0", "", "", "", ],
        ["|Data Center","http://forums.trossenrobotics.com/downloads.php", "", "", "", "", "", "0", "", "", "", ],
        ["|Image Galleries","http://forums.trossenrobotics.com/gallery", "", "", "", "", "", "0", "", "", "", ],
        ["|Calendar","http://forums.trossenrobotics.com/calendar.php?c=1", "", "", "", "", "", "0", "", "", "", ],
        ["|Links Directory","http://forums.trossenrobotics.com/links", "", "", "", "", "", "0", "", "", "", ],
    ["-","", "", "", "", "", "", "", "", "", "", ],
    ["CONTEST","http://www.trossenrobotics.com/contest.aspx", "", "", "", "", "0", "-1", "", "", "", ],
    ["-","", "", "", "", "", "", "", "", "", "", ],
    ["BLOG","http://blog.trossenrobotics.com/index.php", "", "", "", "", "0", "-1", "", "", "", ],
    ["-","", "", "", "", "", "", "", "", "", "", ],
    ["AFFILIATES","http://www.trossenrobotics.com/TrossenRoboticsAffiliates.aspx", "", "", "", "", "0", "", "", "", "", ],
        ["|Sign In","https://www.trossenrobotics.com/store/affiliates/login2.aspx", "", "", "", "", "", "0", "", "", "", ],
        ["|Logos / Graphics","http://www.trossenrobotics.com/TrossenRoboticsLogos.aspx", "", "", "", "", "", "0", "", "", "", ],
        ["|About","http://www.trossenrobotics.com/TrossenRoboticsAffiliates.aspx", "", "", "", "", "", "0", "", "", "", ],
    ["-","", "", "", "", "", "", "", "", "", "", ],
];

dm_init();