#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <QtGui/QVector3D>

struct Renderable
{
    Renderable(float x, float y, float w, float h, const QVector3D color,
        int startIndex, int amountOfVertices, float angle = 0.f)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->color = color;
        this->startIndex = startIndex;
        this->amountOfVertices = amountOfVertices;
        this->angle = angle;
    }

    float x;
    float y;
    float w;
    float h;
    QVector3D color;
    int startIndex;
    int amountOfVertices;
    float angle;
};

#endif // RENDERABLE_H
