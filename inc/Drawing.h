#ifndef DRAWING_H
#define DRAWING_H

#include <Color.h>
#include <GL/freeglut.h>
#include <vector>

enum ShapeKind {CIRCLE_SHAPE, RECT_SHAPE, TRI_SHAPE, PENT_SHAPE, STAR_SHAPE};

class Drawing {
protected:
    Color color;

public:
    Drawing();

    Color getColor() const;
    void setColor(Color c);

    virtual void draw() const = 0;
    virtual bool contains(float mx, float my) const = 0;
    virtual void moveBy(float dx, float dy) = 0;
    virtual void resize(float factor) = 0;
    virtual void getBounds(float& left, float& bottom, float& right, float& top) const = 0;
    virtual bool isScribble() const;

    virtual ~Drawing();
};

class Scribble : public Drawing {
    std::vector<float> xPoints;
    std::vector<float> yPoints;

public:
    Scribble();
    Scribble(Color c);

    void addPoint(float x, float y);
    int getPointCount() const;

    void draw() const;
    bool contains(float mx, float my) const;
    void moveBy(float dx, float dy);
    void resize(float factor);
    void getBounds(float& left, float& bottom, float& right, float& top) const;
    bool isScribble() const;

    ~Scribble();
};

class ShapeDrawing : public Drawing {
    ShapeKind kind;
    float cx, cy;
    float halfW, halfH;

public:
    ShapeDrawing();
    ShapeDrawing(ShapeKind k, float x1, float y1, float x2, float y2, Color c);

    void set(float x1, float y1, float x2, float y2);

    void draw() const;
    bool contains(float mx, float my) const;
    void moveBy(float dx, float dy);
    void resize(float factor);
    void getBounds(float& left, float& bottom, float& right, float& top) const;

    ~ShapeDrawing();
};

#endif
