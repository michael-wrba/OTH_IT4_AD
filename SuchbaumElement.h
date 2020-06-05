#pragma once
typedef int object;

class SuchbaumElement
{
public:
	object content;
	SuchbaumElement* nachfolger_li;
	SuchbaumElement* nachfolger_re;

	SuchbaumElement()
	{
		content = 0;
		nachfolger_li = nullptr;
		nachfolger_re = nullptr;
	}


	bool is_leaf();
};

