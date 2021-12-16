#include<iostream>
#include <D:\OpenGL\include\glad\glad.h>
#include <D:\OpenGL\include\GLFW\glfw3.h>
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

class Shader
{
public:

    //��� ������������� �� ��������� ���������
    unsigned int ID;


    Shader(const char* vertexPath, const char* fragmentPath)
    {
        //��������� ����������
        string vertexCode;
        string fragmentCode;
        ifstream vShaderFile;
        ifstream fShaderFile;

        try
        {
            // ��������� �����
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            // ��������� ���������� �������� ������� � ������ 
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // ������������ ������ �� ������ � ��������� ����������
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

            // ��������� �����
            vShaderFile.close();
            fShaderFile.close();


           


        }
        catch (ifstream::failure& e)
        {
            cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // ����������� �������
        unsigned int vertex, fragment;

        // ��������� ������
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        //�������� �� ������
        int success;
        char infoLog[512];
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

        if (!success)

        {

            glGetShaderInfoLog(vertex, 512, NULL, infoLog);

            cout << "mistake vertex sh " << infoLog << endl;

        }

        

        // ����������� ������
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        //�������� �� ������
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            cout << "mistake frag sh: " << infoLog << endl;
        }


        

        // ��������� ���������
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);

        glLinkProgram(ID);

        //�������� �� ������
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {

            glGetProgramInfoLog(ID, 512, NULL, infoLog);

            cout << "mistake programm: " << infoLog << endl;

        }

       

        // ����������� �������-�������
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    // ��������� �������
    void use()
    {
        glUseProgram(ID);

    }
    

    //uniform-�������

    void setFloat3(string name, float x, float y, float z)
    {
        int position = glGetUniformLocation(ID, name.c_str());
        glUniform3f(position, x, y, z);
    }

   


};
