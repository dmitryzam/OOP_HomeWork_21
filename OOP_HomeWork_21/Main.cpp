#include<iostream>
#include<string>
#include<list>
#include<map>

// ДЗ-20. Реализовать базу данных ГАИ по штрафным квитанциям с помощью бинарного дерева (класс map). 
// Ключом будет служить номер авто (число типа unsigned), значением узла - список правонарушений
// (класс list). Правонарушение - строка (класс string), в кот. написано, что сделал автовладелец.
// Если квитанция добавляется в первый раз, то она добавляется в виде нового узла бинарного дерева, 
// то в соответствующий список добавляется новое правонарушение.

// ф-ия по добавлению нарушителей ПДД:
void addRullBreaker(std::map<unsigned, std::list<std::string>>& base) {
	std::map<unsigned, std::list<std::string>>::iterator it_map;
	std::cout << "Введите номер нарушителя -> ";
	unsigned gos_nom;
	std::cin >> gos_nom;
	std::cout << "Введите правонарушение -> ";
	std::string offens;
	std::cin.ignore();
	std::getline(std::cin, offens);
	bool isBadGuy = false;		// есть ли такой номер в базе?
	for (it_map = base.begin(); it_map != base.end(); ++it_map) {
		if (gos_nom == it_map->first) {
			it_map->second.push_back(offens);	// добавим правонарушение на найденный номер
			std::cout << "Запись нарушения\n";
			isBadGuy = true;
		}		
	}
	if (!isBadGuy) {	// если нет такого намера, то запишем и номер и правонарушение
		std::list<std::string> tmp;
		tmp.push_back(offens);
		base.insert(std::make_pair(gos_nom, tmp));	// добавим новый номер авто и его правонарушение
		std::cout << "Запись номера и нарушения\n";
	}
}
// ф-ия по распечатке базы данных (вывод всех номеров авто и правонарушений, числящихся за ними):
void printFullData(std::map<unsigned, std::list<std::string>>& base) {
	std::map<unsigned, std::list<std::string>>::const_iterator it_map;
	std::list<std::string>::const_iterator it_list;
	for (it_map = base.cbegin(); it_map != base.cend(); ++it_map) {
		std::cout << "Номер авто: " << it_map->first << ", его правонарушения:\n";
		for (it_list = ((*it_map).second).cbegin(); it_list != ((*it_map).second).cend(); ++it_list) {
			std::cout << *it_list << std::endl;
		}
	}
	std::cout << "Кол-во нарушителей -> ";
	if (!base.empty())
		std::cout << base.size() << std::endl;
	else
		std::cout << 0 << std::endl;
}


int main() {
	setlocale(LC_ALL, "RU");
	// База данных ГАИ:
	std::map<unsigned, std::list<std::string>> dataBase;		
	while(true){
		while (true) {
			addRullBreaker(dataBase);
			std::cout << "Хотите закончить? Введите (Y/N) -> ";
			char ch;
			std::cin >> ch;
			if (ch == 'y' || ch == 'Y')
				break;
		}
		std::cout << "Хотите распечатать базу? Введите (Y/N) -> ";
		char ch;
		std::cin >> ch;
		if (ch == 'y' || ch == 'Y')
			printFullData(dataBase);
		std::cout << "Хотите закончить? Введите (Y/N) -> ";
		std::cin >> ch;
		if (ch == 'y' || ch == 'Y')
			break;
	}
	return 0;
}