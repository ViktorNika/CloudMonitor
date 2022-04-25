#include "ModelView.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <emscripten/bind.h>

using namespace std;

EMSCRIPTEN_BINDINGS(jsModelView) {
    emscripten::class_<ModelView>("ModelView")
        .constructor<>()
        .smart_ptr<std::shared_ptr<ModelView>>("ModelView")
        .function("init", &ModelView::init)
        ;
};

std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

ModelView::ModelView()
{
}

void ModelView::init()
{
    m_context = createContext("#modelViewCanvas");
}

void ModelView::render()
{
    if (!m_context)
        return;

    emscripten_webgl_make_context_current(m_context);
    glClearColor(static_cast<double>(rand()) / RAND_MAX, static_cast<double>(rand()) / RAND_MAX, static_cast<double>(rand()) / RAND_MAX, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ModelView::createContext(const char* canvasId)
{
    EmscriptenWebGLContextAttributes attributes;

    emscripten_webgl_init_context_attributes(&attributes); // Pupulate with default attributes

 //   attributes.preferLowPowerToHighPerformance = false;

#if 0
    attributes.alpha = true;
    attributes.depth = true;
    attributes.stencil = false;
    attributes.antialias = true;
    attributes.premultipliedAlpha = true;
    attributes.preserveDrawingBuffer = false;
    attributes.failIfMajorPerformanceCaveat = false;
    attributes.majorVersion = 1;
    attributes.minorVersion = 0;
    attributes.enableExtensionsByDefault = true;
#endif

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context(canvasId, &attributes);
    cout << "create context " << context << endl;
    
    if (!context)
        return NULL;

    EMSCRIPTEN_RESULT res = emscripten_webgl_make_context_current(context);
    cout << "make current context " << (res == EMSCRIPTEN_RESULT_SUCCESS) << endl;

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE current = emscripten_webgl_get_current_context();
    cout << "get current context " << current << endl;

    const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
    std::vector<std::string> exts = split(extensions, ' ');
    for (size_t i = 0; i < exts.size(); ++i)
    {
        EM_BOOL supported = emscripten_webgl_enable_extension(context, exts[i].c_str());
        //    cout << "extention " << exts[i] << " " << supported << endl;
    }

    void* data = nullptr;
    bool capture = true;
    auto callback = [](int eventType, const void* reserved, void* userData) -> EM_BOOL
    {
        switch (eventType) {
        case EMSCRIPTEN_EVENT_WEBGLCONTEXTLOST:
            cout << "context lost";
            break;
        case EMSCRIPTEN_EVENT_WEBGLCONTEXTRESTORED:
            cout << "context restored";
            break;
        default:
            cout << "unexpected this is";
            break;
        };
        return true;
    };

    emscripten_set_webglcontextlost_callback(canvasId, data, capture, callback);
    emscripten_set_webglcontextrestored_callback(canvasId, data, capture, callback);

    return context;
}
