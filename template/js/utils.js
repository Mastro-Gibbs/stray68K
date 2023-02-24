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