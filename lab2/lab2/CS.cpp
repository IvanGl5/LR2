#include "CS.h"
#include <iostream>
#include "Utils.h"
#include "Logger.h"

int CompressorStation::nextId = 1;
std::unordered_map<int, CompressorStation> CompressorStation::stations;

CompressorStation::CompressorStation(int id, const std::string& name, int workshopNumber, int workshopNumberInWork, double efficiency)
    : id(id), name(name), workshopNumber(workshopNumber), workshopNumberInWork(workshopNumberInWork), efficiency(efficiency) {
    logger.log("������ ������ CompressorStation � ID: " + std::to_string(id));
}

void CompressorStation::readFromConsole() {
    std::cout << "������� �������� �������: ";
    std::getline(std::cin, name);

    workshopNumber = inputInRange<int>("������� ���������� �����: ", 1, 1000);
    workshopNumberInWork = inputInRange<int>("������� ���������� ����� � ������: ", 0, workshopNumber);
    efficiency = inputInRange<double>("������� ������������� (� %): ", 0.01, 100);
    logger.log("���� ������ ��� CompressorStation ��������.");
}

void CompressorStation::writeToConsole() const {
    logger.log("����� ���������� � CompressorStation � ID: " + std::to_string(id));
    std::cout << "\nID �������: " << id << std::endl;
    std::cout << "�������� �������: " << name << std::endl;
    std::cout << "���������� �����: " << workshopNumber << std::endl;
    std::cout << "���������� ����� � ������: " << workshopNumberInWork << std::endl;
    std::cout << "������������� (� %): " << efficiency << std::endl << std::endl;
}

void CompressorStation::editWorkshop() {
    int command;
    std::cout << "1 - ��������� ���" << std::endl;
    std::cout << "2 - ���������� ���" << std::endl;

    command = inputInRange<int>("�������� ��������: ", 1, 2);

    if (command == 1) {
        if (workshopNumber > workshopNumberInWork) {
            logger.log("������� ��� ���� ��� � CompressorStation � ID: " + std::to_string(id));
            workshopNumberInWork++;
            std::cout << "��� ���� ��� �������. ������ � ������ " << workshopNumberInWork << " �� " << workshopNumber << " �����.\n";
        }
        else {
            logger.log("��� ���� ��� �������� � CompressorStation � ID: " + std::to_string(id));
            std::cout << "��� ���� ��� ��������.\n";
        }
    }
    else if (command == 2) {
        if (workshopNumberInWork > 0) {
            logger.log("���������� ���� ��� � CompressorStation � ID: " + std::to_string(id));
            workshopNumberInWork--;
            std::cout << "���� ��� ����������. ������ � ������ " << workshopNumberInWork << " �� " << workshopNumber << " �����.\n";
        }
        else {
            logger.log("��� ���� ��� ����������� � CompressorStation � ID: " + std::to_string(id));
            std::cout << "��� ���� ��� �����������.\n";
        }
    }
    else {
        std::cout << "�������� �����, ���������� �����.\n";
    }
}

void CompressorStation::addStation() {
    CompressorStation station;
    station.setId(nextId++);
    station.readFromConsole();
    stations[station.getId()] = station;
    logger.log("��������� ����� CompressorStation � ID: " + std::to_string(station.getId()));

}

void CompressorStation::displayAll() {
    logger.log("����� ���� ������������� �������.");
    std::cout << "\n--- �������� ��� ������������� ������� ---\n";
    for (const auto& [id, station] : stations) {
        station.writeToConsole();
    }
}

void CompressorStation::editStationById(int id) {
    auto it = stations.find(id);
    if (it != stations.end()) {
        it->second.editWorkshop();
        logger.log("�������������� ��������� ��� CompressorStation � ID: " + std::to_string(id));

    }
    else {
        std::cout << "������� � ����� ID �� �������.\n";
        logger.log("������: �� ������� CompressorStation � ID: " + std::to_string(id));

    }
}

void CompressorStation::addNewStation() {
    CompressorStation station;
    station.setId(nextId++);
    station.readFromConsole();
    stations[station.getId()] = station;
    std::cout << "������� ������� ���������.\n";
    logger.log("��������� ����� ������� � ID: " + std::to_string(station.getId()));
}

void CompressorStation::editStation() {
    int stationId;
    std::cout << "������� ID ������� ��� ��������������: ";
    std::cin >> stationId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto it = stations.find(stationId);
    if (it != stations.end()) {
        logger.log("������� � ID " + std::to_string(stationId) + " ������� ���������������.");
        it->second.editWorkshop();
        std::cout << "������� � ID " << stationId << " ������� ���������������.\n";
    }
    else {
        logger.log("������: ������� � ID " + std::to_string(stationId) + " �� �������.");
        std::cout << "������� � ����� ID �� �������.\n";
    }
}

void CompressorStation::deleteStation() {
    int stationId;
    std::cout << "������� ID ������� ��� ��������: ";
    std::cin >> stationId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (stations.erase(stationId)) {
        logger.log("������� � ID " + std::to_string(stationId) + " ������� �������.");
        std::cout << "������� � ID " << stationId << " ������� �������.\n";
    }
    else {
        logger.log("������: ������� � ID " + std::to_string(stationId) + " �� �������.");
        std::cout << "������� � ����� ID �� �������.\n";
    }
}

void CompressorStation::displayStations(const std::vector<CompressorStation>& stationsToDisplay) {
    logger.log("����������� ������� �� �������� ������.");
    if (stationsToDisplay.empty()) {
        std::cout << "��� �������, ��������������� �������� ������.\n";
    }
    else {
        for (const auto& station : stationsToDisplay) {
            station.writeToConsole();
        }
    }
}

void CompressorStation::searchStationsByUnusedWorkshopPercentage() {
    double unusedPercentage;
    std::cout << "������� ������� ����������������� ����� ��� ������: ";
    std::cin >> unusedPercentage;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto results = findStationsByUnusedWorkshopPercentage(unusedPercentage);
    logger.log("����� ������� �� �������� ����������������� �����: " + std::to_string(unusedPercentage) + "%.");
    displayStations(results);
}

std::vector<CompressorStation> CompressorStation::findStationsByName(const std::string& name) {
    std::vector<CompressorStation> results;
    for (const auto& [id, station] : stations) {
        if (station.name == name) {
            results.push_back(station);
        }
    }
    return results;
}

std::vector<CompressorStation> CompressorStation::findStationsByUnusedWorkshopPercentage(double unusedPercentage) {
    std::vector<CompressorStation> results;
    for (const auto& [id, station] : stations) {
        double actualUnusedPercentage = 100.0 * (station.workshopNumber - station.workshopNumberInWork) / station.workshopNumber;
        if (actualUnusedPercentage >= unusedPercentage - 5 && actualUnusedPercentage <= unusedPercentage + 5) {
            results.push_back(station);
        }
    }
    return results;
}

void CompressorStation::searchStationsMenu() {
    logger.log("���� � ���� ������ �������.");
    std::cout << "�������� �������� ������:\n";
    std::cout << "1 - ����� �� ��������\n";
    std::cout << "2 - ����� �� �������� ����������������� �����(+-5%)\n";
    int choice = inputInRange<int>("������� ����� ��������: ", 1, 2);

    if (choice == 1) {
        std::string name;
        std::cout << "������� �������� ������� ��� ������: ";
        std::getline(std::cin, name);
        auto results = findStationsByName(name);
        displayStations(results);
    }
    else if (choice == 2) {
        double unusedPercentage;
        std::cout << "������� ������� ����������������� ����� ��� ������: ";
        std::cin >> unusedPercentage;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        auto results = findStationsByUnusedWorkshopPercentage(unusedPercentage);
        displayStations(results);
    }
}

void CompressorStation::batchEditOrDeleteMenu() {
    logger.log("���� � ���� ��������� ��������������/�������� �������.");
    if (stations.empty()) {
        std::cout << "��� ��������� ������� ��� ��������� ��������������.\n";
        return;
    }

    std::cout << "������� ID �������, ������� ������ ������� ��� ��������� ��������������, ����� ������: ";
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<int> selectedIds;
    int id;

    while (ss >> id) {
        if (stations.find(id) != stations.end()) {
            selectedIds.push_back(id);
        }
        else {
            logger.log("������: ������� � ID " + std::to_string(id) + " �� �������.");
            std::cout << "������� � ID " << id << " �� �������.\n";
        }
    }

    std::cout << "�������� ��������:\n";
    std::cout << "1 - ������������� ��������� �������\n";
    std::cout << "2 - ������� ��������� �������\n";
    int choice = inputInRange<int>("������� ����� ��������: ", 1, 2);

    if (choice == 1) {
        for (int stationId : selectedIds) {
            stations[stationId].editWorkshop();
        }
        logger.log("��������� ������� ������� ���������������.");
        std::cout << "��������� ������� ������� ���������������.\n";
    }
    else if (choice == 2) {
        for (int stationId : selectedIds) {
            stations.erase(stationId);
        }
        logger.log("��������� ������� ������� �������.");
        std::cout << "��������� ������� ������� �������.\n";
    }
}

void CompressorStation::stationSubMenu() {
    std::vector<std::string> getMenuOptionsCS = {
        "�����",
        "�������� ��� �������",
        "�������� �������",
        "������������� �������",
        "������� �������",
        "����� �������",
        "�������� ��������������"
    };

    std::string command;
    long value;

    logger.log("���� � ������� �������.");
    while (true) {
        displayMenu(getMenuOptionsCS);
        std::getline(std::cin, command);
        value = numberOrDefault(command);

        switch (value) {
        case 1:
            displayAll();
            break;
        case 2:
            addNewStation();
            break;
        case 3:
            editStation();
            break;
        case 4:
            deleteStation();
            break;
        case 5:
            searchStationsMenu();
            break;
        case 6:
            batchEditOrDeleteMenu();
            break;
        case 0:
            logger.log("����� �� ������� �������.");
            std::cout << "����� �� ���� ������ �� ���������.\n";
            return;
        default:
            logger.log("������: �������� ����� � ���� �������.");
            std::cout << "�������� �����. ���������� �����.\n";
            break;
        }
    }
}