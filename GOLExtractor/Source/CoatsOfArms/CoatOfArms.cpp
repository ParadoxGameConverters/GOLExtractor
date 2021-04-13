#include "CoatOfArms.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "ParserHelpers.h"

CoatOfArms::CoatOfArms(std::istream& theStream, const std::string& coaID): ID(coaID)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void CoatOfArms::registerKeys()
{
	registerRegex(R"(@[A-Za-z0-9_\-\']+)", [this](const std::string& macroID, std::istream& theStream) {
		macros.emplace(macroID, commonItems::getString(theStream));
	});
	registerKeyword("pattern", [this](std::istream& theStream) {
		pattern = commonItems::singleString(theStream).getString();
	});
	registerKeyword("color1", [this](std::istream& theStream) {
		try
		{
			color1 = laFabricaDeColor.getColor(theStream);
		}
		catch (std::exception& e)
		{
			Log(LogLevel::Warning) << e.what() << " - sidestepping with black.";
			color1 = commonItems::Color(std::array<int, 3>{0, 0, 0});
		}
	});
	registerKeyword("color2", [this](std::istream& theStream) {
		try
		{
			color2 = laFabricaDeColor.getColor(theStream);
		}
		catch (std::exception& e)
		{
			Log(LogLevel::Warning) << e.what() << " - sidestepping with black.";
			color2 = commonItems::Color(std::array<int, 3>{0, 0, 0});
		}
	});
	registerKeyword("color3", [this](std::istream& theStream) {
		try
		{
			color3 = laFabricaDeColor.getColor(theStream);
		}
		catch (std::exception& e)
		{
			Log(LogLevel::Warning) << e.what() << " - sidestepping with black.";
			color3 = commonItems::Color(std::array<int, 3>{0, 0, 0});
		}
	});
	registerKeyword("textured_emblem", [this](std::istream& theStream) {
		texturedEmblems.emplace_back(Emblem(theStream, color1, color2, color3));
	});
	registerKeyword("colored_emblem", [this](std::istream& theStream) {
		auto suspiciousItem = commonItems::stringOfItem(theStream).getString();
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
		coloredEmblems.emplace_back(Emblem(coaStream, color1, color2, color3));
	});
	registerKeyword("sub", [this](std::istream& theStream) {
		subs.emplace_back(std::make_shared<CoatOfArms>(theStream, ""));
	});
	registerKeyword("instance", [this](std::istream& theStream) {
		auto instance = EmblemInstance(theStream);
		if (instance.getOffset().empty())
			instance.defaultOffset();
		instances.emplace_back(instance);
	});
	registerKeyword("parent", [this](std::istream& theStream) {
		parent = std::make_pair(commonItems::singleString(theStream).getString(), nullptr);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}
