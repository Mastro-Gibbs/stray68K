function getACEEditorText()
{
    Wt.emit('EditorCpp', 'onContentRequest_Signal', ace.edit('editor').getValue());
}

function getBreakPoints()
{
    Wt.emit('EditorCpp', 'onBreakpointsRequest_Signal', Object.keys(ace.edit('editor').session.getBreakpoints()).toString());
}