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