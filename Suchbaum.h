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
	int rechtestes_linkes(SuchbaumElement* wurzel_current);
	void delete_and_link(SuchbaumElement* wurzel_current, SEITE seite);
	
	void delete_rekursiv(SuchbaumElement* wurzel_current, SuchbaumElement* to_del);
	void delete_rekursiv(SuchbaumElement* to_del);
	void delete_iterativ(SuchbaumElement*);

	void print_inorder(SuchbaumElement* wurzel_current);

	void print_inorder();


};


