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

    //наш идентификатор на шейдерную программу
    unsigned int ID;


    Shader(const char* vertexPath, const char* fragmentPath)
    {
        //Объявляем переменные
        string vertexCode;
        string fragmentCode;
        ifstream vShaderFile;
        ifstream fShaderFile;

        try
        {
            // Открываем файлы
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            // Считываем содержимое файловых буферов в потоки 
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // Конвертируем данные из потока в строковые переменные
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

            // Закрываем файлы
            vShaderFile.close();
            fShaderFile.close();


           


        }
        catch (ifstream::failure& e)
        {
            cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // Компилируем шейдеры
        unsigned int vertex, fragment;

        // Вершинный шейдер
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        //проверка на ошибки
        int success;
        char infoLog[512];
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

        if (!success)

        {

            glGetShaderInfoLog(vertex, 512, NULL, infoLog);

            cout << "mistake vertex sh " << infoLog << endl;

        }

        

        // Фрагментный шейдер
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        //проверка на ошибки
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            cout << "mistake frag sh: " << infoLog << endl;
        }


        

        // Шейдерная программа
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);

        glLinkProgram(ID);

        //проверка на ошибки
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {

            glGetProgramInfoLog(ID, 512, NULL, infoLog);

            cout << "mistake programm: " << infoLog << endl;

        }

       

        // освобождаем объекты-шейдеры
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    // Активация шейдера
    void use()
    {
        glUseProgram(ID);

    }
    

    //uniform-функции

    void setFloat3(string name, float x, float y, float z)
    {
        int position = glGetUniformLocation(ID, name.c_str());
        glUniform3f(position, x, y, z);
    }

   


};
