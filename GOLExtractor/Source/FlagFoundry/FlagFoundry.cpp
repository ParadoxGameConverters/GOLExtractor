#include "FlagFoundry.h"
#include "../CoatsOfArms/CoatOfArms.h"
#include "../CoatsOfArms/CoatsOfArms.h"
#include "Magick++.h"
#include "OSCompatibilityLayer.h"
#include "Warehouse.h"
#include <ranges>

FlagFoundry::FlagFoundry()
{
	Magick::InitializeMagick(".");
	warehouse = std::make_shared<Warehouse>();
	flagCrafter.loadWarehouse(warehouse);
}

void FlagFoundry::loadImageFolders(const std::string& gamePath) const
{
	std::set<std::string> folders;
	folders.insert(gamePath + "gfx/coat_of_arms/");
	warehouse->loadImageFolders(folders);
}

void FlagFoundry::generateFlags(const CoatsOfArms& coats) const
{
	// prep the battleground.
	if (!commonItems::DeleteFolder("export"))
		Log(LogLevel::Error) << "Could not delete export folder!";
	else if (!commonItems::TryCreateFolder("export"))
		throw std::runtime_error("Could not create export folder!");

	for (const auto& coat: coats.getCoats())
	{
		auto generatedCoa = flagCrafter.craftFlagFromCoA(*coat.second);
		try
		{
			generatedCoa.magick("TGA");
			generatedCoa.write("export/" + coat.first + ".tga");
		}
		catch (std::exception& e)
		{
			Log(LogLevel::Error) << "Failed exporting flag: " << coat.first << " " << e.what();
		}
	}
}
