#ifndef APP
#define APP

// the run() function within an app will be a sefcontained loop that runs until "ESC" is pressed or the app has ended
class App {
    public:
    virtual void run(uint32_t time = 0, bool timed = false) = 0;
};



#endif
