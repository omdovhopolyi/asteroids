#include "ExplosionsListConfig.h"
#include "Utils/Math.h"
#include "Utils/FilePath.h"
#include "Utils/Assert.h"
#include "Serialization/Serialization.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(ExplosionsListConfig)

    void ExplosionsListConfig::Load()
    {
        _explosionAssetsIds.clear();

        const auto fileName = shen::FilePath::Path("assets/configs/explosionsList.xml");
        auto serialization = shen::Serialization{ _systems, fileName };

        if (serialization.IsValid())
        {
            serialization.ForAllChildElements("item", [&](const shen::Serialization& element)
            {
                const auto assetId = element.GetStr("assetId");
                _explosionAssetsIds.push_back(assetId);
            });
        }
    }

    std::string ExplosionsListConfig::GetRandomExplosion() const
    {
        if (!_explosionAssetsIds.empty())
        {
            const int index = shen::RandomInt(0, static_cast<int>(_explosionAssetsIds.size() - 1));
            return _explosionAssetsIds[index];
        }

        Assert(false, "[ExplosionsListConfig::GetRandomExplosion] empty _explosionAssetsIds");
        return {};
    }
}