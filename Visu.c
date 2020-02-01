/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Visu.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clboutry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 01:03:31 by clboutry          #+#    #+#             */
/*   Updated: 2020/02/01 14:04:27 by clboutry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>

int		main(void) 
{
    WINDOW *big_square, *map_corew,*info_box;
    int c;
    int a;
	int	key;
	int cycles;

    c = 1;
    a = 3;
	cycles = 1;
    
    initscr();
	cbreak();
	noecho(); // enleve l'affichage de lettre durant l'affichage du terminnal du corewar
	keypad(stdscr, TRUE);  // permet l'uilisation des key du clavier por interagir

    info_box= subwin(stdscr, LINES - 10, ((COLS - 10) / 2) - 18, 5, 200); // info_box :/
    big_square= subwin(stdscr, LINES, COLS , 0, 0);        // Créé une fenêtre de 'LINES / 2' lignes et de COLS colonnes en 0, 0
    map_corew= subwin(stdscr, LINES - 10 , ((COLS - 10) / 2) + 18, 5, 5); // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent
   
    box(big_square, ACS_VLINE, ACS_HLINE);
    box(map_corew, ACS_VLINE, ACS_HLINE);
    box(info_box, ACS_VLINE, ACS_HLINE);
    
	wborder(map_corew, '|','[','_','_',' ','_',' ','_');
	wborder(info_box, ']','|','_','_','_',' ','_',' ');
	//wborder(big_square, '')
    mvwprintw(big_square, 1, 1, "Ceci est la fenetre du haut, il y a %d collones, et %d lines", COLS, LINES);
    mvwprintw(big_square, 4, COLS / 2, "Score & info");
    wattron(map_corew, A_BOLD);
    mvwprintw(map_corew, 1, COLS / 5, "affichage du terrain du corewar");
    wattroff(map_corew, A_BOLD);


    wrefresh(big_square);
    wrefresh(map_corew);
	wrefresh(info_box);
	while (a < 67)
	{
		while (c < 192)
    	{
    		mvwprintw(map_corew, a, c  + 1 , "00");
			c += 3;
    	}
		c = 1;
		a++;
	}
	
	mvwprintw(info_box, 1, 1,"truc n*1, cette boxe contient %d, collones et %d lines", COLS, LINES);
	
	wattron(info_box, A_BOLD);
	mvwprintw(info_box, 2, 56,"AFFICHAGE POSSIBLE DES RESULTATS / INFOS");
	wattroff(info_box, A_BOLD);
	mvwprintw(info_box, 5, 20, "VITESSE ACTUEL = ");
	mvwprintw(info_box, 5, 39, "%d cycle/s", cycles);
	mvwprintw(info_box, 7, 20, "NOMBRE DE PROCESSUS DANS LE CYCLE ACTUEL = ");
	mvwprintw(info_box, 9, 20, "NOM CHAMPION 1");
	mvwprintw(info_box, 11, 20, "NOM CHAMPION 2");
	mvwprintw(info_box, 13, 20, "NOM CHAMPION 3");
	mvwprintw(info_box, 15, 20, "NOM CHAMPION 4");
	wattron(info_box, A_BOLD);
	mvwprintw(info_box, 18, 20, "CHAMPION ACTUELLEMENT EN TETE = ");
	wattroff(info_box, A_BOLD);
	mvwprintw(info_box, 19, 20, "STATS: ");
	mvwprintw(info_box, 20, 40, "NBR LIVES  ");
	mvwprintw(info_box, 21, 40, "NBR PROCESSUS CREER =  ");
	mvwprintw(info_box, 22, 40, "NBR CASE EN POSSESSION =  ");
	mvwprintw(info_box, 23, 40, "PRIME ACTUELLE = 500 000$");
	wattron(info_box, A_BOLD);
	mvwprintw(info_box, 25, 20, " INSTRUCTION : ");
	wattroff(info_box, A_BOLD);
	mvwprintw(info_box, 27, 40, "+ AUGMENTE LE NOMBRE DE CYCLE PAR SECONDES DE 50");
	mvwprintw(info_box, 29, 40, "- DIMINUE LE NOMBRE DE CYCLE PAR SECONDES DE 50");
	mvwprintw(info_box, 31, 40, "LA TOUCHE DIRECTIONNEL HAUT AUGMENTE LE NOMBRE DE CYCLE PAR SECONDES DE 1");
	mvwprintw(info_box, 33, 40, "LA TOUCHE DIRECTIONNEL BAS DIMINUE LE NOMBRE DE CYCLE PAR SECONDES DE 1");
	mvwprintw(info_box, 35, 40, "LE NOMBRE DE CYCLE PAR SECONDES NE PEUT ETRE PLUS BAS QUE 0 (LE JEU EST MIS EN PAUSE)");
	mvwprintw(info_box, 37, 40, "LA TOUCHE 0 MET LE JEU EST PAUSE SI APPUYER EN PASSANT LE NOMBRE DE CYCLE PAR SECONDE A 0 IMMEDIATEMENT");
	mvwprintw(info_box, 39, 40, "LA TOUCHE ESC PERMET DE QUITTER LE VISUEL");
	wattron(info_box, A_BOLD);
	mvwprintw(info_box, 50, 56, "NOUS VOUS SOUHAITONS UNE BONNE JOURNEE");
	wattroff(info_box, A_BOLD);
	while ((key = getch()) != 27)
	{
		if (key == KEY_UP)
			cycles += 1;
		else if (key == KEY_DOWN)
			cycles -= 1;
		else if (key == 43)
			cycles += 50;
		else if (key == 45)
			cycles -= 50;
		else if (key == 48)
			cycles = 0;
		wrefresh(info_box);
		if (cycles < 0)
			cycles = 0;
		if (key == 45 || key == 43 || key == KEY_UP || key == KEY_DOWN || key == 48)
			mvwprintw(info_box, 5, 39, "%d cycle/s   ", cycles);
	}
    endwin();

    free(big_square);
    free(map_corew);
	free(info_box);
    
    return 0;
}
