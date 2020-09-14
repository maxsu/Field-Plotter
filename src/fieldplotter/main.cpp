#include <fieldplotter/fieldplotter.h>

#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
GLFWwindow* window;
Renderer* renderer;
VectorField* debug_vectorfield;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //if (key == GLFW_KEY_E && action == GLFW_PRESS)
    if(action == GLFW_PRESS) {
        switch(key) {
            case(GLFW_KEY_W):
            renderer->getCamera()->moveLinear(0.1f,0.0f,0.0f);
            break;
            case(GLFW_KEY_S):
            renderer->getCamera()->moveLinear(-0.1f,-0.0f,0.0f);
            break;
            case(GLFW_KEY_A):
            renderer->getCamera()->moveLinear(0.0f,0.0f,-0.1f);
            break;
            case(GLFW_KEY_D):
            renderer->getCamera()->moveLinear(0.0f,0.0f,0.1f);
            break;
            case(GLFW_KEY_R):
            renderer->getCamera()->moveLinear(0.0f,-0.1f,0.0f);
            break;
            case(GLFW_KEY_F):
            renderer->getCamera()->moveLinear(0.0f,0.1f,0.0f);
            break;
            default:
            break;
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos,ypos;
        glfwGetCursorPos(window,&xpos,&ypos);
        renderer->getCamera()->grabCamera((int)xpos,(int)ypos);
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        renderer->getCamera()->releaseCamera();
    }
}

void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)  
{
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
     return;
  }
  renderer->getCamera()->moveCamera((int)xpos,(int)ypos);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



#define FP_MAINMETHOD
#ifndef FP_MAINMETHOD

#else
int main() {
    cout << "Starting...\n";
    
    cout << "VectorField made\n";
    if (!glfwInit()) {
        cout << "GLFW FAILED TO INITIALIZE\n";
        exit(-1);
    }
    cout << "GLFW Initialized\n";
    glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"Test",NULL,NULL);
    cout << "window made\n";
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glewExperimental=GL_TRUE;
    GLenum glewinitialized = glewInit();
    if (glewinitialized != GLEW_OK) {
        cout << "GLEW FAILED TO INITIALIZE!\n";
    }
    cout << "GLEW initialized.. Instantiating renderer\n";
    debug_vectorfield = new VectorField(0.2f,4);//separation,dimension
    cout << "Making renderer\n";
    renderer = new Renderer(debug_vectorfield);
    cout << "Beginning render loop\n";
    while(!glfwWindowShouldClose(window)){
        renderer->render();
        glfwSwapBuffers(window);
        glfwPollEvents();   //faster than glfwPollEvents
    }
    
    return 0;
}
#endif