#include "functions.h"

std::vector<std::string> splitString(std::string input, char terminator) {
	std::vector<std::string> result = std::vector<std::string>();
	if (input == "") {
		return result;
	}

	std::string temp = "";
	input += terminator;

	for (auto i = 0; i < input.size(); i++) {
		if (input[i] == terminator) {
			result.push_back(temp);
			temp = "";
			continue;
		}
		temp += input[i];
	}

	return result;
}

float calcExpAverage(std::deque<float> input) {
	auto numerator = 0.0f;
	auto denominator = 0.0f;
	auto alpha = 2 / (float)(input.size() + 1);

	for (int i = (int)input.size() - 1; i >= 0; i--) {
		auto pi = input[i];
		auto n = input.size() - i - 1;
		auto power = (float)pow(1 - alpha, n);

		numerator += pi * power;
		denominator += power;
	}
	return numerator / denominator;
}

std::deque<float> getLastElements(std::deque<float> container, int number) {
	auto result = std::deque<float>();

	for (int i = (int)container.size() - 1; i >= 0 && i >= (int)container.size() - number; i--) {
		result.push_front(container[i]);
	}
	return result;
}

float calcExpMovingAverage(std::deque<float> container, int number) {
	auto tempContainer = getLastElements(container, number + 1);
	return calcExpAverage(tempContainer);
}

/*
	usuwanie z pamieci nie potrzebnych rekordow
	dzieki temu oszczedzamy na pamieci i
*/
void removeUnusedData(dataContainer* temp) {
	if (temp->date.size() > 40) {
		temp->date.pop_front();
		temp->value.pop_front();
		temp->macd.pop_front();
		temp->signal.pop_front();
	}
}

dataContainer getData(std::string inputFileName, std::string outputFileName, float fund, int numberOfRecords) {
	dataContainer data;

	data.wallet = fund;

	std::ifstream inputFile(inputFileName.c_str());
	std::ofstream outputFile(outputFileName.c_str());

	std::string inputBuffor;
	inputFile >> inputBuffor; // wczytanie etykiet

	#ifdef CONSOLE
		std::cout.width(5);
		std::cout << "dzien";
		std::cout.width(10);
		std::cout << "Otwarcie";
		std::cout.width(15);
		std::cout << "MACD";
		std::cout.width(5);
		std::cout << "";
		std::cout.width(15);
		std::cout << "SIGNAL";
		std::cout.width(15);
		std::cout << "Wallet";
		std::cout << std::endl;
	#endif // CONSOLE

	for (int i = 0; inputFile >> inputBuffor && (i < numberOfRecords || numberOfRecords == -1); i++) {
		auto row = splitString(inputBuffor, ',');

		auto date = row[0];
		data.date.push_back(date);

		auto value = std::stof(row[1]);
		data.value.push_back(value);

		auto ema12 = calcExpMovingAverage(data.value, 12);
		auto ema26 = calcExpMovingAverage(data.value, 26);
		auto macdTemp = ema12 - ema26;
		data.macd.push_back(macdTemp);

		auto signalTemp = calcExpMovingAverage(data.macd, 9);
		data.signal.push_back(signalTemp);

		outputFile << date << "," << value << "," << macdTemp << "," << signalTemp << std::endl;

		#ifdef CONSOLE
			//wypisywanie danych na konsole
			std::cout.width(5);
			std::cout << i + 1;
			std::cout.width(10);
			std::cout << value;
			std::cout.width(15);
			std::cout << macdTemp;
			std::cout.width(5);
			std::cout << (macdTemp > signalTemp ? ">" : "<");
			std::cout.width(15);
			std::cout << signalTemp;
			std::cout.width(15);
			std::cout << data.wallet;
			std::cout.width(20);
		#endif // CONSOLE

		
		if (data.value.size() > 30) {
			if (macdTemp > signalTemp && data.wallet > 0) {
				float moving = data.wallet / value;
				#ifdef CONSOLE
					std::cout << "buying : " << moving << " actions for " << data.wallet << " pln";
				#endif // CONSOLE
				data.wallet = 0;
				data.fund += moving;
			}
			else if (macdTemp < signalTemp && data.fund > 0) {
				float moving = data.fund * value;
				#ifdef CONSOLE
					std::cout << "selling : " << data.fund << " actions for " << moving << " pln";
				#endif // CONSOLE
				data.wallet += moving;
				data.fund = 0;
			}
		}
		#ifdef CONSOLE
			std::cout << std::endl;
		#endif // CONSOLE

		removeUnusedData(&data);
	}

	if (data.fund > 0) {
		float moving = data.fund * data.value[data.value.size() - 1];

		data.wallet = moving;
		data.fund = 0;
		#ifdef CONSOLE
			std::cout.width(85);
			std::cout << "selling : " << data.fund << " actions for " << moving << " pln";
		#endif // CONSOLE
	}

	inputFile.close();
	outputFile.close();

	return data;
}
