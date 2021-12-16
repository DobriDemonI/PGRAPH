#include <iostream>
#include <D:\OpenGL\include\glad\glad.h>
#include <D:\OpenGL\include\GLFW\glfw3.h>
#include <math.h>
#include <D:\OpenGL\include\glm\glm.hpp>
#include <D:\OpenGL\include\glm\gtc\matrix_transform.hpp>
#include <D:\OpenGL\include\glm\gtc\type_ptr.hpp>
#include "Shader.h"


using namespace std;

int SCR_WIDTH = 600;
int SCR_HEIGHT = 600;
double PI = 3.14157;
unsigned int taskNum = 1;
double t = 0.0;

struct color {
    double r;
    double g;
    double b;
};

struct point {
    double x;
    double y;
};

//массивы для рисования цветка
GLfloat elipse_land[400] = {};
GLfloat elipse_leaf_1[400] = {};
GLfloat elipse_leaf_2[400] = {};
GLfloat BezierCurve[200] = {};
GLfloat center_flower[12] = {};
GLfloat center_petals[36] = {};

//массивы для рисования сетки и графиков
GLfloat razm[160] = {};
GLfloat Chart_1[200] = {};
GLfloat Chart_2[200] = {};
GLfloat Chart_3[200] = {};

//цвета для цветка и графиков
GLfloat Color_land[600] = { };
GLfloat Color_leaf[600] = { };
GLfloat Color_bezc[300] = { };
GLfloat Color_centre_flower[36] = { };
GLfloat Color_petals[108] = { };
GLfloat Color_Chart_1[300] = { };
GLfloat Color_Chart_2[300] = { };
GLfloat Color_Chart_3[300] = { };
GLfloat Color_razm[320] = {};


GLfloat color_Os[] = {
0.0, 0.0, 0.0,  0.0, 0.0, 0.0,
0.0, 0.0, 0.0,  0.0, 0.0, 0.0
};


GLfloat Os[] = {
-1.0f, 0.0f,
1.0f, 0.0f,

0.0f, -1.0f,
0.0f, 1.0f
};



//ПЕРВОЕ ЗАДАНИЯ



void draw_land()
{

    glDrawArrays(GL_POLYGON, 0, 200);



}
void draw_BezierCurve()
{
    glLineWidth(5);
    glDrawArrays(GL_LINE_STRIP, 0, 100);


}
void draw_leaf_1()
{
    glDrawArrays(GL_POLYGON, 0, 200);


}

void draw_leaf_2()
{
    glDrawArrays(GL_POLYGON, 0, 200);


}



void draw_center_flower()
{
    
    glDrawArrays(GL_POLYGON, 0, 6);
}

GLfloat petals[36] = {};
int q = 0;
point rotatePoint(point p, point center, double angle) 
{
    petals[q] = cos(angle) * (p.x - center.x) - sin(angle) * (p.y - center.y) + center.x;
    petals[q + 1] = sin(angle) * (p.x - center.x) + cos(angle) * (p.y - center.y) + center.y;
    q += 2;
    return { petals[q], petals[q + 1] };

}
void draw_petals()
{
    glDrawArrays(GL_TRIANGLES, 0, 18);

}
//ВТОРОЕ ЗАДАНИЕ

void razmetka()
{

    glDrawArrays(GL_LINES, 0, 4);


}

void razmetka1()
{

    glLineWidth(1);
    glLineStipple(2, 0xAAAA);//шаблон для пунктирной линии
    glEnable(GL_LINE_STIPPLE);


    glDrawArrays(GL_LINES, 0, 80);
    glDisable(GL_LINE_STIPPLE);
}

void graph1()
{
    glLineWidth(2);
    glDrawArrays(GL_LINE_LOOP, 0, 100);



}
void graph2()
{
    glLineWidth(4);
    glDrawArrays(GL_LINE_LOOP, 0, 100);


}
void graph3()
{
    glLineWidth(6);
    glDrawArrays(GL_LINE_LOOP, 0, 100);


}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) return;
    if (key == GLFW_KEY_ESCAPE) {
        taskNum = 0;
    }
    if (key == GLFW_KEY_1) {
        taskNum = 1;
    }
    if (key == GLFW_KEY_2) {
        taskNum = 2;
    }
    
}

int main()
{
    GLFWwindow* window;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GONCHARENKO IZ OPENGL", NULL, NULL);//Создаем окно

    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//Делаем окно текущим
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    //проверка, что указатели функции имеет не нулевое значение (т.е. найдены в lib)

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))

    {

        cout << "Failed to initialize GLAD" << endl;

        // Если функции не найдены, дальнейшая работа с OpenGL невозможна

        return -1;

    }

    
    int i = 0;
    double a, rx, ry, angle;

    //вычисляем листья и землю
    for (double phi = 0; phi < 2 * PI; phi += PI * 0.01)
    {
        rx = 1.2;
        ry = 0.4;
        angle = 0;
        a = angle * PI / 180;
        elipse_land[i] = cos(a) * (cos(phi) * rx) - sin(a) * (sin(phi) * ry) + 0.0;
        elipse_land[i + 1] = sin(a) * (cos(phi) * rx) + cos(a) * (sin(phi) * ry) + 0.0;


        rx = 0.2;
        ry = 0.1;
        angle = -30 + sin(t) * 10;
        a = angle * PI / 180;
        elipse_leaf_1[i] = cos(a) * (cos(phi) * rx) - sin(a) * (sin(phi) * ry) + 0.0;
        elipse_leaf_1[i + 1] = sin(a) * (cos(phi) * rx) + cos(a) * (sin(phi) * ry) + 0.0;


        angle = 70 + sin(t) * 10;
        a = angle * PI / 180;
        elipse_leaf_2[i] = cos(a) * (cos(phi) * rx) - sin(a) * (sin(phi) * ry) + 0.0;
        elipse_leaf_2[i + 1] = sin(a) * (cos(phi) * rx) + cos(a) * (sin(phi) * ry) + 0.0;
        i += 2;//так как на 1 точку используется 2 координаты, ставим шаг 2 (и так везде)
    }

    
    //центр цветка
    point center = { 0.1 + sin(t) * 0.04, 0.2 };
    int j = 0;
    for (int n = 0; n < 6; n++) {
        
        center_flower[j] = cos(2 * PI * n / 6.0 + 0.15 + sin(t) * 0.2) * 0.2 + center.x;
        center_flower[j+1] = sin(2 * PI * n / 6.0 + 0.15 + sin(t) * 0.2) * 0.2 + center.y;
      j += 2;
    }

    //лепестки
    point p0 = { center.x - 0.08, center.y + 0.24 };
    point p1 = { center.x + 0.08, center.y + 0.24 };
    point p2 = { center.x, center.y + 0.5 };

    for (int i = 0; i < 6; i++) 
    {
        double angle = 2 * PI * i / 6.0 + 0.15 + sin(t) * 0.2;
        point p_0 = rotatePoint(p0, center, angle);
        point p_1 = rotatePoint(p1, center, angle);
        point p_2 = rotatePoint(p2, center, angle);
        
    }

    //стебель
    point p_0 = { 0.5, -0.85 };
    point p_1 = { 0.5, -0.3 };
    point p_2 = { 0.3 + sin(t) * 0.04, 0.0 };

    int k = 0;
    for (double t = 0; t <= 1; t += 0.01)
    {
        BezierCurve[k] = pow((1.0 - t), 2) * p_0.x + 2 * (1.0 - t) * t * p_1.x + t * t * p_2.x;
        BezierCurve[k+1] = pow((1.0 - t), 2) * p_0.y + 2 * (1.0 - t) * t * p_1.y + t * t * p_2.y;
        k += 2;
    }

    //сетка
    int cnt = 0;
    for (float r = -1.0f; r <= 1.0f; r += 0.1f)
    {
        razm[cnt] = r;
        razm[cnt + 1] = 1.0f;

        razm[cnt + 2] = r;
        razm[cnt + 3] = -1.0f;

        cnt += 4;

    }

    for (float r = -1.0f; r <= 1.0f; r += 0.1f)
    {
        razm[cnt] = 1.0f;
        razm[cnt + 1] = r;

        razm[cnt + 2] = -1.0f;
        razm[cnt + 3] = r;

        cnt += 4;

    }
   

    //графики
    int l = 0;
    int l1 = 0;
    int l2 = 0;
    

    for (double phi = 0; phi < 2 * PI; phi += 2*PI /100) 
    {
       float r1, r2, r3;

        r1 = (3 * (1.0 + cos(phi)))/11;
        Chart_1[l] = (r1 * cos(phi));
        Chart_1[l+1] = (r1 * sin(phi));
        l += 2;

        r2 = (4 * (1.0 + cos(phi)))/11;
        Chart_2[l1] = (r2 * cos(phi));
        Chart_2[l1 + 1] = (r2 * sin(phi));
        l1 += 2;

        r3 = (5 * (1.0 + cos(phi)))/11;
        Chart_3[l2] = (r3 * cos(phi));
        Chart_3[l2 + 1] = (r3 * sin(phi));
        l2 += 2;
    }
    
    //вычисление цветов для цветка и графиков
    for (int c = 0; c < 600; c += 3)
    {
        Color_land[c] = 0.0;
        Color_land[c + 1] = 0.8;
        Color_land[c + 2] = 0.0;
    }

   
    for (int c = 0; c < 600; c += 3)
    {
        Color_leaf[c] = 0.0;
        Color_leaf[c + 1] = 0.58;
        Color_leaf[c + 2] = 0.2;

    }

   
    for (int c = 0; c < 300; c += 3)
    {
        Color_bezc[c] = 0.0;
        Color_bezc[c + 1] = 0.58;
        Color_bezc[c + 2] = 0.2;

    }

   
    for (int c = 0; c < 36; c += 3)
    {
        Color_centre_flower[c] = 0.0;
        Color_centre_flower[c + 1] = 0.0;
        Color_centre_flower[c + 2] = 1.0;

    }

    
    for (int c = 0; c < 108; c += 3)
    {
        Color_petals[c] = 0.94;
        Color_petals[c + 1] = 0.58;
        Color_petals[c + 2] = 0.19;

    }

   
    for (int c = 0; c < 300; c += 3)
    {
        Color_Chart_1[c] = 1.0;
        Color_Chart_1[c + 1] = 0.0;
        Color_Chart_1[c + 2] = 0.0;

    }

    
    for (int c = 0; c < 300; c += 3)
    {
        Color_Chart_2[c] = 0.0;
        Color_Chart_2[c + 1] = 1.0;
        Color_Chart_2[c + 2] = 0.0;

    }

    
    for (int c = 0; c < 300; c += 3)
    {
        Color_Chart_3[c] = 0.0;
        Color_Chart_3[c + 1] = 0.0;
        Color_Chart_3[c + 2] = 1.0;

    }

    
    for (int c = 0; c < 300; c += 3)
    {
        Color_razm[c] = 0.0;
        Color_razm[c + 1] = 0.0;
        Color_razm[c + 2] = 0.0;

    }

    //объявляем объекты вершинных буферов и массивов и привязываем к ним массивы
    unsigned int VBOs[21], VAOs[11];
    glGenVertexArrays(11, VAOs);
    glGenBuffers(21, VBOs);


    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(elipse_land), elipse_land, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color_land), Color_land, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(elipse_leaf_1), elipse_leaf_1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color_leaf), Color_leaf, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(elipse_leaf_2), elipse_leaf_2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color_leaf), Color_leaf, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[3]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(BezierCurve), BezierCurve, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color_bezc), Color_bezc, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[4]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[7]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(center_flower), center_flower, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[8]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color_centre_flower), Color_centre_flower, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[5]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[9]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(petals), petals, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color_petals), Color_petals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[6]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[11]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Chart_1), Chart_1, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[12]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color_Chart_1), Color_Chart_1, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    glBindVertexArray(VAOs[7]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[13]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Chart_2), Chart_2, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[14]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color_Chart_2), Color_Chart_2, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    glBindVertexArray(VAOs[8]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[15]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Chart_3), Chart_3, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[16]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color_Chart_3), Color_Chart_3, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    glBindVertexArray(VAOs[9]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[17]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Os), Os, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[18]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_Os), color_Os, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    glBindVertexArray(VAOs[10]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[19]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(razm), razm, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[20]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color_razm), Color_razm, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    //обращаемся к нашим шейдерам
    Shader ourShader("VertShader_1.txt", "FragShader_1.txt");
    Shader ourShader1("VertShader_2.txt", "FragShader_2.txt");
  


    while (!glfwWindowShouldClose(window))

    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.45, 0.73, 1.0, 1.0);

        if (taskNum == 0)
        {

            glfwSetWindowShouldClose(window, true);

        }

        if (taskNum == 1)
        {


            ourShader.use();//обращаемся к 1 объекту шейдра
            glBindVertexArray(VAOs[0]);

            //объявляем glm переменные, с помощью которых будем двигать рисунок
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 model = glm::mat4(1.0f);
          
            view = glm::translate(view, glm::vec3(1.0f, -1.1f, 0.0f));//перемещение для эллипса, который выступает в качестве земли
           
            //связываем наши переменные с юниформ-переменными в наших шейдерах
            int viewLoc = glGetUniformLocation(ourShader.ID, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            int modelLoc = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            draw_land();//рисуем землю

            glBindVertexArray(VAOs[1]);
            //сбрасываем матрицы до единичных
            view = glm::mat4(1.0f);
            model = glm::mat4(1.0f);

            //перемещаем и крутим 1 лист
            view = glm::translate(view, glm::vec3(0.35f, -0.86f, 0.0f));
            model = glm::rotate(model, glm::radians(40.0f) * (sin((float)glfwGetTime()) - 0.5f) / 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
          
            int viewLoc_1 = glGetUniformLocation(ourShader.ID, "view");
            glUniformMatrix4fv(viewLoc_1, 1, GL_FALSE, glm::value_ptr(view));
            int modelLoc_1 = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc_1, 1, GL_FALSE, glm::value_ptr(model));
            draw_leaf_1();//рисуем 1 лист

            glBindVertexArray(VAOs[2]);
            view = glm::mat4(1.0f);
            model = glm::mat4(1.0f);

            //пермещаем и крутим 2 лист
            view = glm::translate(view, glm::vec3(0.62f, -0.65f, 0.0f));
            model = glm::rotate(model, glm::radians(40.0f) * (sin((float)glfwGetTime())-0.5f)/2.0f, glm::vec3(0.0f, 0.0f, 1.0f));

            int viewLoc_2 = glGetUniformLocation(ourShader.ID, "view");
            glUniformMatrix4fv(viewLoc_2, 1, GL_FALSE, glm::value_ptr(view));

            int modelLoc_2 = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc_2, 1, GL_FALSE, glm::value_ptr(model));
            draw_leaf_2();//рисуем 2 лист

            glBindVertexArray(VAOs[3]);
            view = glm::mat4(1.0f);
            model = glm::mat4(1.0f);
          
            //тут просто перемещаем стебель, чтоб она встал на свое место
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
            int viewLoc_4 = glGetUniformLocation(ourShader.ID, "view");
            glUniformMatrix4fv(viewLoc_4, 1, GL_FALSE, glm::value_ptr(view));
            int modelLoc_4 = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc_4, 1, GL_FALSE, glm::value_ptr(model));
    
            draw_BezierCurve();//рисуем стебель

          
            glBindVertexArray(VAOs[4]);
            view = glm::mat4(1.0f);
            model = glm::mat4(1.0f);

            //перемещаем и крутим центр и лепестки цветка
            model = glm::rotate(model, glm::radians(40.0f) * (sin((float)glfwGetTime()) - 0.5f) / 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
            int viewLoc_5 = glGetUniformLocation(ourShader.ID, "view");
            glUniformMatrix4fv(viewLoc_5, 1, GL_FALSE, glm::value_ptr(view));
            int modelLoc_5 = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc_5, 1, GL_FALSE, glm::value_ptr(model));
            draw_center_flower();//рисуем центр

            glBindVertexArray(VAOs[5]);
            glUniformMatrix4fv(modelLoc_5, 1, GL_FALSE, glm::value_ptr(model));
            draw_petals();//рисуем лепестки
        }


        glEnd();
        if (taskNum == 2)
        {
            glClearColor(1.0, 1.0, 1.0, 1.0);
            ourShader1.use();//обращаемся ко второму объекту шейдера
           
            //рисуем разметку, оси и графики
            glBindVertexArray(VAOs[9]);
            razmetka();

            glBindVertexArray(VAOs[10]);
            razmetka1();

            glBindVertexArray(VAOs[6]);
           
            graph1();

            glBindVertexArray(VAOs[7]);
          
            graph2();

            glBindVertexArray(VAOs[8]);
          
            graph3();

        }

        glFlush();

        glfwSwapBuffers(window);

        glfwPollEvents();

    }
    glDeleteVertexArrays(11, VAOs);
    glDeleteBuffers(21, VBOs);
    glfwTerminate();
    return 0;
}
