#include <iostream>
#include <math.h>
#include <algorithm>
#include <stddef.h>
#include <stdlib.h>
#include <iomanip>
/*(http://sadi.ovh.org/arty/cppsort.php  pomocne funkcje sortujace)*/
using namespace std;

/*!
 * \file
 * \brief Definicja szablonu Tablica i jej metod.
 */
template <typename T>
class Kopiec {

  std::size_t rozmiar;
  T * tab_kopiec;

public:

  /*! 
   * \brief konstruktor obiektu Kopiec.
   */
  Kopiec(int konstruktor=0){this->rozmiar=konstruktor; tab_kopiec = new T[rozmiar];
    for(unsigned int i=0; i<this->rozmiar; i++){tab_kopiec[i]=0;}}

  /*! 
   * \brief konstruktor kopiujacy obiektu Kopiec.
   */
  Kopiec(Kopiec & K){ this->rozmiar=K.rozmiar; this->tab_kopiec = new T[rozmiar];
    for(unsigned int i=0; i<this->Rozmiar(); i++){ this->tab_kopiec[i]=K.tab_kopiec[i];}}

  /*! 
   * \brief destruktor obiektu Kopiec.
   */
  ~Kopiec(){ if(tab_kopiec) delete [] tab_kopiec; } //destruktor sprawdzajacy przed wywolaniem czy kopiec nie jest pusty
  /*! 
   * \brief Metoda zwracajaca rozmiar tablicy zapisany w czesci private obiektu Tablica.
   */
  const std::size_t Rozmiar() const {return rozmiar;}
  /*! 
   * \brief Operator indeksujacy nie-const.
   */
  T & operator [] (std::size_t i){return tab_kopiec[i];}
  /*! 
   * \brief Operator indeksujacy const.
   */
  const T & operator [] (std::size_t i) const {return tab_kopiec[i];}
  /*! 
   * \brief Funkcja zwracajaca wskaznik na pierwszy element tablicy.
   */
  T * begin(){return tab_kopiec;}  
  /*! 
   * \brief Funkcja zwracajaca wskaznik na ostatni element kopca.
   */
  T * end(){return (tab_kopiec+rozmiar);}
  /*! 
   * \brief Operator przypisania L - wartosci.
   */
  Kopiec & operator = ( const Kopiec & K){
    this->rozmiar=K.rozmiar;
    for(unsigned int i=0;i<K.rozmiar;i++)
      {
	this->tab_kopiec[i]=K.tab_kopiec[i];
      }
    return *this;
  }
  /*! 
   * \brief Metoda dodajaca nowy element na koncu kopca.
   */
  void insert(T const & wartosc){
    rozmiar++;
    T * K_save=new T[rozmiar+1];
    
    for( unsigned int i=1; i<rozmiar ; i++)
      {
	K_save[i]=tab_kopiec[i];
      }
    K_save[rozmiar]=wartosc;
    // delete [] tab_kopiec;    <- zapytać Prowadzącego
    tab_kopiec=K_save;  
  }
  /*! 
   * \brief Metoda wyswietlajaca kopiec na stdout z zachowaniem odstepow miedzy elementami.
   */
  void Wyswietl(){

    if(rozmiar==0){
      cout<<"Kopiec jest pusty"<<endl;
    }
      int x = (rozmiar + 1) / 2;
      unsigned int k = 2;
      for(unsigned int i = 1; i <= rozmiar; i++)
      {
      for(int j = 1; j <= x - 1; j++) cout << " ";
      cout <<" "<< setw(2) << tab_kopiec[i];
      for(int j = 1; j <= x; j++) cout << " ";
      if(i + 1 == k)
      {
      k += k; x /= 2; cout << endl;
      }
      }

    /*
    int x = (rozmiar + 1) / 2;
    int k = 2;
    for(int i = 1; i <= rozmiar; i++)
      {
	for(int j = 1; j < x; j++) cout << " ";
	cout << tab_kopiec[i];
	for(int j = 1; j <= x; j++) cout << " ";
	if(i + 1 == k)
	  {
	    k += k; x /= 2; cout << endl;
	  }
	  }*/
  }
  /*! 
   * \brief Metoda zwracajaca rodzica do dziecka o podanym indeksie.
   */
  T zwrocRodzica(const int index){
    if(index==1) return tab_kopiec[index];
    int nowy_index = index/2;
    return tab_kopiec[nowy_index];
  }
  /*! 
   * \brief Metoda zwracajaca indeks lewego dziecka rodzica o danym indeksie.
   */
  int zwrocIndexLewegoDziecka(const unsigned int rodzic){
    unsigned int lewy_index = (rodzic*2);
    if(lewy_index>rozmiar){
      //  cerr << "Nie ma lewego dziecka" << endl;
      return -1;}
    return lewy_index;
  }
  /*! 
   * \brief Metoda zwracajaca indeks prawego dziecka rodzica o danym indeksie.
   */
  int zwrocIndexPrawegoDziecka(const unsigned int rodzic){
     unsigned int prawy_index = ((rodzic*2)+1);
    if(prawy_index>rozmiar){
      // cerr << "Nie ma prawego dziecka" << endl;
      return -1;}
    return prawy_index;
  }
  /*! 
   * \brief Metoda zamieniajaca dwa elementy kopca o podanych indeksach.
   */
  void swap(const int index1, const int index2){
    T k_save=tab_kopiec[index1];
    tab_kopiec[index1]=tab_kopiec[index2];
    tab_kopiec[index2]=k_save;
  }
  /*! 
   * \brief Metoda przywracajaca wlasnosc w dol od elementu o podanym indeksie.
   */
  void przywrocWlasnoscDol( const int index){
    int lewy=this->zwrocIndexLewegoDziecka(index);
    int prawy=this->zwrocIndexPrawegoDziecka(index);
    if(lewy==(-1)&&prawy==(-1)) return;
    if (tab_kopiec[index]>tab_kopiec[lewy]){
      if (tab_kopiec[lewy]>=tab_kopiec[prawy]){
	swap(index, prawy);
        przywrocWlasnoscDol(prawy);
      }
      else{
	swap(index, lewy);
        przywrocWlasnoscDol(lewy);
      }
    }
    else if (tab_kopiec[index]>tab_kopiec[prawy]){
      swap(index, prawy);
      przywrocWlasnoscDol(prawy);
    }
  }

  /*! 
   * \brief Metoda przywracajaca wlasnosc w gore od elementu o podanym indeksie.
   */
  void przywrocWlasnoscGora( const int index){
    if(index==1){ return;}
    int rodzic=(index/2);
    if(index==rodzic*2){   //warunek dla lewego dziecka 
      if((unsigned int)index<rozmiar){  //sprawdzenie czy jest jedynym dzieckiem
	if(tab_kopiec[index]<tab_kopiec[rodzic]){
	  if(tab_kopiec[index]<=tab_kopiec[index+1]){
	    swap(index, rodzic);
	    przywrocWlasnoscGora(rodzic);
	  }
	  else {
	    swap(index+1, rodzic);
	    przywrocWlasnoscGora(rodzic);
	  }
	}
	else {
	  swap(index, rodzic);
	  przywrocWlasnoscGora(rodzic);
	}
      }
    }
    else if(index==(rodzic*2+1)){ //sytuacja z prawym dzieckiem
      if(tab_kopiec[index]<=tab_kopiec[rodzic]){
	if(tab_kopiec[index]<tab_kopiec[index-1]){
	  swap(index, rodzic);
	  przywrocWlasnoscGora(rodzic);
	}
	else{
	  swap(index-1, rodzic);
	  przywrocWlasnoscGora(rodzic);
	}
      }
      else {
	if(tab_kopiec[rodzic]>tab_kopiec[index-1]){	
	  swap(index-1, rodzic);
	  przywrocWlasnoscGora(rodzic);
	}
      }
    }
    if(tab_kopiec[rodzic]<=tab_kopiec[index-1]&&tab_kopiec[rodzic]<=tab_kopiec[index])
      przywrocWlasnoscGora(rodzic);
  }
  /*! 
   * \brief Metoda przywracajaca calkowicie wlasnosc kopca w goredol od wezla o zadanym indeksie.
   *        Wywolanie przywracania w dol wielokrotne w zaleznosci od poziomu od dolu do jakiego nalezy
   *        element o danym indeksie
   */
  void przywrocCalaWlasnoscDol(const int index){

    double wysokosc_kopca = log(double(this->rozmiar+1))/log(2.00);
    wysokosc_kopca=ceil(wysokosc_kopca);

    double odl_od_korzenia = log(double(index+1))/log(2.00);
    odl_od_korzenia =ceil(odl_od_korzenia );

    int odl_od_konca=int((wysokosc_kopca-odl_od_korzenia));

    for (int i=1;i<=odl_od_konca;i++){
      this->przywrocWlasnoscDol(index);
    }
  }
  /*! 
   * \brief Metoda przywracajaca calkowicie wlasnosc kopca w gore od wezla o zadanym indeksie.
   */
  void przywrocCalaWlasnoscGora(const int index){
    this->przywrocWlasnoscGora(index);
  }
  /*! 
   * \brief Metoda zwracajaca wartosc elementu bedacego korzeniem kopca.
   */
  T top(){
    return tab_kopiec[1];
  }
  /*! 
   * \brief Metoda usuwajaca korzen kopca, w jego miejsce wstawia ostatni element kopca
   *        i nastepnie naprawia kopiec w dol.
   */
  void pop(){
    T * tab_save=new T[rozmiar];

    tab_save[1]=tab_kopiec[rozmiar];
    for(unsigned int i=2; i<rozmiar;i++)
      tab_save[i]=tab_kopiec[i];

    this->rozmiar=(this->rozmiar-1);
    this->tab_kopiec=tab_save;
    this->przywrocCalaWlasnoscDol(1); // 
  }


/*! 
 * \brief Metoda usuwajaca wartosc z wezla zadanego indeksem i wstawiajaca ostatni element
 *        w to miejsce.
 */
  void remove(size_t index) {
    if(index==1)
      this->pop();
    
    else {
      unsigned int rozmiar=this->rozmiar;
      T * tab_save=new T[rozmiar];
      for(unsigned int i=1;i<index;i++)
	tab_save[i]=tab_kopiec[i];
      if(index<rozmiar){
	tab_save[index]=tab_kopiec[rozmiar];
      }
      for(unsigned int i=(index+1);i<(rozmiar-1);i++)
	tab_save[i]=tab_kopiec[i];
      delete [] this->tab_kopiec;
      this->rozmiar=(rozmiar-1);
      this->tab_kopiec=tab_save;
    }


  }
  /*! 
   * \brief Metoda ukladajaca elementy tablicy w porzadku kopca binarnego
   *        od najmniejszych  wartosci do najwiekszych (od korzenia w dol).
   */
  void przeksztalcTabwKopiec() {
    for( int i=floor(double(rozmiar/2));i>=1;i--)
      this->przywrocWlasnoscDol(i);
  }
  /*! 
 * \brief Metoda przywracajaca wlasnosc kopca po zmniejszeniu wartosci elementu
 *        spod zadanego indeksu.
 */
void decreased(size_t index){
  this->przywrocCalaWlasnoscGora(index);
}
/*! 
 * \brief Metoda przywracajaca wlasnosc kopca po zwiejszeniu wartosci elementu
 *        spod zadanego indeksu.
 */
void increased(size_t index){
  this->przywrocCalaWlasnoscDol(index);
}
/*! 
 * \brief Metoda przywracajaca wlasnosc kopca po zmianie wartosci elementu
 *        spod zadanego indeksu.
 */
void updated(size_t index){
  this->przywrocCalaWlasnoscDol(index);
  this->przywrocCalaWlasnoscGora(index);
}
/*! 
 * \brief Metoda laczaca dwa kopce w jeden i naprawiajaca caly kopiec.
 */
void merge(Kopiec & K){

  T * tab_save=new T[this->rozmiar+K.rozmiar+1];

  for(unsigned int i=1;i<=this->rozmiar;i++) //wkopiowanie 1 kopca
    tab_save[i]=tab_kopiec[i];
  for(unsigned int i=(this->rozmiar+1);i<=(this->rozmiar+K.rozmiar);i++) //wkopiowanie 2 kopca
    tab_save[i]=K.tab_kopiec[i-this->rozmiar];
  this->rozmiar=(this->rozmiar+K.rozmiar);
    this->tab_kopiec=tab_save;
  this->przeksztalcTabwKopiec();
}

};

/*!
 *\brief
 * funkcja main(), w której zostal przetestowany obiekt kopiec
 */
int main(){ 
  cout << endl; 
  Kopiec<int> K; // tworzymy pusty kopiec

  int m = 15;
  int n = 26;
  int element, element1;   
  srand(time(NULL));
  for( int i=1; i<=n; i++)
    K.insert(rand() % (m+1));

  K.Wyswietl();
  cout <<endl << " WWWWWWWWWWWWWWWWWWWWWWWWWW" <<endl; 

  K.przywrocWlasnoscGora(7);
  cout << " przywrocona wartosc w gore od indeksu 7" << endl;
  K.Wyswietl();
  cout <<endl << " WWWWWWWWWWWWWWWWWWWWWWWWW" <<endl; 

  K.przywrocWlasnoscDol(4);
  cout << " przywrocona wartosc w dol od indeksu 4" << endl;
  K.Wyswietl();
  cout <<endl << " WWWWWWWWWWWWWWWWWWWWWWWWW" <<endl;

  cout << " zwrocony rodzic elementu pod indexem 9" << endl;
  element = K.zwrocRodzica(9);
  cout<< "  " << element << endl;
  cout <<endl << " WWWWWWWWWWWWWWWWWWWWWWWWW" <<endl;

  cout << " zwrocony index lewego dziecka rodzica spod indexu 3" << endl;
  element1 = K.zwrocIndexLewegoDziecka(3);
  cout<< "  " << element1 << endl;
  cout <<endl << " WWWWWWWWWWWWWWWWWWWWWWWWW" <<endl;

  cout << " zwrocony index prawego dziecka rodzica spod indexu 3" << endl;
  element = K.zwrocIndexPrawegoDziecka(3);
  cout<< "  " << element << endl;
  cout <<endl << " WWWWWWWWWWWWWWWWWWWWWWWWW" <<endl;

  cout << " zamienione elementy spod indeksow 2 i 8" << endl;
  K.swap(2, 8);
  K.Wyswietl();
  cout <<endl << " WWWWWWWWWWWWWWWWWWWWWWWWW" <<endl;

  cout << "przywrocona cala wlasnosc stosu w dol od elementu spod indeksu 4 " << endl;
  K.przywrocCalaWlasnoscDol(4);
  K.Wyswietl();
  cout <<endl << " WWWWWWWWWWWWWWWWWWWWWWWWW" <<endl;

  cout << "przywrocona cala wlasnosc stosu w gore od elementu spod indeksu 10 " << endl;
  K.przywrocCalaWlasnoscGora(10);
  K.Wyswietl();
  cout <<endl << " WWWWWWWWWWWWWWWWWWWWWWWWW" <<endl;

  cout << "zwrocenie elementu zapisanego w korzeniu kopca " << endl;
  element=K.top();
  cout<< "  " << element << endl;
  cout <<endl << " WWWWWWWWWWWWWWWWWWWWWWWWW" <<endl;

  cout << "usuniecie elementu z korzenia, wstawienie ostatniego elementu do korzenia" << endl;
  cout << " i naprawa kopca w dol od korzenia" << endl;
  K.pop();
  K.Wyswietl();
  cout << endl << " WWWWWWWWWWWWWWWWWWWWWWWWW " <<endl;

  cout << "wstawienie do korzenia wartosci 6 i wywolanie funkcji increased dla indexu 1" << endl;
  K.insert(6);
  K.remove(1);
  K.increased(1);
  K.Wyswietl();
  cout << endl << " WWWWWWWWWWWWWWWWWWWWWWWWW " <<endl;  

  cout << "wstawienie elementu o wartosci 1 na koncu i wywolanie funkcji" << endl;
  cout << "decreased dla tego elementu" << endl;
  K.insert(1);
  element = K.Rozmiar();
  K.decreased(element);
  K.Wyswietl();
  cout << endl << " WWWWWWWWWWWWWWWWWWWWWWWWW " <<endl;

  cout << "uzycie funkcji updated dla elementu o indeksie 8" << endl;  
  K.updated(8);
  K.Wyswietl();
  cout << endl << " WWWWWWWWWWWWWWWWWWWWWWWWW " <<endl;


  cout << "stworzenie drugiego kopca" << endl;  
  int w = 12;
  int l = 7;  
  Kopiec<int> K2; // tworzymy pusty kopiec 
  srand(time(NULL));
  for( int i=1; i<=l; i++)
    K2.insert(rand() % (w+1));
  K2.Wyswietl();
  cout << endl << " WWWWWWWWWWWWWWWWWWWWWWWWW " <<endl;

  cout << "fuzja kopcow i funkcja przeksztalcenia tablicy w kopiec" << endl;  
  K.merge(K2);
  K.Wyswietl();
  cout << endl << " WWWWWWWWWWWWWWWWWWWWWWWWW " <<endl;

 
  return 0;
}

