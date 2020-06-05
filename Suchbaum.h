#pragma once
#include "SuchbaumElement.h"
#include <iostream>

#define SEITE bool
#define LINKS 0
#define RECHTS 1

class Suchbaum
{
public:
	SuchbaumElement* wurzel;

	Suchbaum()
	{
		wurzel = nullptr;
	}


//	void insert(SuchbaumElement*, SuchbaumElement*);
	void insert(SuchbaumElement* wurzel_current, int cont);
	void insert(int content);
	SuchbaumElement* rechtestes_linkes(SuchbaumElement* wurzel_current);
	void delete_and_link(SuchbaumElement* wurzel_current, SEITE seite);
	void delete_iterativ(SuchbaumElement*);

	void print_inorder(SuchbaumElement* wurzel_current);

	void print_inorder();
	void delete_rekursiv(SuchbaumElement*, SuchbaumElement*);

};


