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
    

//--------------FUNZIONI PER LO SVOLGIMENTO DELLE ORPERAZIONI DEL BANTUMI-----------
int other(int giocatore);
int calcolo_vincitore(int B[][7]);
bool controllo_fine(const int B[][7]);
void stampa(const int B[][7]);
void inizializza(int B[][7]);
bool semina(int A[][7],int giocatore,int buca);


//variabili globali
int profondita = 2;
int fagioli_inizio = 3;
int g_iniziale = 0;

//ottengo l'alto giocatore
int other(int giocatore)
{
  //ottengo il giocatore avversario
  return (giocatore+1)%2;
}

//sposta i fagioli rimasti nel campo nelle rispettive ciotole e restituisce il vincitore
int calcolo_vincitore(int B[][7])
{
  //sposto i fagioli rimasti nel campo, nella ciotola del rispettivo giocatore
  for (int i = 0; i < 6; ++i)
  {
    B[0][6] += B[0][i];
    B[0][i] = 0;
  }
  for (int i = 0; i < 6; ++i)
  {
    B[1][6] += B[1][i];
    B[1][i] = 0;
  }


  //controllo chi dei due giocatori è il vincitore. ritorno -1 in caso di parità
  if (B[0][6] > B[1][6])
  {
    return 0;
  }
  else
  {
    if (B[0][6] < B[1][6])
    {
      return 1;
    }
    else
    {
      //parità
      return -1;
    }
  } 
}

//restituscie true o false a seconda che la partita sia stata conclusa
bool controllo_fine(const int B[][7])
{
  bool fine = true; 

  //cerco nel primo campo
  for (int i = 0; i < 6 && fine; ++i)
  {
    if (B[0][i] != 0)
    {
      fine = false;
    }
  }

  if (fine)
  {
    return true;
  }
  else
  {

    //in caso cerco nel secondo
    fine = true;
    for (int i = 0; i < 6 && fine; ++i)
    {
      if (B[1][i] != 0)
      {
        fine =false;
      }
    }

    //ritorno il valore corretto
    return fine;
  }
}

//funzione di stampa della configurazione del campo
void stampa(const int B[][7])
{
    //scrivo nel file di OUTPUT
    cout<<"          "<<B[0][5]<<" "<<B[0][4]<<" "<<B[0][3]<<" "<<B[0][2]<<" "<<B[0][1]<<" "<<B[0][0]<<endl;
    cout<<B[0][6]<<"----------------------------"<<B[1][6]<<endl;
    cout<<"          "<<B[1][0]<<" "<<B[1][1]<<" "<<B[1][2]<<" "<<B[1][3]<<" "<<B[1][4]<<" "<<B[1][5]<<endl;
}

//inizializza il gioco chiedendo all'utente chi inizia per primo, la profondità del min-max e quanti fagioli utilizzare
void inizializza(int B[][7])
{
  //ottiene i parametri in ingresso
  cout<<"Quanti fagioli si desidera utilizzare? ";
  cin >>fagioli_inizio;

  cout<<"Inserire il livello di profondita: ";
  cin >>profondita;

  cout<<"Che giocatore desidera che inizi per primo?"<<endl<<"(0 per computer, 1 per Giocatore) :";
  cin >>g_iniziale;

  //pulisce lo schermo
  system("clear");

  //configura il campo del bantumi
  for(int j=0;j<2;j++)
    for(int i=0; i<6;i++)
      B[j][i] = fagioli_inizio;

  B[0][6] =0;
  B[1][6] =0;
}



//dato il giocatore, la buca scelta e la configurazione del campo e ritorno true se tocca nuovamente allo stesso giocatore, altimenti false
bool semina(int A[][7],int giocatore,int buca)
{
  //prelevo i fagioli
  int fagioli = A[giocatore][buca];

  //mantengo uno stato per verificare che giocatore ha eseguito la mossa
  int giocatore_iniziale = giocatore;

  //resetto la buca
  A[giocatore][buca]= 0;

  //semino i fagioli
  int i = 1;
  for (; i <= fagioli; i++)
  {
    //calcolo la tazza dove andrò ad inserire un fagiolino
    int tazza = (buca + i)% 7;

    //calcolo su che campo sto giocando
    giocatore = ((buca + i)/7 + giocatore_iniziale)%2;

    //faccio si che nel momento che cui trovo la tazza nemica, la salto, aggiungendo un ciclo
    if (giocatore_iniziale != giocatore && tazza == 6)
    {
      fagioli++;
    }
    else
    {
      A[giocatore][tazza] ++;
    }

    //controllo se sto esegundo l'ultima mossa
    if (i == fagioli)
    {
      //controllo se mi trovo sulla buca grande del giocatore che ha giocato
      if (tazza == 6 && giocatore == giocatore_iniziale)
      {
        return true;
      }
      else
      {
        //controllo se questa ultima buca era vuota
        if (A[giocatore][tazza] == 1)
        {
          A[giocatore][tazza] --;
          int raccolta_fagioli = A[((buca + i)/7 + giocatore_iniziale +1)%2][5-tazza] + 1;
          A[((buca + i)/7 + giocatore_iniziale +1)%2][5-tazza] = 0;

          //li aggiungo al giocatore
          A[giocatore_iniziale][6] += raccolta_fagioli;
        }
      }
    }
  }
  return false;
}

//data la configurazione del campo fa scegliere al giocatore quale tazza scegliere
int m_giocatore(int B[2][7])
{
  int mossa = 1;
  cout<<endl;
  cout<<"Tocca a lei. Inserisca il numero della tazza scelta: ";

  bool fine = false;
  while(!fine)
  { 
    try
    {
      cin>>mossa;
      if (mossa <=0 || mossa >=7)
      {
        throw 1;
      }
      else
      {
        if (B[1][mossa-1]==0)
        {
          throw 2;
        }
        else
        {
          fine = true;
        }   
      }
    }
    catch(int x)
    {
      if (x ==2)
      {
        cout<<endl;
        cout<<"Si prega di sceglie una tazza non vuota."<<endl;
        cout<<"Tocca a lei. Inserisca il numero della tazza scelta: ";
      }
      else
      {
        cout<<endl;
        cout<<"Si prega di inserire un numero compreso tra 1 e 6 estremi inclusi."<<endl;
        cout<<"Tocca a lei. Inserisca il numero della tazza scelta: ";
      }
    }
  }

  return mossa-1;
}