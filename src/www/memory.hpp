#ifndef __memory__68000__
#define __memory__68000__

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WTextArea.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLabel.h>

#include "../emulator/motorolatypes.h"

using namespace Wt;
using namespace std;

extern "C" {
    unsigned char* read_chunk(struct EmulationMachine* emulator, const unsigned int pointer, const unsigned int end);
}

class MemoryView : public WTemplate
{
    public: 
        MemoryView();

        void setUpMemory();

        void update(unsigned int _from = 0);

        void setEmulator(struct EmulationMachine* _emulator);

    private:
        WLabel*      currOffSet;
        WLineEdit*   from;
        WPushButton* go;

        WTextArea* addresses;
        WTextArea* bitfield;

        unsigned int offset_;

        void fetchBlock();

        

        void renderChunck(const unsigned char* block, unsigned int chunk_begin);

        struct EmulationMachine* emulator;

};



#endif // __memory__68000__