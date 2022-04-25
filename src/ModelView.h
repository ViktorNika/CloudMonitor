#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <emscripten.h>
#include <emscripten/html5.h>

class ModelView
{
public:
	ModelView();

	void init();
	void render();
private:
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE createContext(const char* canvasId);

	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_context = NULL;
};