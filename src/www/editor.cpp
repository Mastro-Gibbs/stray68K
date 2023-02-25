#include "editor.hpp"

#include <algorithm>

Editor::Editor()
    : self(""),
      jsEditorContentRequestSignal(this, "onContentRequest_Signal"),
      jsEditorInputSignal(this, "onEditorInput_Signal"),
      WTemplate(tr("editor-msg"))
{
    this->setId("EditorCpp");

    jsEditorContentRequestSignal.connect(std::bind(&Editor::onContentRequest, this, std::placeholders::_1));

    jsEditorInputSignal.connect(this, [=]
                                { onTextChange.emit(); });
}

void Editor::onContentRequest(std::string result)
{
    self = result;

    onTextAvailable.emit();
}


std::string Editor::getText()
{
    return self;
}


void Editor::disable(bool status)
{
    if (status)
    {
        doJavaScript("ace.edit('editor').setReadOnly(true);");
    }
    else
    {
        doJavaScript("ace.edit('editor').setReadOnly(false);");
    }
}