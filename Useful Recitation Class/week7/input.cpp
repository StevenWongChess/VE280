#include "input.h"
#include "const.h"
#include <iostream>
#include <fstream>
#include <locale>

using namespace std;

#ifdef _WIN32

char getChar() {
    char c;
    cin >> c;
    return c;
}

#else

#include <termios.h>
#include <unistd.h>

/*
Ref: https://www.ibm.com/docs/en/aix/7.1?topic=files-termiosh-file
man termios

c_lflag = local mode flags
    Controls various terminal functions. The initial value after an open is "all bits clear." 
    In addition to the basic modes, this field uses the following mask name symbols:
    ECHO：它可以让你阻止键入字元的回应。 
        Enables echo. If this flag is set, characters are echoed as they are received.
    ICANON: (正规模式)标志，它可以对所接收的字元在两种不同的终端设备模式之间来回切换。
        Enables canonical input. If this flag is set, it turns on canonical processing, 
        which enables the erase and kill edit functions as well as the assembly of input 
        characters into lines delimited by NL, EOF, and EOL characters. If the ICANON flag 
        is not set, read requests are satisfied directly from the input queue. In this case, 
        a read request is not satisfied until one of the following conditions is met:
        The minimum number of characters specified by MIN are received.
        The time-out value specified by TIME has expired since the last character was received. 
        This allows bursts of input to be read, while still allowing single-character input.
        The MIN and TIME values are stored in the positions for the EOF and EOL characters, 
        respectively. The character values of MIN and TIME are converted to their ascii 
        equivalents to get the numeric value. The time value represents tenths of seconds. 
c_cc[NCC] = control characters
    Specifies an array that defines the special control characters. 
    The relative positions and initial values for each function are:
    VMIN :非 canonical 模式读的最小字符数（MIN 主要是表示能满足read的最小字元数）。
        Indexes the MIN value, which is not a special character. The use of the MIN value 
        is described in the discussion of noncanonical mode input processing in "ldterm 
        Line Discipline" in General Programming Concepts: Writing and Debugging Programs.
    VTIME ：非 canonical 模式读时的延时，以十分之一秒为单位。
        Indexes the TIME value, which is not a special character. The use of the TIME value 
        is described in the discussion of noncanonical mode input processing in "ldterm Line 
        Discipline" in General Programming Concepts: Writing and Debugging Programs.  
int tcgetattr(int fd,struct termois & termios_p);
    取得终端介质（fd）初始值，并把其值 赋给temios_p;函数可以从后台进程中调用；但是，终端属性可能被后来的前 台进程所改变。  
int tcsetattr(int fd,int actions,const struct termios *termios_p);
    设置与终端相关的参数 (除非需要底层支持却无法满足)，使用termios_p 引用的 termios 结构。
    TCSANOW：改变立即发生
    TCSADRAIN：改变在所有写入 fd 的输出都被传输后生效。这个函数应当用于修改影响输出的参数时使用。(当前输出完成时将值改变)   

*/

char getChar() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

#endif

unsigned int getTiles(std::string tilesFile, Tile *tiles) {
    wifstream wif;
    wif.imbue(locale("en_US.UTF-8"));
    wif.open(tilesFile);
    if (!wif) {
        cout << "Error: Cannot open file " << tilesFile << "!" << endl;
        return 0;
    }
    wstring tileValue;
    unsigned int numTiles = 0;
    while (getline(wif, tileValue) && !tileValue.empty()) {
        if (numTiles >= MAXTILES) {
            cout << "Error: Too many tiles!" << endl << "Maximum number of tiles is " << MAXTILES << "." << endl;
            return 0;
        }
        tiles[numTiles] = {tileValue, (unsigned) pow(2, numTiles + 1), DEFAULT};
        numTiles++;
    }
    if (numTiles < MINTILES) {
        cout << "Error: Too few tiles!" << endl << "Minimum number of tiles is " << MINTILES << "." << endl;
        return 0;
    }
    return numTiles;
}
