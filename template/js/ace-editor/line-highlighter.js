var lines = new Map();
var active = -1;

editor = ace.edit('editor');
var Range = ace.require('ace/range').Range;

function getLines()
{
	lines = new Map();
	active = -1;
	var i = 0;
	editor.getValue().split('\n').forEach(function(item, index){
		item = item.trim();
		if (item[0] !== ';' && item.length !== 0 && !item.includes(":") && 
		  !item.includes("DC.") && !item.includes("dc.") && 
		  !item.includes("DS.") && !item.includes("ds.") &&
		  !item.includes("EQU") && !item.includes("equ") &&
			 !item.includes("SET") && !item.includes("set") &&
			 !item.includes("ORG") && !item.includes("org"))
		  {
				lines.set(i, [index, 0]);
				i+=1;
		  }
  });
}

/*
	BUG REPORT: if Emulator exec a BSR|JMP|BRA|RTS|RTR we have an undefinded behavior
*/
function doLineHighLight(index, pc)
{
	removeAllMarkers(); 

	pcAlreadySet = false;

	for (const [key, value] of lines) {
		if (value[1] === pc)
		{
			pcAlreadySet = true;
			editor.session.addMarker(new Range(value[0], 0, value[0], 1), 'marker', 'fullLine');
		}
	}

	if (!pcAlreadySet)
	{
		try{
			lines.get(index)[1] = pc;
			editor.session.addMarker(new Range(lines.get(index)[0], 0, lines.get(index)[0], 1), 'marker', 'fullLine');
		} catch (error) {}
	}
}





function removeAllMarkers()
{
	let prevMarkers = editor.session.getMarkers();
	if (prevMarkers) {
		let prevMarkersArr = Object.keys(prevMarkers);
		for (let item of prevMarkersArr)
			editor.session.removeMarker(prevMarkers[item].id);
	}
}