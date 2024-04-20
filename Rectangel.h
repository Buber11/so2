#ifndef RECTANGEL_H
#define RECTANGEL_H

#include <GLFW/glfw3.h>
#include <vector>
#include </home/jakub/laby/Color.h>

class Rectangel {
private:
    float height = 0.05f;
    float width = 0.05f;
    bool stop = false;
    //float x;
    //float y;
    float speed = 0.02f;
    bool lifeDecreased = false;
    int life = 3;
    Color color;

public:
    float x;
    float y;
    Rectangel(float theX, float theY, float speed,  Color color);

    static std::vector<Rectangel*> objects; 

    void draw();
    void move();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    static float random_speed(float min_speed, float max_speed);
    void braking();
};

#endif /* RECTANGEL_H */