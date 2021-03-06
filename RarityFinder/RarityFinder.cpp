#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <streambuf>
#include <map>
namespace fs = std::experimental::filesystem;

std::map<std::string, std::string> rarityMap {
	{ "EFortRarity::Quality", "Epic" },
	{ "EFortRarity::Sturdy", "Rare" },
	{ "EFortRarity::Fine", "Legendary" },
	{ "EFortRarity::Handmade", "Common" }
};

static bool endsWith(const std::string& str, const std::string& suffix) {
	return (str.size() >= suffix.size()) && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

int main(int argc, char** argv) {
	for (auto & p : fs::recursive_directory_iterator(".")) {
		std::ostringstream oss;
		oss << p;
		if (endsWith(oss.str(), "uasset")) {
			std::ifstream ifs(oss.str(), std::ios::binary);
			std::string contents((std::istreambuf_iterator<char>(ifs)),
								  std::istreambuf_iterator<char>());
			for (const auto &[key, value] : rarityMap) {
				if (contents.find(key) != std::string::npos) {
					std::cout << p << ": " << value << std::endl;
					break;
				}
				if (argc == 2)
					std::cout << p << ": Uncommon or Not Found" << std::endl;
			}
		}
	}
}

