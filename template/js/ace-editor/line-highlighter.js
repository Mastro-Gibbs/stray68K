var lines = new Map();

var Range = ace.require('ace/range').Range;

function getLines()
{
	lines = new Map();
	var editor = ace.edit('editor');
	var array = editor.getValue().split('\n');

	for (let index = 0, i = 0; index < array.length; index++) 
	{
		var item = array[index].trim();
		
		if (item.length !== 0 && item[0] !== ';' && !item.includes(":") && 
		  	!item.includes("DC.") && !item.includes("dc.") && 
		  	!item.includes("DS.") && !item.includes("ds.") &&
		  	!item.includes("EQU") && !item.includes("equ") &&
			!item.includes("SET") && !item.includes("set") &&
			!item.includes("ORG") && !item.includes("org"))
		{
			var label = extractLabel(item);

			if (label !== -1)
				lines.set(i, [index, label, findAheadInstruction(array, label), -1]);
			else
				lines.set(i, [index, label, findNextStatementIndex(array, index), -1]);

			i+=1;
		}
  	};
	
	fixUp();
}


linesIndex = 0;
function doLineHighLight(programcounter)
{
	var editor = ace.edit('editor');

	removeAllMarkers(); 

	try
	{
		var lineData;

		lineData = testPC(programcounter);

		if (lineData === -1)
		{
			lineData = lines.get(linesIndex);
			lineData[3] = programcounter;
		}
		
		editor.session.addMarker(new Range(lineData[0], 0, lineData[0], 1), 'marker', 'fullLine');

		linesIndex = extractLinesIndex(lineData[2]);
		
	} catch (error) {}
	
}

function testPC(pc)
{
	for (const [key, value] of lines)
	{
		if (value[3] === pc)
			return value;
	}

	return -1;
}

function resetHighlightingIndex()
{
	linesIndex = 0;
}



function removeAllMarkers()
{
	var editor = ace.edit('editor');
	let prevMarkers = editor.session.getMarkers();
	if (prevMarkers) {
		let prevMarkersArr = Object.keys(prevMarkers);
		for (let item of prevMarkersArr)
			editor.session.removeMarker(prevMarkers[item].id);
	}
}


function findAheadInstruction(array, _label)
{
	label = new RegExp("\\b^" + _label + "(:)?\\b", "g");
	var pos = -1;
	var exists = array.some(function(item, index) {
		if (item.match(label)){
    		pos = index;
			return true;
		}
	});


	var fui = -1;

	if (exists)
	{
		for (let i = pos+1; i < array.length; i++) {
			var item = array[i].trim();
			if (item[0] !== ';' && item.length !== 0 && !item.includes(":") && 
				!item.includes("DC.") && !item.includes("dc.") && 
				!item.includes("DS.") && !item.includes("ds.") &&
				!item.includes("EQU") && !item.includes("equ") &&
				!item.includes("SET") && !item.includes("set") &&
				!item.includes("ORG") && !item.includes("org"))
				{
					fui = i;
					break;
				}
		};
	}

	return fui;
}

function extractLabel(instruction)
{
	if (instruction.includes("JMP") || instruction.includes("jmp") || 
		instruction.includes("JSR") || instruction.includes("jsr") ||
		instruction.includes("BRA") || instruction.includes("bra") ||
		instruction.includes("BSR") || instruction.includes("bsr"))
	{
		var array = instruction.split(' ');
		return array[array.length - 1];
	}
	
	return -1;
}


function extractRTxLabel(index)
{
	var editor = ace.edit('editor');
	var array = editor.getValue().split('\n');

	for (let i = index-1; i != 0; i--) 
	{
		var item = array[i];
		label = new RegExp("\\b^.*(:)?\\b", "g");
		if (item.match(label))
		{
			return item;
		}
	}

	return -1;
}


function findNextStatementIndex(array, index)
{
	var item0 = array[index];
	var isRTx = false;

	if (item0.includes("RTS") || item0.includes("rts") || 
		item0.includes("RTE") || item0.includes("rte") ||
		item0.includes("RTR") || item0.includes("rtr"))
	{
		index -= 1;
		isRTx = true;
	}

	for (let i = index+1; i < array.length; i++) 
	{
		var item = array[i].trim();
		
		if ((item.includes("RTS") || item.includes("rts") || 
			item.includes("RTE") || item.includes("rte") ||
			item.includes("RTR") || item.includes("rtr")) && isRTx)
		{
			isRTx = false;
			
			label = extractRTxLabel(index);

			if (label !== -1)
			{
				label = label.split(':')[0];

				for (const [key, value] of lines) 
				{
					if (value[1] === label)
					{
						return findNextStatementIndex(array, value[0]);
					}
				}

				return label;
			}
		}
		else
		if (item.length !== 0 && item[0] !== ';' && !item.includes(":") && 
		  	!item.includes("DC.") && !item.includes("dc.") && 
		  	!item.includes("DS.") && !item.includes("ds.") &&
		  	!item.includes("EQU") && !item.includes("equ") &&
			!item.includes("SET") && !item.includes("set") &&
			!item.includes("ORG") && !item.includes("org"))
		{
			return i;
		}  
		
	}

	return -1;
}


function extractLinesIndex(lookahead)
{
	for (const [key, value] of lines)
	{
		if (value[0] === lookahead)
			return key;
	}

	return -1;
}

function fixUp()
{
	var editor = ace.edit('editor');
	var array = editor.getValue().split('\n');

	for (const [key1, value1] of lines)
	{
		if (typeof value1[2] !== "number")
		{
			var label = value1[2];
			for (const [key2, value2] of lines)
			{
				if (value2[1] === label)
				{
					var line = value2[0];
					value1[2] = findNextStatementIndex(array, line);
				}
			}
		}
	}
}
