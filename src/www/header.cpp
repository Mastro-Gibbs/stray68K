#include "header.hpp"

Header::Header()
    : title(nullptr),
      template_(nullptr),
      WContainerWidget()
{
    WApplication* instance = WApplication::instance();
    
    instance->messageResourceBundle().use("template/xmls/header");
    instance->useStyleSheet("template/css/header.css");

    template_ = this->addWidget(make_unique<WTemplate>(tr("header-msg")));

    auto btn = make_unique<WPushButton>(tr("title"));
    btn->setText("Stray68K");
    btn->clicked().connect(this, &Header::openGitHubProjectPage);
    btn->setStyleClass("header-title");

    title = template_->bindWidget("title", move(btn));

}


void Header::openGitHubProjectPage() 
{
    title->doJavaScript("var newUrl = 'https://github.com/Mastro-Gibbs/stray68K'; \
                         window.open(newUrl, '_blank');");
}