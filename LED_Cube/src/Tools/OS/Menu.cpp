#include "Menu.h"
#include "../../Tools/TypingEngine/TypeEngine.h"
Menu::Menu(App **theApps, uint8_t m1, App** screenSavers, uint8_t m2)
{
    
    max = m1;
    asleep = new Asleep(screenSavers, m2);
    apps = theApps;
}
void Menu::run()
{
    asleep->go(15000);
    while (true)
    {
        char c;
        uint8_t current = 0;
        while (true)
        {
            if (keyboard.available())
            {
                c = keyboard.read();
            }

            if (c == PS2_ESC) {
                asleep->go(20000);
            }

            if (c == PS2_LEFTARROW)
            {
                current = current == 0 ? max - 1 : current - 1;
            }

            if (c == PS2_RIGHTARROW)
            {
                current = current == max - 1 ? 0 : current + 1;
            }

            if (c == PS2_ENTER)
            {
                (*apps[current]).run();
            }
            TypeEngine::drawChar(current + '0', 5, 5, 0, Relativistic::FORWARD, 0xFFFF);
            TypeEngine::drawChar(current + '0', 6, 5, 1, Relativistic::FORWARD, 0xFFFF);
            TypeEngine::autoTypeLower((*apps[current]).title, 0x001F, 0xFFE0, true);
            c = '\0';
        }
    }
};