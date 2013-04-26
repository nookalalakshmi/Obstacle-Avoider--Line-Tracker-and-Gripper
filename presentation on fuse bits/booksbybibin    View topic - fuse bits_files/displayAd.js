//(function(){

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
		{
			string: navigator.userAgent,
			subString: "Chrome",
			identity: "Chrome"
		},
		{ 	string: navigator.userAgent,
			subString: "OmniWeb",
			versionSearch: "OmniWeb/",
			identity: "OmniWeb"
		},
		{
			string: navigator.vendor,
			subString: "Apple",
			identity: "Safari",
			versionSearch: "Version"
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
			string: navigator.userAgent,
			subString: "iPhone",
			identity: "iPhone/iPod"
	    },
		{
			string: navigator.platform,
			subString: "Linux",
			identity: "Linux"
		}
	]

};
BrowserDetect.init();


if(typeof(frameSize) == 'undefined' || !frameSize){var frameSize = adSize;}
if(typeof(bgColor) == 'undefined' || !bgColor){var bgColor = "";}
if(typeof(textColor) == 'undefined' || !textColor){var textColor = "";}
if(typeof(linkColor) == 'undefined' || !linkColor){var linkColor = "";}
if(typeof(plid) == 'undefined' || !plid){var plid = '15965';}
if(typeof(dtype) == 'undefined' || !dtype){var dtype = "";}
if(typeof(channel) == 'undefined' || !channel){var channel = "";}
if(typeof(birthDay) == 'undefined' || !birthDay){var birthDay = "";}
if(typeof(birthMonth) == 'undefined' || !birthMonth){var birthMonth = "";}
if(typeof(birthYear) == 'undefined' || !birthYear){var birthYear = "";}
if(typeof(age) == 'undefined' || !age){var age = "";}
if(typeof(gender) == 'undefined' || !gender){var gender = "";}
if(typeof(uid) == 'undefined' || !uid){var uid = "";}
if(typeof(t) == 'undefined' || !t){var t = "";}
if(typeof(cb) == 'undefined' || !cb){var cb = '';}
if(typeof(appId) == 'undefined' || !appId){var appId = 0;}
if(typeof(brdr) == 'undefined' || !brdr){var brdr = 'none';}else{var brdr = 'solid 1px #D3D3D3';}

var adId = Math.floor(Math.random());
var adSizeArr = adSize.split("x");
var frameSizeArr = frameSize.split("x");

var advToExc = "";
if(typeof(excAdv) != "undefined" && excAdv != null){advToExc = "&excAdv=" + excAdv;}

var fbUser = "";
if(typeof(fb_sig_user) != "undefined" && fb_sig_user != null && fb_sig_user != "")
{
	fbUser = fb_sig_user;
}
/*
else if(top.location && top.location.href)
{
	// Pull fb user id from top frame
	var regex = /(fb_sig_user|fb_sig_canvas_user)=(\d*)/i;
	var idMatch = regex.exec(top.location.href);
	if(idMatch && idMatch.length >= 3)
	{
		fbUser = idMatch[2];
	}
}
*/
var ref = "";
if(document.referrer != null){ref = document.referrer;}

var expand = false;
if(BrowserDetect.browser && BrowserDetect.browser == "Explorer" && BrowserDetect.version >= 5 && BrowserDetect.version < 8){expand = true;}


if(frameSizeArr[0] >= adSizeArr[0] && frameSizeArr[1] >= adSizeArr[1])
{
	document.write('<iframe frameborder="0" id="ad' + adId + '" style="border:'+brdr+';height:' + frameSizeArr[1] + 'px; width: ' + frameSizeArr[0] + 'px" scrolling="no" src="http://social.bidsystem.com/showAd.aspx?pid='+pid+'&plid='+plid+'&adsize='+adSize+'&appId='+appId+'&bgColor='+bgColor.replace("#", "%23")+'&textColor='+textColor.replace("#", "%23")+'&linkColor='+linkColor.replace("#", "%23")+'&channel='+channel+'&dtype='+dtype+'&t='+t+'&bday='+birthDay+'&bmonth='+birthMonth+'&byear='+birthYear+'&gender='+gender+'&ref='+ref+'&userTime='+ new Date().getTimezoneOffset() + advToExc + fbUser + '&cb=' + cb + '&expand=' + expand + '"></iframe>');
}
else
{
	document.write('Invalid frame size');
}

//})();