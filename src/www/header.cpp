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
    btn->clicked().connect(this, &Header::redirectToGH);
    btn->setStyleClass("header-title");

    title = template_->bindWidget("title", move(btn));

}


void Header::redirectToGH() 
{
    title->doJavaScript("window.open('https://github.com/Mastro-Gibbs/stray68K', '_blank');");
}