#include "CoatsOfArms.h"
#include "CoatOfArms.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "CommonRegexes.h"
#include <regex>

void CoatsOfArms::loadCoats(const std::string& filePath)
{
	registerKeys();
	parseFile(filePath);
	clearRegisteredKeywords();
}

void CoatsOfArms::registerKeys()
{
	registerRegex(R"(@[A-Za-z0-9_\-\']+)", [this](const std::string& macroID, std::istream& theStream) {		
		macros.insert(std::pair(macroID, commonItems::getString(theStream)));
	});
	registerRegex(R"((e|k|d|c|b)_[A-Za-z0-9_\-\']+)", [this](const std::string& coaID, std::istream& theStream) {
		auto suspiciousItem = commonItems::stringOfItem(theStream).getString();
		if (suspiciousItem.find('{') != std::string::npos)
		{
			// Check for macros first.
			if (suspiciousItem.find('@') != std::string::npos)
			{
				for (const auto& [macroID, macroValue]: macros)
				{
					std::string result;
					std::regex_replace(std::back_inserter(result), suspiciousItem.begin(), suspiciousItem.end(), std::regex(macroID), macroValue);
					suspiciousItem = result;
				}
			}
			
			auto coaStream = std::stringstream(suspiciousItem);
			auto newCoA = std::make_shared<CoatOfArms>(coaStream, coaID);
			coats.insert(std::pair(coaID, newCoA));
		}
		else
		{
			auto coaStream = std::stringstream(suspiciousItem);
			const auto& coaString = commonItems::getString(coaStream);
			if (coats.contains(coaString))
				coats.insert(std::pair(coaID, coats.at(coaString)));
			else
				Log(LogLevel::Warning) << "Coat " << coaID << " is defined from an undefined " << coaString;
		}
		
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}
