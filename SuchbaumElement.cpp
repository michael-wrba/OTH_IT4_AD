#include "SuchbaumElement.h"


bool SuchbaumElement::is_leaf()
{
	return this->nachfolger_li == nullptr && this->nachfolger_re == nullptr;
}