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
    
void copia_array(const int B[][7],int copia[][7]);
double c_mossa_ric(const int B[2][7],  int giocatore,  int buca,int profondita);
int migliore_mossa(const int B[2][7],int giocatore,int livello);
int val_statica(const int B[2][7],int vincitore,bool giocatore,int profondita);
int i_n_max(const double *B);
double prob(const double *B);

const int SogliaMassima = INT_MAX;
const int SogliaMinima = INT_MIN;

//funzione probabilistica che dato un campo non restiuisce a sua volta il min-max ma da un voto complessivo ai valori delle buche
double prob(const double *B)
{
  double n=0,m=0;
  for(int i = 0; i<6;i++)
  {
    if (B[i] != SogliaMinima && B[i] != SogliaMassima)
    {
      m += B[i];
      n++;
    }
  }
  return m/n;
}

//dato un campo restituisce l'indice della buca con il numero di fagioli più alto
int i_n_max(const double *B)
{
  int indice = 0;
  for(int i = 0; i<6;i++)
  {
    if (B[indice]<B[i])
    {
      indice = i;
    }
  }

  return indice;
}

//copia profonda della matrice
void copia_array(const int B[][7],int copia[][7])
{
    //copio l'intero array
    for (int i = 0; i < 2*7; ++i)
    {
        copia[0][i] = B[0][i];
    }
}

//funzione euristica
int val_statica(const int B[2][7],int vincitore,bool giocatore,int prof)
{
  int diff_punti = B[0][6]-B[1][6];
  int fagioliP1= 0;
  int fagioliP0=0;
  int n_bucheP0 = 0;
  int n_bucheP1 = 0;

  for (int i = 0; i < 6; ++i)
  {
    if (B[0][i] != 0)
    {
      n_bucheP0++;
      fagioliP0 += B[0][i];
    }
    if (B[1][i] != 0)
    {
      n_bucheP1++;
      fagioliP1 += B[1][i];
    }
  }
  int diff_fagioli = fagioliP0- fagioliP1;
  int diff_n_buche = n_bucheP0- n_bucheP1;



  //vince il computer
  if (vincitore == 0)
  {
    return 10000 + 100*prof;
  }
  //vince il giocatore
  if (vincitore == 1)
  {
    return -(10000 + 100*prof);
  }
  //parita tra i giocatori
  if (vincitore == -1)
  {
    return 0;
  }

  if (vincitore == -2)
  {
    //Ritorno il vincitore nei casi in cui gia prima della fine della partita si nota chi vince
    if (abs(diff_punti) >= fagioliP1 + fagioliP0)
    {
      //vincita sicura per il comuter
      if (diff_punti > 0)
      {
        return 10000 + 100*prof;
      }
      //Si ricorda che non e possibile che la differenza di punti tra i giocatori
      //sia 0 e cche anche fagioliP1 e fagiolP2 sia 0 poiche deve esserci almeno un fagiolo per campo
      //vincita sicura per il giocatore
      if (diff_punti < 0)
      {
        return -(10000 + 100*prof);
      }
    }
    else
    {
        return diff_punti*100 + diff_fagioli*10 + diff_n_buche;
    }
  }
}


//calcola la mossa ricorsiva
double c_mossa_ric(const int B[2][7],  int giocatore,  int buca,int prof)
{

  //copio l'array
  int C[2][7];
  copia_array(B,C);

  //eseguo la semina
  bool rigioca = semina(C,giocatore,buca);

  if(controllo_fine(C))
  {
    int vincitore = calcolo_vincitore(C);
    int valut = val_statica(C,vincitore,giocatore,prof);
    return valut;
  }

  if (!prof && !rigioca)
  {
    int valut = val_statica(C,-2,giocatore,prof);
    return valut;
  }
  else
  {
    //creo l'array e lo imposto con il valore iniziale
    double D[6];
    for (int i = 0; i < 6; ++i)
    {
        if (giocatore == 0)
        {
          D[i] = SogliaMinima;
        }
        else
        {
          D[i] = SogliaMassima;
        }
    }

    //cambio giocatore nel caso servisse
    if (!rigioca)
    {
      giocatore = other(giocatore);
      prof --;
    }

    //tento tutte le mosse possibili
    for (int i = 0; i < 6; i++)
    {
      if (C[giocatore][i])
      { 
        D[i]=c_mossa_ric(C, giocatore, i, prof);
      }
    }

      return prob(D);
    
  }

}


//Tenta tutte le combinazioni possibili del giocatore passato come parametro fino ad un determinato livello
int meglio_mossa(const int B[2][7],int giocatore,int livello)
{
  double C[6];
  //tento tutte le mosse possibili
  for (int i = 0; i < 6; i++)
  {
    if (B[0][i])
    { 
      C[i]=c_mossa_ric(B,giocatore, i, livello);
    }
    else
    {
      C[i]=SogliaMinima;
    }
  }
  return i_n_max(C);
}