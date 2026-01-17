#pragma once

#ifdef __INTELLISENSE__
// Force standard OpenGL prototypes
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

// Fake the GLAD loader function so it doesn't red-squiggle
inline int gladLoadGL(void) { return 1; }
inline int gladLoadGLLoader(void*) { return 1; }
typedef void* (*GLADloadproc)(const char* name);

#else
#include <glad/glad.h>
#endif