#include <iostream>
#include <string>

using namespace std;

class Film
{
private:
	string* film_name;
	string* genre;
	int* time; //в минутах
	double* ticket_price;

protected:
	int seats = 200;
	int revenue() const {
		return seats * (*ticket_price);
	}

	void showCommon() const {
		cout << "Фильм: " << *film_name << endl
			<< "Жанр: " << *genre << endl
			<< "Длительность (в минутах): " << *time << endl
			<< "Стоимость билета: " << *ticket_price << " рублей" << endl
			<< "Выручка с полного зала (" << seats << " мест): "
			<< revenue() << " рублей" << endl;
	}

public:
	//конструктор 1
	Film(const string& nameFilm, const string& genre_,
		int time_, double price_)
	{
		film_name = new string(nameFilm);
		genre = new string(genre_);
		time = new int(time_);
		ticket_price = new double(price_);
	}

	//деконструктор
	virtual ~Film()
	{
		delete film_name;
		delete genre;
		delete time;
		delete ticket_price;
	}

	//1 set & get
	void setFilm_name(const string& nameFilm) {
		if (nameFilm.empty()) {
			throw invalid_argument("Поле не может быть пустым!");
		} 
		*film_name = nameFilm;
	}
	string getFilm_name() const {
		return *film_name;
	}
	//2 set & get
	void setGenre(const string& genre_) {
		if (genre_.empty()) {
			throw invalid_argument("Поле не может быть пустым!");
		} 
		*genre = genre_;
	}
	string getGenre() const {
		return *genre;
	}
	//3 set & get
	void setTime(int time_) {
		if (time_ <= 0) {
			throw invalid_argument("Длительность фильма не может быть меньше или равна 0.");
		} 
		*time = time_;
	}
	int getTime() const {
		return *time;
	}
	//4 set & get
	void setPrice(double price_) {
		if (price_ <= 0) {
			throw invalid_argument("Стоимость билета не может быть меньше или равна 0.");
		}
		*ticket_price = price_;
	}
	//вывод
	virtual void showFilm() const = 0;
};

class FilmCrew : public Film {
private:
	string* nameDirector;
	string* nameMainActor;
public:
	//конструктор
	FilmCrew(const string& nameFilm, const string& genre_,
		int time_, double price_,
		const string& nameDirector_, const string& nameMainActor_) : Film(nameFilm, genre_, time_, price_){
		nameMainActor = new string(nameMainActor_);
		nameDirector = new string(nameDirector_);
	}

	//деконструктор
	~FilmCrew () override
	{
		delete nameMainActor;
		delete nameDirector;
		
	}
	void setNameDirector(const string nameDirector_) {
		if (nameDirector_.empty()) {
			throw invalid_argument("Поле не может быть пустым!");
		}
		*nameDirector = nameDirector_;
	}
	void setNameMainActor(const string nameMainActor_) {
		if (nameMainActor_.empty()) {
			throw invalid_argument("Поле не может быть пустым!");
		}
		*nameMainActor = nameMainActor_;
	}
	void showFilm() const override {
		showCommon();
		cout << "Режиссёр: " << *nameDirector << endl
			<< "Главная роль: " << *nameMainActor << endl << endl;
	}
};


class DirectorPopularFilm : public FilmCrew {
private:
	string* nameFilmDir;
public:
	//конструктор
	DirectorPopularFilm(const string& nameFilm, const string& genre_,
		int time_, double price_,
		const string& nameDirector_, const string& nameMainActor_,
		const string& nameFilmDir_) : FilmCrew(nameFilm, genre_, time_, price_,
			nameDirector_, nameMainActor_)
	{
		nameFilmDir = new string(nameFilmDir_);

	}
	//деконструктор
	~DirectorPopularFilm() override
	{
		delete nameFilmDir;
	}
	void setNameFilmDir(const string nameFilmDir_) {
		if (nameFilmDir_.empty()) {
			throw invalid_argument("Поле не может быть пустым!");
		}
		*nameFilmDir = nameFilmDir_;
	}
	void showFilm() const override {
		FilmCrew::showFilm();
		cout << "Другой популярный фильм режиссера: " << *nameFilmDir << endl << endl;
	}
};
   
//lab9 & 10
class Session {
	private:
		int* hallNumber;      
		string* startTime;    
		Film* film;           //поле род.класса (вложенное поле)

		Session(int hallNumber_, const string& time_, Film* film_) {
			hallNumber = new int(hallNumber_);
			startTime = new string(time_);
			film = film_;
		}  

	public:
		~Session() {
			delete hallNumber;
			delete startTime;
		}
		//--- статический метод
		static Session* createSession(int hallNumber_, const string& time_, Film* film_) {
			//проверка
			if (hallNumber_ <= 0) {
				throw invalid_argument("Номер зала должен быть положительным!");
			}
			if (time_.empty()) {
				throw invalid_argument("Время не может быть пустым!");
			}
			if (film_ == nullptr) {
				throw invalid_argument("Указатель на фильм не может быть пустым!");
			}

			return new Session(hallNumber_, time_, film_);
		}
		//-------------------------------

		void setHallNumber(int hallNum) {
			if (hallNum <= 0) throw invalid_argument("Номер зала должен быть положительным!");
			*hallNumber = hallNum;
		}

		void setStartTime(const string& time_) {
			if (time_.empty()) throw invalid_argument("Время не может быть пустым");
			*startTime = time_;
		}

		int getHallNumber() const { return *hallNumber; }
		string getStartTime() const { return *startTime; }

		//---методы для дз10---
		  //класс Film
		void changePrice(double newPrice) {
			film->setPrice(newPrice);
			cout << "!!Цена билета на фильм изменена!!" << endl;
		}
		//класс FilmCrew
		void changeDirName(const string& newDirector) {
			FilmCrew* crewFilm = dynamic_cast<FilmCrew*>(film);

			if (crewFilm != nullptr) {
				crewFilm->setNameDirector(newDirector);
				cout << endl << "!!Имя режиссера изменено.!!" << endl;
			}
			else {
				cout << endl << "Ошибка.";
			}
		}
		//класс DirectorPopularFilm
		void changeDirFilm(const string& newDirFilm) {
			DirectorPopularFilm* dirFilm = dynamic_cast<DirectorPopularFilm*>(film);

			if (dirFilm != nullptr) {
				dirFilm->setNameFilmDir(newDirFilm);
				cout << endl << "!!Название популярного фильма режиссера изменено.!!" << endl;
			}
			else {
				cout << endl << "Ошибка.";
			}
		}

		//--- -------------- ---
		void showSession() const {
			cout << endl << "--- ИНФОРМАЦИЯ О СЕАНСЕ ---" << endl;
			cout << "Зал № " << *hallNumber << endl;
			cout << "Время начала: " << *startTime << endl;
			cout << "--- ИНФОРМАЦИЯ О ФИЛЬМЕ ---" << endl;
			film->showFilm();
		}
};