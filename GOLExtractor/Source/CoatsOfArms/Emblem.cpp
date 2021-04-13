#include "Emblem.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "CommonRegexes.h"

Emblem::Emblem(std::istream& theStream, const std::optional<commonItems::Color>& color1, const std::optional<commonItems::Color>& color2, const std::optional<commonItems::Color>& color3): parentColor1(color1), parentColor2(color2), parentColor3(color3)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void Emblem::registerKeys()
{
	registerRegex(R"(@[A-Za-z0-9_\-\']+)", [this](const std::string& macroID, std::istream& theStream) {
		macros.insert(std::pair(macroID, commonItems::getString(theStream)));
		});
	registerKeyword("texture", [this](const std::string& unused, std::istream& theStream) {
		texture = commonItems::singleString(theStream).getString();
	});
	registerKeyword("color1", [this](const std::string& unused, std::istream& theStream) {
		const auto& suspiciousItem = commonItems::stringOfItem(theStream).getString();
		if (suspiciousItem.find("color1") != std::string::npos)
		{
			color1 = parentColor1;
			return;
		}
		if (suspiciousItem.find("color2") != std::string::npos)
		{
			color1 = parentColor2;
			return;
		}
		if (suspiciousItem.find("color3") != std::string::npos)
		{
			color1 = parentColor3;
			return;
		}
		auto colorStream = std::stringstream(suspiciousItem);
		try
		{
			color1 = laFabricaDeColor.getColor(colorStream);
		}
		catch (std::exception& e)
		{			
			Log(LogLevel::Warning) << e.what() << " - sidestepping with black.";
			color1 = commonItems::Color(std::array<int, 3>{0, 0, 0});
		}
	});
	registerKeyword("color2", [this](const std::string& unused, std::istream& theStream) {
		const auto& suspiciousItem = commonItems::stringOfItem(theStream).getString();
		if (suspiciousItem.find("color1") != std::string::npos)
		{
			color2 = parentColor1;
			return;
		}
		if (suspiciousItem.find("color2") != std::string::npos)
		{
			color2 = parentColor2;
			return;
		}
		if (suspiciousItem.find("color3") != std::string::npos)
		{
			color2 = parentColor3;
			return;
		}
		auto colorStream = std::stringstream(suspiciousItem);
		try
		{
			color2 = laFabricaDeColor.getColor(colorStream);
		}
		catch (std::exception& e)
		{
			Log(LogLevel::Warning) << e.what() << " - sidestepping with black.";
			color2 = commonItems::Color(std::array<int, 3>{0, 0, 0});
		}
	});
	registerKeyword("color3", [this](const std::string& unused, std::istream& theStream) {
		const auto& suspiciousItem = commonItems::stringOfItem(theStream).getString();
		if (suspiciousItem.find("color1") != std::string::npos)
		{
			color3 = parentColor1;
			return;
		}
		if (suspiciousItem.find("color2") != std::string::npos)
		{
			color3 = parentColor2;
			return;
		}
		if (suspiciousItem.find("color3") != std::string::npos)
		{
			color3 = parentColor3;
			return;
		}
		auto colorStream = std::stringstream(suspiciousItem);
		try
		{
			color3 = laFabricaDeColor.getColor(colorStream);
		}
		catch (std::exception& e)
		{
			Log(LogLevel::Warning) << e.what() << " - sidestepping with black.";
			color3 = commonItems::Color(std::array<int, 3>{0, 0, 0});
		}
	});
	registerKeyword("mask", [this](const std::string& unused, std::istream& theStream) {
		mask = commonItems::intList(theStream).getInts();
	});
	registerKeyword("instance", [this](const std::string& unused, std::istream& theStream) {
		auto suspiciousItem = commonItems::stringOfItem(theStream).getString();
		// Check for macros first.
		if (suspiciousItem.find('@') != std::string::npos)
		{
			for (const auto& [macroID, macroValue] : macros)
			{
				std::string result;
				std::regex_replace(std::back_inserter(result), suspiciousItem.begin(), suspiciousItem.end(), std::regex(macroID), macroValue);
				suspiciousItem = result;
			}
		}
		auto coaStream = std::stringstream(suspiciousItem);

		auto instance = EmblemInstance(coaStream);
		if (instance.getPosition().empty())
			instance.defaultPosition();
		instances.emplace_back(instance);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}
