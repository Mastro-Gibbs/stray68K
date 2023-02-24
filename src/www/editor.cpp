#include "editor.hpp"

#include <algorithm>

Editor::Editor()
    : self(""),
      jsEditorContentRequestSignal(this, "onContentRequest_Signal"),
      jsBreakpointsRequestSignal(this, "onBreakpointsRequest_Signal"),
      jsEditorInputSignal(this, "onEditorInput_Signal"),
      WTemplate(tr("editor-msg"))
{
    this->setId("EditorCpp");

    jsEditorContentRequestSignal.connect(std::bind(&Editor::onContentRequest, this, std::placeholders::_1));

    jsBreakpointsRequestSignal.connect(std::bind(&Editor::onBreakpointsRequest, this, std::placeholders::_1));

    jsEditorInputSignal.connect(this, [=]
                                { onTextChange.emit(); });
}

void Editor::onContentRequest(std::string result)
{
    self = result;

    onTextAvailable.emit();
}

void Editor::onBreakpointsRequest(std::string result)
{
    breakpoints.clear();
    
    std::stringstream ss(result);
    std::string token;
    while (std::getline(ss, token, ',')) 
        breakpoints.push_back(std::stoi(token));

    onBreakpointsAvavilable.emit();
}

std::string Editor::getText()
{
    return self;
}

const std::vector<int>& Editor::getBreakpointList()
{
    return breakpoints;
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