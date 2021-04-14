#ifndef COATSOFARMS_H
#define COATSOFARMS_H
#include "Parser.h"

class CoatOfArms;
class CoatsOfArms: commonItems::parser
{
  public:
	CoatsOfArms() = default;
	void loadCoats(const std::string& filepath);
	[[nodiscard]] const auto& getCoats() const { return coats; }

  private:
	void registerKeys();

	std::map<std::string, std::shared_ptr<CoatOfArms>> coats;
	std::map<std::string, std::string> macros; // translates @something into 0.22 or similar.
};

#endif // COATSOFARMS_H
