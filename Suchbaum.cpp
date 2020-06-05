#include "Suchbaum.h"

/*
void Suchbaum::insert(SuchbaumElement* wurzel_current, SuchbaumElement* to_insert)
{
	if (to_insert->content < wurzel_current->content)
	{
		if (wurzel_current->nachfolger_li->is_leaf())
		{
			wurzel_current->nachfolger_li = to_insert;
		}
		else
		{
			insert(wurzel_current->nachfolger_li, to_insert);
		}

	}
	else if (to_insert->content > wurzel_current->content)
	{
		if (wurzel_current->nachfolger_re->is_leaf())
		{
			wurzel_current->nachfolger_re = to_insert;
		}
		else
		{
			insert(wurzel_current->nachfolger_re, to_insert);
		}
	}
}
*/

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











	/*


	else
	{
		if (wurzel_current->is_leaf())
		{
			if (to_insert->content < wurzel_current->content && wurzel_current->nachfolger_li != nullptr)
				wurzel_current->nachfolger_li = to_insert;
			else if(to_insert->content < wurzel_current->content && wurzel_current->nachfolger_li != nullptr)
				wurzel_current->nachfolger_re = to_insert;
		}
		else
		{
			if (to_insert->content < wurzel_current->content)
				insert(wurzel_current->nachfolger_li, cont);
			else if (to_insert->content > wurzel_current->content)
				insert(wurzel_current->nachfolger_re, cont);
		}
	}
	*/
}

void Suchbaum::insert(int content)
{
	insert(wurzel, content);
}



SuchbaumElement* Suchbaum::rechtestes_linkes(SuchbaumElement* wurzel_current)
{
	SuchbaumElement* nachfolger = wurzel_current->nachfolger_li;	//gehe erstmal zum linken TB
	while (nachfolger->nachfolger_re != nullptr)
		nachfolger = nachfolger->nachfolger_re;
	return nachfolger;
}


void Suchbaum::delete_and_link(SuchbaumElement* wurzel_current, SEITE seite)
{
	SuchbaumElement* nf_li_temp;
	SuchbaumElement* nf_re_temp;

	if (seite == LINKS)
	{
		if (wurzel_current->nachfolger_li->is_leaf())	//trivialloesung
		{
			delete wurzel_current->nachfolger_li;
			wurzel_current->nachfolger_li = nullptr;
		}
		else
		{
			/*Jetzt muss neuer Knoten an diese Stelle,
			dieser ist entweder das rechteste Blatt des linken NF, oder das linkeste des re NF
			gleichwertig => nehme rechtestes des linken*/

			nf_li_temp = wurzel_current->nachfolger_li->nachfolger_li;	//wc->nf_li soll ja geloescht werden
			nf_re_temp = wurzel_current->nachfolger_li->nachfolger_re;	//Nachfolger temporaer speichern, um sie nachher wieder verlinken zu koennen

			delete wurzel_current->nachfolger_li;

			wurzel_current->nachfolger_li = rechtestes_linkes(wurzel_current->nachfolger_li);
			wurzel_current->nachfolger_li->nachfolger_li = nf_li_temp;
			wurzel_current->nachfolger_li->nachfolger_re = nf_re_temp;

			delete_rekursiv(wurzel_current, rechtestes_linkes(wurzel_current->nachfolger_li));	/*da das ja jetzt weiter oben ist
																								auch egal, dass nicht mehr der knoten von vorher da,
																								weil der neue ja die selbe Struktur hat*/
		}
	}
	else if (seite == RECHTS)
	{
		if (wurzel_current->nachfolger_re->is_leaf())
		{
			delete wurzel_current->nachfolger_re;
			wurzel_current->nachfolger_re = nullptr;
		}
		else
		{

			nf_li_temp = wurzel_current->nachfolger_re->nachfolger_li;
			nf_re_temp = wurzel_current->nachfolger_re->nachfolger_re;

			delete wurzel_current->nachfolger_re;

			wurzel_current->nachfolger_re = rechtestes_linkes(wurzel_current->nachfolger_re);
			wurzel_current->nachfolger_re->nachfolger_li = nf_li_temp;
			wurzel_current->nachfolger_re->nachfolger_re = nf_re_temp;

			delete_rekursiv(wurzel_current, rechtestes_linkes(wurzel_current->nachfolger_re));
		}
	}
}




void Suchbaum::delete_rekursiv(SuchbaumElement* wurzel_current, SuchbaumElement* to_del)
{
	if (wurzel_current->is_leaf())
	{
		std::cout << "ERROR: nicht gefunden" << std::endl;
	}

	else if (wurzel_current->nachfolger_li == to_del)
	{
		delete_and_link(wurzel_current, LINKS);
	}
	else if (wurzel_current->nachfolger_re == to_del)
	{
		delete_and_link(wurzel_current, RECHTS);
	}

	else if (to_del->content < wurzel_current->content)
	{
		delete_rekursiv(wurzel_current->nachfolger_li, to_del);
	}
	else if (to_del->content > wurzel_current->content)
	{
		delete_rekursiv(wurzel_current->nachfolger_re, to_del);
	}
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
}