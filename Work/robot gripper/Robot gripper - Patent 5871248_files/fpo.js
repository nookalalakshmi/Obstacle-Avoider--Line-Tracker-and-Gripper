function SetChecked(formName, chkName) 
{
	var form = formName;
	dml=document.forms[form];
	len = dml.elements.length;
	var i=0;

	for( i=1 ; i<len ; i++) 
	{
		if (dml.elements[i].name==chkName) 
		{
			dml.elements[i].checked = dml.master.checked;
		}
	}
}

function popUpWindow(url, height, width, left, top)
{
	var load_win = window.open(url, 'FPU', 'resizable=yes, copyhistory=no, scrollbars=yes, menubar=no, height='+height+', width='+width+', left='+left+', top='+top+', toolbar=no, location=no, status=no');
    return false
}

function rePopulate(c, form_id, append_flag)
{	 	
	if (form_id=="apn") 
	{ 	
	    opener.document.getElementById(form_id).value=c+"/";
	}
	else if (append_flag=="append")
	{
        opener.document.results.query_txt.focus();
		val = opener.document.results.query_txt.value;
        c = c.replace(/ /,"");		
	    opener.document.results.query_txt.value=(val+c);
	}
	else
	{   	    
	    opener.document.getElementById(form_id).value=c;	
	} 
  
	window.close();

	if (append_flag=="append")
	{
	    opener.document.results.query_txt.focus();
	}
	else
	{
		opener.document.getElementById(form_id).focus();
	}
}

function updateAlert11(alertId,id,so)
{
	alert(alertId);
	var form='myalert';
	dml=document.forms[form];

	alert_f=document.getElementById(id).selectedIndex;
	alert(alert_f);
	location.href="myalert.html?update="+ alertId +"&alert_f="+ alert_f +"&so=" + so ;
}

function monthlyAlert(so)
{
	var form='myalert';
	dayOfMonth=document.getElementById("day-of-month").value;
	location.href="acct-alerts.pl?a_month=" + dayOfMonth +"&so=" + so ;
	alert(alert_f);
}

function toggleMenuSection(unique) 
{
	action = "toggleType = toggleDiv('div_" + unique + "', '" + unique + "_div');";
	eval(action);
	action = "thisImage = document.getElementById('img_" + unique + "');";
	eval(action);
	if (document.getElementById('div_' + unique).offsetHeight > 0)
	{
        thisImage.src = "/images/menu_tree_open.gif";
    }
    else 
	{
       	thisImage.src = "/images/menu_tree_closed.gif";
    }
}

function enable_combo(checkboxName, comboboxName)
{
	if(document.getElementById(checkboxName).checked==true)
	{
		document.getElementById(comboboxName).disabled=false;
	}
	else
	{
		document.getElementById(comboboxName).disabled=true;
	}
}

function openpopup(popurl)
{
	var winpops=window.open(popurl,"","top=50,left=150,width=570,height=600,scrollbars=yes,resizable=yes");
}

function toggleDiv(divName, hiddenBoxName) 
{
    thisDiv = document.getElementById(divName);
    if (thisDiv)
    {
       	if (thisDiv.style.display == "none") 
		{
        	thisDiv.style.display = "block";
    		for(i=1;i<4;i++)
    		{
   			document.getElementById(hiddenBoxName+i).value = true;
    		}
        }
        else 
		{
    		thisDiv.style.display = "none";
    		for(i=1;i<4;i++)
    		{
    			document.getElementById(hiddenBoxName+i).value = false;
    		}
        }
    }
    else 
	{
    	errorString = "Error: Could not locate div with id: " + divName;
    	alert(errorString);
    }
}

function CreateBookmarkLink(hostName) 
{
	var urlAddress = "http://" + hostName;
	var pageName = "FreePatentsOnline.com";
	
	if (window.sidebar)  // Mozilla Firefox Bookmark
	{
   		// window.sidebar.addPanel(document.title, location.href, "")
   		window.sidebar.addPanel(pageName, urlAddress, 0);
	} 
	else if(window.external)  // IE Favorite
	{
    	// window.external.AddFavorite(location.href, document.title)
    	window.external.AddFavorite(urlAddress, pageName); 
	}
	else if(window.opera && window.print)  // Opera Hotlist
	{
   		var mbm = document.createElement('a');
		mbm.setAttribute('rel','sidebar');
		mbm.setAttribute('href',url);
		mbm.setAttribute('title',title);
		mbm.click();
	}
	else
	{
		// alert("Sorry! Your browser doesn't support this function.");
		return true;
	}
}

function ietruebody()
{
	return (document.compatMode && document.compatMode!="BackCompat")? document.documentElement : document.body
}

function ddrivetip(thetext, thecolor, thewidth)
{   
	document.onmousemove=positiontip
	var ns6=document.getElementById && !document.all
	if (ns6||ie)
	{
		if (typeof thewidth!="undefined") tipobj.style.width=thewidth+"px"
		if (typeof thecolor!="undefined" && thecolor!="") tipobj.style.backgroundColor=thecolor
		tipobj.innerHTML=thetext
		enabletip=true
		return false
	}
}

function positiontip(e)
{  	
  var BrowserDetect = {
	init: function () {
		this.browser = this.searchString(this.dataBrowser) || "An unknown browser";
		this.version = this.searchVersion(navigator.userAgent)
			|| this.searchVersion(navigator.appVersion)
			|| "an unknown version";
		this.OS = this.searchString(this.dataOS) || "an unknown OS";
	},
	searchString: function (data) {
		for (var i=0;i<data.length;i++)	{
			var dataString = data[i].string;
			var dataProp = data[i].prop;
			this.versionSearchString = data[i].versionSearch || data[i].identity;
			if (dataString) {
				if (dataString.indexOf(data[i].subString) != -1)
					return data[i].identity;
			}
			else if (dataProp)
				return data[i].identity;
		}
	},
	searchVersion: function (dataString) {
		var index = dataString.indexOf(this.versionSearchString);
		if (index == -1) return;
		return parseFloat(dataString.substring(index+this.versionSearchString.length+1));
	},
	dataBrowser: [
		{ 	string: navigator.userAgent,
			subString: "OmniWeb",
			versionSearch: "OmniWeb/",
			identity: "OmniWeb"
		},
		{
			string: navigator.vendor,
			subString: "Apple",
			identity: "Safari"
		},
		{
			prop: window.opera,
			identity: "Opera"
		},
		{
			string: navigator.vendor,
			subString: "iCab",
			identity: "iCab"
		},
		{
			string: navigator.vendor,
			subString: "KDE",
			identity: "Konqueror"
		},
		{
			string: navigator.userAgent,
			subString: "Firefox",
			identity: "Firefox"
		},
		{
			string: navigator.vendor,
			subString: "Camino",
			identity: "Camino"
		},
		{		// for newer Netscapes (6+)
			string: navigator.userAgent,
			subString: "Netscape",
			identity: "Netscape"
		},
		{
			string: navigator.userAgent,
			subString: "MSIE",
			identity: "Explorer",
			versionSearch: "MSIE"
		},
		{
			string: navigator.userAgent,
			subString: "Gecko",
			identity: "Mozilla",
			versionSearch: "rv"
		},
		{ 		// for older Netscapes (4-)
			string: navigator.userAgent,
			subString: "Mozilla",
			identity: "Netscape",
			versionSearch: "Mozilla"
		}
	],
	dataOS : [
		{
			string: navigator.platform,
			subString: "Win",
			identity: "Windows"
		},
		{
			string: navigator.platform,
			subString: "Mac",
			identity: "Mac"
		},
		{
			string: navigator.platform,
			subString: "Linux",
			identity: "Linux"
		}
	]

};
BrowserDetect.init();
	if (enabletip)
	{
		var curX=(ns6)?e.pageX : event.clientX+ietruebody().scrollLeft;
		var curY=(ns6)?e.pageY : event.clientY+ietruebody().scrollTop;
		//Find out how close the mouse is to the corner of the window
		var rightedge=ie&&!window.opera? ietruebody().clientWidth-event.clientX-offsetxpoint : window.innerWidth-e.clientX-offsetxpoint-20
		var bottomedge=ie&&!window.opera? ietruebody().clientHeight-event.clientY-offsetypoint : window.innerHeight-e.clientY-offsetypoint-20

		var leftedge=(offsetxpoint<0)? offsetxpoint*(-1) : -1000

		//if the horizontal distance isn't enough to accomodate the width of the context menu
		if (rightedge<tipobj.offsetWidth)
		{
			//move the horizontal position of the menu to the left by it's width
			tipobj.style.left=ie? ietruebody().scrollLeft+event.clientX-tipobj.offsetWidth+"px" : window.pageXOffset+e.clientX-tipobj.offsetWidth+"px";
		}
		else if (curX<leftedge)
			tipobj.style.left="5px"
		else
			//position the horizontal position of the menu where the mouse is positioned
			tipobj.style.left=curX+offsetxpoint+"px"

			//same concept with the vertical position
		if (bottomedge<tipobj.offsetHeight)
		{
		     tipobj.style.top=ie? ietruebody().scrollTop+event.clientY-tipobj.offsetHeight-offsetypoint+"px" : window.pageYOffset+e.clientY-tipobj.offsetHeight-offsetypoint+"px";
		}
		else
			tipobj.style.top=curY+offsetypoint+"px"
			tipobj.style.visibility="visible"
	}
}

function hideddrivetip()
{ 
	if (ns6||ie)
	{
		enabletip=false
		tipobj.style.visibility="hidden"
		tipobj.style.left="-1000px"
		tipobj.style.backgroundColor=''
		tipobj.style.width=''
	}
}

function clearSearchForm()
{
	var formInputs = document.getElementsByTagName('input');
	for (var i = 0; i < formInputs.length; i++)
	{
		var theInput = formInputs[i];
		if (theInput.type == 'text')
		{
			theInput.value = '';
		}
		
		if (theInput.type == 'checkbox')
		{
			if (theInput.name == "uspat")
			{
				theInput.checked = true;
			}
			else
			{
				theInput.checked = false;
			}
		}
		
		if (theInput.type == 'radio')
		{
			if (theInput.id == "exdate_all" || theInput.id == "exstemmingon" || theInput.id =="exsortchrono" || theInput.id =="ezdate_all" || theInput.id =="ezstemmingon" || theInput.id =="ezsortchrono")
			{
				theInput.checked = true;
			}
			else
			{
				theInput.checked = false;
			}
		}
	}
	
	formInputs = document.getElementsByTagName('textArea');
	var theTextArea = formInputs[0];
	theTextArea.value = '';
}

function clearContactUsForm()
{
	var formInputs = document.getElementsByTagName('input');
	for (var i = 0; i < formInputs.length; i++)
	{
		var theInput = formInputs[i];
		if (theInput.type == 'text')
		{
			theInput.value = '';
		}
	}
	formInputs = document.getElementsByTagName('textArea');
	var theTextArea = formInputs[0];
	theTextArea.value = '';
	formInputs = document.getElementsByTagName('select');
	var theSelect = formInputs[0];
	theSelect.value= 'Select';
	theSelect = formInputs[1];
	theSelect.value= 'QuestionComment';
}

function tmenudata0()
{
	this.imgage_gap = 3	
	this.plus_image = "/images/plus.jpg"
	this.minus_image = "/images/minus.jpg"
	this.pm_width_height = "12,9"
	this.folder_image = "/images/folder.gif"
	this.document_image = "/images/document.gif"
	this.icon_width_height = "16,14"
	this.indent = 20;
	this.use_hand_cursor = true;
	this.main_item_styles =           "text-decoration:none;		\
                                           font-weight:normal;		\
                                           font-family:Arial;		\
                                           font-size:12px;			\
                                           color:#333333;			\
                                           padding:2px;				"


    this.sub_item_styles =            "text-decoration:none;		\
                                           font-weight:normal;		\
                                           font-family:Arial;		\
                                           font-size:12px;			\
                                           color:#333333;			"

	this.main_container_styles = "padding:0px;"
	this.sub_container_styles = "padding-top:7px; padding-bottom:7px;"

	this.main_link_styles = "color:#ff6923; text-decoration:none;"
	this.main_link_hover_styles = "color:#ff6923; text-decoration:underline;"

	this.sub_link_styles = ""
	this.sub_link_hover_styles = ""

	this.main_expander_hover_styles = "text-decoration:underline;";
	this.sub_expander_hover_styles = "";
}

/*
Function to dynamically change the font size of inventor name in Patent Plaque
*/

function FormUpdate(input_param) 
{
    document.getElementById(input_param).innerHTML= document.getElementById('plaque_data').value;
   
    var inv_length = document.getElementById('plaque_data').value.length;
    var diff = inv_length - 11; 
    if(diff > 0)
    {
	    if (diff <= 1)
	    {
            document.getElementById(input_param).style.fontSize = '11px';
	    }
	    else if(diff > 1 && diff <= 5 )
	    {
            document.getElementById(input_param).style.fontSize = '10px';    
        }
        else if(diff > 5)
        {
            document.getElementById(input_param).style.fontSize = '9px'; 
        }	
    }
    else if(document.getElementById(input_param).style.fontSize != 12)
    {
        document.getElementById(input_param).style.fontSize = '12px';
    }	
}

// Copy to clipboard functions

function getvalue(){
  document.getElementById('source_textarea').value;
}

function ClipBoard(from)
{
Copied = from.createTextRange();

Copied.execCommand("Copy");
}

function copy_clip(meintext){
	if (window.clipboardData){
		window.clipboardData.setData("Text", meintext);
	}else if (window.netscape){
		netscape.security.PrivilegeManager.enablePrivilege  ('UniversalXPConnect');

		var clip = Components.classes['@mozilla.org/widget/clipboard;1'].createInstance(Components.interfaces.nsIClipboard  );
		if (!clip) return;

		var trans = Components.classes['@mozilla.org/widget/transferable;1'].createInstance(Components.interfaces.nsITransferable);
		if (!trans) return;

		trans.addDataFlavor('text/unicode');

		var str = new Object();
		var len = new Object();

		var str = Components.classes["@mozilla.org/supports-string;1"].createInstance(Components.interfaces.nsISupportsString);
		var copytext=meintext;
		str.data=copytext;
		trans.setTransferData("text/unicode",str,copytext.length*2);
		var clipid=Components.interfaces.nsIClipboard;

		if (!clip) return false;
		clip.setData(trans,null,clipid.kGlobalClipboard);

	}

	return false;
}



