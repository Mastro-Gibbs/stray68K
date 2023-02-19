#include "editor.hpp"

#include <algorithm>

#define EDITOR_TEXT_TEMPLATE "\tORG\t$1000\n\n\t; write code here\n\t; no END instuction needed\n\t; you can write declarations after executable code\n\n\t"


Editor::Editor()
    : self(nullptr),
      line_counter(nullptr),
      WTemplate(tr("editor-msg"))
{}

void Editor::setUpEditor()
{
    auto row_c = make_unique<WTextArea>(tr("row_counter"));
    row_c->setStyleClass("containeritem-row-count-style");

    auto editor = make_unique<WTextArea>(tr("editor"));
    editor->setStyleClass("containeritem-editor-style");

    line_counter = bindWidget("row_counter", move(row_c));
    self      = bindWidget("editor",      move(editor));

    self->setAttributeValue("wrap", "off");

    line_counter->setText("1");
    self->setText(EDITOR_TEXT_TEMPLATE);
    updateLines();

    self->setId("editor-id");
    line_counter->setId("row-c-id");

    enableTabEvent();
    scroll();

    self->textInput().connect(this, &Editor::updateLines);

    line_counter->setReadOnly(true);
}

void Editor::enableTabEvent()
{
    self->doJavaScript("const textArea = document.getElementById(\"editor-id\"); \
                                    textArea.addEventListener(\"keydown\", function(event) { \
                                        if (event.code === \"Tab\") { \
                                            event.preventDefault(); \
                                            let start = this.selectionStart; \
                                            let end = this.selectionEnd; \
                                            this.value = this.value.substring(0, start) + '\\t' + this.value.substring(end); \
                                            this.selectionStart = this.selectionEnd = start + 1; \
                                        } \
                                    });");
}




void Editor::updateLines()
{
    
    self->doJavaScript("editor = document.getElementById('editor-id'); \
                           lc =     document.getElementById('row-c-id'); \
                           let lines = editor.value.split(\"\\n\"); \
                           let lineNumbersHTML = \"\"; \
                           for (let i = 0; i < lines.length; i++) { \
                                lineNumbersHTML += (i + 1) + \"\\n\"; \
                           } \
                           lc.value = lineNumbersHTML; \
                        ");
    
    text_changed.emit();
}

void Editor::scroll()
{
    self->doJavaScript("var textarea1 = document.getElementById('editor-id'); \
                            var textarea2 = document.getElementById('row-c-id'); \
                            textarea1.addEventListener('scroll', function() { \
                                textarea2.scrollTop = textarea1.scrollTop; \
                            }); \
                            textarea2.addEventListener('scroll', function() { \
                                textarea1.scrollTop = textarea2.scrollTop; \
                            });");
}

void Editor::setReady()
{
    self->setFocus();
    self->doJavaScript("\
        const myTextarea = document.getElementById('editor-id'); \
        const length = myTextarea.value.length; \
        myTextarea.setSelectionRange(length, length);"
    );
}

WString Editor::text_()
{
    return self->text();
}

void Editor::disable(bool status)
{
    self->setDisabled(status);
}