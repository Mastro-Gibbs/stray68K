#ifndef __HELP_68000_HPP_
#define __HELP_68000_HPP_

#include <Wt/WResource.h>


class HelpSection : public Wt::WResource
{
public:
  HelpSection();
  virtual ~HelpSection();

protected:
  virtual void handleRequest(const Wt::Http::Request &request,
                             Wt::Http::Response &response);
};

#endif // __HELP_68000_HPP_
