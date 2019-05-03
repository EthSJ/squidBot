#include <windows.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
#include <thread>

std::string squidSelect(int &k);
void printLoop();
void stopMe();
void toClipboard(const std::string &s);

static boolean stop, random;
static int ttk, timing, minutes, ss;
static std::string units;

int main(int argc, char* argv[])
{
    std::cout<<"Select your squid\n1.Surprised\n2.kittykraken\n3.raspberry\n4. Discord\n10. random\n";
    std::cin>>ss;
    toClipboard(squidSelect(ss));

    //turning on and off random
    if(ss==10)
        random=1;
    else
        random=0;

    std::cout<<"Timing?\n1. Minute\n2. Half Minute\n3. Seconds\n";
    std::cin>>timing;

    switch(timing)
    {
        case 1: timing=60000;
                units=" minutes\n";
            break;
        case 2: timing=30000;
                units=" half minutes\n";
            break;
        case 3: timing=1000;
                units =" seconds\n";
            break;
        default: timing=1000;
                units=" seconds\n";
            break;
    }
    std::cout<<"Minute variance (10 is standard)?\n";
    std::cin>>minutes;

    stop = 0;
    std::thread first (printLoop);
    std::thread second (stopMe);

    first.join();
    second.join();
    return 0;
}
std::string squidSelect(int &k)
{
    switch(k)
    {
        //surprised squid
        case 1: return "\\\\\\\\ºoº/////";
            break;
        //kittykraken
        case 2: return "\\\\\\\\ºwº/////";
            break;
        //raspberries
        case 3: return "\\\\\\\\ºÞº/////";
            break;
        //discord
        case 4: return ":squid::";
            break;
        //just mess it all up
        case 10:
            {
                srand(time(NULL));
                int i= rand()%4+1;
                return squidSelect(i);
            }
            break;
        //surprised
        default: return "\\\\\\\\ºoº/////";
            break;
    }
}

void printLoop()
{
    const int KEYEVENT_KEYUP = 0x02;
    srand(time(NULL));

    while(stop==0)
    {
        //if it's random time
        if(random==1)
            toClipboard(squidSelect(ss));

        //otherwise print what we have
        keybd_event(VK_CONTROL,0,0,0);              // press the CTRL key
        keybd_event(0x56,0,0,0);                    // press the v key
        keybd_event(0x56,0,KEYEVENT_KEYUP,0);       // let up the V key
        keybd_event(VK_CONTROL,0,KEYEVENT_KEYUP,0); //let up CTRL
        keybd_event(VK_RETURN,0,0,0);               // press enter
        keybd_event(VK_CONTROL,0,KEYEVENT_KEYUP,0); // release enter
        ttk = (rand()%minutes+1)*timing;                  //sleep for 1 to 10 minutes
        std::cout<<"Next nuking in: "<< (ttk/timing) << units;
        Sleep(ttk);
    }
}

void stopMe()
{
    Sleep(2000);
    while(stop==0)
    {
        std::string check;
        std::cin>>check;
        if(check.compare("stop") == 0)
            stop=1;
    }
}

//black magic windows stuff
void toClipboard(const std::string &s)
{
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size());
	if (!hg)
        {
            CloseClipboard();
            return;
        }
	memcpy(GlobalLock(hg),s.c_str(),s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}
