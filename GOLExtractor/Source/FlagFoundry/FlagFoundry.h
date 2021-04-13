#ifndef FLAG_FOUNDRY_H
#define FLAG_FOUNDRY_H
#include "Color.h"
#include "FlagCrafter.h"
#include <memory>
#include <string>

namespace Magick
{
class Image;
} // namespace Magick

class CoatOfArms;
class CoatsOfArms;
class Warehouse;
class FlagFoundry
{
  public:
	FlagFoundry();
	void generateFlags(const CoatsOfArms& coats) const;
	void loadImageFolders(const std::string& gamePath) const;

  private:
	FlagCrafter flagCrafter;				  // image processor
	std::shared_ptr<Warehouse> warehouse; // background image storage, loading and preparation
};

#endif // FLAG_FOUNDRY_H