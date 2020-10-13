#include "SimpleMelody.h"



SimpleMelody::SimpleMelody()
{
    _head = new Node();
    _head->melody = new EmptyMelody();
    _head->next = nullptr;
    _cursor = _head;
}

SimpleMelody::~SimpleMelody()
{
    Node *next = _head;

    while (next)
    { // iterate over all elements
        Node *deleteMe = next;
        next = next->next; // save pointer to the next element
        delete deleteMe->melody;
        delete deleteMe;   // delete the current entry
    }
}

void SimpleMelody::addMelody(Melody *melody)
{
    Node *n = new Node();
    n->melody = melody;
    n->next = nullptr;

    Node *_cur = _head;
    while (_cur->next != nullptr)
    {
        _cur = _cur->next;
    }
    _cur->next = n;
    _cur = nullptr;

    n = nullptr;
}
bool SimpleMelody::hasNext()
{
    return _cursor->melody->hasNext() || _cursor->next != nullptr;
}
void SimpleMelody::restart()
{
    Node *n = _head;
    while (n != nullptr)
    {
        n->melody->restart();
        n = n->next;
    }
    _cursor = _head;
    n = nullptr;
}
void SimpleMelody::next()
{

    if (_cursor->melody->hasNext())
    {
        _cursor->melody->next();
    }
    else
    {
        if (_cursor->next!=nullptr)
        {
            _cursor = _cursor->next;
            _cursor->melody->next();
        }
    }
}

int SimpleMelody::length()
{
    int total = 0;
    Node *c = _head;
    while (c != nullptr)
    {
        total += c->melody->length();
        c = c->next;
    }
    return total;
}

int SimpleMelody::getNoteIndex()
{
    return _cursor->melody->getNoteIndex();
}
bool SimpleMelody::isRest()
{
    return _cursor->melody->isRest();
}
unsigned int SimpleMelody::getDurationNumerator()
{
    return _cursor->melody->getDurationNumerator();
}
unsigned int SimpleMelody::getDurationDenominator()
{
    return _cursor->melody->getDurationDenominator();
}
int SimpleMelody::getIntensityIndex()
{
    return _cursor->melody->getIntensityIndex();
}