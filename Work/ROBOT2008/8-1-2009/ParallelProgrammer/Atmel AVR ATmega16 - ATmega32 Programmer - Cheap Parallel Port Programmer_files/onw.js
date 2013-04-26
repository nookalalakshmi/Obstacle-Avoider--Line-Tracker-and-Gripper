document.write("<div id='opensinnewwindow' style='position:absolute; visibility:hidden; top:1; left:1; border: 1px solid #000000; background-color:#fff9c8; font-family:Verdana; font-size: 11px; color:#111111; font-weight: normal;'>&nbsp;This link opens in a new window!&nbsp;</div>");
var links = document.getElementsByTagName('A');
for (var i=0; i<links.length; i++) {
	if (links[i].target == "_blank") {
		if(window.addEventListener){//Moz,NN
			links[i].addEventListener('mouseover',displaylayer,false);
			links[i].addEventListener('mouseout',displaylayer,false);
		} else {//IE
			links[i].attachEvent('onmouseover',displaylayer);
			links[i].attachEvent('onmouseout',displaylayer);
		}		
	}
}

var state = 0;
var mousex = 0;
var mousey = 0;

var IE = document.all?true:false
if (!IE) document.captureEvents(Event.MOUSEMOVE)
document.onmousemove = getMouseXY;

function getMouseXY(e) {
	if (IE) {
		mousex = event.clientX + document.body.scrollLeft
		mousey = event.clientY + document.body.scrollTop
	} else {
		mousex = e.pageX;
		mousey = e.pageY;
	}  
	if (mousex < 0) { mousex = 0; }
	if (mousey < 0) { mousey = 0; }
	mousex = mousex + 20;
	return true;
}

function displaylayer() {
	if (state == 1) { state = 0; } else { state = 1; }
    if(document.layers)	{//NN4+
		document.layers['opensinnewwindow'].style.left = mousex;
		document.layers['opensinnewwindow'].style.top = mousey;
    	document.layers['opensinnewwindow'].visibility = state ? "show" : "hide";
	} else if(document.getElementById) {//Moz,NN6,IE5+
    	var obj = document.getElementById('opensinnewwindow');
		obj.style.visibility = state ? "visible" : "hidden";
		document.getElementById('opensinnewwindow').style.left = mousex;
		document.getElementById('opensinnewwindow').style.top = mousey;
	} else if(document.all) {//IE 4
		document.all['opensinnewwindow'].style.left = mousex;
		document.all['opensinnewwindow'].style.top = mousey;
		document.all['opensinnewwindow'].style.visibility = state ? "visible" : "hidden";
	}
	return false;
}