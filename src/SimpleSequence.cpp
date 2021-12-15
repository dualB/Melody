#include "SimpleSequence.h"

SimpleSequence::SimpleSequence()
{
    _head = new Node();
    _head->sequence = new EmptySequence();
    _head->next = nullptr;
    _cursor = _head;
}

SimpleSequence::~SimpleSequence()
{
    Node *next = _head;

    while (next)
    { // iterate over all elements
        Node *deleteMe = next;
        next = next->next; // save pointer to the next element
        delete deleteMe->sequence;
        delete deleteMe; // delete the current entry
    }
}

void SimpleSequence::addSequence(Sequence *Sequence)
{
    Node *n = new Node();
    n->sequence = Sequence;
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
bool SimpleSequence::hasNext()
{
    return _cursor->sequence->hasNext() || _cursor->next != nullptr;
}
void SimpleSequence::restart()
{
    Node *n = _head;
    while (n != nullptr)
    {
        n->sequence->restart();
        n = n->next;
    }
    _cursor = _head;
    n = nullptr;
}
void SimpleSequence::next()
{

    if (_cursor->sequence->hasNext())
    {
        _cursor->sequence->next();
    }
    else
    {
        if (_cursor->next != nullptr)
        {
            _cursor = _cursor->next;
            _cursor->sequence->next();
        }
    }
}

int SimpleSequence::length()
{
    int total = 0;
    Node *c = _head;
    while (c != nullptr)
    {
        total += c->sequence->length();
        c = c->next;
    }
    return total;
}

int SimpleSequence::getNoteIndex()
{
    return _cursor->sequence->getNoteIndex();
}
bool SimpleSequence::isRest()
{
    return _cursor->sequence->isRest();
}
int SimpleSequence::isTieOrBreath()
{
    return _cursor->sequence->isTieOrBreath();
}
unsigned int SimpleSequence::getDurationNumerator()
{
    return _cursor->sequence->getDurationNumerator();
}
unsigned int SimpleSequence::getDurationDenominator()
{
    return _cursor->sequence->getDurationDenominator();
}
int SimpleSequence::getIntensityIndex()
{
    return _cursor->sequence->getIntensityIndex();
}