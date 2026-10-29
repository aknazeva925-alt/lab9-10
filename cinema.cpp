#include <iostream>
#include "film.h"

using namespace std;

int main()
{
	setlocale(0, "");

	FilmCrew duneFC("Оппенгеймер", "Биография", 180, 900, "Кристофер Нолан", "Киллиан Мерфи");
	DirectorPopularFilm duneDPC("Интерстеллар", "Фантастика", 169, 800, "Кристофер Нолан", "Мэттью МакКонахи", "Начало");

	/*Session session1(5, "18:30", &duneFC);
	session1.showSession();*/

	Session* session1 = Session::createSession(5, "18:30", &duneFC);
	session1->showSession();
	delete session1;

	//тест работы нисходящего приведения типов
	DirectorPopularFilm godfather("Крестный отец", "драма", 175, 670, "Френсис Форд Коппола", "Марлон Брандо", "Апокалипсис сегодня");
	/*Session session2(1, "12:00", &godfather);*/
	Session* session2 = Session::createSession(1, "12:00", &godfather);
	cout << endl << "1) Было: " << endl;
	/*session2.showSession();*/
	session2->showSession();
	cout << endl << "2) Стало: " << endl << endl;
	session2->changePrice(455);
	session2->changeDirName("Фрэнсис Коппола");
	session2->changeDirFilm("Сады камней");
	session2->showSession();

	delete session2;

}

