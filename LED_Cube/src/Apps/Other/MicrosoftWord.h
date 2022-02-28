#ifndef MICROSOFT_WORD
#define MICROSOFT_WORD
#include "../../../src/LED_Cube_library/Basic_Functions.h"
#include "../../../src/LED_Cube_library/Helpful_Functions.h"
#include "../App.h"
#include "../../Tools/Input/Input.h"
#include "../../Tools/TypingEngine/TypeEngine.h"
class MicrosoftWord: public App
{
private:
    bool lower = false;
    uint16_t color1 = 0xFFE0;
    uint16_t color2 = 0x001F;
protected:
    App::Resut frame();
public:
    const String title = "Word";
};
#endif
