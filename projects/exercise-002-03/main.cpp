#include <gl_intellisense.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Shaders
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource[2] = {
    // Orange
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0",

    // Yellow
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0"};

// --- Function prototypes ---
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// --- Main function ---
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, "opengl_demo");

    // Create window
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Vertices
    float triangle1[] = {
        -0.5f, 1.0f, 0.0f, // P1
        0.5f,  1.0f, 0.0f, // P2
        0.0f,  0.0f, 0.0f, // P3

    };
    float triangle2[] = {
        -0.5f, -1.0f, 0.0f, // P1
        0.5f,  -1.0f, 0.0f, // P2
        0.0f,  0.0f,  0.0f, // P3

    };
    unsigned int triangles[2];
    glGenBuffers(2, triangles);

    // Shaders
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShaders[2];
    for (int i = 0; i < 2; i++)
    {
        fragmentShaders[i] = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaders[i], 1, &fragmentShaderSource[i], NULL);
        glCompileShader(fragmentShaders[i]);
        glGetShaderiv(fragmentShaders[i], GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShaders[i], 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    unsigned int shaderProgram[2];
    for (int i = 0; i < 2; i++)
    {
        shaderProgram[i] = glCreateProgram();
        glAttachShader(shaderProgram[i], vertexShader);
        glAttachShader(shaderProgram[i], fragmentShaders[i]);
        glLinkProgram(shaderProgram[i]);
        glGetProgramiv(shaderProgram[i], GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(shaderProgram[i], 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(fragmentShaders[i]);
    }
    glDeleteShader(vertexShader);

    // Create vertex array object
    unsigned int VAO[2];
    glGenVertexArrays(2, VAO);
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, triangles[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, triangles[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram[0]);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderProgram[1]);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// --- Callback function definitions ---
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// --- Function definitions ---
void processInput(GLFWwindow *window)
{
    static bool wasPressedW = false;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !wasPressedW)
    {
        wasPressedW = true;
        // Toggle wireframe mode
        static bool wireframe = false;
        wireframe = !wireframe;
        if (wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
    {
        wasPressedW = false;
    }
}