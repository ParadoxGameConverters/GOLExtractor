#include "NamedColors.h"
#include "ParserHelpers.h"
#include "CommonRegexes.h"
#include "Log.h"

void NamedColors::loadColors(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void NamedColors::loadColors(const std::string& filepath)
{
	registerKeys();
	parseFile(filepath);
	clearRegisteredKeywords();
}

void NamedColors::registerKeys()
{
	// If we get a color named "colors", we're f--d.
	registerKeyword("colors", [](const std::string& unused, std::istream& theStream) {
		auto loadedColors = NamedColors();
		loadedColors.loadColors(theStream);
	});
	registerRegex(commonItems::catchallRegex, [](const std::string& colorName, std::istream& theStream) {
		laFabricaDeColor.addNamedColor(colorName, theStream);
	});
}