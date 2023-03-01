#include "editor.hpp"

#include <algorithm>
#include <ctime>

unsigned long long FILE_ID = 0;

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

std::string Editor::getSourceFileNameByTime()
{
    char buf[150];

    time_t now = std::time(nullptr);

    strftime(buf, sizeof(buf), "%Y_%m_%d_%H_%M_%S", localtime(&now));
    string dateTimeStr(buf);

    return "source" + dateTimeStr + "_" + to_string(FILE_ID++) + ".X68";
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