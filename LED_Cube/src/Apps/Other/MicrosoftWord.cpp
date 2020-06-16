#include "MicrosoftWord.h"

bool MicrosoftWord::frame()
{
    if (c == PS2_ENTER)
    {
        lower = !lower; // just flip the layer on enter
    }
    else if (c != '\0')
    {
        if (lower)
        {
            TypeEngine::typeLower(c, TypeEngine::getLowerCharCount() % 2 == 0 ? color1 : color2);
        }
        else
        {
            TypeEngine::typeUpper(c, TypeEngine::getUpperCharCount() % 2 == 0 ? color1 : color2);
        }
    }
    return CONTINUE_PROGRAM;
};