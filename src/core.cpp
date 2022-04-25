#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <iostream>

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    const char *getHelloMessage()
    {
        const char *str = "Hello, world!";
        return str;
    }
}

int main() {
    std::cout << "hello, world!\n";
    return 0;
}
