#include "Button.h"

Button::Button()
{
    isFired = true;
    image = NULL;
}

Button::~Button()
{

}

void Button::setImage(Image* i)
{
    image = i;
    setWidth(i->getWidth());
    setHeight(i->getHeight());
}

void Button::update(Input* i)
{
    isFired = false;
    mouseOver = false;

    if(contains(i->getMouseX(), i->getMouseY()))
    {
        mouseOver = true;

        if(i->mouseDown(Input::MOUSE_LEFT))
        {
            isFired = true;
        }
    }
}

void Button::draw(Graphics* g)
{
    image->draw(getX(), getY(), g);

    if(mouseOver)
    {
        int red = rand()%255;

        g->drawRect(getX(), getY(), getWidth(), getHeight(), red, 0, 0);
        g->drawRect(getX()+1, getY()+1, getWidth()-2, getHeight()-2, red, 0, 0);
    }
}

bool Button::fired()
{
    return isFired;
}
