#ifndef FLAG_CRAFTER_H
#define FLAG_CRAFTER_H
#include "Color.h"

namespace Magick
{
class Image;
} // namespace Magick

class CoatOfArms;
class Emblem;
class EmblemInstance;
class Warehouse;
class FlagCrafter
{
  public:
	void loadWarehouse(const std::shared_ptr<Warehouse>& theWarehouse) { warehouse = theWarehouse; }

	[[nodiscard]] Magick::Image craftFlagFromCoA(const CoatOfArms& coa) const;

  private:
	[[nodiscard]] std::pair<Magick::Image, Magick::Image> processEmblemsOnImage(const std::pair<Magick::Image, Magick::Image>& imagePair,
		 const std::vector<std::pair<Emblem, Magick::Image>>& emblems) const;
	[[nodiscard]] std::pair<Magick::Image, Magick::Image> processSubsOnImage(const std::pair<Magick::Image, Magick::Image>& imagePair,
		 const std::vector<std::pair<CoatOfArms, Magick::Image>>& subs) const;
	[[nodiscard]] std::pair<Magick::Image, Magick::Image> imposeEmblemInstancesOnImage(const std::pair<Magick::Image, Magick::Image>& imagePair,
		 const std::vector<EmblemInstance>& instances,
		 const Magick::Image& emblem,
		 const std::vector<int>& masks) const;

	std::shared_ptr<Warehouse> warehouse;
};

#endif // FLAG_CRAFTER_H