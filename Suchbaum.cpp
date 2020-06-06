#include "Suchbaum.h"


void Suchbaum::insert(SuchbaumElement* wurzel_current, int cont)
{
	SuchbaumElement* to_insert = new SuchbaumElement;
	to_insert->content = cont;

	if (wurzel == nullptr)	//fragt das jedes mal ab...=> scheisse
	{
		wurzel = to_insert;
	}
	else
	{
		if (to_insert->content < wurzel_current->content)
		{
			if(wurzel_current->nachfolger_li != nullptr)
				insert(wurzel_current->nachfolger_li, cont);
			else
				wurzel_current->nachfolger_li = to_insert;
		}
		else if (to_insert->content > wurzel_current->content)
		{
			if (wurzel_current->nachfolger_re != nullptr)
				insert(wurzel_current->nachfolger_re, cont);
			else
				wurzel_current->nachfolger_re = to_insert;
		}
	}
}

void Suchbaum::insert(int content)
{
	insert(wurzel, content);
}



int Suchbaum::rechtestes_linkes(SuchbaumElement* wurzel_current)
{
	SuchbaumElement* nachfolger = new SuchbaumElement();
	int rl_content;
	if (wurzel_current->nachfolger_li != nullptr)
		nachfolger = wurzel_current->nachfolger_li;	//gehe erstmal zum linken TB
	
	while (nachfolger->nachfolger_re->nachfolger_re != nullptr)
		nachfolger = nachfolger->nachfolger_re;
	rl_content = nachfolger->nachfolger_re->content;
	delete nachfolger->nachfolger_re;
	nachfolger->nachfolger_re = nullptr;
	return rl_content;
}



void Suchbaum::delete_and_link(SuchbaumElement* vorgaenger, SEITE seite)	//vorgaenger des zu loeschenden wird mit nf des zL zusammengehaengt
{
	SuchbaumElement* neuer_knoten_temp = new SuchbaumElement;
	//SuchbaumElement* knoten_rechtester_linker = new SuchbaumElement;

	if (seite == LINKS)
	{

		//knoten_rechtester_linker = rechtestes_linkes(vorgaenger->nachfolger_li);
		neuer_knoten_temp->nachfolger_li = vorgaenger->nachfolger_li->nachfolger_li;
		neuer_knoten_temp->nachfolger_re = vorgaenger->nachfolger_li->nachfolger_re;
		neuer_knoten_temp->content = rechtestes_linkes(vorgaenger->nachfolger_li);

		delete (vorgaenger->nachfolger_li);


		vorgaenger->nachfolger_li = neuer_knoten_temp;

	}
	else if (seite == RECHTS)
	{

		//knoten_rechtester_linker = rechtestes_linkes(vorgaenger->nachfolger_re);
		neuer_knoten_temp->nachfolger_li = vorgaenger->nachfolger_re->nachfolger_li;
		neuer_knoten_temp->nachfolger_re = vorgaenger->nachfolger_re->nachfolger_re;
		neuer_knoten_temp->content = rechtestes_linkes(vorgaenger->nachfolger_re);

		delete (vorgaenger->nachfolger_re);

		vorgaenger->nachfolger_re = neuer_knoten_temp;
	}
}

void Suchbaum::delete_rekursiv(SuchbaumElement* wurzel_current, SuchbaumElement* to_del)
{
	if (to_del->content < wurzel_current->content)	//dann linken NF betrachten
	{
		if (wurzel_current->nachfolger_li->content == to_del->content) //dann direkt loeschen
		{
			delete_and_link(wurzel_current, LINKS);
		}
		else if (wurzel_current->nachfolger_li != nullptr)
		{
			delete_rekursiv(wurzel_current->nachfolger_li, to_del);
		}
		else
		{
			std::cout << "Nicht gefunden" << std::endl;
		}
	}
	else if (to_del->content > wurzel_current->content)
	{
		if (wurzel_current->nachfolger_re->content == to_del->content) //dann direkt loeschen
		{
			delete_and_link(wurzel_current, RECHTS);
		}
		else if (wurzel_current->nachfolger_re != nullptr)
		{
			delete_rekursiv(wurzel_current->nachfolger_re, to_del);
		}
		else
		{
			std::cout << "Nicht gefunden" << std::endl;
		}
	}
}


void Suchbaum::delete_rekursiv(SuchbaumElement* to_del)
{
	delete_rekursiv(wurzel, to_del);
}


void Suchbaum::delete_iterativ(SuchbaumElement* to_del)
{

}



void Suchbaum::print_inorder(SuchbaumElement* wurzel_current)
{
	if (wurzel_current->nachfolger_li != nullptr)
		print_inorder(wurzel_current->nachfolger_li);

	std::cout << " " << wurzel_current->content << " ";

	if (wurzel_current->nachfolger_re != nullptr)
		print_inorder(wurzel_current->nachfolger_re);
}

void Suchbaum::print_inorder()
{
	print_inorder(wurzel);
	std::cout << std::endl;
}