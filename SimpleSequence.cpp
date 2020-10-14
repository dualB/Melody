#include "SimpleSequence.h"

SimpleSequence::SimpleSequence()
{
    _head = new Node();
    _head->Sequence = new EmptySequence();
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
        delete deleteMe->Sequence;
        delete deleteMe; // delete the current entry
    }
}

void SimpleSequence::addSequence(Sequence *Sequence)
{
    Node *n = new Node();
    n->Sequence = Sequence;
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
    return _cursor->Sequence->hasNext() || _cursor->next != nullptr;
}
void SimpleSequence::restart()
{
    Node *n = _head;
    while (n != nullptr)
    {
        n->Sequence->restart();
        n = n->next;
    }
    _cursor = _head;
    n = nullptr;
}
void SimpleSequence::next()
{

    if (_cursor->Sequence->hasNext())
    {
        _cursor->Sequence->next();
    }
    else
    {
        if (_cursor->next != nullptr)
        {
            _cursor = _cursor->next;
            _cursor->Sequence->next();
        }
    }
}

int SimpleSequence::length()
{
    int total = 0;
    Node *c = _head;
    while (c != nullptr)
    {
        total += c->Sequence->length();
        c = c->next;
    }
    return total;
}

int SimpleSequence::getNoteIndex()
{
    return _cursor->Sequence->getNoteIndex();
}
bool SimpleSequence::isRest()
{
    return _cursor->Sequence->isRest();
}
unsigned int SimpleSequence::getDurationNumerator()
{
    return _cursor->Sequence->getDurationNumerator();
}
unsigned int SimpleSequence::getDurationDenominator()
{
    return _cursor->Sequence->getDurationDenominator();
}
int SimpleSequence::getIntensityIndex()
{
    return _cursor->Sequence->getIntensityIndex();
}