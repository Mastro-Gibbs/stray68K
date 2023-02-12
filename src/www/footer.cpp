#include "footer.hpp"

Footer::Footer()
    : template_(nullptr),
      WContainerWidget()
{
    WApplication* instance = WApplication::instance();

    instance->messageResourceBundle().use("template/xmls/footer");
    instance->useStyleSheet("template/css/footer.css");

    template_ = this->addWidget(make_unique<WTemplate>(tr("footer-msg")));
}