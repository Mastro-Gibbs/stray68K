#include "editor.hpp"

#include <algorithm>

Editor::Editor()
    : editor_(nullptr),
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
    editor_      = bindWidget("editor",      move(editor));

    line_counter->setText("1");
    editor_->setText("");

    editor_->setId("editor-id");
    line_counter->setId("row-c-id");

    enableTabEvent();
    scroll();

    editor_->keyWentDown().connect(this, &Editor::updateLines);

    line_counter->setReadOnly(true);
}

void Editor::enableTabEvent()
{
    editor_->doJavaScript("const textArea = document.getElementById(\"editor-id\"); \
                                    textArea.addEventListener(\"keydown\", function(event) { \
                                        if (event.code === \"Tab\") { \
                                        event.preventDefault(); \
                                        let start = this.selectionStart; \
                                        let end = this.selectionEnd; \
                                        this.value = this.value.substring(0, start) + \"    \" + this.value.substring(end); \
                                        this.selectionStart = this.selectionEnd = start + 4; \
                                        } \
                                    });");
}




void Editor::updateLines()
{
    
    editor_->doJavaScript("editor = document.getElementById('editor-id'); \
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
    editor_->doJavaScript("var textarea1 = document.getElementById('editor-id'); \
                            var textarea2 = document.getElementById('row-c-id'); \
                            textarea1.addEventListener('scroll', function() { \
                                textarea2.scrollTop = textarea1.scrollTop; \
                            }); \
                            textarea2.addEventListener('scroll', function() { \
                                textarea1.scrollTop = textarea2.scrollTop; \
                            });");
}

WString Editor::text_()
{
    return editor_->text();
}