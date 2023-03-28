#include "ViewPortGL.h"
#include "ShaderLib.h"



void windowCallbackFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true); // We will detect this in the rendering loop
}



ViewPortGL::ViewPortGL(string title, int width, int height) {
    this->width = width;
    this->height = height;
    aspectRatio = (float)width / height;
    initStaticBuffers();
    win = new WindowInterface(title, width, height);
    win->createWindow();

    glfwSetKeyCallback(win->getWinReference(), windowCallbackFunc);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    std::pair<GLuint, GLuint> pi = setupGLPointColorBuf();
    std::pair<GLuint, GLuint> li = setupGLPointColorBuf();
    std::pair<GLuint, GLuint> ti = setupGLPointColorBuf();

    pixelDataVAO = pi.first;
    pixelDataVBO = pi.second;
    lineDataVAO = li.first;
    lineDataVBO = li.second;
    triangleDataVAO = ti.first;
    triangleDataVBO = ti.second;

    plain2DPixelShader = nullptr;
    initPlain2DShaders();
    disableDepthTest();
}


void ViewPortGL::initStaticBuffers() {
    pixelData = new float[PIXDATA_ARRAY_SIZE];
    for (int i = 0; i < PIXDATA_ARRAY_SIZE; i++) {
        pixelData[i] = 0;
    }
    pixelDataPointer = 0;
    lineData = new float[LINEDATA_ARRAY_SIZE];
    for (int i = 0; i < LINEDATA_ARRAY_SIZE; i++) {
        lineData[i] = 0;
    }
    lineDataPointer = 0;
    triangleData = new float[TRIANGLEDATA_ARRAY_SIZE];
    for (int i = 0; i < TRIANGLEDATA_ARRAY_SIZE; i++) {
        triangleData[i] = 0;
    }
    triangleDataPointer = 0;
}



ViewPortGL::~ViewPortGL() {
    delete pixelData;
    delete lineData;
    delete triangleData;
    delete win;
    if (plain2DPixelShader != nullptr) delete plain2DPixelShader;
}

GLFWwindow* ViewPortGL::getWindId() {
    return win->getWinReference();
}



void ViewPortGL::enableDepthTest() {
    glEnable(GL_DEPTH_TEST);
}



void ViewPortGL::disableDepthTest() {
    glDisable(GL_DEPTH_TEST);
}



void ViewPortGL::initPlain2DShaders() {
    plain2DPixelShader = new ShaderInterface("plain2D", false, false, false, true);
    plain2DPixelShader->setVertexShader(ShaderLib::vertexShaderForPlain2DPixels);
    plain2DPixelShader->setFragmentShader(ShaderLib::fragmentShaderForPlain2DPixels);
    plain2DPixelShader->useMe();
}



bool ViewPortGL::windowShouldClose() {
    return win->windowShouldClose();
}

void ViewPortGL::swapBuffers() {
    win->swapBuffers();
}



int ViewPortGL::getXSize() {
    return width;
}



int ViewPortGL::getYSize() {
    return height;
}



void ViewPortGL::clearViewPort() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void ViewPortGL::sendPixels() {
    glBindVertexArray(pixelDataVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pixelDataVBO);

    glBufferData(GL_ARRAY_BUFFER, pixelDataPointer * 4, pixelData, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_POINTS, 0, pixelDataPointer / 5);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
    pixelDataPointer = 0;
}

void ViewPortGL::sendLines() {
    glBindVertexArray(lineDataVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lineDataVBO);

    glBufferData(GL_ARRAY_BUFFER, lineDataPointer * 4, lineData, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_LINES, 0, lineDataPointer / 5);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
    lineDataPointer = 0;
}

void ViewPortGL::sendTriangles() {
    glBindVertexArray(triangleDataVAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleDataVBO);

    glBufferData(GL_ARRAY_BUFFER, triangleDataPointer * 4, triangleData, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, triangleDataPointer / 5);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
    triangleDataPointer = 0;
}

void ViewPortGL::execDrawing2DPrimitives() {
    plain2DPixelShader->useMe();
    sendPixels();
    sendLines();
    sendTriangles();
}

void ViewPortGL::preparePix(int x, int y, int red, int green, int blue) {
    pixelData[pixelDataPointer++] = (2 * (float)(x + 1) / width - 1);
    pixelData[pixelDataPointer++] = -2 * (float)y / height + 1;
    pixelData[pixelDataPointer++] = red / 255.0f;
    pixelData[pixelDataPointer++] = green / 255.0f;
    pixelData[pixelDataPointer++] = blue / 255.0f;
}

void ViewPortGL::prepareLine(int x1, int y1, int x2, int y2, int red1, int green1, int blue1, int red2, int green2, int blue2) {
    lineData[lineDataPointer++] = (2 * (float)(x1 + 1) / width - 1);
    lineData[lineDataPointer++] = -2 * (float)y1 / height + 1;
    lineData[lineDataPointer++] = red1 / 255.0f;
    lineData[lineDataPointer++] = green1 / 255.0f;
    lineData[lineDataPointer++] = blue1 / 255.0f;
    lineData[lineDataPointer++] = (2 * (float)(x2 + 1) / width - 1);
    lineData[lineDataPointer++] = -2 * (float)y2 / height + 1;
    lineData[lineDataPointer++] = red2 / 255.0f;
    lineData[lineDataPointer++] = green2 / 255.0f;
    lineData[lineDataPointer++] = blue2 / 255.0f;
}

void ViewPortGL::prepareLine(int x1, int y1, int x2, int y2, int red, int green, int blue) {
    lineData[lineDataPointer++] = (2 * (float)(x1 + 1) / width - 1);
    lineData[lineDataPointer++] = -2 * (float)y1 / height + 1;
    lineData[lineDataPointer++] = red / 255.0f;
    lineData[lineDataPointer++] = green / 255.0f;
    lineData[lineDataPointer++] = blue / 255.0f;
    lineData[lineDataPointer++] = (2 * (float)(x2 + 1) / width - 1);
    lineData[lineDataPointer++] = -2 * (float)y2 / height + 1;
    lineData[lineDataPointer++] = red / 255.0f;
    lineData[lineDataPointer++] = green / 255.0f;
    lineData[lineDataPointer++] = blue / 255.0f;
}

void ViewPortGL::prepareTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int red1, int green1, int blue1, int red2, int green2, int blue2, int red3, int green3, int blue3) {
    triangleData[triangleDataPointer++] = (2 * (float)(x1 + 1) / width - 1);
    triangleData[triangleDataPointer++] = -2 * (float)y1 / height + 1;
    triangleData[triangleDataPointer++] = red1 / 255.0f;
    triangleData[triangleDataPointer++] = green1 / 255.0f;
    triangleData[triangleDataPointer++] = blue1 / 255.0f;

    triangleData[triangleDataPointer++] = (2 * (float)(x2 + 1) / width - 1);
    triangleData[triangleDataPointer++] = -2 * (float)y2 / height + 1;
    triangleData[triangleDataPointer++] = red2 / 255.0f;
    triangleData[triangleDataPointer++] = green2 / 255.0f;
    triangleData[triangleDataPointer++] = blue2 / 255.0f;

    triangleData[triangleDataPointer++] = (2 * (float)(x3 + 1) / width - 1);
    triangleData[triangleDataPointer++] = -2 * (float)y3 / height + 1;
    triangleData[triangleDataPointer++] = red3 / 255.0f;
    triangleData[triangleDataPointer++] = green3 / 255.0f;
    triangleData[triangleDataPointer++] = blue3 / 255.0f;
}

void ViewPortGL::prepareTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int red, int green, int blue) {
    prepareTriangle(x1, y1, x2, y2, x3, y3, red, green, blue, red, green, blue, red, green, blue);
}

void ViewPortGL::prepareBlock(int x, int y, int width, int height, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3, int r4, int g4, int b4) {
    prepareTriangle(x, y, x + width - 1, y + height - 1, x, y + height - 1, r1, g1, b1, r4, g4, b4, r3, g3, b3);
    prepareTriangle(x + width - 1, y, x + width - 1, y + height - 1, x, y, r2, g2, b2, r4, g4, b4, r1, g1, b1);
}

void ViewPortGL::prepareBlock(int x, int y, int width, int height, int r, int g, int b) {
    prepareBlock(x, y, width, height, r, g, b, r, g, b, r, g, b, r, g, b);
}



std::pair<GLuint, GLuint> ViewPortGL::setupGLPointColorBuf() {
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * 4, (GLvoid*)0); // use factor 4, since the stride has to be specified in bytes
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * 4, (GLvoid*)(2 * 4)); // use factor 4, since the stride has to be specified in bytes
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    return std::pair<GLuint, GLuint>(vertexArrayObject, vertexBufferObject);
}







