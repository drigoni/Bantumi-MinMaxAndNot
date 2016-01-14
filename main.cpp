/*
    This program allows you to play the game of Bantumi against the computer that implements the algorithm Min - Max.
    Copyright (C) 2016  Davide Rigoni

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
    
#include <iostream>
#include <fstream>
#include <climits>
#include <cstdlib>
#include <cmath>

using namespace std;


//----------------FUNZIONI PER IA------------------
#include "f_bantumi.cpp"

//--------------------FUNZIONI PER BANTUMI----------------
#include "f_ia_bantumi_MinMax.cpp"





main()
{
	//inizializzo il campo di gioco
	int B[2][7];
	inizializza(B);
	bool fine=false;
	int giocatore = g_iniziale;

	//stampo il campo iniziale
	stampa(B);
	int mossa;

	//a seconda del giocatore inizio la mossa
	if (g_iniziale)
	{
		mossa = m_giocatore(B);
	}
	else
	{
		mossa = meglio_mossa(B,0,profondita);
	}
  

  while(!fine && mossa != -1)
  {
    if (giocatore == 1)
    {
      system("reset");
      cout<<"Mossa del giocatore 1: "<<mossa +1<<endl;
    }
    else
    {
      cout<<endl<<"La mossa del computer è: "<<mossa+1<<endl;
    }

    //eseguo la mossa e verifico se tocca nuovamente lui
    bool x = semina(B,giocatore, mossa);
    cout<<endl;
    stampa(B);

    //controllo se qualcuno dei due ha vinto
    if (controllo_fine(B))
    {
      //esco dal ciclo e mostro chi è il vincitore
      fine = true;
      int vincitore = calcolo_vincitore(B);
      if (vincitore == 0)
      {
        cout<<endl<<"Il vincitore è il computer"<<endl;
      }
      else
      {
        if (vincitore == 1)
        {
          cout<<endl<<"Il vincitore è il giocatore"<<endl;
        }
        else
        {
          cout<<endl<<"La partita si è conclusa in pareggio"<<endl;
        } 
      } 
    }
    else
    { 
      //controllo chi deve giocare
      if (!x)
      {
        //cambio di giocatore
        giocatore = other(giocatore);
      }

      
      if (giocatore == 1)
      {
        mossa = m_giocatore(B);
      }
      else
      {
        //TURNO DEL COMPUTER
        mossa = meglio_mossa(B,0,profondita);
      }
    }

  }
}



