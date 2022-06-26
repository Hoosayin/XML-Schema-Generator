#include "pch.h"
#include "Element.h"
#include "Attribute.h"

Element::Element()
{
	MinimumOccurance = 1;
	MaximumOccurance = 1;
	Elements = new CList<Element*>();
	Attributes = new CList<Attribute*>();
}
