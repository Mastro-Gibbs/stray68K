function getACEEditorText()
{
    Wt.emit('EditorCpp', 'onContentRequest_Signal', ace.edit('editor').getValue());
}