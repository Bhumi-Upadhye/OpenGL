#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include<fstream>

#include <string.h>
#include<sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include "Shader.h"
#include "Texture.h"
/*#define  ASSERT(x) if  (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))


static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}


static bool GLLogCall(const char * function ,const char * file ,int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << "" << file << ":" << line << std::endl;
        return false;
    }

    return true;
} */



// shader


/*struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};


static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE=-1,VERTEX=0,FRAGMENT=1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
   // while (getline(stream, line))
    while (getline (stream,line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;

            //set mode to vertex
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;

                //set mode to fragment


        }
        else
        {
            ss[(int)type] << line << '\n';

        }
    }

    return{ ss[0].str(),ss[1].str() };
}


static unsigned int CompileShader(unsigned int type,const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader !" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }


    //Error handling

    return id;

}

static unsigned int  CreateShader(const std::string& vertexShader, const  std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);


    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return(program);


}
*/
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);




    //initialize the glew

    glewInit();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    //set interval

    glfwSwapInterval(1);




    if (glewInit() != GLEW_OK)
        std::cout << "Error !" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {


        float vertices[] = {

            -0.5f, -0.5f, 0.0f, 0.0f,  //0
            0.5f ,  -0.5f, 1.0f, 0.0f,   //1
            0.5f,  0.5f, 1.0f, 1.0f,   //2
            -0.5f, 0.5f , 0.0f, 1.0f   //3


        };

        unsigned int indices[] =
        {
            0 , 1 , 2,
            2 , 3 , 0

        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));
     

        /*unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao)); */

       VertexArray va;
 VertexBuffer vb(vertices, 4 * 4 * sizeof(float));


 //va.AddBuffer(vb);

 VertexBufferLayout layout;
      layout.push<float>(2);
      layout.push<float>(2);
      va.AddBuffer(vb, layout);
 
      // create rectangle 

       /* unsigned int buffer;
        GLCall(glGenBuffers(1, &buffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
       GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), vertices, GL_STATIC_DRAW));  */

        //GLCall(glEnableVertexAttribArray(0));
       // GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

IndexBuffer ib(indices, 6);

        /* unsigned int ibo;
       glGenBuffers(1, &ibo);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
         glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW); */


Shader shader("res/shaders/Basic.shader");
shader.Bind();

        /*ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        glUseProgram(shader);  */
        


       /* GLCall(int location = glGetUniformLocation(shader, "u_Color"));
        _ASSERT(location != -1);
        GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f)); */
        

        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        Texture texture("res/textures/wall.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);
        va.Unbind();
       

        vb.UnBind();
        ib.UnBind();

        shader.Unbind();

        Renderer renderer;

       // glBindVertexArray(0);
       //GLCall( glUseProgram(0));

        //GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
       // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));


        float r = 0.0f;
        float increment = 0.05f;




        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
           // GLCall(glClear(GL_COLOR_BUFFER_BIT));

            renderer.Clear();

            //GLCall(glUseProgram(shader));

            shader.Bind();
            shader.SetUniform4f("u_Color",r,0.3f, 0.8f, 1.0f);

            renderer.draw(va, ib, shader);

            //glUniform4f(location, r, 0.3f, 0.8f, 1.0f);

            //GLCall(glBindVertexArray(vao));

            //va.Bind();

            // glBindBuffer(GL_ARRAY_BUFFER, buffer);

           // ib.Bind();

            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


            // glUniform4f(location, r, 0.3f, 0.8f, 1.0f);



            //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            //ASSERT(GLLogCall());






            if (r > 1.0f)

                increment = -0.05f;



            else   if (r < 0.0f)

                increment = 0.05f;

            r += increment;




            // GLCheckError();


           // glDrawArrays(GL_TRIANGLES, 0, 6);

            //glBegin(GL_TRIANGLES);
            //glVertex2f(-0.5f,-0.5f);
            //glVertex2f(0.0f, 0.5f);
            //glVertex2f(0.5f, -0.5f);

            //glEnd();


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            //GLCall(glDeleteProgram(shader));
        }

        //glDeleteProgram(shader);

    }
    

    
    glfwTerminate();
    return 0;
}
