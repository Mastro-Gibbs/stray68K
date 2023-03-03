function hidePopupConsoleDiv()
{
    const popupconsole = document.getElementById('console-popup');
    popupconsole.style.display = 'none';
}

function showPopupConsoleDiv()
{
    const popupconsole = document.getElementById('console-popup');
    popupconsole.style.display = 'block';
}

function downloadSourceFile(timestamp)
{
    var content = ace.edit('editor').getValue(); 
    var fileBlob = new Blob([content], {type: 'text/plain'}); 
    var downloadLink = document.createElement('a'); 
    downloadLink.href = URL.createObjectURL(fileBlob); 
    downloadLink.download = timestamp; 
    document.body.appendChild(downloadLink); 
    downloadLink.click(); 
    downloadLink.remove(); 
}

function isValidInstruction(item)
{
    item = item.trim();
    
    if (item.length !== 0 && item[0] !== ';' && !item.includes(":") && 
		!item.includes("DC.") && !item.includes("dc.") && 
		!item.includes("DS.") && !item.includes("ds.") &&
		!item.includes("EQU") && !item.includes("equ") &&
		!item.includes("SET") && !item.includes("set") &&
		!item.includes("ORG") && !item.includes("org"))
    {
        return true;
    }

    return false;
}


function showEditorError(editor, msg)
{
    var err_lab = document.getElementById('editor-error-label');
    err_lab.innerText = msg;
    err_lab.style.display = 'block';
    err_lab.classList.add("popup-div-editor-animation-in");
    editor.setReadOnly(true);

    if (err_lab.offsetWidth < err_lab.scrollWidth)
        err_lab.style.width = err_lab.scrollWidth + "px";

    err_lab.addEventListener("click", function()
    {
        err_lab.innerText = "";
        err_lab.style.opacity = '0';
        err_lab.style.display = 'none';
        err_lab.classList.remove("popup-div-editor-animation-in");
        editor.setReadOnly(false);
    });
}


function initACEEditor()
{
    var editor_template  = "\t; Stray68K Motorola68000-ASM Emulator\n\n\n\tORG\t\t$1000\n\n\t\n\t; place code here\n\n\n\tEND"; 

    var editor = ace.edit('editor'); 
    editor.setTheme('ace/theme/tomorrow_night'); 
    editor.setFontSize(16); 
    editor.session.setMode('ace/mode/motorola68000'); 
   
    editor.setValue(editor_template); 
    editor.focus();
    editor.gotoLine(6, 1, true);

    editor.addEventListener('input', function(){ 
        let prevMarkers = editor.session.getMarkers();
        if (prevMarkers) {
            let prevMarkersArr = Object.keys(prevMarkers);
            for (let item of prevMarkersArr)
                editor.session.removeMarker(prevMarkers[item].id);
        }
        Wt.emit('EditorCpp', 'onEditorInput_Signal', null); 
    }); 
   
    editor.commands.addCommands(
        [
            {
                name: 'zoomin', 
                bindKey: {win: 'Ctrl-Alt-I'},
                exec: function(editor) {
                    editor.setFontSize(editor.getFontSize() + 2);
                },
                readOnly: false,
            }, 
            {
                name: 'zoomout',
                bindKey: {win: 'Ctrl-Alt-D'},
                exec: function(editor) {
                    editor.setFontSize(editor.getFontSize() - 2);
                },
                readOnly: false,
            }
        ]
    );
   
    editor.on('gutterclick', function(e) {
        showEditorError(editor, 'Breakpoints are not available for now.');
    });
    
    var langTools = ace.require('ace/ext/language_tools'); 
   
    langTools.setCompleters([myCompleter]);
   
    editor.setOptions({
        enableBasicAutocompletion: true,
        enableSnippets: true,
        enableLiveAutocompletion: true
    });
}