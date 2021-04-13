#include "GOLExtractor.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"

void GOLExtractor::parseGarments(const std::string& gamePath)
{
	primeLaFabricaDeColor(gamePath);
	loadCoats(gamePath);
}

void GOLExtractor::primeLaFabricaDeColor(const std::string& gamePath)
{
	Log(LogLevel::Info) << "-> Loading colors: " << gamePath + "common/named_colors";
	for (const auto& file : commonItems::GetAllFilesInFolder(gamePath + "common/named_colors"))
	{
		if (file.find(".txt") == std::string::npos)
			continue;
		namedColors.loadColors(gamePath + "common/named_colors/" + file);
	}
	Log(LogLevel::Info) << "<> Loaded " << laFabricaDeColor.getRegisteredColors().size() << " colors.";
}

void GOLExtractor::loadCoats(const std::string& gamePath)
{
	Log(LogLevel::Info) << "-> Loading garments: " << gamePath + "common/coat_of_arms/coat_of_arms/01_landed_titles.txt";
	coats.loadCoats(gamePath + "common/coat_of_arms/coat_of_arms/01_landed_titles.txt");
	Log(LogLevel::Info) << "<> Loaded " << coats.getCoats().size() << " garments of limbs.";
}
